#include "Output.h"

Output::Output(char * directory) {
  output_dir = directory;
};

Directory::Directory(char * directory, bool append, bool output_by_label): Output(directory) {
  if(!append) {
    CHECK_EQ(mkdir(output_dir, 0744), 0)
        << "mkdir " << output_dir << "failed";
  }
  outfile.open( string(output_dir) + "/results.csv", std::ios_base::app);

  output_by_label_ = output_by_label;
};

void Directory::write( cv::Mat dst, string filename, int nb_sample, string label, cv::RotatedRect rrect, float delta_x, float delta_y , float delta_rotation , float delta_scale, int left, int right, int up, int down ) {

  string label_dir = "";
  string label2 = "";
  string target_dir = string(output_dir);
  if( output_by_label_ ) {
    if( !label.length() )
      label2 = "_";
    else
      label2 = label ;

    target_dir += "/" + label2;
    label_dir = label2 + "/";
  } ;

  struct stat st;
  if(stat(target_dir.c_str(),&st) != 0)
    CHECK_EQ(mkdir( target_dir.c_str() , 0744), 0)
      << "mkdir " << target_dir << " failed";

  string out_filename  = filename + "_" + std::to_string(nb_sample) + ".jpg";
  string output_path = target_dir + "/" + out_filename;
  imwrite( output_path , dst  );

  std::cout << "    Output file path : " << label_dir << out_filename << std::endl;
  std::cout << "    New values : [" << label << "," << rrect.center.x << "," << rrect.center.y << "," << rrect.size.width << "," << rrect.size.height << "," << rrect.angle << "," << delta_x << "," << delta_y << "," << delta_rotation << "," << delta_scale << "]" << std::endl;

  //write rectangle position
  outfile << label_dir + out_filename << "," << label << "," << rrect.center.x << "," << rrect.center.y << "," << rrect.size.width << "," << rrect.size.height << "," << rrect.angle << "," << delta_x << "," << delta_y << "," << delta_rotation << "," << delta_scale << std::endl;
  outfile.flush();
};

void Directory::close() {
  outfile.close();
};


OpnCV::OpnCV(char * directory) : Output(directory) {
  string dir_paths [5] = { string(directory), string(directory) + "/pos", string(directory) + "/neg", string(directory) + "/pos/img", string(directory) + "/neg/img" };
  for(int i = 0 ; i < 5 ; i ++) {
    const char * dir_path = dir_paths[i].c_str();
    LOG(INFO) << "Creating directory " << dir_path;
    CHECK_EQ(mkdir(dir_path, 0744), 0)
        << "mkdir " << directory << " failed";
  }
  outfile.open( std::string( directory ) + "/pos/info.dat", std::ios_base::app);
  item_id = 0;
};

void OpnCV::write( cv::Mat dst, string filename, int nb_sample, string label, cv::RotatedRect rrect, float delta_x, float delta_y , float delta_rotation , float delta_scale, int left, int right, int up, int down)
{
  // save a positive
  string output_path =  "img/" + std::to_string(item_id) + ".jpg" ;
  imwrite( string(output_dir) + "/pos/" + output_path , dst );
  outfile << output_path << " 1 " << (int)(rrect.center.x - (rrect.size.width/2)) << " " << (int)(rrect.center.y - ( rrect.size.height / 2)) << " " << (int)rrect.size.width << " " << (int)rrect.size.height << endl;
  outfile.flush();
  item_id ++;

};

void OpnCV::close() {
  outfile.close();
};
