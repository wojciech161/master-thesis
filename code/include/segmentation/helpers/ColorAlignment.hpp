#ifndef SEGMENTATION_HELPERS_COLOR_ALIGNMENT_HPP_
#define SEGMENTATION_HELPERS_COLOR_ALIGNMENT_HPP_

#include <boost/shared_ptr.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "Color.hpp"
#include "core/Parameters.hpp"

namespace segmentation
{
namespace helpers
{

class ColorAlignment
{
public:
    ColorAlignment( const LineDetectionParams& );
    ~ColorAlignment();

    boost::shared_ptr<cv::Mat> apply( const boost::shared_ptr<cv::Mat> ) const;

private:
    bool isWhite( const Color& ) const;

private:
    const LineDetectionParams& parameters_;
};

} // namespace helpers
} // namespace segmentation 

#endif // SEGMENTATION_HELPERS_COLOR_ALIGNMENT_HPP_
