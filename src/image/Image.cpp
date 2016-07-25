#include "Image.h"

Image::Image (std::string image_path)
{
    full_image = imread(image_path, CV_LOAD_IMAGE_COLOR);
    if(! full_image.data )
    {
        std::cerr <<  "Could not open or find:" << image_path << std::endl ;
        this->successful_loading = false;
        std::abort();
    } 
    else
    {
      this->successful_loading = true;
      this->height = full_image.rows;
      this->width = full_image.cols;
      this->channels = full_image.channels();
      auto resizing_factor = static_cast< double >( std::max( this->height , this->width ) ) / this->max_dim;
      if( resizing_factor > 1.5)
      {
        resizing_factor = 1. / resizing_factor;
        resize( full_image , image , Size() , resizing_factor ,resizing_factor , INTER_AREA );
        this->height = image.rows;
        this->width = image.cols;
      }
      else
      {
        image = full_image;
      }
      this->area = height * width;
    }
}

void Image::process()
{
  assert(this->get_area()>0);
  assert(this->get_channels()>0);
  const int depth(2^8-1);
  cvtColor( this->image , this->gray_image , CV_BGR2GRAY );
  adaptiveThreshold( this->gray_image , this->threshold_image , depth , ADAPTIVE_THRESH_MEAN_C , THRESH_BINARY , 11 , 12 );
}

void Image::release()
{
  this->image.release();
  this->gray_image.release();
  this->threshold_image.release();
  this->full_image.release();

  this->height = 0;
  this->width = 0;
  this->area = 0;
  this->channels = 0;
  this->successful_loading = false;
}
