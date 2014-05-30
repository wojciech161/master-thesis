#include "segmentation/LineDetection.hpp"
#include <iostream>
#include "filtration/Threshold.hpp"
#include "filtration/UnsharpMask.hpp"
#include "filtration/ElliminateWhiteNoise.hpp"
#include "filtration/RemoveLonePixels.hpp"
#include "segmentation/helpers/ContourColorRestoration.hpp"
#include "segmentation/helpers/ColorAlignment.hpp"

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
    const int THRESHOLD_VALUE = 140;
    // const int HOLES_REMOVAL_WINDOW_SIZE = 3;
    boost::shared_ptr<cv::Mat> result = input;

    // Apply unsharp mask to image
    result = filtration::UnsharpMask().apply( result );
    // Threshold image
    result = filtration::Threshold( THRESHOLD_VALUE ).apply( result );

    // Elliminate white noise
    result = filtration::ElliminateWhiteNoise().apply( result );

    // Substitute black pixels with color ones from input
    result = helpers::ContourColorRestoration( input, result ).apply();

    // Elliminate single dots
    result = filtration::RemoveLonePixels().apply( result );

    // Find common colors of lines
    result = helpers::ColorAlignment().apply( result );

    return result;
}

} // namespace segmentation
