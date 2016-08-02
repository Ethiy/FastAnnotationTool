#ifndef IMAGE_H
#define IMAGE_H

#include "../tools/tools.h"
#include "../annotation/Annotation.h"

#include <cassert>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


/*---Dimensions---*/
extern const double min_dim; /* Minimum dimension of the full image */
extern const double max_dim; /* Maximum dimension of the to-be-shown image */

/*---Colors---*/
extern const cv::Scalar RED;
extern const cv::Scalar BLUE;
extern const cv::Scalar GREEN;
extern const cv::Scalar YELLOW;

/*---Window names---*/
extern const std::string annotation_window;
extern const std::string console_window;

/*---Navigating Keys---*/
extern const int Confirm;
extern const int Next;
extern const int Delete;
extern const int ESC;

typedef union
{
    cv::Point corner;
    cv::Mat image;
} Parameter;

class Image
{
public:

    Image(sys::path);
    ~Image();

    bool is_loaded(void);
    int get_height(void);
    int get_width(void);
    long get_area(void);
    int get_channels(void);

    void redimension(void);

    void save_to(sys::path);

    static void mouse_click(int, int, int, int , void*);
    std::vector<Annotation> annotate(void);

private:

    bool loaded;

    cv::Mat image;

    int height;
    int width;
    long area;
    int channels;
    
};

inline bool Image::is_loaded(void)
{
	  return loaded;
}

inline int Image::get_height(void)
{
	  assert( is_loaded(void) );
	  return height;
}

inline int Image::get_width(void)
{
	  assert( is_loaded(void) );
	  return width;
}

inline long Image::get_area(void)
{
	  assert( is_loaded(void) );
	  return(area);
}

inline int Image::get_channels(void)
{
	  assert( is_loaded(void) );
	  return(channels);
}

#endif
