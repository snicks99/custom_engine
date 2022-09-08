#include "Resource/DBLRscPakMgr.h"
#include "Resource/DBLPakDefines.h"

RscPakMgr& GetRscPakMgr()
{
    return DBLRscPakMgr::Instance();
}

DBLRscPakMgr::DBLRscPakMgr()
    : RscPakMgr{}
{
#define CREATE_PACK( pack ) CreatePack( pack, DBL_PAK_PROP[pack][0], DBL_PAK_PROP[pack][1] )

    CREATE_PACK( DBL_PAK_TYPE_ANIMATION );
    CREATE_PACK( DBL_PAK_TYPE_MODEL );
    CREATE_PACK( DBL_PAK_TYPE_PROPERTY );
    CREATE_PACK( DBL_PAK_TYPE_TEXTURE );
    CREATE_PACK( DBL_PAK_TYPE_WORLD );

#undef CREATE_PACK
}
