#ifndef FILEHANDLER_IPATHMANAGER_HPP
#define FILEHANDLER_IPATHMANAGER_HPP

#include <list>
#include <string>

namespace filehandler
{

class IPathManager
{
public:
    virtual ~IPathManager() {}
    virtual std::list<std::string> getInputFileList() const = 0;
    virtual std::string getOutputPath( const std::string& ) const = 0;
};

} // namespace filehandler

#endif
