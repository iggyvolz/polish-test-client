#pragma once
#include "../PolishObject.hpp"
#include <unordered_map>
class RootConstructor: public PolishObject
{
    private:
        static const std::unordered_map<std::string, PolishObject*(*)(PolishClient*, uint64_t)> constructors;
        PolishClient* polish;

    public:
        virtual Suspendable Process();
        RootConstructor(PolishClient* polish);
        virtual PolishObjectTypes GetType();
};