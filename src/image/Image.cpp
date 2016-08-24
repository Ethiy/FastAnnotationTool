#include "Image.h"


const cv::Scalar RED = cv::Scalar(0,0,255);
const cv::Scalar BLUE = cv::Scalar(255,0,0);
const cv::Scalar GREEN = cv::Scalar(0,255,0);
const cv::Scalar YELLOW = cv::Scalar(0, 255, 255);

const std::string annotation_window = "Fast Image Annotation Tool";
const std::string console_window = "Console";

const int Confirm = 99;
const int Next = 110;
const int Delete = 100;
const int ESC = 27;

cv::Point first_corner(0,0), second_corner(0,0);
bool getting_roi = false;


Image::Image(sys::path image_path)
{
    image = cv::imread(image_path.string(), CV_LOAD_IMAGE_COLOR);
    if(!image.data )
    {
        std::cerr <<  "[ERROR]:[Could not load image from:" << image_path << "]." << std::endl ;
        loaded = false;
        std::exit(EXIT_FAILURE);
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

void Image::redimension(int min_dim)
{
    double ratio = static_cast<double>(min_dim) /static_cast<double>( height );
    cv::resize( image , image , cv::Size() , ratio ,ratio , cv::INTER_AREA );
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
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
        compression_params.push_back(PNG_COMPRESSION_PARAMETER);
        cv::imwrite(image_path.string(), image, compression_params);
	  }
    catch (std::runtime_error& exeption) 
    {
        std::cerr << "[ERROR]:[Exception converting image to PNG format: " << exeption.what() << "]." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::cout << "[INFO]:[Image Saved to: " << image_path.string() << "]" << std::endl;
}

void Image::mouse_click(int event, int x, int y, int flags, void* params)
{
    Image* that = static_cast<Image*>(params);
    that->_mouse_click(event, x, y, flags);
}

void Image::_mouse_click(int event, int x, int y, int flags)
{
    switch(event)
    {
        case cv::EVENT_LBUTTONDOWN:
        {
            if(!getting_roi)
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
        case cv::EVENT_MOUSEMOVE:
        {
            if(getting_roi)
            {
                current_view = image.clone();
                cv::rectangle(current_view, first_corner, cv::Point(x,y), RED);
                cv::imshow(annotation_window, current_view);
            }
            break;
        }
        default:
            break;
    }
}

Annotations Image::annotate(void)
{
    Annotations RoIs;

    cv::namedWindow(annotation_window, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(annotation_window, Image::mouse_click, this);

    current_view = image;
    cv::imshow(annotation_window, current_view);

    int key = 0;
    bool escape = false;

    do
    {
        key = 0xFF & cv::waitKey(0);
        cv::Mat temporary_view = current_view.clone();

        switch (key)
        {
            case ESC:
            {
                escape = true;
                break;
            }
            case Confirm:
            {
                std::cout << "Enter class: ";
                std::string object_class;
                std::cin >> object_class;
                Annotation current_annotation = Annotation(object_class, first_corner, second_corner);
                bool appended = RoIs.append( current_annotation ); // No error is thrown for now
                std::cout << "[INFO]:[ \"" << current_annotation << "\" has just been added.]" << std::endl;
                std::cout << "[INFO]:[ Currently, you have annotated \"" << RoIs.size() << "\" objects.]" << std::endl;
                break;
            }
            case Delete:
            {
                if(!RoIs.is_empty())
                {
                    Annotation last_annotation = RoIs.pop();
                    std::cout << "[INFO]:[ \"" << last_annotation << "\" has just been deleted.]" << std::endl;
                    std::cout << "[INFO]:[ Currently, you have annotated \"" << RoIs.size() << "\" objects.]" << std::endl;
                }
                else
                    std::cout << "[INFO]:[There is no annotation to delete!]" << std::endl;
                break;
            }
            default:
                break;
        }

        if(escape)
            break;

        RoIs.draw(temporary_view, GREEN);
        current_view = temporary_view;
        cv::imshow(annotation_window, current_view);
        current_view = image.clone();

    } while(key != Next );

    cv::destroyWindow(annotation_window);
    return RoIs;
}

Image::~Image(){}
