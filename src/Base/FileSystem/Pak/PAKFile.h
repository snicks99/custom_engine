#ifndef PAK_FILE_H
#define PAK_FILE_H

#include "FileSystem/File.h"

class PAKFile : public File
{
  public:
    template<typename T>
    static bool8 ReadToBuffer( uint32 pak, const char8* filePath, T& buffer )
    {
        PAKFile file{};

        if ( file.Open( pak, filePath ) == false )
            return false;

        const word_t size{ file.Size() };

        if ( size == 0 )
            return true;

        buffer.resize( size );

        return file.Read( buffer.data(), buffer.size() );
    }

  public:
    PAKFile();
    virtual ~PAKFile() = default;

    bool8 Open( uint32 pak, const char8* filePath );

    constexpr word_t Size() const override { return mEnd - mBeg; }

    bool8  Seek( uint32 method, int64 offset = 0 ) override;
    word_t Tell() const override;

  protected:
    word_t mBeg;
    word_t mEnd;
};

#endif
