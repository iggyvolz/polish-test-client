#pragma once
#include "../PolishObject.hpp"
#include <vector>
// HASH 015ae42867e6e3b2bae75f0fa3fd11aac0c41e4cd51b3c0dc33383a1f6074a7e
class Window;
class WindowFactory: public PolishObject
{
    public:
        Suspendable Process();
        static PolishObject* create(PolishClient* polish, uint64_t id);
        ~WindowFactory();
        virtual PolishObjectTypes GetType();
    private:
        WindowFactory(PolishClient* polish, uint64_t id);
        PolishClient* polish;
        uint64_t id;
        std::vector<Window*> windows;
};