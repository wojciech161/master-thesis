#ifndef SEGMENTATION_HELPERS_CONTOUR_MERGE_HPP_
#define SEGMENTATION_HELPERS_CONTOUR_MERGE_HPP_

#include <boost/shared_ptr.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace segmentation
{
namespace helpers
{

class ContourMerge
{
public:
    ContourMerge( boost::shared_ptr<cv::Mat>,
                  boost::shared_ptr<cv::Mat>,
                  boost::shared_ptr<cv::Mat> );
    ~ContourMerge();

    boost::shared_ptr<cv::Mat> apply() const;

private:
    bool isBlack( const cv::Vec3b& ) const;

private:
    boost::shared_ptr<cv::Mat> redContour_;
    boost::shared_ptr<cv::Mat> greenContour_;
    boost::shared_ptr<cv::Mat> blueContour_;
};

} // namespace helpers
} // namespace segmentation

#endif // SEGMENTATION_HELPERS_CONTOUR_MERGE_HPP_
