#ifndef FILTRATION_UNSHARP_MASK_HPP_
#define FILTRATION_UNSHARP_MASK_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class UnsharpMask : public IFiltrationAlgorithm
{
public:
    UnsharpMask( int );
    ~UnsharpMask();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int standardDeviation_;
};

} // namespace filtration

#endif // FILTRATION_UNSHARP_MASK_HPP_
