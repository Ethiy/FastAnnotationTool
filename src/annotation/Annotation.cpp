#include "Annotation.h"


Annotation::Annotation(void): set(true), object_class(""), x1(0), y1(0), x2(0), y2(0)
{
    height = y2 - y1;
    width = x2 - x1;
}

Annotation::~Annotation(void){}

Annotation::Annotation(std::string object_class, cv::Point first_corner, cv::Point second_corner): set(true), object_class(object_class)
{
    x1 = std::min(first_corner.x, second_corner.x);
    y1 = std::min(first_corner.y, second_corner.y);
    x2 = std::max(first_corner.x, second_corner.x);
    y2 = std::max(first_corner.y, second_corner.y);
    height = y2 - y1;
    width = x2 - x1;
}

int Annotation::get_width(void)
{
    assert(is_set());
    return width;
}

int Annotation::get_height(void)
{
    assert(is_set());
    return height;
}

std::ostream& operator<<(std::ostream &strm, const Annotation &a) 
{
  return strm << a.object_class << " " << a.x1 << " " << a.x2 << " " << a.y1 << " " << a.y2;
}
