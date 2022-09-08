#ifndef FILE_STREAM_H
#define FILE_STREAM_H

#include "Containers/ScopedPtr.h"
#include "Containers/Array.h"
#include "Containers/Vector.h"
#include "Stream/Stream.h"
#include "FileSystem/File.h"

constexpr word_t FILE_STREAM_BUFFER_SIZE{ 4 * MEMORY_KIBIBYTE };

/*
    NOTE: FileStream class is expected to be linear based read/write
            and can't both at same time - niccco
 */
class FileStream : public Stream
{
  public:
    FileStream();
    virtual ~FileStream();

    bool8 Open( const char8* filePath, uint32 mode, Disposition disposition = Disposition::NONE );
    bool8 IsOpen() const;

    /** we know we can't write over PAK - niccco */
    bool8 OpenPak( uint32 pak, const char8* filePath );

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    word_t append( const void* src, word_t cnt ) override;
    word_t read( void* src, word_t cnt ) override;

    void read_skip( word_t skip ) override;

    /************************************************************************/
    /*                                                                      */
    /************************************************************************/
    void*       data() noexcept override { return mBuffer.data(); }
    const void* data() const noexcept override { return mBuffer.data(); }

    bool8 empty() const noexcept override { return mBuffer.empty(); }

    bool8 eof() const override;

  protected:
    void ReadBufferChunk();
    void WriteBufferChunk();

    ScopedPtr<File> mFile;
    Vector<uint8>   mBuffer;
};

#endif
