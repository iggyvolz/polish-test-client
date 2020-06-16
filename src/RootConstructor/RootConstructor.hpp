#pragma once
#include "../PolishObject.hpp"
#include <unordered_map>
class RootConstructor: public PolishObject
{
    private:
        static const std::unordered_map<std::string, PolishObject*(*)(PolishClient*)> constructors;

    public:
        virtual Suspendable Process(PolishClient* polish);
        RootConstructor();
        static PolishObject* testFn();
        virtual PolishObjectTypes GetType();
};