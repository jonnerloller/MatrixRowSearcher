#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <string>
#include <vector>
#include <functional>
#include <map>
namespace CP 
{ 
    using CommandLineArgumentType = std::string;
    using CommandLineArgumentPack = std::vector<CommandLineArgumentType>;
    using CommandLineCallback = std::function<void(const CommandLineArgumentPack&)>;
    class CommandLineOptionManager
    {
        public:
        void AddCommandLineOption(const std::string& option,const std::string& description, CommandLineCallback& functor);
        void ProcessCommandLine(const std::string& option, std::vector<CommandLineArgumentType>&& arguments);
        private:
        struct CommandLineData
        {
            std::string description;
            CommandLineCallback functor;
        };
        std::map<std::string,CommandLineData> m_CommandLineLUT;
    };
}

#endif