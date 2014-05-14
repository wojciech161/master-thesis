#ifndef FILTRATION_THRESHOLD_HPP_
#define FILTRATION_THRESHOLD_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{
    
class Threshold : public IFiltrationAlgorithm
{
public:
    Threshold( int );
    ~Threshold();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;

private:
    const int THRESHOLD_TYPE;
    int thresholdValue_;
};

} // namespace filtration

#endif // FILTRATION_THRESHOLD_HPP_
