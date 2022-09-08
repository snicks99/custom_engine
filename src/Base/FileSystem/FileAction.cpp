#include "FileSystem/FileAction.h"
#include "FileSystem/File.h"
#include "FileSystem/Pak/PAKFile.h"

bool8 FileAction::RunAction()
{
    bool8 ret{ false };

    if ( mFlags & IO_OPEN_READ )
    {
        ret = PAKFile::ReadToBuffer( mPAK, mFilePath.c_str(), mStream );
    }
    else if ( mFlags & IO_OPEN_WRITE )
    {
        ret = File::WriteFromBuffer( mFilePath.c_str(), Disposition::CREATE, mStream );
    }

    mDone = ret;

    return ret;
}
