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
    std::transform(images.begin(), images.end(), annotations.begin(),
                                                                    [](sys::path image_path)
                                                                    {
                                                                        Image working_image(image_path);
                                                                        working_image.redimension();
                                                                        working_image.save_to(image_path);
                                                                        
                                                                        return working_image.annotate();
                                                                    }
                                                                    );
    
    return EXIT_SUCCESS;
}
