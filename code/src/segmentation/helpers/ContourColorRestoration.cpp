#include "segmentation/helpers/ContourColorRestoration.hpp"
#include <iostream>

namespace segmentation
{
namespace helpers
{

ContourColorRestoration::ContourColorRestoration(
    boost::shared_ptr<cv::Mat> colorImage,
    boost::shared_ptr<cv::Mat> blackAndWhiteImage )
 : colorImage_( colorImage )
 , blackAndWhiteImage_( blackAndWhiteImage )
{
}

ContourColorRestoration::~ContourColorRestoration()
{
}

boost::shared_ptr<cv::Mat> ContourColorRestoration::apply()
{
    if ( !sizesOfInputImagesAreEqual() )
    {
        return blackAndWhiteImage_;
    }

    boost::shared_ptr<cv::Mat> result( new cv::Mat( colorImage_->clone() ) );

    for( int row = 0; row < colorImage_->rows; ++row )
    {
        for( int col = 0; col < colorImage_->cols; ++col )
        {
            cv::Vec3b bwPx = blackAndWhiteImage_->at<cv::Vec3b>( row, col );
            helpers::Color bwColor( bwPx );
            
            if( !isDark( bwColor ) )
            {
                result->at<cv::Vec3b>( row, col )[0] = 255;
                result->at<cv::Vec3b>( row, col )[1] = 255;
                result->at<cv::Vec3b>( row, col )[2] = 255;
            }
        }
    }

    return result;
}

bool ContourColorRestoration::sizesOfInputImagesAreEqual()
{
    if( colorImage_->cols == blackAndWhiteImage_->cols &&
        colorImage_->rows == blackAndWhiteImage_->rows )
    {
        return true;    
    }

    std::cout << "ContourColorRestoration - ERROR - Sizes of input images are NOT equal\n";

    return false;
}

bool ContourColorRestoration::isDark( const Color& c )
{
    const int BW_THRESHOLD = 75;
    if( c.getRed() < BW_THRESHOLD && c.getGreen() < BW_THRESHOLD && c.getBlue() < BW_THRESHOLD )
    {
        return true;
    }

    return false;
}

} // namespace helpers
} // namespace segmentation
