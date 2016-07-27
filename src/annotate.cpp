#include "tools/tools.h"

#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(int argc, const char *argv[])
{
    std::string images_folder, annotations_folder;
    int success(0);
    success = argument_parser(argc, argv, images_folder, annotations_folder);

    return success;
}