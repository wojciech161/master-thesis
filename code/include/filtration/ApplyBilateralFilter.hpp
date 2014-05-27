#ifndef FILTRATION_APPLY_BILATERAL_FILTER_HPP_
#define FILTRATION_APPLY_BILATERAL_FILTER_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class ApplyBilateralFilter : public IFiltrationAlgorithm
{
public:
    ApplyBilateralFilter( int, int, int );
    ~ApplyBilateralFilter();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
    
private:
    int diameter_;
    int sigmaColor_;
    int sigmaSpace_;
};

} // namespace filtration

#endif // FILTRATION_APPLY_BILATERAL_FILTER_HPP_
