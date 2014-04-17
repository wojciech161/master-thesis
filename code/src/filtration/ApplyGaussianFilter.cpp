#include "filtration/ApplyGaussianFilter.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

ApplyGaussianFilter::ApplyGaussianFilter()
{
    std::cout << "FILTRATION: ApplyGaussianFilter - created\n";
}

ApplyGaussianFilter::~ApplyGaussianFilter()
{
    std::cout << "FILTRATION: ApplyGaussianFilter - applied\n";
}

boost::shared_ptr<cv::Mat> ApplyGaussianFilter::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int STANDARD_DEVIATION = 0;
    boost::shared_ptr<cv::Mat> result( new cv::Mat( input->clone() ) );

    int blurWidth = getBlurWidth( input->rows, input->cols );
    int blurHeight = getBlurHeight( input->rows, input->cols );

    try
    {
        cv::GaussianBlur(
            *input,
            *result,
            cv::Size( blurWidth, blurHeight ),
            STANDARD_DEVIATION,
            STANDARD_DEVIATION );
    }
    catch( cv::Exception& e )
    {
        std::cout << "FILTRATION: ApplyGaussianFilter - ERROR:\n";
        std::cout << e.err << std::endl;
        std::cout << e.msg << std::endl;
    }

    return result;
}

int ApplyGaussianFilter::getBlurWidth( int rows, int cols ) const
{
    return 3;
}

int ApplyGaussianFilter::getBlurHeight( int rows, int cols ) const
{
    return 3;
}

} // namespace filtration
