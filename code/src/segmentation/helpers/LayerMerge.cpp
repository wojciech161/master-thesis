#include "segmentation/helpers/LayerMerge.hpp"
#include <iostream>

namespace segmentation
{
namespace helpers
{

LayerMerge::LayerMerge( boost::shared_ptr<cv::Mat> background, boost::shared_ptr<cv::Mat> contour )
 : backgroundImage_( background )
 , contourImage_( contour )
{
    std::cout << "UTILITY: LayerMerge - created\n";
}

LayerMerge::~LayerMerge()
{   
    std::cout << "UTILITY: LayerMerge - applied\n";
}

boost::shared_ptr<cv::Mat> LayerMerge::apply() const
{
    if( isInputValid() )
    {
        return merge();
    }
    else
    {
        std::cout << "ERROR: Sizes of contour and background images are not equal";
    }

    return contourImage_;
}

bool LayerMerge::isInputValid() const
{
    return ( contourImage_->cols == backgroundImage_->cols
                && contourImage_->rows == backgroundImage_->rows );
}

boost::shared_ptr<cv::Mat> LayerMerge::merge() const
{
    boost::shared_ptr<cv::Mat> result = backgroundImage_;

    // Substitute result image pixels with colors of groups
    for( int row = 0; row < result->rows; ++row )
    {
        for( int col = 0; col < result->cols; ++col )
        {
            cv::Vec3b contourPx = contourImage_->at<cv::Vec3b>( row, col );
            helpers::Color contourColor( contourPx );
            if( !isWhite( contourColor ) )
            {
                result->at<cv::Vec3b>( row, col ) = contourColor.toVec3b();
            }
        }
    }

    return result;
}

bool LayerMerge::isWhite( const Color& c ) const
{
    const int WHITE_VALUE = 250;
    if( c.getRed() >= WHITE_VALUE && c.getGreen() >= WHITE_VALUE && c.getBlue() >= WHITE_VALUE )
    {
        return true;
    }

    return false;
}
    
} // namespace helpers
} // namespace segmentation
