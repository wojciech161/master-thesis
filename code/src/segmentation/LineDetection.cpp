#include "segmentation/LineDetection.hpp"
#include <iostream>
#include "filtration/Threshold.hpp"
#include "filtration/UnsharpMask.hpp"
#include "filtration/RemoveLonePixels.hpp"
#include "segmentation/helpers/ContourColorRestoration.hpp"
#include "segmentation/helpers/ColorAlignment.hpp"

namespace segmentation
{

LineDetection::LineDetection( const LineDetectionParams& parameters )
 : parameters_( parameters )
{
    std::cout << "SEGMENTATION: LineDetection - created\n";
}

LineDetection::~LineDetection()
{
    std::cout << "SEGMENTATION: LineDetection - applied\n";
}

boost::shared_ptr<cv::Mat> LineDetection::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int THRESHOLD_VALUE = parameters_.thresholdValue;
    // const int UNSHARP_MASK_STANDARD_DEVIATION = parameters_.unsharpMaskStandardDeviation;

    boost::shared_ptr<cv::Mat> result = input;

    // Threshold image
    result = filtration::Threshold( THRESHOLD_VALUE ).apply( result );

    // Substitute black pixels with color ones from input
    result = helpers::ContourColorRestoration( input, result ).apply();

    // Elliminate single dots
    result = filtration::RemoveLonePixels().apply( result );

    // // Apply unsharp mask to image
    // result = filtration::UnsharpMask( UNSHARP_MASK_STANDARD_DEVIATION ).apply( result );

    // Find common colors of lines
    result = helpers::ColorAlignment( parameters_ ).apply( result );

    return result;
}

} // namespace segmentation
