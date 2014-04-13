#include "filtration/ConvertToBlackAndWhite.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

namespace filtration
{

ConvertToBlackAndWhite::ConvertToBlackAndWhite()
{
    std::cout << "FILTRATION: ConvertToBlackAndWhite - created\n";
}

ConvertToBlackAndWhite::~ConvertToBlackAndWhite()
{
    std::cout << "FILTRATION: ConvertToBlackAndWhite - destructed\n";
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::apply( const cv::Mat& inputImage ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    cv::cvtColor( inputImage, *result, CV_RGB2GRAY );
    std::cout << "FILTRATION: ConvertToBlackAndWhite - applied\n";
    return result;
}

} // namespace filtration
