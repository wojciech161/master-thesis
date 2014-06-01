#include "segmentation/helpers/ContourMerge.hpp"
#include <iostream>

namespace segmentation
{
namespace helpers
{

ContourMerge::ContourMerge( boost::shared_ptr<cv::Mat> redContour,
              boost::shared_ptr<cv::Mat> greenContour,
              boost::shared_ptr<cv::Mat> blueContour )
 : redContour_( redContour )
 , greenContour_( greenContour )
 , blueContour_( blueContour )
{
    std::cout << "UTILITY: ContourMerge - created\n";
}

ContourMerge::~ContourMerge()
{
    std::cout << "UTILITY: ContourMerge - applied\n";
}

boost::shared_ptr<cv::Mat> ContourMerge::apply() const
{
    const int BLACK_VALUE = 0;

    boost::shared_ptr<cv::Mat> result( new cv::Mat( redContour_->clone() ) );

    for( int row = 0; row < result->rows; ++row )
    {
        for( int col = 0; col < result->cols; ++col )
        {
            cv::Vec3b red = redContour_->at<cv::Vec3b>( row, col );
            cv::Vec3b green = greenContour_->at<cv::Vec3b>( row, col );
            cv::Vec3b blue  = blueContour_->at<cv::Vec3b>( row, col );

            if( isBlack( red ) || isBlack( green ) || isBlack( blue )  )
            {
                result->at<cv::Vec3b>( row, col )[0] = BLACK_VALUE;
                result->at<cv::Vec3b>( row, col )[1] = BLACK_VALUE;
                result->at<cv::Vec3b>( row, col )[2] = BLACK_VALUE;
            }
        }
    }

    return result;
}

bool ContourMerge::isBlack( const cv::Vec3b& color ) const
{
    const int BLACK_VALUE = 0;

    return ( color[0] == BLACK_VALUE && color[1] == BLACK_VALUE && color[2] == BLACK_VALUE );
}

} // namespace helpers
} // namespace segmentation
