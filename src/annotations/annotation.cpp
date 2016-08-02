#include "annotation.h"


Annotation::Annotation()
{
    set = false;
    object_class = "";
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    height = y2 - y1;
    width = x2 - x1;
}

Annotation::Annotation(std::string object_class, cv::Point first_corner, cv::Point second_corner)
{
    set = true;
    object_class = object_class;
    x1 = std::min(first_corner.x, second_corner.x);
    y1 = std::min(first_corner.y, second_corner.y);
    x2 = std::max(first_corner.x, second_corner.x);
    y2 = std::max(first_corner.y, second_corner.y);
    height = y2 - y1;
    width = x2 - x1;
}

Annotation::~Annotation()
{
}

int Annotation::get_width()
{
    assert(is_set());
    return width;
}

int Annotation::get_height()
{
    assert(is_set());
    return height;
}
