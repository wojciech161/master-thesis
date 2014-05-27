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

ColorSegmentation::ColorSegmentation()
    : threshold_( 30 )
    , MIN_NUMBER_OF_COLORS( 5 )
    , MAX_NUMBER_OF_COLORS( 30 )
{
    std::cout << "SEGMENTATION: ColorSegmentation - created\n";
}

ColorSegmentation::~ColorSegmentation()
{
    std::cout << "SEGMENTATION: ColorSegmentation - applied\n";
}

boost::shared_ptr<cv::Mat> ColorSegmentation::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int GAUSSIAN_BLUR_RADIUS = 7;
    const int DIAMETER = 20;
    const int SIGMA_COLOR = 150;
    const int SIGMA_SPACE = 150;
    const int DILATION_AND_EROSION_SIZE = 3;
    const int DILATION_AND_EROSION_COUNTER = 4;
    boost::shared_ptr<cv::Mat> result = input;

    // First, we apply a bilateral and gaussian filters to remove noises from maps
    result = filtration::ApplyGaussianFilter( GAUSSIAN_BLUR_RADIUS ).apply( result );

    for( int i = 0 ; i < DILATION_AND_EROSION_COUNTER ; ++i )
    {
        result = 
            filtration::Dilation( DILATION_AND_EROSION_SIZE ).apply( result );
    }

    for( int i = 0 ; i < DILATION_AND_EROSION_COUNTER; ++i )
    {
        result = 
            filtration::Erosion( DILATION_AND_EROSION_SIZE ).apply( result );  
    }

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

    result = helpers::HolesRemoval().apply( result );

    return result;
}

    
} // namespace segmentation
