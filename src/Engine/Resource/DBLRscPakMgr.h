#ifndef DBL_RESOURCE_PACK_MANAGER_H
#define DBL_RESOURCE_PACK_MANAGER_H

#include "Containers/BasicString.h"
#include "FileSystem/Pack/RscPakMgr.h"
#include "FileSystem/Pack/ResourcePack.h"

class DBLRscPakMgr : public RscPakMgr
{
  public:
    virtual ~DBLRscPakMgr() = default;

    static DBLRscPakMgr& Instance()
    {
        static DBLRscPakMgr sDBLRscPakMgr{};
        return sDBLRscPakMgr;
    }

  protected:
    DBLRscPakMgr();
};

#endif
