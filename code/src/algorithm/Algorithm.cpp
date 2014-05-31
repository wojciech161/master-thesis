#include "algorithm/Algorithm.hpp"
#include "segmentation/ColorSegmentation.hpp"
#include "segmentation/LineDetection.hpp"
#include "segmentation/helpers/LayerMerge.hpp"

namespace algorithm
{

Algorithm::Algorithm( const cv::Mat& image, core::ParametersGetter& parameters )
 : image_( new cv::Mat( image ) )
 , parameters_( parameters )
{

}

Algorithm::~Algorithm()
{

}

boost::shared_ptr<cv::Mat> Algorithm::run()
{
    boost::shared_ptr<cv::Mat> result;
    boost::shared_ptr<cv::Mat> backgroundImage;
    boost::shared_ptr<cv::Mat> contourImage;

    contourImage = segmentation::LineDetection( parameters_.getLineDetectionParams() )
        .apply( image_ );
    backgroundImage = segmentation::ColorSegmentation( parameters_.getColorSegmentationParams() )
        .apply( image_ );

    result = segmentation::helpers::LayerMerge( backgroundImage, contourImage ).apply();

    return result;
}

} // namespace algorithm
