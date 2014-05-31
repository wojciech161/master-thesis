#ifndef FILEHANDLER_CONFIGURATION_FILE_READER_HPP_
#define FILEHANDLER_CONFIGURATION_FILE_READER_HPP_

#include "core/ParametersGetter.hpp"

namespace filehandler
{

class ConfigurationFileReader
{
public:
    ConfigurationFileReader( core::ParametersGetter& );
    ~ConfigurationFileReader();

private:
    void read();

private:
    core::ParametersGetter& parameters_;
};

} // namespace filehandler

#endif // FILEHANDLER_CONFIGURATION_FILE_READER_HPP_
