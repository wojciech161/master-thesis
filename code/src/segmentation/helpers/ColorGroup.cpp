#include "segmentation/helpers/ColorGroup.hpp"
#include <boost/foreach.hpp>
#include <iostream>

#define foreach BOOST_FOREACH

namespace segmentation
{
namespace helpers
{

ColorGroup::ColorGroup( int threshold )
 : threshold_( threshold )
{

}

ColorGroup::ColorGroup( const Color& color, int threshold )
 : threshold_( threshold )
{
    colorContainers_.push_back( ColorContainer( color ) );
}

ColorGroup::~ColorGroup()
{

}

void ColorGroup::addToGroup( const Color& color )
{
    // If color is in range of one of existing groups, we add it to this group
    // Otherwise we create new group

    bool colorAddedToGroup = false;

    foreach( ColorContainer& c, colorContainers_ )
    {
        if( c.isInRange( color, threshold_ ) )
        {
            c.add( color );
            colorAddedToGroup = true;
        }
    }

    if( !colorAddedToGroup )
    {
        colorContainers_.push_back( ColorContainer( color ) );
    }
}

int ColorGroup::getNumberOfGroups() const
{
    return colorContainers_.size();
}

Color ColorGroup::getGroupColor( const Color& color ) const
{
    foreach( const ColorContainer& c, colorContainers_ )
    {
        if( c.isInRange( color, threshold_ ) )
        {
            return c.getAverage();
        }
    }

    return Color( 166, 0, 220 );
}

void ColorGroup::mergeGroupsToThreshold( int treshold )
{
    std::list<ColorContainer> mergedColors;

    do
    {
        // Get first color container from list
        std::list<ColorContainer>::iterator colorContainer = colorContainers_.begin();
        // Create new container basing on it
        ColorContainer mergedContainer( *colorContainer );
        // erase this element
        colorContainer = colorContainers_.erase( colorContainer );

        while( colorContainer != colorContainers_.end() )
        {
            // Get average color of next container
            Color anotherContainerAverage = colorContainer->getAverage();
            
            // if this container is in same range as merged one
            if( mergedContainer.isInRange( anotherContainerAverage, treshold ) )
            {
                // Merge containers and remove merged element from colorContainers_ list
                mergedContainer.merge( *colorContainer );
                colorContainer = colorContainers_.erase( colorContainer );
            }
            else
            {
                // Otherwise, take next element
                ++colorContainer;
            }
        }

        // Add merged container to new list
        mergedColors.push_back( mergedContainer );

    } while ( !colorContainers_.empty() );

    // Save new list as a class attribute
    colorContainers_ = mergedColors;
}

void ColorGroup::printAllContainers() const
{
    foreach( ColorContainer c, colorContainers_ )
    {
        Color avg = c.getAverage();
        std::cout << "( " << avg.getRed() << " , " << avg.getGreen()
                  << " , " << avg.getBlue() << " ) " 
                  << "COLORS: " << c.getNumberOfColors() << std::endl;
    }
}

} // namespace helpers
} // namespace segmentation
