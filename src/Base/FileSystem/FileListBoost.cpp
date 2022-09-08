#include "FileSystem/File.h"
#include "Debug/DBLAssert.h"

#include <boost/filesystem.hpp>

void GetFileListBoost( StringView folder, FileList& fileList, bool8 recursive )
{
    boost::filesystem::path target{ folder.data() };

    boost::filesystem::recursive_directory_iterator it{ target }, end{};

    for ( ; it != end; ++it )
    {
        auto dir{ *it };

        if ( recursive == false )
        {
            if ( dir.path().parent_path() != target.parent_path() )
                continue;
        }

        if ( boost::filesystem::is_regular_file( dir.path() ) )
        {
            fileList.emplace_back( dir.path().string() );
        }
    }
}
