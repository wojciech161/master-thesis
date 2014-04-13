#ifndef FILTRATION_APPLY_BILATERAL_FILTER_HPP_
#define FILTRATION_APPLY_BILATERAL_FILTER_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class ApplyBilateralFilter : public IFiltrationAlgorithm
{
public:
    ApplyBilateralFilter();
    ~ApplyBilateralFilter();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int computeDiameter( int, int ) const;
    int computeSigmaColor( int, int ) const;
    int computeSigmaSpace( int, int ) const;
};

} // namespace filtration

#endif // FILTRATION_APPLY_BILATERAL_FILTER_HPP_
