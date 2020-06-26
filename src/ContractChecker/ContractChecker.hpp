#pragma once
#include "../PolishObject.hpp"
#include <unordered_set>
class ContractChecker: public PolishObject
{
    private:
        static const std::unordered_set<std::string> contracts;
        PolishClient* polish;

    public:
        virtual Suspendable Process();
        ContractChecker(PolishClient* polish);
        virtual PolishObjectTypes GetType();
};