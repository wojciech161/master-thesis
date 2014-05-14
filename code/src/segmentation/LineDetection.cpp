#include "segmentation/LineDetection.hpp"
#include <iostream>
#include "filtration/Threshold.hpp"
#include "filtration/UnsharpMask.hpp"
#include "opencv2/photo/photo.hpp"

namespace segmentation
{

LineDetection::LineDetection()
{
    std::cout << "SEGMENTATION: LineDetection - created\n";
}

LineDetection::~LineDetection()
{
    std::cout << "SEGMENTATION: LineDetection - applied\n";
}

boost::shared_ptr<cv::Mat> LineDetection::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int THRESHOLD_VALUE = 75;
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    boost::shared_ptr<cv::Mat> unsharpedImage;
    boost::shared_ptr<cv::Mat> thresholdedImage;

    // Apply unsharp mask to image
    unsharpedImage = filtration::UnsharpMask().apply( input );
    // Threshold image
    thresholdedImage = filtration::Threshold( THRESHOLD_VALUE ).apply( unsharpedImage );

    // Elliminate single dots
    cv::fastNlMeansDenoising( *thresholdedImage, *result, 50 );

    // Substitute black pixels with color ones from input

    // Find common colors of lines

    return result;
}

} // namespace segmentation
