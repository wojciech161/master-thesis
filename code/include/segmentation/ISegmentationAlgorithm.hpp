#ifndef SEGMENTATION_ISEGMENTATION_ALGORITHM_HPP_
#define SEGMENTATION_ISEGMENTATION_ALGORITHM_HPP_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>

namespace segmentation
{

class ISegmentationAlgorithm
{
public:
    virtual ~ISegmentationAlgorithm() {}
    virtual boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const = 0;
};

} // namespace segmentation

#endif // SEGMENTATION_ISEGMENTATION_ALGORITHM_HPP_
