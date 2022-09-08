#ifndef FILE_H
#define FILE_H

#include "Common/BaseIO.h"
#include "Containers/BasicString.h"
#include "Containers/List.h"
#include "FileSystem/FileIO.h"

using FileList = List<String>;

class File
{
  public:
    template<typename T>
    static bool8 ReadToBuffer( const char8* filePath, T& buffer )
    {
        File file{};

        if ( file.Open( filePath, IO_OPEN_READ, Disposition::NONE ) == false )
            return false;

        const word_t fileSize{ file.Size() };

        if ( fileSize == 0 )
            return true;

        buffer.resize( fileSize );

        return file.Read( buffer.data(), buffer.size() );
    }

    template<typename T>
    static bool8 WriteFromBuffer( const char8* filePath, Disposition disposition, T& buffer )
    {
        File file{};

        file.Open( filePath, IO_OPEN_WRITE, disposition );

        if ( file.IsOpen() == false )
            return false;

        return file.Write( buffer.data(), buffer.size() );
    }

  public:
    File();
    virtual ~File();

    bool8 Open( const char8* filePath, uint32 mode, Disposition disposition );
    void  Close();

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    bool8 IsOpen() const { return mFileHandle; }

    uint32 GetOpenMode() const { return mOpenMode; }

    constexpr virtual word_t Size() const { return mSize; }

    virtual bool8  Seek( uint32 method, int64 offset = 0 );
    virtual word_t Tell() const;

    word_t Read( void* buffer, word_t length );
    word_t Write( const void* buffer, word_t length );

  protected:
    String mFilePath;

    FileHandle mFileHandle;

    uint32 mOpenMode;

    word_t mSize;
};

extern void GetFileListBoost( StringView folder, FileList& fileList, bool8 recursive = true );

#endif
