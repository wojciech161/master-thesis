#include "algorithm/Algorithm.hpp"
#include "segmentation/ColorSegmentation.hpp"
#include "segmentation/LineDetection.hpp"

namespace algorithm
{

Algorithm::Algorithm( const cv::Mat& image ) : image_( new cv::Mat( image ) )
{

}

Algorithm::~Algorithm()
{

}

boost::shared_ptr<cv::Mat> Algorithm::run()
{
    boost::shared_ptr<cv::Mat> result;

    // result = segmentation::LineDetection().apply( image_ );

    result = segmentation::ColorSegmentation().apply( image_ );

    return result;
}

} // namespace algorithm
