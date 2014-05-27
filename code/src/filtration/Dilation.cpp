#include "filtration/Dilation.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

Dilation::Dilation( int size )
 : dilationSize_( size )
{
    std::cout << "FILTRATION: Dilation - created\n";
}

Dilation::~Dilation()
{
    std::cout << "FILTRATION: Dilation - applied\n";
}

boost::shared_ptr<cv::Mat> Dilation::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );   

    cv::Mat element = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size( 2 * dilationSize_ + 1, 2 * dilationSize_ + 1 ),
        cv::Point( dilationSize_, dilationSize_ )  );

    cv::dilate( *input, *result, element );

    return result;
}


} // namespace filtration
