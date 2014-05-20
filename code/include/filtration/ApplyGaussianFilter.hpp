#ifndef FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_
#define FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{
    
class ApplyGaussianFilter : public IFiltrationAlgorithm
{
public:
    ApplyGaussianFilter( int );
    ~ApplyGaussianFilter();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int blurRadius_;
};

} // namespace filtration

#endif // FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_
