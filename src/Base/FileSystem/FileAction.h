#ifndef FILE_ACTION_H
#define FILE_ACTION_H

#include "Common/Defines.h"
#include "Containers/BasicString.h"
#include "Stream/ByteStream.h"
#include "Event/Action.h"

class FileAction : public Action
{
  public:
    FileAction()
        : Action{}
        , mPAK{ 0 }
        , mFilePath{}
        , mFlags{ 0 }
        , mStream{}
    {
        mFilePath.reserve( MAX_DIR_PATH );

        mStream.resize( 64 * MEMORY_KIBIBYTE );
    }

    virtual ~FileAction() = default;

    bool8 RunAction() override;

  public:
    uint32     mPAK;
    String     mFilePath;
    uint32     mFlags;
    ByteStream mStream;
};

#endif
