#include "core/ParametersGetter.hpp"

namespace core
{

ParametersGetter::ParametersGetter()
{

}

ParametersGetter::~ParametersGetter()
{

}

LineDetectionParams& ParametersGetter::getLineDetectionParams()
{
    return lineDetectionParams_;
}

ColorSegmentationParams& ParametersGetter::getColorSegmentationParams()
{
    return colorSegmentationParams_;
}

} // namespace core
