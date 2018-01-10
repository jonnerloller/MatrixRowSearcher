#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>
namespace CommandLine
{
    using CommandLineArgumentType = std::string;

    class CommandLineOptionManager
    {
        public:
        void AddCommandLineOption(const std::string& option, std::function<void(const std::vector<CommandLineArgumentType>&)>& functor);
        void ProcessCommandLine(const std::string& option, std::vector<CommandLineArgumentType>&& arguments);
        private:
        std::map<std::string,std::function<void(const std::vector<CommandLineArgumentType>&)>> m_function_lut;
    };
    
}

#endif