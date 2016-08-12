#ifndef TOOLS_H
#define TOOLS_H

#include "../annotation/Annotations.h"

#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include <vector>

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

void argument_parser(int, char const** , std::string &, std::string &, int &);

std::vector<sys::path> get_images(std::string);

void save_annotations(std::string, sys::path, Annotations);

#endif
