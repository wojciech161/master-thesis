#include "filtration/ApplyGaussianFilter.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

ApplyGaussianFilter::ApplyGaussianFilter( int blurRadius, int standardDeviation )
 : blurRadius_( blurRadius )
 , standardDeviation_( standardDeviation )
{
    std::cout << "FILTRATION: ApplyGaussianFilter - created\n";
}

ApplyGaussianFilter::~ApplyGaussianFilter()
{
    std::cout << "FILTRATION: ApplyGaussianFilter - applied\n";
}

boost::shared_ptr<cv::Mat> ApplyGaussianFilter::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( input->clone() ) );

    try
    {
        cv::GaussianBlur(
            *input,
            *result,
            cv::Size( blurRadius_, blurRadius_ ),
            standardDeviation_,
            standardDeviation_ );
    }
    catch( cv::Exception& e )
    {
        std::cout << "FILTRATION: ApplyGaussianFilter - ERROR:\n";
        std::cout << e.err << std::endl;
        std::cout << e.msg << std::endl;
    }

    return result;
}

} // namespace filtration
