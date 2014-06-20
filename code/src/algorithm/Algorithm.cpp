#include "algorithm/Algorithm.hpp"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

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

    boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: Start time: " 
                  << startTime.time_of_day() << std::endl;

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

    boost::posix_time::ptime stopTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: Stop time: "
                  << stopTime.time_of_day() << std::endl;
        std::cout << "ALGORITHM: Duration: "
                  << ( stopTime - startTime ) << std::endl;

    return result;
}

void Algorithm::backgroundDetection( bool isEnabled )
{
    if( isEnabled )
    {
        boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: ColorSegmentation: Start time: " 
                  << startTime.time_of_day() << std::endl;

        backgroundImage_ =
            segmentation::ColorSegmentation( parameters_.getColorSegmentationParams() )
                .apply( image_ );

        boost::posix_time::ptime stopTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: ColorSegmentation: Stop time: "
                  << stopTime.time_of_day() << std::endl;
        std::cout << "ALGORITHM: ColorSegmentation: Duration: "
                  << ( stopTime - startTime ) << std::endl;
    }
    else
    {
        std::cout << "ALGORITHM: ColorSegmentation DISABLED\n";
    }
}

void Algorithm::lineDetection( bool isEnabled )
{
    if( isEnabled )
    {
        boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: LineDetection: Start time: " 
                  << startTime.time_of_day() << std::endl;

        contourImage_ =
            segmentation::LineDetection( parameters_.getLineDetectionParams() ).apply( image_ );

        boost::posix_time::ptime stopTime = boost::posix_time::microsec_clock::local_time();
        std::cout << "ALGORITHM: LineDetection: Stop time: "
                  << stopTime.time_of_day() << std::endl;
        std::cout << "ALGORITHM: LineDetection: Duration: "
                  << ( stopTime - startTime ) << std::endl;
    }
    else
    {
        std::cout << "ALGORITHM: LineDetection DISABLED\n";
    }
}


} // namespace algorithm
