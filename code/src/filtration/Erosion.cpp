#include "filtration/Erosion.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

Erosion::Erosion( int erosionSize )
 : erosionSize_( erosionSize )
{
    std::cout << "FILTRATION: Erosion - created\n";
}

Erosion::~Erosion()
{
    std::cout << "FILTRATION: Erosion - applied\n";
}

boost::shared_ptr<cv::Mat> Erosion::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );

    cv::Mat element = cv::getStructuringElement(
        cv::MORPH_RECT,
        cv::Size( 2 * erosionSize_ + 1, 2 * erosionSize_ + 1 ),
        cv::Point( erosionSize_, erosionSize_ )  );

    cv::erode( *input, *result, element );

    return result;
}


} // namespace filtration
