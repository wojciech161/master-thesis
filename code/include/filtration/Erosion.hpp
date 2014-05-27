#ifndef FILTRATION_EROSION_HPP_
#define FILTRATION_EROSION_HPP_

#include "IFiltrationAlgorithm.hpp"

namespace filtration
{

class Erosion : public IFiltrationAlgorithm
{
public:
    Erosion(int);
    ~Erosion();

    boost::shared_ptr<cv::Mat> apply( boost::shared_ptr<cv::Mat> ) const;
private:
    int erosionSize_;
};

} // namespace filtration

#endif // FILTRATION_EROSION_HPP_
