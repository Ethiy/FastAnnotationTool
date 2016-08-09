#include "Annotations.h"


Annotations::Annotations(void):length(0), annotations{} {}

Annotations::~Annotations(void){}

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
