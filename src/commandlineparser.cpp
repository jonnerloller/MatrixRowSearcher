#include "../include/commandlineparser.hpp"
namespace CP
{
    void CommandLineOptionManager::AddCommandLineOption(const std::string& option, std::function<void(const std::vector<CommandLineArgumentType>&)>& functor)
    {
        
    }

    void CommandLineOptionManager::ProcessCommandLine(const std::string& option, std::vector<CommandLineArgumentType>&& arguments)
    {
         auto it = m_function_lut.find(option);
         if(it != m_function_lut.end())
         {
             if(it->second)
             {
                 (it->second)(arguments);
             }
         }
    }
}