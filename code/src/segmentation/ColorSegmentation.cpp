#include "segmentation/ColorSegmentation.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "segmentation/helpers/ColorGroup.hpp"
#include "segmentation/helpers/ImageGenerator.hpp"
#include "filtration/ApplyBilateralFilter.hpp"
#include "filtration/ApplyGaussianFilter.hpp"
#include "filtration/Erosion.hpp"
#include "filtration/Dilation.hpp"
#include "segmentation/helpers/HolesRemoval.hpp"

namespace segmentation
{

ColorSegmentation::ColorSegmentation( const ColorSegmentationParams& parameters )
    : threshold_( 30 )
    , parameters_( parameters )
{
    std::cout << "SEGMENTATION: ColorSegmentation - created\n";
}

ColorSegmentation::~ColorSegmentation()
{
    std::cout << "SEGMENTATION: ColorSegmentation - applied\n";
}

boost::shared_ptr<cv::Mat> ColorSegmentation::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int GAUSSIAN_BLUR_RADIUS = parameters_.gaussianBlurRadius;
    const int GAUSSIAN_BLUR_STANDARD_DEVIATION = parameters_.gaussianBlurStandardDeviation;
    const int DIAMETER = parameters_.diameter;
    const int SIGMA_COLOR = parameters_.sigmaColor;
    const int SIGMA_SPACE = parameters_.sigmaSpace;
    const int DILATION_AND_EROSION_SIZE = parameters_.dilationAndErosionSize;
    const int EROSION_COUNTER = parameters_.dilationAndErosionCounter;
    const int DILATION_COUNTER = static_cast<int>( 2.5 * EROSION_COUNTER );
    const int WINDOW_WIDTH = parameters_.windowWidth;
    const int MAX_NUMBER_OF_COLORS = parameters_.maxNumberOfColors;

    boost::shared_ptr<cv::Mat> result = input;

    for( int i = 0 ; i < EROSION_COUNTER ; ++i )
    {
        result = 
            filtration::Erosion( DILATION_AND_EROSION_SIZE ).apply( result );
    }

    for( int i = 0 ; i < DILATION_COUNTER; ++i )
    {
        result = 
            filtration::Dilation( DILATION_AND_EROSION_SIZE ).apply( result );  
    }

    // First, we apply a bilateral and gaussian filters to remove noises from maps
    result = filtration::ApplyGaussianFilter(
        GAUSSIAN_BLUR_RADIUS, GAUSSIAN_BLUR_STANDARD_DEVIATION ).apply( result );

    for(int i = 0; i < 2 ; ++i)
    {
        result = 
            filtration::ApplyBilateralFilter( DIAMETER, SIGMA_COLOR, SIGMA_SPACE ).apply( result );
    }

    helpers::ColorGroup colorGroup( threshold_ );

    for( int row = 0; row < result->rows; ++row )
    {
        for( int col = 0; col < result->cols; ++col )
        {
            cv::Vec3b px = result->at<cv::Vec3b>( row, col );
            helpers::Color pxColor( px );
            colorGroup.addToGroup( pxColor );
        }
    }

    int newThreshold = threshold_;

    do
    {
        colorGroup.mergeGroupsToThreshold( newThreshold );
        ++newThreshold;
    } while ( colorGroup.getNumberOfGroups() > MAX_NUMBER_OF_COLORS );

    colorGroup.printAllContainers();

    result = helpers::ImageGenerator( result, colorGroup ).getImage();

    result = helpers::HolesRemoval( WINDOW_WIDTH ).apply( result );

    return result;
}

    
} // namespace segmentation
