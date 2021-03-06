#include "filtration/UnsharpMask.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{
    
UnsharpMask::UnsharpMask( int standardDeviation )
 : standardDeviation_( standardDeviation )
{
    std::cout << "FILTRATION: UnsharpMask - created\n";
}

UnsharpMask::~UnsharpMask()
{
    std::cout << "FILTRATION: UnsharpMask - applied\n";
}

boost::shared_ptr<cv::Mat> UnsharpMask::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    cv::Mat tmpImage;

    int blurWidth = 5;
    int blurHeight = 5;

    cv::GaussianBlur(
        *input,
        tmpImage,
        cv::Size( blurWidth, blurHeight ),
        standardDeviation_ );

    cv::addWeighted( *input, 2.5, tmpImage, -1.5, 0, *result );

    return result;
}


} // namespace filtration
