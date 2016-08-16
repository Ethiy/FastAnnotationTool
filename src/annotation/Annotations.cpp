#include "Annotations.h"


Annotations::Annotations(void):length(0), annotations() {}

Annotations::~Annotations(void){}

void Annotations::draw(cv::Mat& current_view, cv::Scalar color)
{
    if(!is_empty())
    {
        std::for_each(annotations.begin(), annotations.end(), [& current_view, color](Annotation annotation)
                                                                {
                                                                    annotation.draw(current_view, color);
                                                                }
                                                            );
    }
}

bool Annotations::append(Annotation annotation)
{
    assert(length==annotations.size());
    annotations.push_back(annotation);
    length++;
}

Annotation Annotations::pop(void)
{
    assert(length==annotations.size());
    Annotation last = annotations.back();
    annotations.pop_back();
    length--;
    return last;
}

std::ostream& operator<<(std::ostream &strm, const Annotations &rois)
{
    return std::accumulate(rois.annotations.begin(), rois.annotations.end(), std::ref(strm), 
                                                                                        [](std::ostream& os, Annotation annot)-> std::ostream&
                                                                                        { 
                                                                                            return os << annot << std::endl; 
                                                                                        }
                                                                                        );
}
