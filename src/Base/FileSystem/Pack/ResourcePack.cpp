#include "Stream/Stream.h"
#include "Stream/FileStream.h"
#include "Stream/ByteStream.h"
#include "Utilities/Utils.h"
#include "FileSystem/File.h"
#include "FileSystem/Pack/ResourcePack.h"
#include "FileSystem/Pack/RscPakDefines.h"
#include "Cryptography/AES_256_CBC.h"
#include "Debug/DBLAssert.h"

#include <algorithm>

constexpr unsigned char PAK_KEY[32] = { 0x20, 0xd4, 0xa6, 0x1c, 0xea, 0x57, 0xa2, 0x5c, 0x10, 0x08, 0xc8, 0x77, 0x0c, 0x67, 0x47, 0x09, 0xcc, 0x90, 0x24, 0xd0, 0x92, 0x9d, 0x57, 0x1b, 0xcd, 0xc7, 0x6a, 0x87, 0xa0, 0x97, 0x0e, 0xc0 };
constexpr unsigned char PAK_IV[16]  = { 0x6b, 0xb5, 0xdc, 0x56, 0x0c, 0x7f, 0xb2, 0x1c, 0x87, 0x7a, 0x93, 0x93, 0xe2, 0xda, 0x9c, 0xae };

/** https://stackoverflow.com/questions/15541263/how-to-determine-if-a-file-is-contained-by-path-with-boost-filesystem-library-v3 */
bool8 path_contains_file( boost::filesystem::path dir, boost::filesystem::path file )
{
    // If dir ends with "/" and isn't the root directory, then the final
    // component returned by iterators will include "." and will interfere
    // with the std::equal check below, so we strip it before proceeding.
    if ( dir.filename() == "." )
        dir.remove_filename();

    // We're also not interested in the file's name.
    DBL_ASSERT( file.has_filename() );
    file.remove_filename();

    // If dir has more components than file, then file can't possibly
    // reside in dir.
    auto dir_len  = std::distance( dir.begin(), dir.end() );
    auto file_len = std::distance( file.begin(), file.end() );
    if ( dir_len > file_len )
        return false;

    // This stops checking when it reaches dir.end(), so it's OK if file
    // has more directory components afterward. They won't be checked.
    return std::equal( dir.begin(), dir.end(), file.begin() );
}

void PackElement::Serialize( Stream& s ) const
{
    s << mUnit;

    s << mFilePath.string();

    s << mSize;
    s << mOffset;
}

void PackElement::Deserialize( Stream& s )
{
    String tmp{};

    s >> mUnit;

    s >> tmp;
    mFilePath = tmp;

    s >> mSize;
    s >> mOffset;
}

ResourcePack::ResourcePack( StringView folder, StringView pak )
    : mFolder{ folder }
    , mPak{ pak }
    , mPakEnc{ PAK_ENC_NONE }
{
}

void ResourcePack::LoadHeader( StringView path )
{
    uint32 pakEnc{};

    String filePath{};

    filePath.reserve( MAX_DIR_PATH );

    filePath = path;
    filePath += mPak;
    filePath += PAK_FILE_EXT;

    ByteStream fstream{};
    ByteStream stream{};

    if ( File::ReadToBuffer( filePath.c_str(), fstream ) == false )
        return;

    fstream >> pakEnc;

    /** decrypt according to pak type - niccco */
    switch ( pakEnc )
    {
        case PAK_ENC_SALT:
        {
            AES256CBC dec{};

            dec.InitDecKey( PAK_KEY, PAK_IV );

            dec.Decrypt( static_cast<unsigned char*>( fstream.rdata() ), fstream.size() - fstream.rpos(), stream );
        }
        break;
    }

    while ( stream.eof() == false )
    {
        PackElement elem{};

        elem.mPath = path;
        elem.Deserialize( stream );

        const String filePath{ elem.mFilePath.string() };

        auto it{ mElements.find( filePath ) };
        if ( it != mElements.end() )
        {
            PackElement& tmp{ it->second };

            mElements.erase( it );
        }

        mElements.emplace( filePath, std::move( elem ) );
    }
}

void ResourcePack::SaveHeader( StringView path, uint32 enc )
{
    /** Save Body */
    String   folder{};
    FileList files{};

    folder.reserve( MAX_DIR_PATH );

    folder = path;
    folder += mFolder;

    GetFileListBoost( folder, files );
    SaveBody( path, files );

    if ( mElements.empty() )
        return;

    /** Save Header */
    String     header{};
    ByteStream fstream{};
    ByteStream stream{};

    fstream << enc;

    for ( auto it{ mElements.begin() }, end{ mElements.end() }; it != end; ++it )
    {
        const PackElement& elem{ it->second };

        elem.Serialize( stream );
    }

    switch ( enc )
    {
        case PAK_ENC_SALT:
        {
            AES256CBC enc{};

            enc.InitEncKey( PAK_KEY, PAK_IV );

            enc.Encrypt( static_cast<unsigned char*>( stream.data() ), stream.size(), fstream );
        }
        break;
    }

    header.reserve( MAX_DIR_PATH );

    header = path;
    header += PACK_FOLDER;
    header += mPak;
    header += PAK_FILE_EXT;

    File::WriteFromBuffer( header.c_str(), Disposition::CREATE, fstream );

    mElements.clear();
}

void ResourcePack::SaveBody( StringView path, FileList& files )
{
    ByteStream stream{};

    uint32 unit{ 0 };
    uint32 cursor{ 0 };

    for ( auto it{ files.begin() }, end{ files.end() }; it != end; ++it )
    {
        String filePath{ *it };

        std::replace( filePath.begin(), filePath.end(), '\\', '/' );
        std::transform( filePath.begin(), filePath.end(), filePath.begin(), ::tolower );

        ByteStream buffer{};

        if ( File::ReadToBuffer( filePath.c_str(), buffer ) == false )
            continue;

        PackElement elem{};

        elem.mUnit = unit;

        elem.mFilePath = filePath;

        elem.mSize   = buffer.size();
        elem.mOffset = stream.wpos();

        mElements.emplace( filePath, std::move( elem ) );

        stream.append( buffer.data(), buffer.size() );
        if ( stream.wpos() >= MAX_PAK_BODY_SIZE )
        {
            String pak{};

            pak.reserve( MAX_DIR_PATH );

            pak = path;
            pak += PACK_FOLDER;
            pak += mPak;
            pak += std::to_string( unit++ );
            pak += PAK_FILE_EXT;

            File::WriteFromBuffer( pak.c_str(), Disposition::CREATE, stream );
            stream.clear();
        }
    }

    if ( stream.wpos() > 0 )
    {
        String pak{};

        pak.reserve( MAX_DIR_PATH );

        pak = path;
        pak += PACK_FOLDER;
        pak += mPak;
        pak += std::to_string( unit++ );
        pak += PAK_FILE_EXT;

        File::WriteFromBuffer( pak.c_str(), Disposition::CREATE, stream );
    }
}

const PackElement* ResourcePack::GetPackElement( StringView fileName ) const
{
    auto it{ mElements.find( fileName ) };
    if ( it == mElements.end() )
        return nullptr;

    return &it->second;
}

void ResourcePack::GetFileList( StringView folder, FileList& fileList, bool8 recursive /*= false*/ ) const
{
    boost::filesystem::path target{ folder.data() };

    for ( auto it{ mElements.begin() }; it != mElements.end(); ++it )
    {
        const PackElement& element{ it->second };

        if ( path_contains_file( target, element.mFilePath ) == false )
            continue;

        if ( recursive == false )
        {
            if ( target.parent_path() != element.mFilePath.parent_path() )
                continue;
        }

        fileList.emplace_back( element.mFilePath.string() );
    }
}
