// Yggdrasil.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core/YggConfigs.h"
#include "core/YggCommandOptions.h"

#include <iostream>

#include <boost/di.hpp>

#include <conio.h>

namespace ygg {
    namespace di = boost::di;

    class Yggdrasill
    {
    public:
        Yggdrasill(std::shared_ptr<Configs> configs, std::shared_ptr<CommandOptions> options)
            : mConfigs(configs)
            , mOptions(options)
        {
        }

        int run()
        {
            const std::string key = "Test.name";
            std::cout << key << " = " << mConfigs->get<std::string>(key) << std::endl;
            std::cout << key << " = " << mConfigs->get<int>(key) << std::endl;

            waitForKeyboardHit();

            return 0;
        }

    private:
        void waitForKeyboardHit()
        {
            std::cout << std::endl << "(Press any key to continue...)" << std::endl;
            _getch();
        }
        std::shared_ptr<ygg::Configs> mConfigs;
        std::shared_ptr<ygg::CommandOptions> mOptions;
    };
}

int main(int argc, char* argv[], char* envp[])
{
    using namespace ygg;
    auto injector = di::make_injector(
        di::bind<std::string>().named(Configs::File).to("yggdrasil.ini"),
        di::bind<>().named(CommandOptions::ARGC).to(argc),
        di::bind<char*[]>().named(CommandOptions::ARGV).to(argv),
        di::bind<char*[]>().named(CommandOptions::ENVP).to(envp)
    );
    auto yggdrasill = injector.create<Yggdrasill>();
    yggdrasill.run();
    return 0;
}
