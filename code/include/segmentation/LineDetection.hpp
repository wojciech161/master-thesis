#ifndef SEGMENTATION_LINE_DETECTION_HPP_
#define SEGMENTATION_LINE_DETECTION_HPP_

#include "ISegmentationAlgorithm.hpp"
#include "core/Parameters.hpp"

namespace segmentation
{

class LineDetection : public ISegmentationAlgorithm
{
public:
    LineDetection( const LineDetectionParams& );
    ~LineDetection();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    const LineDetectionParams& parameters_;
};

} // namespace segmentation

#endif // SEGMENTATION_LINE_DETECTION_HPP_
