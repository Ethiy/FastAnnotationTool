#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

extern const double min_dim; /* Minimum dimension of the full image */
extern const double max_dim; /* Maximum dimension of the to-be-shown image */

class Image
{
public:
    /*---Constructor--*/
    Image( std::string image_path );

    /*---Encapsulators---*/
    int get_height();
    int get_width();
    long get_area();
    int get_channels();
    bool is_loaded();

    /*---Image Processing---*/
    void process();
    void redimension();

    /*---Save---*/
    void save( std::string image_name );

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
    long area = 0;
    int channels = 0;
    
    /*---Success---*/
    bool loaded = false;

};

inline bool Image::is_loaded()
{
  return this->loaded;
}

inline int Image::get_height()
{
  assert( this->is_loaded() );
  return this->height;
}

inline int Image::get_width()
{
  assert( this->is_loaded() );
  return this->width;
}

inline long Image::get_area()
{
  assert( this->is_loaded() );
  return(this->area);
}

inline int Image::get_channels()
{
  assert( this->is_loaded() );
  return(this->channels);
}

inline void Image::save( std::string image_name )
{
  if( this->is_loaded() )
  {
    try 
    {
      std::vector<int> compression_params;
      compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
      compression_params.push_back(9);
      imwrite(".png", this->full_image, compression_params);
    }
    catch (std::runtime_error& ex) 
    {
      std::cerr << "Exception converting image to PNG format: " << ex.what() << std::endl;
    }
    std::cout << "Saved Image." << std::endl;
  }
}

#endif
