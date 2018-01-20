#include "../include/commandlineoptions.hpp"
#include <cassert>
#include <iostream>
namespace CP
{
    CommandLineOptions& CommandLineOptions::GetInstance()
    {
        static CommandLineOptions instance;
        return instance;
    }

    void CommandLineOptions::RunCommandLine(const std::string& commandName, ArgumentPack&& arguments)
    {
        auto it = m_CommandLineOptions.find(commandName);
        if (it != m_CommandLineOptions.end())
        {
            // it is mapped to commandName:pair<Description,Callback>
            // first = description
            // second = callback
            (it->second).second(commandName,std::move(arguments));
        }
    }

    void CommandLineOptions::AddCommandLineOption(const std::string& commandName,CommandLineCallback callback,const std::string& description)
    {
        auto it = m_CommandLineOptions.find(commandName);

        // avoid overriding command lines. We should only take in unique command line options.
        assert(it == m_CommandLineOptions.end());
        m_CommandLineOptions[commandName] = std::make_pair(description,callback);
    }

    void CommandLineOptions::DumpCommandLineOptions()
    {
        std::cout << "Options:" << std::endl;
        for (auto it : m_CommandLineOptions)
        {
            std::cout << "\t" << (it.second).first << std::endl;
        }
    }
}