#include "tools/tools.h"

#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(int argc, const char *argv[])
{
    std::string images_folder, annotations_folder;
    int EXIT_CODE(EXIT_SUCCESS);
    EXIT_CODE = argument_parser(argc, argv, images_folder, annotations_folder);
    if(EXIT_CODE)
        std::exit(EXIT_CODE);
    
    std::vector<sys::path> images = get_images(images_folder);
    std::vector<std::string> s;

    return EXIT_SUCCESS;
}
