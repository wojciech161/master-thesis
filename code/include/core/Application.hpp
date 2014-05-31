#ifndef CORE_APPLICATION_HPP_
#define CORE_APPLICATION_HPP_

#include <opencv2/core/core.hpp>
#include <boost/shared_ptr.hpp>
#include "core/ParametersGetter.hpp"

namespace core
{

class Application
{
public:
    Application();
    ~Application();

private:
    void displayIntroMessage() const;
    void start();
    boost::shared_ptr<cv::Mat> runFiltrationAndSegmentationAlgorithm( const cv::Mat& );
    void readParameters();

private:
    ParametersGetter parameters_;
};

} // namespace core

#endif // CORE_APPLICATION_HPP_
