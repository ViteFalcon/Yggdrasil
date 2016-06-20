#pragma once
#include "YggDIAnnotations.h"

#include <map>
#include <string>

#include <boost/di.hpp>
#include <boost/property_tree/ptree.hpp>

namespace ygg
{
    class CommandOptions
    {
    public: // DI Annotations
        static const DIAnnotations::Void ARGC;
        static const DIAnnotations::Void ARGV;
        static const DIAnnotations::Int ENVP;

    public:
        BOOST_DI_INJECT(CommandOptions, (named = ARGC) int argc, (named = ARGV) char* argv[], (named = ENVP) char* envp[]);
        ~CommandOptions();

        template <typename T>
        T getEnv(const std::string& name, const T& defaultValue) const
        {
            return mEnvironmentVariables.get("ENV." + name, defaultValue);
        }
    private: // types
        using PropertyTree = boost::property_tree::ptree;

    private:
        PropertyTree mEnvironmentVariables;
    };
}
