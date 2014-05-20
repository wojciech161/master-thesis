#ifndef FILTRATION_REMOVE_LONE_PIXELS_HPP_
#define FILTRATION_REMOVE_LONE_PIXELS_HPP_

#include "IFiltrationAlgorithm.hpp"
#include <list>

namespace filtration
{

class RemoveLonePixels : public IFiltrationAlgorithm
{
public:
    RemoveLonePixels();
    ~RemoveLonePixels();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    bool isImageBorder( int, int, int, int ) const;
    bool isWhite( const cv::Vec3b& ) const;
    bool isLonely( int, int, boost::shared_ptr<cv::Mat> ) const;
    bool shouldBeColored( int, int, boost::shared_ptr<cv::Mat> ) const;
    void colorPixel( cv::Vec3b&, int, int, boost::shared_ptr<cv::Mat> ) const;
    void whitenPixel( cv::Vec3b& ) const;
    void getRoundPixels( int, int, boost::shared_ptr<cv::Mat>, std::list<cv::Vec3b>& ) const;
};

} // namespace filtration

#endif
