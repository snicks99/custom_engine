#ifndef DBL_PAK_DEFINE_H
#define DBL_PAK_DEFINE_H

#include "Common/Defines.h"
#include "FileSystem/Pack/RscPakDefines.h"
#include "Utilities/Utils.h"
#include "Debug/DBLAssert.h"

enum EDBLPakType : uint32
{
    DBL_PAK_TYPE_ANIMATION = 0,
    DBL_PAK_TYPE_EFFECT,
    DBL_PAK_TYPE_FLASH,
    DBL_PAK_TYPE_GUI,
    DBL_PAK_TYPE_LANGUAGE,
    DBL_PAK_TYPE_MODEL,
    DBL_PAK_TYPE_PROPERTY,
    DBL_PAK_TYPE_SCRIPT,
    DBL_PAK_TYPE_SOUND,
    DBL_PAK_TYPE_TABLE,
    DBL_PAK_TYPE_TEXTURE,
    DBL_PAK_TYPE_WORLD,

    MAX_DBL_PAK_TYPE,

    INVALID_DBL_PAK_TYPE = 0xFFFFFFFF
};

// clang-format off
CONSTEXPR_INLINE const char8* DBL_PAK_PROP[MAX_DBL_PAK_TYPE][2]
{
    {
        "animation/",
        "anm"
    },
    {
        "effect/",
        "eff"
    },
    {
        "flash/",
        "fls"
    },
    {
        "gui/",
        "gui"
    },
    {
        "language/",
        "lng"
    },
    {
        "model/",
        "mdl"
    },
    {
        "property/",
        "prp"
    },
    {
        "script/",
        "scr"
    },
    {
        "sound/",
        "snd"
    },
    {
        "table/",
        "tbl"
    },
    {
        "texture/",
        "tex"
    },
    {
        "world/",
        "wld"
    }
};
// clang-format on

inline bool8 ExistsDBLFile( uint32 pak, const char8* filePath, void* data = nullptr )
{
    bool8 ret{ false };

    switch ( pak )
    {
        case DBL_PAK_TYPE_TEXTURE:
        {
            String             texFile{};
            Vector<StringView> paths{};

            texFile.reserve( MAX_DIR_PATH );

            Util::TokenizeView( paths, data ? static_cast<const char8*>( data ) : EMPTY_STRING.c_str(), ";" );
            for ( auto it{ paths.begin() }; it != paths.end(); ++it )
            {
                StringView curPath{ *it };

                texFile = curPath;
                texFile += filePath;

                ret = ExistsFile( pak, texFile.c_str() );
                if ( ret )
                    break;
            }
        }
        break;
        default:
            ret = ExistsFile( pak, filePath );
            break;
    }

    return ret;
}

inline bool8 ObtainDBLFileInfo( FileInfo& info, uint32 pak, const char8* filePath, void* data = nullptr )
{
    bool8 ret{ false };

    switch ( pak )
    {
        case DBL_PAK_TYPE_TEXTURE:
        {
            String             texFile{};
            Vector<StringView> paths{};

            texFile.reserve( MAX_DIR_PATH );

            Util::TokenizeView( paths, data ? static_cast<const char8*>( data ) : EMPTY_STRING.c_str(), ";" );
            for ( auto it{ paths.begin() }; it != paths.end(); ++it )
            {
                StringView curPath{ *it };

                texFile = curPath;
                texFile += filePath;

                ret = ObtainFileInfo( info, pak, texFile.c_str() );
                if ( ret )
                    break;
            }
        }
        break;
        default:
            ret = ObtainFileInfo( info, pak, filePath );
            break;
    }

    DBL_ERROR( ret, "File not found %s pak %u", filePath, pak );

    return ret;
}

#endif
