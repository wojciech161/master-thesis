#ifndef FILEHANDLER_PATH_MANAGER_HPP
#define FILEHANDLER_PATH_MANAGER_HPP

#include "IPathManager.hpp"
#include <boost/filesystem.hpp>
#include <string>

namespace filehandler
{

class PathManager : public IPathManager
{
public:
    PathManager();
    ~PathManager();

    std::list<std::string> getInputFileList() const;
    std::string getOutputPath( const std::string& ) const;
private:
    boost::filesystem::path getInputPath() const;
};

} // namespace filehandler

#endif // FILEHANDLER_FILEHANDLER_HPP
