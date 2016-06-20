#include "stdafx.h"
#include "YggCommandOptions.h"

#include <regex>

#include <boost/program_options.hpp>

#include <iostream>

namespace ygg
{
    namespace detail
    {
        class EnvironmentVariableParser
        {
        public:
            using PropertyTree = boost::property_tree::ptree;

            EnvironmentVariableParser(char* envp[])
            {
                char* env = envp[0];
                for (int i = 0; env != nullptr; ++i, env = envp[i])
                {
                    addEnvironmentVariable(env);
                }
            }

            operator PropertyTree() const
            {
                return mProperties;
            }
        private:
            void addEnvironmentVariable(char* env)
            {
                std::string envStr(env);
                std::sregex_iterator itr(envStr.begin(), envStr.end(), ENV_PATTERN), itr_end;
                std::string variableName = (itr++)->str();
                std::string variableValue = itr->str();
                std::cout << variableName << " = " << variableValue << std::endl;
                mProperties.add("ENV." + variableName, variableValue);
            }
            PropertyTree mProperties;

        private: // static
            static const std::regex ENV_PATTERN;
        };

        const std::regex EnvironmentVariableParser::ENV_PATTERN("(.*?)=(.*)");
    }
    const DIAnnotations::Void CommandOptions::ARGC = [] {};
    const DIAnnotations::Void CommandOptions::ARGV = [] {};
    const DIAnnotations::Int CommandOptions::ENVP = [](int i) {};

    CommandOptions::CommandOptions(int argc, char* argv[], char* envp[])
        : mEnvironmentVariables(detail::EnvironmentVariableParser(envp))
    {
        std::cout << "Blah!" << std::endl;
    }


    CommandOptions::~CommandOptions()
    {
    }
}
