#ifndef SEGMENTATION_LINE_DETECTION_HPP_
#define SEGMENTATION_LINE_DETECTION_HPP_

#include "ISegmentationAlgorithm.hpp"

namespace segmentation
{

class LineDetection : public ISegmentationAlgorithm
{
public:
    LineDetection();
    ~LineDetection();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
};

} // namespace segmentation

#endif // SEGMENTATION_LINE_DETECTION_HPP_
