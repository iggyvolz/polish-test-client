#pragma once
#include "../PolishObject.hpp"
#include <vector>
#include "../PolishClient.hpp"
// IDENTIFIER 6ba849be4a2df9c4b23ca8567fc3dc1cc858b47e704ef16e2d5321feccc885a8
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
        std::vector<Window*> windows;
};