// Yggdrasil.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "core/YggConfigs.h"

#include <iostream>

int main()
{
    auto configs = ygg::Configs::Open("yggdrasil.ini");
    const std::string key = "Test.name";
    std::cout << key << " = " << configs->getString(key) << std::endl;
    std::cout << key << " = " << configs->getInt(key) << std::endl;
    char buffer[100];
    std::cin.getline(buffer, sizeof(buffer));
    return 0;
}
