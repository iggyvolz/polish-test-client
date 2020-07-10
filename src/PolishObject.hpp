#pragma once
#include "Suspendable.hpp"
class PolishClient;
enum PolishObjectTypes
{
    T_Root,
    T_WindowFactory,
    T_Window,
    T_DummyObject,
};
class PolishObject
{
    public:
        PolishObject(PolishClient* polish, uint64_t id):polish(polish), id(id) {}
        virtual Suspendable Process()=0;
        virtual PolishObjectTypes GetType()=0;
    protected:
        PolishClient* polish;
        uint64_t id;
};