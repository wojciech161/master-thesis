#ifndef SEGMENTATION_HELPERS_HOLES_REMOVAL_HPP_
#define SEGMENTATION_HELPERS_HOLES_REMOVAL_HPP_

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <boost/shared_ptr.hpp>
#include <list>
#include "Color.hpp"

namespace segmentation
{
namespace helpers
{

class HolesRemoval
{
public:
    HolesRemoval();
    ~HolesRemoval();

    boost::shared_ptr<cv::Mat> apply( const boost::shared_ptr<cv::Mat> ) const;

private:
    void removeHole( int, int, cv::Vec3b&, const boost::shared_ptr<cv::Mat> ) const;
    std::list<Color> getWindow( int, int, int, const boost::shared_ptr<cv::Mat> ) const;
    Color getPixelColor( const std::list<Color>&, const Color& ) const;
};

} // namespace helpers
} // namespace segmentation

#endif // SEGMENTATION_HELPERS_HOLES_REMOVAL_HPP_
