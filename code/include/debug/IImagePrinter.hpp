#ifndef DEBUG_IIMAGEPRINTER_HPP_
#define DEBUG_IIMAGEPRINTER_HPP_

#include <opencv2/core/core.hpp>
#include <string>

namespace debug
{

class IImagePrinter
{
public:
    ~IImagePrinter() {}
    virtual void print( const cv::Mat&, const std::string& ) const = 0;
};

} // namespace debug

#endif
