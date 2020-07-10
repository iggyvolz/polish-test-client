#pragma once
#include "../PolishObject.hpp"
#include "../PolishClient.hpp"
#include <unordered_map>
class Root: public PolishObject
{
    private:
        static const std::unordered_map<std::string, PolishObject*(*)(PolishClient*, uint64_t)> constructors;
    public:
        virtual Suspendable Process();
        Root(PolishClient* polish, uint64_t id);
        virtual PolishObjectTypes GetType();
};