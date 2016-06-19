#pragma once
#include <memory>
#include <string>

namespace ygg
{
    class Configs
    {
    public:
        static std::shared_ptr<Configs> Open(const std::string& fileName);

    public:
        virtual ~Configs() = default;

        virtual int getInt(const std::string& key) const = 0;
        int getInt(const std::string& section, const std::string& key) const
        {
            return getInt(getKey(section, key));
        }

        virtual float getFloat(const std::string& key) const = 0;
        float getFloat(const std::string& section, const std::string& key) const
        {
            return getFloat(getKey(section, key));
        }

        virtual std::string getString(const std::string& key) const = 0;
        std::string getString(const std::string& section, const std::string& key) const
        {
            return getString(getKey(section, key));
        }

    private:
        std::string getKey(const std::string& section, const std::string& key) const
        {
            return section.empty() ? key : section + "." + key;
        }

        std::unique_ptr<Configs> mImpl;
    };
}
