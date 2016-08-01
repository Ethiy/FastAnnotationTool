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
    
    std::vector< std::vector< std::pair< std::string, std::map<std::string, int>>> > image_annotations;
    std::transform( images.begin(), images.end(), image_annotations.begin(),[] (sys::path path)
                                                                            {
                                                                                Image current_image;
                                                                                return get_annotations( current_image.get_image());
                                                                            }
                                                                            );

    return EXIT_SUCCESS;
}
