#include "filtration/ConvertToBlackAndWhite.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

namespace filtration
{

ConvertToBlackAndWhite::ConvertToBlackAndWhite( EConversionType conversion )
 : conversion_( conversion )
{
    std::cout << "FILTRATION: ConvertToBlackAndWhite - created\n";
}

ConvertToBlackAndWhite::~ConvertToBlackAndWhite()
{
    std::cout << "FILTRATION: ConvertToBlackAndWhite - applied\n";
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::apply( 
    boost::shared_ptr<cv::Mat> inputImage ) const
{
    switch( conversion_ )
    {
    case EConversionType_All:
        return convertAll( inputImage );
        break;
    case EConversionType_Red:
        return convertRed( inputImage );
        break;
    case EConversionType_Green:
        return convertGreen( inputImage );
        break;
    case EConversionType_Blue:
        return convertBlue( inputImage );
        break;
    }

    return inputImage;
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::convertAll( boost::shared_ptr<cv::Mat> inputImage ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat() );
    boost::shared_ptr<cv::Mat> blackAndWhiteMode( new cv::Mat() );
    if( inputImage )
    {
        // Convert to black and white
        cv::cvtColor( *inputImage, *blackAndWhiteMode, CV_RGB2GRAY );

        // Convert black and white image to RGB mode
        cv::cvtColor( *blackAndWhiteMode, *result, cv::COLOR_GRAY2RGB );
    }

    return result;
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::convertRed( 
    boost::shared_ptr<cv::Mat> inputImage ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( inputImage->clone() ) );

    if( inputImage )
    {
        for( int row = 0; row < result->rows; ++row )
        {
            for( int col = 0; col < result->cols; ++col )
            {
                cv::Vec3b inColor = result->at<cv::Vec3b>( row, col );
                result->at<cv::Vec3b>( row, col )[1] = inColor[0];
                result->at<cv::Vec3b>( row, col )[2] = inColor[0];
            }
        }
    }

    return result;
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::convertGreen( 
    boost::shared_ptr<cv::Mat> inputImage ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( inputImage->clone() ) );

    if( inputImage )
    {
        for( int row = 0; row < result->rows; ++row )
        {
            for( int col = 0; col < result->cols; ++col )
            {
                cv::Vec3b inColor = result->at<cv::Vec3b>( row, col );
                result->at<cv::Vec3b>( row, col )[0] = inColor[1];
                result->at<cv::Vec3b>( row, col )[2] = inColor[1];
            }
        }
    }

    return result;
}

boost::shared_ptr<cv::Mat> ConvertToBlackAndWhite::convertBlue( 
    boost::shared_ptr<cv::Mat> inputImage ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( inputImage->clone() ) );

    if( inputImage )
    {
        for( int row = 0; row < result->rows; ++row )
        {
            for( int col = 0; col < result->cols; ++col )
            {
                cv::Vec3b inColor = result->at<cv::Vec3b>( row, col );
                result->at<cv::Vec3b>( row, col )[0] = inColor[2];
                result->at<cv::Vec3b>( row, col )[1] = inColor[2];
            }
        }
    }

    return result;
}


} // namespace filtration
