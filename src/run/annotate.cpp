#include "../tools/tools.h"
#include "../annotation/Annotation.h"
#include "../image/Image.h"

#include <algorithm>
#include <numeric>
#include <iostream>

int main(int argc, const char **argv)
{
    std::string images_folder(""), annotations_folder("");
    int min_dim(0);
    argument_parser(argc, argv, images_folder, annotations_folder, min_dim);
    std::vector<sys::path> images = get_images(images_folder);
    std::for_each(images.begin(), images.end(), [annotations_folder, min_dim]
                                                (sys::path current_png_file)
                                                {
                                                    Image current_image(current_png_file);
                                                    current_image.redimension(min_dim);
                                                    std::cout << current_image.get_width() << std::endl;
                                                    current_image.save_to(current_png_file);
                                                    Annotations current_annotations = current_image.annotate();
                                                    save_annotations(annotations_folder, current_png_file, current_annotations);
                                                }
                                                );
    return EXIT_SUCCESS;
}
