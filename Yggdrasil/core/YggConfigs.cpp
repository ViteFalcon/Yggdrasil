#include "stdafx.h"
#include "YggConfigs.h"

#include <boost/bind.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace ygg
{
    const Configs::DIFileType Configs::File = [] {};
    const std::locale Configs::DEFAULT_LOCALE("");

    ygg::Configs::PropertyTree Configs::readIni(const std::string& fileName)
    {
        PropertyTree properties;
        boost::property_tree::ini_parser::read_ini(fileName, properties, DEFAULT_LOCALE);
        return properties;
    }

    void Configs::merge(const PropertyTree &parent, const PropertyTree::path_type &childPath, const PropertyTree &child)
    {
        mProperties.put(childPath, child.data());
    }
}
