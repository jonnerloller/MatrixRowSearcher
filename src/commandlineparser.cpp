#include "../include/commandlineparser.hpp"
namespace CP
{
    void CommandLineOptionManager::AddCommandLineOption(const std::string& option,const std::string& description, CommandLineCallback& functor)
    {
        m_CommandLineLUT[option] = {description,functor};
    }

    void CommandLineOptionManager::ProcessCommandLine(const std::string& option, std::vector<CommandLineArgumentType>&& arguments)
    {
    }
}