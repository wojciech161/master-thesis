#include "filehandler/PathManager.hpp"
#include <iostream>
#include <string>

namespace filehandler
{

PathManager::PathManager()
{
    std::cout << "Loading files\n";
}

PathManager::~PathManager()
{

}

std::list<std::string> PathManager::getInputFileList() const
{
    namespace fs = boost::filesystem;
    typedef fs::directory_iterator DirIter;
    std::list<std::string> fileList;

    fs::path inputPath = getInputPath();
    DirIter endIterator;

    if( fs::exists( inputPath ) && fs::is_directory( inputPath ) )
    {
        for( DirIter fileIterator(inputPath) ; fileIterator != endIterator ; ++fileIterator )
        {
            if( fs::is_regular_file( fileIterator->status() ) )
            {
                fileList.push_back( fileIterator->path().string() );
            }
        }
    }
    else
    {
        std::cout << "ERROR: Input path does not exist!";
    }

    return fileList;
}

std::string PathManager::getOutputPath(const std::string& inputPathStr) const
{
    namespace fs = boost::filesystem;
    const std::string PATH_TO_OUTPUT_IMAGE = "/resources/output_images/";

    // Get filename from input path
    std::string filename = fs::path( inputPathStr ).filename().string();
    // Get current path
    std::string currentPath = fs::current_path().string();

    // Concatenate strings to create output path
    std::string outputPath = currentPath + PATH_TO_OUTPUT_IMAGE + filename;
    std::cout << "Output path set to: " << outputPath << std::endl;

    return outputPath;

}

boost::filesystem::path PathManager::getInputPath() const
{
    const std::string PATH_TO_INPUT_IMAGE = "/resources/input_images";

    // Get current path
    std::string currentPath = boost::filesystem::current_path().string();
    currentPath += PATH_TO_INPUT_IMAGE;

    std::cout << "Image Input directory set to: " << currentPath << std::endl;

    return boost::filesystem::path( currentPath );
}


} // namespace filehandler
