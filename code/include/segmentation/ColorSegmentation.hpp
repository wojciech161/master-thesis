#ifndef SEGMENTATION_COLOR_SEGMENTATION_HPP_
#define SEGMENTATION_COLOR_SEGMENTATION_HPP_

#include "ISegmentationAlgorithm.hpp"
#include "core/Parameters.hpp"

namespace segmentation
{
    
class ColorSegmentation : public ISegmentationAlgorithm
{
public:
    ColorSegmentation( const ColorSegmentationParams& );
    ~ColorSegmentation();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    int threshold_;
    const ColorSegmentationParams& parameters_;
};

} // namespace segmentation

#endif // SEGMENTATION_COLOR_SEGMENTATION_HPP_
