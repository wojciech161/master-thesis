#include "segmentation/helpers/ImageGenerator.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace segmentation
{
namespace helpers
{

ImageGenerator::ImageGenerator( boost::shared_ptr<cv::Mat> input, const ColorGroup& colorGroup )
 : result_( new cv::Mat( input->clone() ) )
{
    std::cout << "UTILITY: ImageGenerator - created\n";
    for( int row = 0; row < input->rows; ++row )
    {
        for( int col = 0; col < input->cols; ++col )
        {
            cv::Vec3b inPx = input->at<cv::Vec3b>( row, col );
            helpers::Color inColor( inPx );
            helpers::Color outColor = colorGroup.getGroupColor( inColor );
            result_->at<cv::Vec3b>( row, col ) = outColor.toVec3b();
        }
    }
}

ImageGenerator::~ImageGenerator()
{
    std::cout << "UTILITY: ImageGenerator - applied\n";
}

boost::shared_ptr<cv::Mat> ImageGenerator::getImage() const
{
    return result_;
}

} // namespace helpers
} // namespace segmentation
