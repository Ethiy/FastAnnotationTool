#include "Image.h"

const double min_dim = 224; 
const double max_dim = 500;

Image::Image (std::string image_path)
{
    this->full_image = imread(image_path, CV_LOAD_IMAGE_COLOR);
    if(! full_image.data )
    {
        std::cerr <<  "Could not open or find:" << image_path << std::endl ;
        this->loaded = false;
        std::abort();
    } 
    else
    {
      this->loaded = true;
      this->height = this->full_image.rows;
      this->width = this->full_image.cols;
      this->channels = this->full_image.channels();
      auto ratio = static_cast< double >( std::max( this->height , this->width ) ) / max_dim;
      if( ratio > 1.5)
      {
        ratio = 1. / ratio;
        resize( this->full_image , this->image , Size() , ratio ,ratio , INTER_AREA );
        this->height = this->image.rows;
        this->width = this->image.cols;
      }
      else
      {
        this->image = this->full_image.clone();
      }
      this->area = this->height * this->width;
    }
}

void Image::redimension()
{
  auto ratio = static_cast<double>( this->height ) / min_dim;
  ratio = 1. / ratio;
  resize( this->full_image , this->full_image , Size() , ratio ,ratio , INTER_AREA );
  this->height = this->full_image.rows;
  this->width = this->full_image.cols;
  this->area = this->height * this->width;
}


void Image::process()
{
  assert(this->get_area()>0);
  assert(this->get_channels()>0);
  const int depth(2^8-1);
  cvtColor( this->full_image , this->gray_image , CV_BGR2GRAY );
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
  this->loaded = false;
}
