#ifndef FILTRATION_IFILTRATION_ALGORITHM_HPP_
#define FILTRATION_IFILTRATION_ALGORITHM_HPP_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>

namespace filtration
{

class IFiltrationAlgorithm
{
public:
    virtual ~IFiltrationAlgorithm() {}
    virtual boost::shared_ptr<cv::Mat> apply( const cv::Mat& ) const = 0;
};

} // namespace filtration

#endif // FILTRATION_IFILTRATION_ALGORITHM_HPP_
