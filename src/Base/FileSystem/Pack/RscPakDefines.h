#ifndef RESOURCE_PACK_DEFINES_H
#define RESOURCE_PACK_DEFINES_H

#include "Common/Platform.h"
#include "FileSystem/FileIO.h"
#include "FileSystem/FileInfo.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "FileSystem/Pack/RscPakDefines.h"

enum EPakEncryption : uint8
{
    PAK_ENC_NONE = 0,
    PAK_ENC_XOR,
    PAK_ENC_SALT
};

CONSTEXPR_INLINE const char8* LOCALIZE_FOLDER{ "localize/" };

CONSTEXPR_INLINE const char8* PACK_FOLDER{ "pack/" };
CONSTEXPR_INLINE const char8* PAK_FILE_EXT{ ".pak" };

CONSTEXPR_INLINE word_t MAX_PAK_BODY_SIZE{ 100 * MEMORY_MEBIBYTE };
CONSTEXPR_INLINE word_t MAX_PAK_FILE_SIZE{ 10 * MEMORY_MEBIBYTE };

inline bool8 ExistsFile( uint32 pak, const char8* filePath )
{
    const ResourcePack* rscPak{ GetRscPakMgr().GetRscPak( pak ) };

    if ( rscPak )
    {
        const PackElement* elem{ rscPak->GetPackElement( filePath ) };

        if ( elem == nullptr )
            return false;
    }
    else
    {
        if ( FileIO::Exists( filePath ) == false )
            return false;
    }

    return true;
}

inline bool8 ObtainFileInfo( FileInfo& info, uint32 pak, const char8* filePath )
{
    const ResourcePack* rscPak{ GetRscPakMgr().GetRscPak( pak ) };

    if ( rscPak )
    {
        const PackElement* elem{ rscPak->GetPackElement( filePath ) };

        if ( elem == nullptr )
            return false;

        info.mFilePath = elem->mPath;
        info.mFilePath += rscPak->GetPak();
        info.mFilePath += std::to_string( elem->mUnit );
        info.mFilePath += PAK_FILE_EXT;

        info.mSize = elem->mSize;
        info.mPtr  = elem->mOffset;
    }
    else
    {
        if ( FileIO::Exists( filePath ) == false )
            return false;

        info.mFilePath = filePath;

        info.mSize = 0;
        info.mPtr  = 0;
    }

    return true;
}

#endif
