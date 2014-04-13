#include "core/Application.hpp"
#include <iostream>
#include <boost/foreach.hpp>
#include "filehandler/PathManager.hpp"
#include "filehandler/FileHandler.hpp"
#include "debug/ImagePrinter.hpp"
#include "filtration/ConvertToBlackAndWhite.hpp"

namespace core
{

Application::Application()
{
    displayIntroMessage();
    start();
}

Application::~Application()
{

}

void Application::displayIntroMessage() const
{
    std::cout << "Master Thesis\n";
    std::cout << "Author:\t\tMarcin Wojciechowski\n";
    std::cout << "University:\tWrocław University of Technology\n";
    std::cout << "Topic:\t\tDesign of filtration and segmentation algorithms for images taken "
                 "from colour printed documents\n";
    std::cout << "Supervisor:\tTomasz Babczyński, Ph. D.\n";
    std::cout << "Academic Year:\t2013/2014\n";
}

void Application::start() const
{
    // Constants definitions
    const std::string INPUT_WINDOW_TITLE = "Input Image";
    const std::string OUTPUT_WINDOW_TITLE = "Output Image";

    // Needed classes
    filehandler::PathManager pathManager;
    filehandler::FileHandler fileHandler;
    debug::ImagePrinter imagePrinter;

    // Get all available input images
    std::list<std::string> inputImages = pathManager.getInputFileList();

    // For each image...
    BOOST_FOREACH( std::string inputPath, inputImages )
    {
        // Load it
        boost::optional<cv::Mat> image = fileHandler.loadImage( inputPath );
        if( image.is_initialized() )
        {
            // Print it
            imagePrinter.print( *image,INPUT_WINDOW_TITLE );
            
            // Run algorithm
            boost::shared_ptr<cv::Mat> outputImage =
                runFiltrationAndSegmentationAlgorithm( *image );

            // Save results in output directory
            std::string outputPath = pathManager.getOutputPath( inputPath );
            fileHandler.saveImage( outputPath, outputImage );
            
            // And finally print result image
            imagePrinter.print( *outputImage, OUTPUT_WINDOW_TITLE );
        }
    }
}

boost::shared_ptr<cv::Mat> Application::runFiltrationAndSegmentationAlgorithm(
    const cv::Mat& inputImage) const
{
    boost::shared_ptr<cv::Mat> resultImage;

    // Convert image to Black - and - white
    resultImage = filtration::ConvertToBlackAndWhite().apply( inputImage );

    return resultImage;
}

} // namespace core
