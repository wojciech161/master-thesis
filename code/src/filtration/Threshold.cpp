#include "filtration/Threshold.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "filtration/ConvertToBlackAndWhite.hpp"
#include "segmentation/helpers/ContourMerge.hpp"

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

    boost::shared_ptr<cv::Mat> result;
    boost::shared_ptr<cv::Mat> redContours( new cv::Mat() );
    boost::shared_ptr<cv::Mat> greenContours( new cv::Mat() );
    boost::shared_ptr<cv::Mat> blueContours( new cv::Mat() );

    // Get red contours
    boost::shared_ptr<cv::Mat> blackAndWhiteImage = 
        ConvertToBlackAndWhite( EConversionType_Red ).apply( input );
    // threshold image
    cv::threshold( *blackAndWhiteImage,
                   *redContours,
                   thresholdValue_,
                   BLACK_VALUE,
                   THRESHOLD_TYPE );

    // Get green contours
    blackAndWhiteImage = 
        ConvertToBlackAndWhite( EConversionType_Green ).apply( input );
    // threshold image
    cv::threshold( *blackAndWhiteImage,
                   *greenContours,
                   thresholdValue_,
                   BLACK_VALUE,
                   THRESHOLD_TYPE );

    // Get blue contours
    blackAndWhiteImage = 
        ConvertToBlackAndWhite( EConversionType_Blue ).apply( input );
    // threshold image
    cv::threshold( *blackAndWhiteImage,
                   *blueContours,
                   thresholdValue_,
                   BLACK_VALUE,
                   THRESHOLD_TYPE );

    // Merge layers
    result = 
        segmentation::helpers::ContourMerge( redContours, greenContours, blueContours ).apply();

    return result;
}

} // namespace filtration
