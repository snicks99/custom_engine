#include "Stream/ByteStream.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "FileSystem/Pack/ResourcePack.h"
#include "FileSystem/Pack/RscPakDefines.h"
#include "FileSystem/Pak/PAKFile.h"

RscPakMgr::RscPakMgr()
    : mPAKs{}
    , mFlags{ 0 }
{
}

void RscPakMgr::CreatePack( uint32 pakType, StringView folder, StringView pak )
{
    ResourcePack* rscPak{ new ResourcePack{ folder, pak } };

    mPAKs.emplace( pakType, rscPak );
}

void RscPakMgr::LoadSstream( uint32 pak, StringView filePath, std::stringstream& sstream )
{
    ByteStream buffer{};

    if ( PAKFile::ReadToBuffer( pak, filePath.data(), buffer ) == false )
        return;

    sstream << static_cast<char*>( buffer.data() );
}

void RscPakMgr::LoadLocalizedHeader( StringView localize )
{
    LoadHeader( PACK_FOLDER );

    if ( localize.empty() )
        return;

    String path{};

    path.reserve( MAX_DIR_PATH );

    path = LOCALIZE_FOLDER;
    path += localize;
    path += PACK_FOLDER;

    LoadHeader( path );
}

void RscPakMgr::SaveLocalizedHeader( uint32 pakType, StringView localize, uint32 enc )
{
    ResourcePack* rscPak{ mPAKs[pakType] };

    rscPak->SaveHeader( "", enc );

    if ( localize.empty() )
        return;

    String path{};

    path.reserve( MAX_DIR_PATH );

    path = LOCALIZE_FOLDER;
    path += localize;

    rscPak->SaveHeader( path, enc );
}

const ResourcePack* RscPakMgr::GetRscPak( uint32 pakType ) const
{
    auto it{ mPAKs.find( pakType ) };
    if ( it == mPAKs.end() )
        return nullptr;

    ResourcePack* rscPak{ it->second };

    return rscPak;
}

const PackElement* RscPakMgr::GetPackElement( uint32 pakType, StringView fileName ) const
{
    auto it{ mPAKs.find( pakType ) };
    if ( it == mPAKs.end() )
        return nullptr;

    ResourcePack* rscPak{ it->second };

    return rscPak->GetPackElement( fileName );
}

void RscPakMgr::LoadHeader( StringView path )
{
    for ( auto it{ mPAKs.begin() }; it != mPAKs.end(); ++it )
    {
        ResourcePack* rscPak{ it->second };

        rscPak->LoadHeader( path );
    }
}

void RscPakMgr::SaveHeader( StringView path, uint32 enc )
{
    for ( auto it{ mPAKs.begin() }; it != mPAKs.end(); ++it )
    {
        ResourcePack* rscPak{ it->second };

        rscPak->SaveHeader( path, enc );
    }
}
