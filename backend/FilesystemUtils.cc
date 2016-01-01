
#include "FilesystemUtils.hh"
#include <iostream>

namespace jvis
{

int utils::getFilesInDirectory (const std::string &dir,
                                 std::vector<std::string> & relative_paths,
                                 const std::string & rel_path_so_far,
                                 const std::string & regex_pattern,
                                 bool recursive)
{
    bf::path dir_bf = dir;
    if ( !bf::is_directory ( dir_bf ) ) {
        std::cerr << dir << " is not a directory!" << std::endl;
        return -1;
    }
    const boost::regex file_filter( regex_pattern );

    bf::directory_iterator end_itr;
    for (bf::directory_iterator itr (dir_bf); itr != end_itr; ++itr)
    {
        //check if its a directory, then get files in it
        if (bf::is_directory (*itr))
        {
#if BOOST_FILESYSTEM_VERSION == 3
#ifdef _WIN32
            std::string so_far = rel_path_so_far + (itr->path ().filename ()).string () + "\\";
#else
            std::string so_far = rel_path_so_far + (itr->path ().filename ()).string () + "/";
#endif

#else
#ifdef _WIN32
            std::string so_far = rel_path_so_far + (itr->path ().filename ()) + "\\";
#else
            std::string so_far = rel_path_so_far + (itr->path ().filename ()) + "/";
#endif
#endif

            if (recursive)
            {
                if( getFilesInDirectory (itr->path().string(), relative_paths, so_far, regex_pattern, recursive) == -1)
                    return -1;
            }
        }
        else
        {
            //check for correct file pattern (extension,..) and then add, otherwise ignore..

#if BOOST_FILESYSTEM_VERSION == 3
            std::string file = (itr->path ().filename ()).string ();
            std::string path = rel_path_so_far + (itr->path ().filename ()).string ();
#else
            std::string file = (itr->path ()).filename ();
            std::string path = rel_path_so_far + (itr->path ()).filename ();
#endif
            boost::smatch what;
            if( boost::regex_match( file, what, file_filter ) )
                relative_paths.push_back (path);
        }
    }
    return relative_paths.size();
}

}


