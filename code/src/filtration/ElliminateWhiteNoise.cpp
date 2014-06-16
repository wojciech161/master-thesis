#include "filtration/ElliminateWhiteNoise.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>

namespace filtration
{

ElliminateWhiteNoise::ElliminateWhiteNoise( int denoisingFactor )
 : denoisingFactor_( denoisingFactor )
{
    std::cout << "FILTRATION: ElliminateWhiteNoise - created\n";
}

ElliminateWhiteNoise::~ElliminateWhiteNoise()
{
    std::cout << "FILTRATION: ElliminateWhiteNoise - applied\n";
}

boost::shared_ptr<cv::Mat> ElliminateWhiteNoise::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    cv::fastNlMeansDenoisingColored( *input, *result, denoisingFactor_ );
    return result;
}


} // namespace filtration
