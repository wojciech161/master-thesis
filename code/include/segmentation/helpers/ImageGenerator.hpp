#ifndef SEGMENTATION_HELPERS_IMAGE_GENERATOR_HPP_
#define SEGMENTATION_HELPERS_IMAGE_GENERATOR_HPP_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>
#include "ColorGroup.hpp"

namespace segmentation
{
namespace helpers
{
    
class ImageGenerator
{
public:
    ImageGenerator( boost::shared_ptr<cv::Mat>, const ColorGroup& );
    ~ImageGenerator();

    boost::shared_ptr<cv::Mat> getImage() const;

private:
    boost::shared_ptr<cv::Mat> result_;
};

} // namespace helpers
} // namespace segmentation

#endif // SEGMENTATION_HELPERS_IMAGE_GENERATOR_HPP_
