#include "segmentation/helpers/ColorAlignment.hpp"
#include "filtration/ApplyBilateralFilter.hpp"
#include "filtration/ApplyGaussianFilter.hpp"
#include "filtration/UnsharpMask.hpp"
#include "segmentation/helpers/ColorGroup.hpp"

namespace segmentation
{
namespace helpers
{
    
ColorAlignment::ColorAlignment( const LineDetectionParams& parameters )
 : parameters_( parameters )
{
    std::cout << "SEGMENTATION: ColorAlignment - created\n";
}

ColorAlignment::~ColorAlignment()
{
    std::cout << "SEGMENTATION: ColorAlignment - applied\n";
}

boost::shared_ptr<cv::Mat> ColorAlignment::apply( const boost::shared_ptr<cv::Mat> image ) const
{
    const int BILATERAL_FILTER_COUNTER = parameters_.bilateralFilterCounter;
    const int GAUSSIAN_BLUR_RADIUS = parameters_.gaussianBlurRadius;
    const int GAUSSIAN_BLUR_STANDARD_DEVIATION = parameters_.gaussianBlurStandardDeviation;
    const int GAUSSIAN_BLUR_COUNTER = parameters_.gaussianBlurCounter;
    const int INITIAL_THRESHOLD = parameters_.initialThreshold;
    const int MINIMAL_COLOR_AREA = parameters_.mimimalColorArea;
    const int MAX_NUMBER_OF_COLORS = parameters_.maxNumberOfColors;
    const int DIAMETER = parameters_.diameter;
    const int SIGMA_COLOR = parameters_.sigmaColor;
    const int SIGMA_SPACE = parameters_.sigmaSpace;
    
    boost::shared_ptr<cv::Mat> result( new cv::Mat( image->clone() ) );

    // First apply bilateral filter multiple times
    for( int i = 0 ; i < BILATERAL_FILTER_COUNTER ; ++i )
    {
        result = 
            filtration::ApplyBilateralFilter( DIAMETER, SIGMA_COLOR, SIGMA_SPACE ).apply( result );
    }

    // Next, apply Gaussian Filter and unsharp mask to remove some holes
    for( int i = 0 ; i < GAUSSIAN_BLUR_COUNTER ; ++i )
    {
        result = filtration::ApplyGaussianFilter( 
            GAUSSIAN_BLUR_RADIUS, GAUSSIAN_BLUR_STANDARD_DEVIATION ).apply( result );
    }

    // Create groups of colors
    helpers::ColorGroup colorGroup( INITIAL_THRESHOLD );

    for( int row = 0; row < image->rows; ++row )
    {
        for( int col = 0; col < image->cols; ++col )
        {
            cv::Vec3b px = image->at<cv::Vec3b>( row, col );
            helpers::Color pxColor( px );
            if( !isWhite( pxColor ) )
            {
                colorGroup.addToGroup( pxColor );
            }
        }
    }

    // Merge similar groups
    int mergeThreshold = INITIAL_THRESHOLD;

    do
    {
        colorGroup.mergeGroupsToThreshold( mergeThreshold );
        ++mergeThreshold;
    } while ( colorGroup.getNumberOfGroups() > MAX_NUMBER_OF_COLORS );

    colorGroup.removeSmallAreaColors( MINIMAL_COLOR_AREA );

    colorGroup.printAllContainers();

    // Substitute result image pixels with colors of groups
    for( int row = 0; row < result->rows; ++row )
    {
        for( int col = 0; col < result->cols; ++col )
        {
            cv::Vec3b inPx = image->at<cv::Vec3b>( row, col );
            helpers::Color inColor( inPx );
            if( !isWhite( inColor ) )
            {
                helpers::Color outColor = colorGroup.getGroupColor( inColor );
                result->at<cv::Vec3b>( row, col ) = outColor.toVec3b();
            }
        }
    }

    return result;
}

bool ColorAlignment::isWhite( const Color& c ) const
{
    const int WHITE_BORDER_VALUE = 240;
    if( c.getRed() >= WHITE_BORDER_VALUE && c.getGreen() >= WHITE_BORDER_VALUE && c.getBlue() >= WHITE_BORDER_VALUE )
    {
        return true;
    }

    return false;
}

} // namespace helpers
} // namespace segmentation
