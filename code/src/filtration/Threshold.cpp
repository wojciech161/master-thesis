#include "filtration/Threshold.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "filtration/ConvertToBlackAndWhite.hpp"

namespace filtration
{

Threshold::Threshold( int thresholdValue )
    : THRESHOLD_TYPE( 0 ) // Binary
    , thresholdValue_( thresholdValue )
{
    std::cout << "FILTRATION: Threshold - created\n";
}

Threshold::~Threshold()
{
    std::cout << "FILTRATION: Threshold - applied\n";
}

boost::shared_ptr<cv::Mat> Threshold::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int BLACK_VALUE = 255;

    boost::shared_ptr<cv::Mat> result( new cv::Mat() );

    // Convert image to black and white
    boost::shared_ptr<cv::Mat> blackAndWhiteImage = ConvertToBlackAndWhite().apply( input );

    // threshold image
    cv::threshold( *blackAndWhiteImage, *result, thresholdValue_, BLACK_VALUE, THRESHOLD_TYPE );

    return result;
}

} // namespace filtration
