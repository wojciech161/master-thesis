#ifndef FILTRATION_CONVERT_TO_BLACK_AND_WHITE_HPP_
#define FILTRATION_CONVERT_TO_BLACK_AND_WHITE_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class ConvertToBlackAndWhite : public IFiltrationAlgorithm
{
public:
    ConvertToBlackAndWhite();
    ~ConvertToBlackAndWhite();

    boost::shared_ptr<cv::Mat> apply( const cv::Mat& ) const;
};

}

#endif
