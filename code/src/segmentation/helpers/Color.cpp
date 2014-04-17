#include "segmentation/helpers/Color.hpp"

namespace segmentation
{
namespace helpers
{

Color::Color( int red, int green, int blue )
 : red_( red )
 , green_( green )
 , blue_( blue )
{

}

Color::Color( const cv::Vec3b& pixel )
 : red_( pixel[2] )
 , green_( pixel[1] )
 , blue_( pixel[0] )
{

}

Color::~Color()
{

}

int Color::getRed() const
{
    return red_;
}

int Color::getGreen() const
{
    return green_;
}

int Color::getBlue() const
{
    return blue_;
}

cv::Vec3b Color::toVec3b() const
{
    cv::Vec3b pixel;
    
    pixel[0] = blue_;
    pixel[1] = green_;
    pixel[2] = red_;

    return pixel;
}

} // namespace helpers
} // namespace segmentation
