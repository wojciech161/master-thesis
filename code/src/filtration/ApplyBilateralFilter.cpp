#include "filtration/ApplyBilateralFilter.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

ApplyBilateralFilter::ApplyBilateralFilter( int diameter, int sigmaColor, int sigmaSpace )
 : diameter_( diameter )
 , sigmaColor_( sigmaColor )
 , sigmaSpace_( sigmaSpace )
{
    std::cout << "FILTRATION: ApplyBilateralFilter - created\n";
}

ApplyBilateralFilter::~ApplyBilateralFilter()
{
    std::cout << "FILTRATION: ApplyBilateralFilter - applied\n";
}

boost::shared_ptr<cv::Mat> ApplyBilateralFilter::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( input->clone() ) );

    try
    {
        cv::bilateralFilter( *input, *result, diameter_, sigmaColor_, sigmaSpace_ );    
    }
    catch( cv::Exception& e )
    {
        std::cout << "FILTRATION: ApplyBilateralFilter - ERROR:\n";
        std::cout << e.err << std::endl;
        std::cout << e.msg << std::endl;
    }
    

    return result;
}
    
} // namespace filtration
