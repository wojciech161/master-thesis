#include "filehandler/FileHandler.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

namespace filehandler
{

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler()
{

}

boost::optional<cv::Mat> FileHandler::loadImage( const std::string& fileName ) const
{
    boost::optional<cv::Mat> result;

    cv::Mat image = cv::imread( fileName, CV_LOAD_IMAGE_COLOR );

    if( !image.data )
    {
        std::cout << "Could not load image.\n";
        return result;
    }

    std::cout << "Loaded " << fileName << "\n";
    result = image;
    return result;
}

void FileHandler::saveImage(
    const std::string& outputPath, boost::shared_ptr<cv::Mat> outputImage ) const
{
    bool success = cv::imwrite( outputPath, *outputImage );
    std::cout << "Output image " << (success ? "saved" : "save failure.") << std::endl;
}

} // namespace filehandler
