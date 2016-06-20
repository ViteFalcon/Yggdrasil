#pragma once
#include <memory>
#include <string>

#include <boost/di.hpp>
#include <boost/property_tree/ptree.hpp>

namespace ygg
{
    class Configs
    {
    public: // types
        using PropertyTree = boost::property_tree::ptree;
        using DIFileType = void(*)();

        const static DIFileType File;

    public: // methods
        BOOST_DI_INJECT(Configs, (named = File) std::string filename)
            : mProperties(readIni(filename))
        {
        }

        template <typename T>
        T get(const std::string& key) const
        {
            return mProperties.get<T>(key);
        }

        template <typename T>
        T get(const std::string& section, const std::string& key) const
        {
            return get<T>(getKey(section, key));
        }

    private:
        std::string getKey(const std::string& section, const std::string& key) const
        {
            return section.empty() ? key : section + "." + key;
        }

        static PropertyTree readIni(const std::string& fileName);

        template<typename T>
        static void traverse_recursive(
            const boost::property_tree::ptree &parent,
            const boost::property_tree::ptree::path_type &childPath,
            const boost::property_tree::ptree &child, T &method);

        template<typename T>
        static void traverse(const boost::property_tree::ptree &parent, T &method);

        void merge(const PropertyTree &parent, const PropertyTree::path_type &childPath, const PropertyTree &child);

    private: // fields
        static const std::locale DEFAULT_LOCALE;

        PropertyTree mProperties;
    };

    template<typename T>
    void ygg::Configs::traverse_recursive(
        const boost::property_tree::ptree &parent,
        const boost::property_tree::ptree::path_type &childPath,
        const boost::property_tree::ptree &child, T &method)
    {
        using boost::property_tree::ptree;

        method(parent, childPath, child);
        for (ptree::const_iterator it = child.begin();it != child.end();++it) {
            ptree::path_type curPath = childPath / ptree::path_type(it->first);
            traverse_recursive(parent, curPath, it->second, method);
        }
    }

    template<typename T>
    void ygg::Configs::traverse(const boost::property_tree::ptree &parent, T &method)
    {
        traverse_recursive(parent, "", parent, method);
    }
}
