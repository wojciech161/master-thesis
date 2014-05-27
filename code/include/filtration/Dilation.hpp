#ifndef FILTRATION_DILATION_HPP_
#define FILTRATION_DILATION_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{
    
class Dilation : IFiltrationAlgorithm
{
public:
    Dilation(int);
    ~Dilation();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int dilationSize_;
};

} // namespace filtration

#endif // FILTRATION_DILATION_HPP_
