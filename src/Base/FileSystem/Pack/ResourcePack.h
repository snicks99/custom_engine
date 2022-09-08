#ifndef RESOURCE_PACK_H
#define RESOURCE_PACK_H

#include "Common/Defines.h"
#include "Containers/UnorderedMap.h"
#include "Containers/BasicString.h"
#include "Hash/String/StringID.h"
#include "FileSystem/File.h"

#include <boost/filesystem.hpp>

class Stream;
class ICryptography;

struct PackElement
{
  public:
    PackElement()
        : mPath{}
        , mUnit{}
        , mFilePath{}
        , mSize{}
        , mOffset{}
    {
    }

    void Serialize( Stream& s ) const;
    void Deserialize( Stream& s );

    String mPath;

    uint8 mUnit;

    boost::filesystem::path mFilePath;

    uint32 mSize;
    uint32 mOffset;
};

using PackElemUMap = UnorderedMap<StringID, PackElement>;

class ResourcePack
{
  public:
    ResourcePack( StringView folder, StringView pak );
    virtual ~ResourcePack() = default;

    StringView GetPak() const { return mPak; }

    void LoadHeader( StringView path );
    void SaveHeader( StringView path, uint32 enc );
    void SaveBody( StringView path, FileList& files );

    const PackElement* GetPackElement( StringView fileName ) const;

    void GetFileList( StringView folder, FileList& fileList, bool8 recursive = false ) const;

  protected:
    String mFolder;
    String mPak;

    uint8 mPakEnc;

    PackElemUMap mElements;
};

#endif
