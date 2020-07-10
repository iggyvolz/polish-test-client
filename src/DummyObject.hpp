#pragma once
#include "PolishObject.hpp"
#include "PolishClient.hpp"
class DummyObject: public PolishObject
{
    public:
        DummyObject(PolishClient* polish, uint64_t id):PolishObject(polish,id) {}
        virtual Suspendable Process() { throw std::exception(); }
        virtual PolishObjectTypes GetType() { return T_DummyObject; }
        static PolishObject* create(PolishClient* polish, uint64_t id) {return new DummyObject(polish,id);}
};