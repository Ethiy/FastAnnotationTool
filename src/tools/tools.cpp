#include "tools.h"

void check_path(const sys::path images_path)
{
    try
    {
        if(!sys::is_directory(images_path))
            throw images_path;
    }
    catch (sys::path& images_path)
    {
        std::cerr << std::endl << "[ERROR]:[" << images_path.string() << " is not a valid directory]." << std::endl;
        std::exit(ERROR_IN_PATH);
    }
}

std::string default_annotations_folder(std::string images_folder)
{
    const sys::path images_path( images_folder );
    const sys::path temp_path( "Annotations" );
    try
    {
        check_path(images_path);
        sys::path annotations_path = images_path.parent_path();
        annotations_path /= temp_path;
        if(!sys::is_directory(annotations_path))
        {
            bool created_path = sys::create_directory(annotations_path);
            if(!created_path)
                std::exit(ERROR_IN_PATH);
            else
            {
                std::cout << std::endl << "      [INFO]:[Successfully created directory: \"" << annotations_path.string() << " \".]" << std::endl;
            }
        }
        return annotations_path.string();
    }
    catch (sys::filesystem_error const& error)
    {
        if(error.code() == boost::system::errc::permission_denied)
            std::cerr << "[ERROR]:[Permission denied for: " << images_folder << "]." << std::endl;
        else
            std::cerr << "[ERROR]:[boost::filesystem::is_directory(" << images_folder << ") failed:" << error.code().message() << "]." << std::endl;
        std::exit(ERROR_IN_PATH);
    }
}

void argument_parser(int argc, const char *argv[], std::string& images_folder, std::string& annotations_folder)
{
    std::cout << std::endl << "[INFO]:[Parsing arguments]." << std::endl;
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
                annotations_folder = default_annotations_folder(images_folder);
                std::cout << "    The annotations folder path was not specified." << std::endl << 
                                        "      - The default value is deduced to be:            \"" << annotations_folder << "\"." << std::endl;
            }
        }
        catch (arg_parser::error const& error)
        {
            std::cerr << std::endl << "[ERROR]:[" << error.what() << "]." << std::endl << std::endl;
            std::cerr << description << std::endl;
            std::exit(ERROR_IN_COMMAND_LINE);
        }
    }
    catch (std::exception const& exception)
    {
        std::cerr << std::endl << std::endl << "[ERROR]:[Unhandled Exception in the argument parser: " << exception.what() << "]." << std::endl;
        std::exit(ERROR_UNHANDLED_EXCEPTION);
    }
}

std::vector<sys::path> get_images(std::string images_folder)
{
    sys::path images_path(images_folder);
    std::cout << std::endl << "[INFO]:[Getting all PNG images in folder: \"" << images_folder << "\" ]." << std::endl;
    std::vector<sys::path> images;
    sys::directory_iterator end_itr;
    try
    {
        for (sys::directory_iterator iterator(images_path); iterator != end_itr; ++iterator)
        {
            if( sys::is_regular_file( iterator->path() ) && iterator->path().extension().string() == ".png" )
                images.push_back( iterator->path() );
        }
    }
    catch (sys::filesystem_error const& error)
    {
        std::cerr << "[ERROR]:[boost::filesystem::is_regular_file(" << images_folder << ") failed:" << error.code().message() << "]." << std::endl;
        std::exit(ERROR_IN_PATH);
    }
    return images;
}

sys::path set_annotation_path(std::string annotations_folder, sys::path image_path)
{
    sys::path file = image_path.filename();
    sys::path annotation_path(annotations_folder);
    annotation_path /= file;
    return annotation_path.replace_extension("txt");
}

void save_annotations(std::string annotations_folder, sys::path image_path, Annotations annotations)
{
    sys::path annotation_path = set_annotation_path(annotations_folder, image_path);
    save_annotations_to(annotation_path, annotations);
}


void save_annotations_to(sys::path annotation_path, Annotations annotations)
{
    std::ofstream output(annotation_path.string());
    output.exceptions( std::ofstream::failbit | std::ofstream::badbit );
    try
    {
        output << Annotations << std::endl;
    }
    catch (std::ofstream::failure& const exception)
    {
        std::cerr << "[ERROR]:" << exception.what() << std::endl;
        std::exit(ERROR_IN_PATH);
    }

}

