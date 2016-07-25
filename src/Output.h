#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using std::string;

class Output
{
  public:
    Output(char * directory);
    virtual void write(cv::Mat dst, string filename, int nb_sample, string label, cv::RotatedRect rrect, float delta_x, float delta_y , float delta_rotation , float delta_scale, int left, int right, int up, int down) = 0;
    virtual void close() = 0;
  protected:
    char * output_dir;
};


class Directory: public Output
{
  public:
    Directory(char * directory, bool append = false, bool output_by_label = true );
    void write(cv::Mat dst, string filename, int nb_sample, string label, cv::RotatedRect rrect, float delta_x, float delta_y , float delta_rotation , float delta_scale, int left, int right, int up, int down );
    void write();
    void close();
  protected:
    std::ofstream outfile;
    bool output_by_label_;
};


class OpnCV : public Output
{
  public:
    OpnCV(char* directory);
    void write(cv::Mat dst, string filename, int nb_sample, string label, cv::RotatedRect rrect, float delta_x, float delta_y , float delta_rotation , float delta_scale, int left, int right, int up, int down );
    void write();
    void close();

  protected:
    std::ofstream outfile;
    int item_id ;
};
