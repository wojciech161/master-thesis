#ifndef SEGMENTATION_HELPERS_CONTOUR_COLOR_RESTORATION_HPP_
#define SEGMENTATION_HELPERS_CONTOUR_COLOR_RESTORATION_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <boost/shared_ptr.hpp>
#include "Color.hpp"

namespace segmentation
{
namespace helpers
{

class ContourColorRestoration
{
public:
    ContourColorRestoration( boost::shared_ptr<cv::Mat>, boost::shared_ptr<cv::Mat> );
    ~ContourColorRestoration();

    boost::shared_ptr<cv::Mat> apply();

private:
    bool sizesOfInputImagesAreEqual();
    bool isDark( const Color& );

private:
    boost::shared_ptr<cv::Mat> colorImage_;
    boost::shared_ptr<cv::Mat> blackAndWhiteImage_;
};

} // namespace helpers
} // namespace segmentation

#endif
