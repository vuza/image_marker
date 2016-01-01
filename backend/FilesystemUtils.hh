/*
 * FilesystemUtils.hh
 *
 *  Created on: Mar 15, 2013
 *      Author: aitor
 */

#ifndef JVIS_FILESYSTEM_UTILS_HH
#define JVIS_FILESYSTEM_UTILS_HH

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <fstream>

namespace bf = boost::filesystem;

namespace jvis
{

  class utils
  {

    public:

    /** Returns a the name of files in a folder </br>
    * '(.*)bmp'
    * @param dir
    * @param relative_paths
    * @param rel_path_so_far
    * @param regex_pattern examples "(.*)bmp",  "(.*)$"
    * @param recursive (true if files in subfolders should be returned as well)
    * @return number of files in folder (-1 in case directory name is not valid)
    */
    static int
    getFilesInDirectory (   const std::string & dir,
                            std::vector<std::string> & relative_paths,
                            const std::string & rel_path_so_far = std::string(""),
                            const std::string & regex_pattern = std::string(""),
                            bool recursive = true);
  };
}
#endif /* FILESYSTEM_UTILS_H_ */
