#ifndef Annotations_H
#define Annotations_H

#include "Annotation.h"

#include <cassert>
#include <string>
#include <algorithm>
#include <numeric>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class Annotations
{
public:
    Annotations(void);
    ~Annotations(void);

    bool is_empty(void);
    size_t size(void);
    bool append(Annotation);
    Annotation pop(void);

    void draw(cv::Mat& , cv::Scalar);

private:
    std::vector<Annotation> annotations;
    size_t length;

    friend std::ostream& operator<<(std::ostream&, const Annotations&);
};

inline bool Annotations::is_empty(void)
{
    return annotations.empty();
}

inline size_t Annotations::size()
{
    assert(length==annotations.size());
    return length;
}

#endif //  Annotations_H
