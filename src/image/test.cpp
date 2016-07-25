#include "Image.h"

int main()
{
  const std::string image_path = "/Users/ETHIY/Workspace/FastAnnotationTool/ressources/images/pic.jpg";
  Image test_image = Image( image_path );

  std::cout << "Checking Dimensions:" << std::endl << "   1. Height: " << test_image.get_height();
  assert(test_image.get_height()>0);
  std::cout << " >0" << std::endl << "   2. Width: " << test_image.get_width();
  assert(test_image.get_width()>0);
  std::cout << " >0" << std::endl << "   3. Channels: " << test_image.get_channels();
  assert(test_image.get_channels()>0);
  std::cout << " >0" << std::endl << "   4. Area: " << test_image.get_area();
  assert( test_image.get_area() == test_image.get_height() * test_image.get_width() );
  std::cout << " = " << test_image.get_height() << " x " << test_image.get_width() << std::endl;

  test_image.process();

  test_image.release();

  std::cout << "End of tests no problem detected!" << std::endl;

  return 0;
}