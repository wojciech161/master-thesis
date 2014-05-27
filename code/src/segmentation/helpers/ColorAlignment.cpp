#include "segmentation/helpers/ColorAlignment.hpp"
#include "filtration/ApplyBilateralFilter.hpp"
#include "filtration/ApplyGaussianFilter.hpp"
#include "filtration/UnsharpMask.hpp"
#include "segmentation/helpers/ColorGroup.hpp"

namespace segmentation
{
namespace helpers
{
    
ColorAlignment::ColorAlignment()
{

}

ColorAlignment::~ColorAlignment()
{

}

boost::shared_ptr<cv::Mat> ColorAlignment::apply( const boost::shared_ptr<cv::Mat> image ) const
{
    const int BILATERAL_FILTER_COUNTER = 5;
    const int GAUSSIAN_BLUR_RADIUS = 3;
    const int INITIAL_THRESHOLD = 10;
    const int MINIMAL_COLOR_AREA = 500;
    const int MAX_NUMBER_OF_COLORS = 30;
    const int DIAMETER = 20;
    const int SIGMA_COLOR = 75;
    const int SIGMA_SPACE = 50;
    
    boost::shared_ptr<cv::Mat> result( new cv::Mat( image->clone() ) );

    // First apply bilateral filter multiple times
    for( int i = 0 ; i < BILATERAL_FILTER_COUNTER ; ++i )
    {
        result = 
            filtration::ApplyBilateralFilter( DIAMETER, SIGMA_COLOR, SIGMA_SPACE ).apply( result );
    }

    // Next, apply Gaussian Filter and unsharp mask to remove some holes
    result = filtration::ApplyGaussianFilter( GAUSSIAN_BLUR_RADIUS ).apply( result );
    result = filtration::UnsharpMask().apply( result );

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
            cv::Vec3b inPx = result->at<cv::Vec3b>( row, col );
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