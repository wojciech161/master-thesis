#ifndef FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_
#define FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{
    
class ApplyGaussianFilter : public IFiltrationAlgorithm
{
public:
    ApplyGaussianFilter();
    ~ApplyGaussianFilter();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int getBlurWidth( int, int ) const;
    int getBlurHeight( int, int ) const;
};

} // namespace filtration

#endif // FILTRATION_APPLY_GAUSSIAN_FILTER_HPP_
