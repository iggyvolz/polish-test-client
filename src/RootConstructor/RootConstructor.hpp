#include "PolishObject.hpp"
#include <unordered_map>
class RootConstructor: public PolishObject
{
    private:
        static const std::unordered_map<std::string, PolishObject*(*)()> constructors;

    public:
        void Process(PolishClient* polish);
        RootConstructor();
        static PolishObject* testFn();
};