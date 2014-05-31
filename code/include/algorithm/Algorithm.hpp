#ifndef ALGORITHM_ALGORITHM_HPP_
#define ALGORITHM_ALGORITHM_HPP_

#include "IAlgorithm.hpp"
#include "core/ParametersGetter.hpp"

namespace algorithm
{

class Algorithm : public IAlgorithm
{
public:
    Algorithm( const cv::Mat&, core::ParametersGetter& );
    ~Algorithm();

    boost::shared_ptr<cv::Mat> run();
private:
    boost::shared_ptr<cv::Mat> image_;
    core::ParametersGetter& parameters_;
};

} // namespace algorithm

#endif // ALGORITHM_ALGORITHM_HPP_
