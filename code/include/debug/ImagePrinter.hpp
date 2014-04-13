#ifndef DEBUG_IMAGEPRINTER_HPP_
#define DEBUG_IMAGEPRINTER_HPP_

#include "debug/IImagePrinter.hpp"

namespace debug
{

class ImagePrinter : public IImagePrinter
{
public:
    ImagePrinter();
    ~ImagePrinter();
    void print( const cv::Mat&, const std::string& ) const;
private:
    bool isPrintingEnabled() const;
};

} // namespace debug

#endif
