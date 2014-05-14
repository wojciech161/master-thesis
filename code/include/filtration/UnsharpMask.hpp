#ifndef FILTRATION_UNSHARP_MASK_HPP_
#define FILTRATION_UNSHARP_MASK_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class UnsharpMask : public IFiltrationAlgorithm
{
public:
    UnsharpMask();
    ~UnsharpMask();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
};

} // namespace filtration

#endif // FILTRATION_UNSHARP_MASK_HPP_
