#include "../include/commandlineoptions.hpp"
#include <cassert>
namespace CP
{
    CommandLineOptions& CommandLineOptions::GetInstance()
    {
        static CommandLineOptions instance;
        return instance;
    }

    void CommandLineOptions::RunCommandLine(const std::string commandName, ArgumentPack&& arguments)
    {
        auto it = m_CommandLineOptions.find(commandName);
        if (it != m_CommandLineOptions.end())
        {
            (it->second)(commandName,std::move(arguments));
        }
    }

    void CommandLineOptions::AddCommandLineOption(const std::string commandName, CommandLineCallback callback)
    {
        auto it = m_CommandLineOptions.find(commandName);
        assert(it == m_CommandLineOptions.end());
        m_CommandLineOptions[commandName] = callback;
    }
}