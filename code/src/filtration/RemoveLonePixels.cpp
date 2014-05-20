#include "filtration/RemoveLonePixels.hpp"
#include <iostream>
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH

namespace filtration
{

RemoveLonePixels::RemoveLonePixels()
{
    std::cout << "FILTRATION: RemoveLonePixels - created\n";
}

RemoveLonePixels::~RemoveLonePixels()
{
    std::cout << "FILTRATION: RemoveLonePixels - applied\n";
}

boost::shared_ptr<cv::Mat> RemoveLonePixels::apply( boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( input->clone() ) );

    for( int row = 0; row < input->rows; ++row )
    {
        for( int col = 0; col < input->cols; ++col )
        {
            cv::Vec3b& pixel = result->at<cv::Vec3b>( row, col );
            
            if ( !isImageBorder( row, col, input->rows, input->cols ) )
            {
                if( isWhite( pixel ) )
                {
                    if ( shouldBeColored( row, col, result ) )
                    {
                        colorPixel( pixel, row, col, result );
                    }
                }
                else
                {
                    if( isLonely( row, col, result ) )
                    {
                        whitenPixel( pixel );
                    }
                }   
            }
        }
    }

    return result;
}

bool RemoveLonePixels::isImageBorder( 
    int row,
    int col,
    int allRows,
    int allCols ) const
{
    if ( 
        row == 0 ||
        col == 0 ||
        row == allRows - 1 ||
        col == allCols - 1 )
    {
        return true;
    }

    return false;
}

bool RemoveLonePixels::isWhite( const cv::Vec3b& pixel ) const
{
    const int THRESHOLD = 250;
    if( 
        pixel[0] >=THRESHOLD &&
        pixel[1] >=THRESHOLD &&
        pixel[2] >=THRESHOLD )
    {
        return true;
    }

    return false;
}

bool RemoveLonePixels::isLonely(
    int row,
    int col,
    boost::shared_ptr<cv::Mat> image ) const
{
    std::list<cv::Vec3b> roundPixels;
    getRoundPixels( row, col, image, roundPixels );

    foreach( const cv::Vec3b& pixel, roundPixels )
    {
        if( !isWhite( pixel ) )
        {
            return false;
        }
    }

    return true;
}

bool RemoveLonePixels::shouldBeColored(
    int row,
    int col,
    boost::shared_ptr<cv::Mat> image ) const
{
    std::list<cv::Vec3b> roundPixels;
    getRoundPixels( row, col, image, roundPixels );

    foreach( const cv::Vec3b& pixel, roundPixels )
    {
        if( isWhite( pixel ) )
        {
            return false;
        }
    }

    return true;
}

void RemoveLonePixels::colorPixel( 
    cv::Vec3b& pixel,
    int row,
    int col,
    boost::shared_ptr<cv::Mat> image ) const
{
    std::list<cv::Vec3b> roundPixels;
    getRoundPixels( row, col, image, roundPixels );

    double redSum = 0.0;
    double greenSum = 0.0;
    double blueSum = 0.0;

    foreach( const cv::Vec3b& px, roundPixels )
    {
        redSum += px[2];
        greenSum += px[1];
        blueSum += px[0];
    }

    pixel[0] = static_cast<int>( blueSum / 8.0 );
    pixel[1] = static_cast<int>( greenSum / 8.0 );
    pixel[2] = static_cast<int>( redSum / 8.0 );
}

void RemoveLonePixels::whitenPixel( cv::Vec3b& pixel ) const
{
    pixel[0] = 255;
    pixel[1] = 255;
    pixel[2] = 255;
}

void RemoveLonePixels::getRoundPixels(
    int row,
    int col,
    boost::shared_ptr<cv::Mat> image,
    std::list<cv::Vec3b>& result ) const
{
    result.push_back( image->at<cv::Vec3b>( row - 1, col - 1 ) );
    result.push_back( image->at<cv::Vec3b>( row    , col - 1 ) );
    result.push_back( image->at<cv::Vec3b>( row + 1, col - 1 ) );
    result.push_back( image->at<cv::Vec3b>( row - 1, col     ) );
    result.push_back( image->at<cv::Vec3b>( row + 1, col     ) );
    result.push_back( image->at<cv::Vec3b>( row - 1, col + 1 ) );
    result.push_back( image->at<cv::Vec3b>( row    , col + 1 ) );
    result.push_back( image->at<cv::Vec3b>( row + 1, col + 1 ) );
}

} // namespace filtration
