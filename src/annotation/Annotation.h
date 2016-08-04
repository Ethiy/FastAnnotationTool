#ifndef Annotation_H
#define Annotation_H

#include <string>
#include <algorithm>
#include <cassert>
#include <iostream>

#include <opencv2/core/core.hpp>

class Annotation
{
public:
    Annotation(void);
    Annotation(std::string, cv::Point, cv::Point);
    ~Annotation(void);

    bool is_set(void);
    std::string get_object_class(void);
    cv::Point get_first_corner(void);
    cv::Point get_second_corner(void);
    int get_width(void);
    int get_height(void);

private:
    bool set;

    std::string object_class;
    
    int x1;
    int y1;
    int x2;
    int y2;
    int height;
    int width;

    friend std::ostream& operator<<(std::ostream&, const Annotation&);
};

inline bool Annotation::is_set(void)
{
    return set;
}

inline cv::Point Annotation::get_first_corner(void)
{
    assert(is_set());
    return cv::Point(x1, y1);
}

inline cv::Point Annotation::get_second_corner(void)
{
    assert(is_set());
    return cv::Point(x2, y2);
}

inline std::string Annotation::get_object_class(void)
{
    assert(is_set());
    return object_class;
}

#endif //  Annotation_H
