#include "Image.h"

const double min_dim = 224; 
const double max_dim = 500;

const cv::Scalar RED = Scalar(0,0,255);
const cv::Scalar BLUE = Scalar(255,0,0);
const cv::Scalar GREEN = Scalar(0,255,0);
const cv::Scalar YELLOW = Scalar(0, 255, 255);

const std::string annotation_window = "Fast Image Annotation Tool";
const std::string console_window = "Console";

const int Confirm = 99;
const int Next = 110;
const int Delete = 100;
const int ESC = 27;


Image::Image(sys::path image_path)
{
    image = cv::imread(image_path.string(), cv::CV_LOAD_IMAGE_COLOR);
    if(!image.data )
    {
        std::cerr <<  "[ERROR]:[Could not load image from:" << image_path << "]." << std::endl ;
        loaded = false;
        std::exit(EXIT_FAILURE)
    } 
    else
    {
      loaded = true;
      height = image.rows;
      width = image.cols;
      channels = image.channels();
      area = height * width;
    }
}

void Image::redimension(void)
{
    auto ratio = min_dim/static_cast<double>( height );
    cv::resize( image , image , Size() , ratio ,ratio , cv::INTER_AREA );
    height = image.rows;
    width = image.cols;
    area = height * width;
}

void Image::save_to(sys::path image_path)
{
    assert( is_loaded() );
    try{
        const int PNG_COMPRESSION_PARAMETER = 9;
        std::vector<int> compression_params;
        compression_params.push_back(cv::CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(PNG_COMPRESSION_PARAMETER);
        cv::imwrite(image_path.string(), image, compression_params);
	  }
    catch (std::runtime_error& exeption) 
    {
        std::cerr << "[ERROR]:[Exception converting image to PNG format: " << exeption.what() << "]." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::cout << "[INFO]:[Image Saved.]" << std::endl;
}

void Image::mouse_click(int event, int x, int y, int flags, void* that)
{
    Image* that = static_cast<Image*>(that);
    that->_mouse_click(int event, int x, int y, int flags);
}

void Image::_mouse_click(int event, int x, int y, int flags)
{
    bool getting_roi = false;
    cv::Mat current_view = image;
    switch(event)
    {
        case EVENT_LBUTTONDOWN:
        {
            if(getting_roi)
            {
                first_corner.x = x;
                first_corner.y = y;
                getting_roi = true;
            }
            else
            {
                second_corner.x = x;
                second_corner.y = y;
                getting_roi = false;
            }
            break;
        }
        case EVENT_MOUSEMOVE:
        {
            if(getting_roi)
            {
                cv::rectangle(current_view, first_corner, cv::Point(x,y), RED);
                cv::imshow(annotations_window, current_view);
            }
            break;
        }
        default:
            break;
    }
}

std::vector<Annotation> Image::annotate(void)
{
    std::vector< Annotation> RoIs;

    cv::namedWindow(annotations_window, WINDOW_AUTOSIZE);
    cv::setMouseCallback(annotations_window, Image::mouse_click, this);

    cv::Mat current_view = image;
    cv::imshow(annotation_window, current_view);

    int key = 0;

    do
    {
        key = 0xFF & waitKey(0);

        switch (key)
        {
            case ESC:
            {
                cv::destroyWindow(annotation_window);
                break;
            }
            case Confirm:
            {
                cv::rectangle(current_view, first_corner, second_corner, YELLOW);
                std::cout << "Enter class: ";
                std::string object_class;
                std::cin >> object_class;
                std::cout << std::endl;
                RoIs.push_back( Annotation(object_class, first_corner, second_corner) );
                cv::rectangle(current_view, first_corner, second_corner, GREEN);
                break;
            }
            case Delete:
            {
                if(!RoIs.empty())
                    RoIs.pop_back();
                else
                    std::cout << "[INFO]:[There is no annotation to delete!]" << std::endl;
                break;
            }
            default:
                break;
        }

    } while(key != Next );
    cv::destroyWindow(annotation_window);
    return RoIs;
}
