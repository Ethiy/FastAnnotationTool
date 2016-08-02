#include "tools/tools.h"
#include "annotations/annotations.h"

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <iostream>

#include <opencv2/core/core.hpp>

int main(int argc, const char *argv[])
{
    std::string images_folder, annotations_folder;
    argument_parser(argc, argv, images_folder, annotations_folder);
    std::vector<sys::path> images = get_images(images_folder);
    
    return EXIT_SUCCESS;
}
