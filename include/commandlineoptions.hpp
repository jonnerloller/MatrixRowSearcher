#ifndef COMMANDLINEOPTIONS_HPP
#define COMMANDLINEOPTIONS_HPP
#include <string>
#include <vector>
#include <map>
#include <functional>
namespace CP
{
    class CommandLineOptions
    {
    public:
        using ArgumentPack = std::vector<std::string>;
        using CommandLineCallback = std::function<void(const std::string& functionName,ArgumentPack&&)>;
        static CommandLineOptions& GetInstance();
        
        void RunCommandLine(const std::string commandName, ArgumentPack&& arguments);
        void AddCommandLineOption(const std::string commandName, CommandLineCallback callback);
    private:
        CommandLineOptions() = default;
        CommandLineOptions(const CommandLineOptions& rhs) = delete;
        CommandLineOptions(CommandLineOptions&& rhs) = delete;
        CommandLineOptions& operator = (const CommandLineOptions& rhs) = delete;
        CommandLineOptions& operator = (CommandLineOptions&& rhs) = delete;
        virtual ~CommandLineOptions() = default;
        std::map<std::string, CommandLineCallback> m_CommandLineOptions;
    };
}
#endif