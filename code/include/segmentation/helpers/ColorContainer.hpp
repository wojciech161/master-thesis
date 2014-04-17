#ifndef SEGMENTATION_HELPERS_COLOR_CONTAINER_HPP_
#define SEGMENTATION_HELPERS_COLOR_CONTAINER_HPP_

#include "Color.hpp"
#include <list>

namespace segmentation
{
namespace helpers
{

// Class groups similar color pixels in one container
class ColorContainer
{
public:
    ColorContainer();
    ColorContainer( const Color& );
    ColorContainer( const ColorContainer& );
    ~ColorContainer();

    bool isInRange( const Color&, int ) const;
    void add( const Color& );
    Color getAverage() const;
    int getNumberOfColors() const;
    double getCurrentRed() const;
    double getCurrentGreen() const;
    double getCurrentBlue() const;
    void merge( const ColorContainer& );

private:
    void correctAverage( double&, int );
    bool checkColor( int, int, int ) const;

private:
    int numberOfColors_;
    double currentRedAverage_;
    double currentGreenAverage_;
    double currentBlueAverage_;
};

} // namespace helpers
} // namespace segmentation

#endif
