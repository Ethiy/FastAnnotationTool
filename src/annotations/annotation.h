#ifndef Annotation_H
#define Annotation_H

#include <string>
#include <algorithm>

#include <opencv2/core/core.hpp>

class Annotation
{
public:
    Annotation();
    Annotation(std::string, cv::Point, cv::Point);
    ~Annotation();

    bool is_set();
    std::string get_object_class();
    cv::Point get_first_corner();
    cv::Point get_second_corner();
    int get_width();
    int get_height();

private:
    bool set;
    std::string object_class;
    int x1;
    int y1;
    int x2;
    int y2;
    int height;
    int width;
};

inline bool Annotation::is_set()
{
    return set;
}

inline cv::Point Annotation::get_first_corner()
{
    assert(is_set());
    return cv::Point(x1, y1);
}

inline cv::Point Annotation::get_second_corner()
{
    assert(is_set());
    return cv::Point(x2, y2);
}

inline std::string Annotation::get_object_class()
{
    assert(is_set());
    return object_class;
}

#endif //  Annotation_H