#include "stdafx.h"
#include "YggConfigs.h"

#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace ygg
{
    namespace detail
    {
        class IniConfigs : public Configs
        {
        public:
            using PropertyTree = boost::property_tree::ptree;

            IniConfigs(const std::string& filename)
                : mProperties(readIni(filename))
            {
            }

            virtual int getInt(const std::string& key) const override
            {
                return mProperties.get<int>(key);
            }

            virtual float getFloat(const std::string& key) const override
            {
                return mProperties.get<float>(key);
            }

            virtual std::string getString(const std::string& key) const override
            {
                return mProperties.get<std::string>(key);
            }
        private:
            static PropertyTree readIni(const std::string& fileName)
            {
                PropertyTree properties;
                boost::property_tree::ini_parser::read_ini(fileName, properties, UTF8_LOCALE);
                return properties;
            }

            template<typename T>
            static void traverse_recursive(
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
            static void traverse(const boost::property_tree::ptree &parent, T &method)
            {
                traverse_recursive(parent, "", parent, method);
            }
        private:
            void merge(const PropertyTree &parent, const PropertyTree::path_type &childPath, const PropertyTree &child)
            {
                mProperties.put(childPath, child.data());
            }

            static const std::locale UTF8_LOCALE;

            PropertyTree mProperties;
        };

        const std::locale IniConfigs::UTF8_LOCALE("");
    }

    std::shared_ptr<Configs> Configs::Open(const std::string & fileName)
    {
        return std::make_unique<detail::IniConfigs>(fileName);
    }
}
