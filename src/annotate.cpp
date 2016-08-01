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
    int EXIT_CODE(EXIT_SUCCESS);
    EXIT_CODE = argument_parser(argc, argv, images_folder, annotations_folder);
    if(EXIT_CODE)
        std::exit(EXIT_CODE);
    
    std::vector<sys::path> images = get_images(images_folder);
    /*std::string s;
    s = std::accumulate( images.begin(), images.end(), std::string{}, 
                                                                [](const std::string& a, sys::path b) {
                                                                    return a.empty() ? b.string()
                                                                        : a + '\n' + b.string();}
                                                                );
    std::cout << std::endl << s << std::endl;*/

    return EXIT_SUCCESS;
}
