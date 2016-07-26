#Image documentation
This is a wrapper of the OpenCV 'cv::Mat' class representing images.
The goal is to store all relevant information to be available almost instantly.

Thus we preprocess images at the very moment we load them.

Due to the later use, we also need to resize images to have a 224px minimum for both dimensions if need be.

Here is the Image members:

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