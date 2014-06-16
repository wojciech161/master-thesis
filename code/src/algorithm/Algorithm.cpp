#include "algorithm/Algorithm.hpp"

#include <boost/thread.hpp>
#include <boost/bind.hpp>

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

    // Get params determining if algorithm is enabled
    bool lineDetectionEnabled = parameters_.getLineDetectionParams().enabled;
    bool colorSegmentationEnabled = parameters_.getColorSegmentationParams().enabled;

    // Start algorithms in a different threads
    boost::thread backgroundDetectionThread(
        boost::bind(
            &Algorithm::backgroundDetection,
            this,
            colorSegmentationEnabled )
        );
    boost::thread lineDetectionThread(
        boost::bind(
            &Algorithm::lineDetection,
            this,
            lineDetectionEnabled )
        );

    // Join threads
    backgroundDetectionThread.join();
    lineDetectionThread.join();

    if( lineDetectionEnabled && colorSegmentationEnabled )
    {
        result = segmentation::helpers::LayerMerge( backgroundImage_, contourImage_ ).apply();
    }
    else if ( lineDetectionEnabled ) // Only line detection enabled
    {
        result = contourImage_;
    }
    else if ( colorSegmentationEnabled ) // Only color segmentation enabled
    {
        result = backgroundImage_;
    }
    else // Nothing enabled
    {
        result = image_;
    }

    return result;
}

void Algorithm::backgroundDetection( bool isEnabled )
{
    if( isEnabled )
    {
        backgroundImage_ =
            segmentation::ColorSegmentation( parameters_.getColorSegmentationParams() )
                .apply( image_ );
    }
    else
    {
        std::cout << "ColorSegmentation DISABLED\n";
    }
}

void Algorithm::lineDetection( bool isEnabled )
{
    if( isEnabled )
    {
        contourImage_ =
            segmentation::LineDetection( parameters_.getLineDetectionParams() ).apply( image_ );
    }
    else
    {
        std::cout << "LineDetection DISABLED\n";
    }
}


} // namespace algorithm
