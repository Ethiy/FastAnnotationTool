#ifndef Annotations_H
#define Annotations_H

#include "Annotation.h"

#include <cassert>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

class Annotations
{
public:
    Annotations(void);
    ~Annotations(void);

    bool is_empty(void);
    size_t size(void);
    bool append(Annotation);
    Annotation pop(void);

private:
    bool set;

    std::vector<Annotation> annotations;
    size_t length;

    friend std::ostream& operator<<(std::ostream&, const Annotations&);
};

inline bool Annotations::is_empty(void)
{
    assert(length==0);
    return annotations.empty();
}

inline size_t Annotations::size()
{
    assert(length==annotations.size());
    return length;
}

#endif //  Annotations_H
