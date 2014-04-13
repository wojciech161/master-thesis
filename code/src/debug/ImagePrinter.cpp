#include "debug/ImagePrinter.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <string>

namespace debug
{

ImagePrinter::ImagePrinter()
{

}

ImagePrinter::~ImagePrinter()
{

}

void ImagePrinter::print( const cv::Mat& image, const std::string& windowTitle ) const
{
    if( isPrintingEnabled() )
    {
        cv::namedWindow(windowTitle, CV_WINDOW_AUTOSIZE);
        cv::imshow( windowTitle, image );
        cv::waitKey( 0 );
    }
}

bool ImagePrinter::isPrintingEnabled() const
{
    #ifdef DEBUG_IMAGES
    return true;
    #endif
    return false;
}

} // namespace debug
