#include "tools.h"

/*---default_annotations_folder(std::string images_folder):
        specifies: - annotations_folder, annotations' default folder path from images_folder.
---*/
int default_annotations_folder(std::string images_folder, std::string& annotations_folder )
{
    const sys::path images_path( images_folder );
    const sys::path temp_path( "Annotations/" );
    try
    {
      sys::is_directory(images_path);
      sys::path annotations_path = images_path.parent_path();
      annotations_path /= temp_path;
      annotations_folder = annotations_path.string();
    }
    catch (const sys::filesystem_error& error)
    {
      if(error.code() == boost::system::errc::permission_denied)
        std::cerr << "Permission denied for: " << images_path << std::endl;
      else
        std::cerr << "boost::filesystem::is_directory(" << images_path << ") failed:" << error.code().message() << std::endl;
      return ERROR_IN_PATH;
    }
    return EXIT_SUCCESS;
}

/*---argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder):
        specifies: - images_folder, images' folder path.
                   - annotations_folder, annotations' folder path.
---*/ 
int argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder)
{
    int success(0);
    try
    {
        arg_parser::options_description description("Options");
        description.add_options()
            ("help,h", "Prints help message.")
            ("images", arg_parser::value<std::string>(& images_folder)->required(), 
            "Folder containing images:\nUse absolute paths to avoid problems.\n[example - /some/long/path/to/data/Images]")
            ("annotations", arg_parser::value<std::string>(& annotations_folder),
            "Folder containing annotations:\nUse absolute paths to avoid problems.\n[default value - /some/long/path/to/data/Annotations]");
        arg_parser::variables_map vm;

        try
        {
            arg_parser::store( arg_parser::parse_command_line(argc, argv, description), vm);
            notify(vm);

            if(vm.count("help"))
                std::cout << description << std::endl;
            if (vm.count("images")) 
                std::cout << std::endl << "    The images folder path has been set to:           \"" << vm["images"].as<std::string>() << "\"." << std::endl;
            if (vm.count("annotations")) 
                std::cout << std::endl << "    The annotations folder path has been set to:     \"" << vm["annotations"].as<std::string>() << "\"." << std::endl;
            else
            {
                success = default_annotations_folder(images_folder, annotations_folder);
                std::cout << std::endl << "    The annotations folder path was not specified." << std::endl << 
                                          "      - The default value is deduced to be:            \"" << annotations_folder << "\"." << std::endl;
            }
        }
        catch (arg_parser::error& error)
        {
            std::cerr << std::endl << "ERROR: " << error.what() << std::endl << std::endl;
            std::cerr << description << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    }
    catch (const std::exception& exception)
    {
        std::cerr << std::endl << std::endl << "Unhandled Exception in the argument parser:" << exception.what() << ", exiting ..." << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    success += EXIT_SUCCESS;
    return success;
}
