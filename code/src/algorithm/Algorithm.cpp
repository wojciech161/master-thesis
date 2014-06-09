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
    bool lineDetectionEnabled = parameters_.getLineDetectionParams().enabled;
    bool colorSegmentationEnabled = parameters_.getColorSegmentationParams().enabled;

    if( lineDetectionEnabled )
    {
        contourImage = segmentation::LineDetection( parameters_.getLineDetectionParams() )
            .apply( image_ );
    }
    if( colorSegmentationEnabled )
    {
        backgroundImage = segmentation::ColorSegmentation( parameters_.getColorSegmentationParams() )
            .apply( image_ );
    }

    if( lineDetectionEnabled && colorSegmentationEnabled )
    {
        result = segmentation::helpers::LayerMerge( backgroundImage, contourImage ).apply();
    }
    else if ( lineDetectionEnabled ) // Only line detection enabled
    {
        result = contourImage;
    }
    else if ( colorSegmentationEnabled ) // Only color segmentation enabled
    {
        result = backgroundImage;
    }
    else // Nothing enabled
    {
        result = image_;
    }

    return result;
}

} // namespace algorithm
