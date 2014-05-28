#include "algorithm/Algorithm.hpp"
#include "segmentation/ColorSegmentation.hpp"
#include "segmentation/LineDetection.hpp"
#include "segmentation/helpers/LayerMerge.hpp"

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
    boost::shared_ptr<cv::Mat> backgroundImage;
    boost::shared_ptr<cv::Mat> contourImage;

    contourImage = segmentation::LineDetection().apply( image_ );
    backgroundImage = segmentation::ColorSegmentation().apply( image_ );

    result = segmentation::helpers::LayerMerge( backgroundImage, contourImage ).apply();

    return result;
}

} // namespace algorithm
