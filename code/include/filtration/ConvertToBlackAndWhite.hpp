#ifndef FILTRATION_CONVERT_TO_BLACK_AND_WHITE_HPP_
#define FILTRATION_CONVERT_TO_BLACK_AND_WHITE_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

enum EConversionType
{
    EConversionType_All,
    EConversionType_Red,
    EConversionType_Green,
    EConversionType_Blue
};

enum EColor
{
    EColor_Red,
    EColor_Green,
    EColor_Blue
};

class ConvertToBlackAndWhite : public IFiltrationAlgorithm
{
public:
    ConvertToBlackAndWhite( EConversionType );
    ~ConvertToBlackAndWhite();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    boost::shared_ptr<cv::Mat> convertAll( boost::shared_ptr<cv::Mat> ) const;
    boost::shared_ptr<cv::Mat> convertRed( boost::shared_ptr<cv::Mat> ) const;
    boost::shared_ptr<cv::Mat> convertGreen( boost::shared_ptr<cv::Mat> ) const;
    boost::shared_ptr<cv::Mat> convertBlue( boost::shared_ptr<cv::Mat> ) const;

private:
    EConversionType conversion_;
};

}

#endif
