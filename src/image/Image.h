#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Image
{
public:
    /*---Constructor--*/
    Image( std::string image_path );

    /*---Encapsulators---*/
    int get_height();
    int get_width();
    int get_area();
    int get_channels();

    /*---Image Processing---*/
    void process();

    /*---Destructor---*/
    void release();

private:
    Mat image;
    /*---Temporary images---*/
    Mat full_image;
    Mat gray_image;
    Mat threshold_image;

    /*---Dimensions---*/
    int height = 0;
    int width = 0;
    int area = 0;
    int channels = 0;
    const double max_dim = 500.;     // maximum dimension of the to be shown image.
    
    /*---Success---*/
    bool successful_loading = false;

};

inline int Image::get_height()
{
  assert(this->height>0);
  return this->height;
}

inline int Image::get_width()
{
  assert(this->width>0);
  return this->width;
}

inline int Image::get_area()
{
  assert(this->area>0);
  return(this->area);
}

inline int Image::get_channels()
{
  assert(this->channels>0);
  return(this->channels);
}

#endif
