#ifndef SEGMENTATION_HELPERS_LAYER_MERGE_HPP_
#define SEGMENTATION_HELPERS_LAYER_MERGE_HPP_

#include <boost/shared_ptr.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Color.hpp"

namespace segmentation
{
namespace helpers
{

class LayerMerge
{
public:
    LayerMerge( boost::shared_ptr<cv::Mat>, boost::shared_ptr<cv::Mat> );
    ~LayerMerge();

    boost::shared_ptr<cv::Mat> apply() const;

private:
    bool isInputValid() const;
    boost::shared_ptr<cv::Mat> merge() const;
    bool isWhite( const Color& ) const;

private:
    const boost::shared_ptr<cv::Mat> backgroundImage_;
    const boost::shared_ptr<cv::Mat> contourImage_;
};

} // namespace helpers
} // namespace segmentation

#endif // SEGMENTATION_HELPERS_LAYER_MERGE_HPP_
