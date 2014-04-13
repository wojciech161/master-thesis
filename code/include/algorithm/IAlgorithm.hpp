#ifndef ALGORITHM_IALGORITHM_HPP_
#define ALGORITHM_IALGORITHM_HPP_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>

namespace algorithm
{

class IAlgorithm
{
public:
    virtual ~IAlgorithm() {}
    virtual boost::shared_ptr<cv::Mat> run() = 0;
};

} // namespace algorithm

#endif // ALGORITHM_IALGORITHM_HPP_
