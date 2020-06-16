#pragma once
#include "Suspendable.hpp"
class TcpClient;
class PolishClient;
enum PolishObjectTypes
{
    T_RootConstructor,
    T_WindowFactory,
    T_Window,
};
class PolishObject
{
    public:
        virtual Suspendable Process(PolishClient* polish)=0;
        virtual PolishObjectTypes GetType()=0;
};