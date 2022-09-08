#ifndef DBL_PAK_HELPERS_H
#define DBL_PAK_HELPERS_H

#include "Common/Defines.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "Resource/DBLPakDefines.h"

inline uint32 GetDBLPak( StringView folder )
{
    const StringID pakId{ folder };

    switch ( pakId )
    {
        case MAKE_SID( "animation" ):
            return DBL_PAK_TYPE_ANIMATION;
            break;
        case MAKE_SID( "model" ):
            return DBL_PAK_TYPE_MODEL;
            break;
        case MAKE_SID( "texture" ):
            return DBL_PAK_TYPE_TEXTURE;
            break;
        case MAKE_SID( "world" ):
            return DBL_PAK_TYPE_WORLD;
            break;
        default:
            return INVALID_DBL_PAK_TYPE;
            break;
    }

    return INVALID_DBL_PAK_TYPE;
}

inline void GetDBLFileList( uint32 pak, StringView folder, FileList& fileList, bool8 recursive )
{
    const ResourcePack* rscPak{ GetRscPakMgr().GetRscPak( pak ) };

    rscPak ? rscPak->GetFileList( folder, fileList, recursive ) : GetFileListBoost( folder, fileList, recursive );
}

#endif
