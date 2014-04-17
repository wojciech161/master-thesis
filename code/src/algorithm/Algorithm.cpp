#include "algorithm/Algorithm.hpp"
#include "filtration/ApplyBilateralFilter.hpp"
#include "filtration/ApplyGaussianFilter.hpp"
#include "segmentation/ColorSegmentation.hpp"

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

    boost::shared_ptr<cv::Mat> filteredImage;
    // First, we apply a bilateral and gaussian filters to remove noises from maps
    filteredImage = filtration::ApplyBilateralFilter().apply( image_ );
    filteredImage = filtration::ApplyGaussianFilter().apply( filteredImage );

    result = segmentation::ColorSegmentation().apply( filteredImage );

    return result;
}

} // namespace algorithm
