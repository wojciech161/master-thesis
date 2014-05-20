#include "filtration/ElliminateWhiteNoise.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/photo/photo.hpp>

namespace filtration
{

ElliminateWhiteNoise::ElliminateWhiteNoise()
{
    std::cout << "FILTRATION: ElliminateWhiteNoise - created\n";
}

ElliminateWhiteNoise::~ElliminateWhiteNoise()
{
    std::cout << "FILTRATION: ElliminateWhiteNoise - applied\n";
}

boost::shared_ptr<cv::Mat> ElliminateWhiteNoise::apply( boost::shared_ptr<cv::Mat> input ) const
{
    const int DENOISING_FACTOR = 50;

    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    cv::fastNlMeansDenoising( *input, *result, DENOISING_FACTOR );
    return result;
}


} // namespace filtration
