#ifndef SEGMENTATION_COLOR_SEGMENTATION_HPP_
#define SEGMENTATION_COLOR_SEGMENTATION_HPP_

#include "ISegmentationAlgorithm.hpp"

namespace segmentation
{
    
class ColorSegmentation : public ISegmentationAlgorithm
{
public:
    ColorSegmentation();
    ~ColorSegmentation();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    int threshold_;

// CONST MEMBERS
private:
    const int MIN_NUMBER_OF_COLORS;
    const int MAX_NUMBER_OF_COLORS;
};

} // namespace segmentation

#endif // SEGMENTATION_COLOR_SEGMENTATION_HPP_
