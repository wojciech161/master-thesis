#include "segmentation/helpers/ColorContainer.hpp"
#include <cmath>

namespace segmentation
{
namespace helpers
{

ColorContainer::ColorContainer()
 : numberOfColors_( 0 )
 , currentRedAverage_( 0 )
 , currentGreenAverage_( 0 )
 , currentBlueAverage_( 0 )
{
}

ColorContainer::ColorContainer( const Color& color )
 : numberOfColors_( 1 )
 , currentRedAverage_( color.getRed() )
 , currentGreenAverage_( color.getGreen() )
 , currentBlueAverage_( color.getBlue() )
{
}

ColorContainer::ColorContainer( const ColorContainer& container )
 : numberOfColors_( container.getNumberOfColors() )
 , currentRedAverage_( container.getCurrentRed() )
 , currentGreenAverage_( container.getCurrentGreen() )
 , currentBlueAverage_( container.getCurrentBlue() )
{
}

ColorContainer::~ColorContainer()
{

}

bool ColorContainer::isInRange( const Color& color, int threshold ) const
{
    double distance = getDistance( color );

    return ( distance <= threshold );
}

void ColorContainer::add( const Color& color )
{
    correctAverage( currentRedAverage_, color.getRed() );
    correctAverage( currentGreenAverage_, color.getGreen() );
    correctAverage( currentBlueAverage_, color.getBlue() );

    numberOfColors_++;
}

void ColorContainer::correctAverage( double& average, int colorValue )
{
    double oldListSize = static_cast<double>( numberOfColors_ );
    double newListSize = oldListSize + 1;

    double oldValues = average * oldListSize;
    oldValues += static_cast<double>( colorValue );
    average = oldValues / newListSize;
}

bool ColorContainer::checkColor( int color, int threshold, int average ) const
{
    double colorDouble = static_cast<double>( color );

    double min = colorDouble - threshold;
    double max = colorDouble + threshold;

    if( average >= min && average <= max )
    {
        return true;
    }

    return false;
}

Color ColorContainer::getAverage() const
{
    int redTrimmed = static_cast<int>( currentRedAverage_ );
    int greenTrimmed = static_cast<int>( currentGreenAverage_ );
    int blueTrimmed = static_cast<int>( currentBlueAverage_ );

    return Color( redTrimmed, greenTrimmed, blueTrimmed );
}
 
long ColorContainer::getNumberOfColors() const
{
    return numberOfColors_;
}

double ColorContainer::getCurrentRed() const
{
    return currentRedAverage_;
}

double ColorContainer::getCurrentGreen() const
{
    return currentGreenAverage_;
}

double ColorContainer::getCurrentBlue() const
{
    return currentBlueAverage_;
}

void ColorContainer::merge( const ColorContainer& anotherContainer )
{
    long newNumberOfColors_ = anotherContainer.getNumberOfColors() + numberOfColors_;

    // Get sum of colors of this object
    double myRedSum = currentRedAverage_ * numberOfColors_;
    double myGreenSum = currentGreenAverage_ * numberOfColors_;
    double myBlueSum = currentBlueAverage_ * numberOfColors_;

    // Get sum of colors of another object
    double anotherRedSum = 
        anotherContainer.getCurrentRed() * anotherContainer.getNumberOfColors();;
    double anotherGreenSum =
        anotherContainer.getCurrentGreen() * anotherContainer.getNumberOfColors();;
    double anotherBlueSum =
        anotherContainer.getCurrentBlue() * anotherContainer.getNumberOfColors();;

    // merge this object with another object
    currentRedAverage_ = ( myRedSum + anotherRedSum ) / newNumberOfColors_;
    currentGreenAverage_ = ( myGreenSum + anotherGreenSum ) / newNumberOfColors_;
    currentBlueAverage_ = ( myBlueSum + anotherBlueSum ) / newNumberOfColors_;
    numberOfColors_ = newNumberOfColors_;
}

double ColorContainer::getDistance( const Color& color ) const
{
    double redDistance = pow( (color.getRed() - currentRedAverage_), 2 );
    double greenDistance = pow( (color.getGreen() - currentGreenAverage_), 2 );
    double blueDistance = pow( (color.getBlue() - currentBlueAverage_), 2 );

    double distance = sqrt( redDistance + greenDistance + blueDistance );

    return distance;
}

} // namespace helpers
} // namespace segmentation
