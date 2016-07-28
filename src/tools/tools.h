#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <iostream>
#include <exception>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
namespace 
{ 
  const size_t ERROR_IN_COMMAND_LINE = 2; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 3; 
  const size_t ERROR_IN_PATH = 4;
 
}

namespace arg_parser = boost::program_options;
namespace sys = boost::filesystem;

void check_path(const sys::path images_path);

/**default_annotations_folder(std::string images_folder):
*       specifies: - annotations_folder, annotations' default folder path from images_folder.
**/
std::string default_annotations_folder(std::string images_folder);
/**argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder):
*       specifies: - images_folder, images' folder path.
*                  - annotations_folder, annotations' folder path.
**/ 
int argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder);

#endif
