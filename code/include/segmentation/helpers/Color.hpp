#ifndef SEGMENTATION_HELPERS_COLOR_HPP_
#define SEGMENTATION_HELPERS_COLOR_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace segmentation
{
namespace  helpers
{
    
// This class represents color of single pixel
class Color
{
public:
    Color( int, int, int );
    Color( const cv::Vec3b& );
    ~Color();

    int getRed() const;
    int getGreen() const;
    int getBlue() const;

    cv::Vec3b toVec3b() const;

private:
    int red_;
    int green_;
    int blue_;
};

} // namespace helpers
} // namespace segmentation

#endif
