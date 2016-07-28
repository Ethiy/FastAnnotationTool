#include "tools.h"

std::string default_annotations_folder(std::string images_folder)
{
    const sys::path images_path( images_folder );
    sys::is_directory(images_path);
    const sys::path temp_path( "Annotations" );
    sys::path annotations_path = images_path.parent_path();
    annotations_path /= temp_path;
    return annotations_path.string();
}

int argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder)
{
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
                try
                {
                    annotations_folder = default_annotations_folder(images_folder);
                    std::cout << std::endl << "    The annotations folder path was not specified." << std::endl << 
                                            "      - The default value is deduced to be:            \"" << annotations_folder << "\"." << std::endl;
                }
                catch (sys::filesystem_error const& error)
                {
                    if(error.code() == boost::system::errc::permission_denied)
                        std::cerr << "Permission denied for: " << images_folder << std::endl;
                    else
                        std::cerr << "boost::filesystem::is_directory(" << images_folder << ") failed:" << error.code().message() << std::endl;
                    return ERROR_IN_PATH;
                }
            }
        }
        catch (arg_parser::error const& error)
        {
            std::cerr << std::endl << "ERROR: " << error.what() << std::endl << std::endl;
            std::cerr << description << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    }
    catch (std::exception const& exception)
    {
        std::cerr << std::endl << std::endl << "Unhandled Exception in the argument parser:" << exception.what() << ", exiting ..." << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return EXIT_SUCCESS;
}
