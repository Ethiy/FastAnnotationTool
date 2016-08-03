#include "tools/tools.h"
#include "annotation/Annotation.h"
#include "image/Image.h"

#include <algorithm>
#include <numeric>
#include <iostream>

int main(int argc, const char *argv[])
{
    std::string images_folder, annotations_folder;
    argument_parser(argc, argv, images_folder, annotations_folder);
    std::vector<sys::path> images = get_images(images_folder);
    std::vector<std::vector<Annotation>> annotations;
    for(std::vector<sys::path>::iterator iterator = images.begin(); iterator != images.end(); iterator++)
    {
        Image current_image(*iterator);
        current_image.redimension();
        current_image.save_to(*iterator);
        annotations.push_back(current_image.annotate());
    }    
    return EXIT_SUCCESS;
}
