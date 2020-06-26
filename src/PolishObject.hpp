#pragma once
#include "Suspendable.hpp"
enum PolishObjectTypes
{
    T_RootConstructor,
    T_WindowFactory,
    T_Window,
    T_ContractChecker,
};
class PolishObject
{
    public:
        virtual Suspendable Process()=0;
        virtual PolishObjectTypes GetType()=0;
};