#ifndef FILEHANDLER_IFILEHANDLER_HPP
#define FILEHANDLER_IFILEHANDLER_HPP

#include <string>
#include <opencv2/core/core.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

namespace filehandler
{

class IFileHandler
{
public:
    virtual ~IFileHandler() {}

    virtual boost::optional<cv::Mat> loadImage( const std::string& ) const = 0;
    virtual void saveImage( const std::string&, boost::shared_ptr<cv::Mat> ) const = 0;
};

} // namespace filehandler

#endif // FILEHANDLER_IFILEHANDLER_HPP
