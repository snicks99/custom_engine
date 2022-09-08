#ifndef RESOURCE_PACK_MANAGER_H
#define RESOURCE_PACK_MANAGER_H

#include "Common/Defines.h"
#include "Containers/ScopedPtr.h"
#include "Containers/UnorderedMap.h"
#include "FileSystem/Pack/ResourcePack.h"

#include <fstream>
#include <sstream>

struct PackElement;

class RscPakMgr
{
  public:
    virtual ~RscPakMgr() = default;

    static void LoadSstream( uint32 pak, StringView filePath, std::stringstream& fstream );

    void LoadLocalizedHeader( StringView localize );
    void SaveLocalizedHeader( uint32 pakType, StringView localize, uint32 enc );

    void SetFlags( uint32 flags ) noexcept { mFlags = flags; }

    const ResourcePack* GetRscPak( uint32 pakType ) const;
    const PackElement*  GetPackElement( uint32 pakType, StringView fileName ) const;

  protected:
    RscPakMgr();

    void CreatePack( uint32 pakType, StringView folder, StringView pak );

    void LoadHeader( StringView path );
    void SaveHeader( StringView path, uint32 enc );

    UnorderedMap<uint32, ScopedPtr<ResourcePack>> mPAKs;
    uint32                                        mFlags;
};

extern RscPakMgr& GetRscPakMgr();

#endif
