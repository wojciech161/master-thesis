#ifndef CORE_PARAMETERS_GETTER_HPP_
#define CORE_PARAMETERS_GETTER_HPP_

#include "Parameters.hpp"

namespace core
{

class ParametersGetter
{
public:
    ParametersGetter();
    ~ParametersGetter();

    LineDetectionParams& getLineDetectionParams();
    ColorSegmentationParams& getColorSegmentationParams();

private:
    LineDetectionParams lineDetectionParams_;
    ColorSegmentationParams colorSegmentationParams_;
};

} // namespace core

#endif // CORE_PARAMETERS_GETTER_HPP_
