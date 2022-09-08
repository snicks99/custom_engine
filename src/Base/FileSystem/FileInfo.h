#ifndef FILE_INFO_H
#define FILE_INFO_H

#include "Common/Platform.h"
#include "Containers/BasicString.h"

class FileInfo
{
  public:
    FileInfo()
        : mFilePath{}
        , mSize{ 0 }
        , mPtr{ 0 }
    {
        mFilePath.reserve( MAX_DIR_PATH );
    }

    ~FileInfo() = default;

  public:
    String mFilePath;
    word_t mSize;
    word_t mPtr;
};

#endif
