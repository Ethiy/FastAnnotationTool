#ifndef ANNOTATIONS_H
#define ANNOTATIONS_H

#include "../image/Image.h"

#include <vector>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


/*---Colors---*/
extern const cv::Scalar RED;
extern const cv::Scalar BLUE;
extern const cv::Scalar GREEN;
extern const cv::Scalar YELLOW;

/*---Windows' names---*/
extern const std::string annotation_window_name;
extern const std::string console_window_name;

/*---Navigating Keys---*/
extern const int Confirm;
extern const int Next;
extern const int Delete;
extern const int ESC;


/**Get up left and bottom down
*   conventional: i.e. (x1,y1) and (x2,y2).
**/
std::map<std::string, int> get_conventional_corners(std::pair<cv::Point,cv::Point>);

/**Mouse click function**/
void mouse_click(int, int, int, int, void*);

/**Annotation function**/
std::vector< std::pair< std::string, std::map<std::string, int> > > get_annotations(cv::Mat);

#endif //  ANNOTATIONS_H