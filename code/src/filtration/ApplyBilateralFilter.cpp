#include "filtration/ApplyBilateralFilter.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace filtration
{

ApplyBilateralFilter::ApplyBilateralFilter()
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

    int diameter = computeDiameter( input->rows, input->cols );
    int sigmaColor = computeSigmaColor( input->rows, input->cols );
    int sigmaSpace = computeSigmaSpace( input->rows, input->cols );

    try
    {
        cv::bilateralFilter( *input, *result, diameter, sigmaColor, sigmaSpace );    
    }
    catch( cv::Exception& e )
    {
        std::cout << "FILTRATION: ApplyBilateralFilter - ERROR:\n";
        std::cout << e.err << std::endl;
        std::cout << e.msg << std::endl;
    }
    

    return result;
}

int ApplyBilateralFilter::computeDiameter( int rows, int cols ) const
{
    return 20;
}

int ApplyBilateralFilter::computeSigmaColor( int rows, int cols ) const
{
    return 75;
}

int ApplyBilateralFilter::computeSigmaSpace( int rows, int cols ) const
{
    return 50;
}

    
} // namespace filtration
