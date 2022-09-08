#include "Common/BaseIO.h"
#include "FileSystem/Pak/PAKFile.h"
#include "FileSystem/Pack/RscPakDefines.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "Debug/DBLAssert.h"

PAKFile::PAKFile()
    : File{}
    , mBeg{ 0 }
    , mEnd{ 0 }
{
}

bool8 PAKFile::Open( uint32 pak, const char8* filePath )
{
    const ResourcePack* const rscPak{ GetRscPakMgr().GetRscPak( pak ) };

    bool8 isPAK{ false };

    String pakFile{};

    word_t ptr{ 0 };
    word_t size{ 0 };

    pakFile.reserve( MAX_DIR_PATH );

    if ( rscPak )
    {
        const PackElement* const elem{ rscPak->GetPackElement( filePath ) };

        if ( elem == nullptr )
        {
            DBL_ERROR( false, "File not found %s", filePath );
            return false;
        }

        isPAK = true;

        pakFile = elem->mPath;
        pakFile += rscPak->GetPak();
        pakFile += std::to_string( elem->mUnit );
        pakFile += PAK_FILE_EXT;

        ptr  = elem->mOffset;
        size = elem->mSize;
    }
    else
    {
        isPAK = false;

        pakFile = filePath;

        ptr  = 0;
        size = 0;
    }

    FileHandle hFl{ FileIO::Open( pakFile.c_str(), IO_OPEN_READ, Disposition::NONE ) };

    if ( hFl == nullptr )
    {
        if ( isPAK )
        {
            DBL_ERROR( false, "Couldn't open file %s (%s)", pakFile.c_str(), filePath );
        }
        else
        {
            DBL_ERROR( false, "Couldn't open file %s", pakFile.c_str() );
        }

        return false;
    }

    Close();

    mFilePath   = pakFile;
    mFileHandle = hFl;
    mOpenMode   = IO_OPEN_READ;

    mSize = FileIO::Size( hFl );

    mBeg = ptr;
    mEnd = mBeg + ( isPAK ? size : mSize );

    FileIO::Seek( mFileHandle, IO_SEEK_BEG, mBeg );

    return IsOpen();
}

bool8 PAKFile::Seek( uint32 method, int64 offset /*= 0*/ )
{
    switch ( method )
    {
        case IO_SEEK_BEG:
        {
            const int64 beg{ static_cast<int64>( mBeg ) };
            const int64 end{ static_cast<int64>( mEnd ) };

            offset = std::clamp( beg + offset, beg, end );
        }
        break;
        case IO_SEEK_CUR:
        {
            const word_t tell{ FileIO::Tell( mFileHandle ) };

            if ( tell + offset > mEnd )
            {
                offset = mEnd - tell;
            }
            else if ( tell + offset < mBeg )
            {
                offset = tell - mBeg;
            }
        }
        break;
        case IO_SEEK_END:
        {
            const int64 beg{ static_cast<int64>( mSize - mEnd ) };
            const int64 end{ static_cast<int64>( mSize - mBeg ) };

            offset = std::clamp( beg + offset, beg, end );
        }
        break;
    }

    return FileIO::Seek( mFileHandle, method, offset );
}

word_t PAKFile::Tell() const
{
    const word_t tell{ FileIO::Tell( mFileHandle ) };

    return tell - mBeg;
}
