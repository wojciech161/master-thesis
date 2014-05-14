#include "segmentation/ColorSegmentation.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "segmentation/helpers/ColorGroup.hpp"
#include "segmentation/helpers/ImageGenerator.hpp"
#include "filtration/ApplyBilateralFilter.hpp"
#include "filtration/ApplyGaussianFilter.hpp"

namespace segmentation
{

ColorSegmentation::ColorSegmentation()
    : threshold_( 30 )
    , MIN_NUMBER_OF_COLORS( 5 )
    , MAX_NUMBER_OF_COLORS( 200 )
{
    std::cout << "SEGMENTATION: ColorSegmentation - created\n";
}

ColorSegmentation::~ColorSegmentation()
{
    std::cout << "SEGMENTATION: ColorSegmentation - applied\n";
}

boost::shared_ptr<cv::Mat> ColorSegmentation::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result;

    // First, we apply a bilateral and gaussian filters to remove noises from maps
    boost::shared_ptr<cv::Mat> filteredImage;
    filteredImage = filtration::ApplyBilateralFilter().apply( input );
    filteredImage = filtration::ApplyGaussianFilter().apply( filteredImage );

    helpers::ColorGroup colorGroup( threshold_ );

    double numberOfPixels = static_cast<double>(input->rows * input->cols);
    double done = 0.0;

    for( int row = 0; row < input->rows; ++row )
    {
        for( int col = 0; col < input->cols; ++col )
        {
            cv::Vec3b px = input->at<cv::Vec3b>( row, col );
            helpers::Color pxColor( px );
            colorGroup.addToGroup( pxColor );
            done += 1.0;
            std::cout << "Done: " << ((done / numberOfPixels) * 100) << " percent               \r";
        }
    }

    std::cout << "NOG: " << colorGroup.getNumberOfGroups() << std::endl;

    int newThreshold = threshold_;

    do
    {
        colorGroup.mergeGroupsToThreshold( newThreshold );
        std::cout << "Threshold: " << newThreshold << std::endl;
        std::cout << "NOG: " << colorGroup.getNumberOfGroups() << std::endl;
        ++newThreshold;
    } while ( colorGroup.getNumberOfGroups() > MAX_NUMBER_OF_COLORS );

    colorGroup.printAllContainers();
    std::cout << "NOG: " << colorGroup.getNumberOfGroups() << std::endl;

    result = helpers::ImageGenerator( input, colorGroup ).getImage();

    return result;
}

    
} // namespace segmentation
