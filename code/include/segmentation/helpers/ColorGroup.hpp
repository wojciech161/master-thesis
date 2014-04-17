#ifndef SEGMENTATION_HELPERS_COLOR_GROUP_HPP_
#define SEGMENTATION_HELPERS_COLOR_GROUP_HPP_

#include <list>
#include "ColorContainer.hpp"

namespace segmentation
{
namespace helpers
{

// Class keeps all groups of color containers from entire image
class ColorGroup
{
public:
    ColorGroup( int );
    ColorGroup( const Color&, int );
    ~ColorGroup();

    void addToGroup( const Color& );
    int getNumberOfGroups() const;
    Color getGroupColor( const Color& ) const;
    void mergeGroupsToThreshold( int );

    void printAllContainers() const;

private:
    std::list<ColorContainer> colorContainers_;
    int threshold_;
};

} // namespace helpers
} // namespace segmentation

#endif
