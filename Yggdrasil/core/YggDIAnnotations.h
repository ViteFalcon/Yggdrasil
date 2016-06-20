#pragma once

namespace ygg
{
    class DIAnnotations
    {
        DIAnnotations() = delete;
        ~DIAnnotations() = delete;
    public: // Types
        using Void = void(*)();
        using Int = void(*)(int);
    };
}
