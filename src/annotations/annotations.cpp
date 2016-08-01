#include "annotations.h"

cv::Point first_corner;
cv::Point second_corner;
cv::Mat capture_image;

const cv::Scalar RED = Scalar(0,0,255);
const cv::Scalar BLUE = Scalar(255,0,0);
const cv::Scalar GREEN = Scalar(0,255,0);
const cv::Scalar YELLOW = Scalar(0, 255, 255);

const std::string annotation_window_name = "Fast Image Annotation Tool";
const std::string console_window_name = "Console";

const int Confirm = 99;
const int Next = 110;
const int Delete = 100;
const int ESC = 27;


std::map<std::string, int> get_conventional_corners(cv::Point first_corner, cv::Point second_corner)
{
    std::map<std::string, int> rectangle;
    rectangle['x1'] = std::min(first_corner.x, second_corner.x);
    rectangle['y1'] = std::min(first_corner.y, second_corner.y);
    rectangle['x2'] = std::max(first_corner.x, second_corner.x);
    rectangle['y2'] = std::max(first_corner.y, second_corner.y);
    return rectangle;
}

void mouse_click(int event, int x, int y, int , void* params)
{
    bool getting_roi = false;
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
                cv::Mat current_view = capture_image.clone();
                cv::rectangle(current_view, first_corner, cv::Point(x,y), RED);
                cv::imshow(annotations_window_name, current_view);
            }
            break;
        }
        default:
            break;
    }
}

std::vector< std::pair< std::string, std::map<std::string, int> > > get_annotations(cv::Mat input_image)
{
    std::vector< std::pair< std::string, std::map<std::string, int> > > RoIs;
    bool stop = false;

    cv::namedWindow(annotations_window_name, WINDOW_AUTOSIZE);
    cv::setMouseCallback(annotations_window_name, mouse_click);

    capture_image = input_image;
    cv::imshow(annotation_window_name);

    int key = 0;

    do
    {
        key = 0xFF & waitKey(0);

        switch (key)
        {
            case ESC:
            {
                cv::destroyWindow(annotation_window_name);
                stop = true;
                break;
            }
            case Confirm:
            {
                std::map<std::string, int> rectangle = get_conventional_corners(first_corner, second_corner);
                cv::rectangle(current_view, first_corner, second_corner, YELLOW);
                std::cout << "Enter class: ";
                std::string object_class;
                std::cin >> object_class;
                std::cout << std::endl;
                RoIs.push_back( std::make_pair(object_class, rectangle) );
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

        if(stop)
            break;
                    
    } while(key != Next );
}
