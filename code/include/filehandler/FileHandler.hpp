#ifndef FILEHANDLER_IMAGELOADER_HPP
#define FILEHANDLER_IMAGELOADER_HPP

#include "IFileHandler.hpp"

namespace filehandler
{

class FileHandler : public IFileHandler
{
public:
    FileHandler();
    ~FileHandler();

    boost::optional<cv::Mat> loadImage( const std::string& ) const;
    void saveImage( const std::string&, boost::shared_ptr<cv::Mat> ) const;
};

} // namespace filehandler

#endif // FILEHANDLER_IMAGELOADER_HPP
