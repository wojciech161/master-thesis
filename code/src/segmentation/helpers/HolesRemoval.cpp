#include "segmentation/helpers/HolesRemoval.hpp"
#include <boost/foreach.hpp>
#include <iostream>
#include <algorithm>

#define foreach BOOST_FOREACH

namespace segmentation
{
namespace helpers
{

struct PairCompare
{
    PairCompare( const Color& c ) : c_(c) { }

    bool operator () ( std::pair<Color, int> const& p )
    {
        return ( p.first == c_ );
    }

    const Color& c_;
};

HolesRemoval::HolesRemoval()
{
    std::cout << "HR begin\n";
}

HolesRemoval::~HolesRemoval()
{
    std::cout << "HR end\n";
}

boost::shared_ptr<cv::Mat> HolesRemoval::apply( const boost::shared_ptr<cv::Mat> input ) const
{
    boost::shared_ptr<cv::Mat> result( new cv::Mat( input->clone() ) );

    for( int row = 0; row < result->rows; ++row )
    {
        for( int col = 0; col < result->cols; ++col )
        {
            cv::Vec3b& inPx = result->at<cv::Vec3b>( row, col );
            removeHole( row, col, inPx, input );
        }
    }

    return result;
}

void HolesRemoval::removeHole( int row, int col, cv::Vec3b& changedPixel, const boost::shared_ptr<cv::Mat> image ) const
{
    const int WINDOW_WIDTH = 5;

    Color pxColor( changedPixel );

    std::list<Color> window = getWindow( row, col, WINDOW_WIDTH, image );
    if( !window.empty() )
    {
        pxColor = getPixelColor( window, pxColor );
    }

    changedPixel[2] = pxColor.getRed();
    changedPixel[1] = pxColor.getGreen();
    changedPixel[0] = pxColor.getBlue();
}

std::list<Color> HolesRemoval::getWindow(
    int row,
    int col,
    int width,
    const boost::shared_ptr<cv::Mat> image ) const
{
    std::list<Color> result;

    for( int i = 0 ; i < width ; ++i )
    {
        for( int j = 0 ; j < width ; ++j )
        {
            int windowRow = row - width/2 + i;
            int windowCol = col - width/2 + j;
            if( windowRow >= 0 && windowCol >= 0 &&
                windowRow < image->rows && windowCol < image->cols )
            {
                Color c( image->at<cv::Vec3b>( windowRow, windowCol ) );
                result.push_back( c );
            }
        }
    }

    return result;
}

Color HolesRemoval::getPixelColor( const std::list<Color>& colors, const Color& current ) const
{
    Color result( current );
    std::list< std::pair<Color, int> > colorCounter;
    int max = 0;

    foreach( const Color& c, colors )
    {
        std::list< std::pair<Color, int> >::iterator iter = 
            std::find_if( colorCounter.begin(), colorCounter.end(), PairCompare( c ) );

        if( iter != colorCounter.end() )
        {
            ++iter->second;
        }
        else
        {
            std::pair<Color, int> newPair( c, 1 );
            colorCounter.push_back( newPair );
        }

        if( iter->second > max )
        {
            result = c;
            max = iter->second;
        }
    }

    return result;
}

} // namespace helpers
} // namespace segmentation
