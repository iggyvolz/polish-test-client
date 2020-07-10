#include<unordered_map>
#include<string>
#include "Root.hpp"
#include "../Window/WindowFactory.hpp"
    
const std::unordered_map<std::string, PolishObject*(*)(PolishClient*,uint64_t)> Root::constructors = {

	{std::string({107,-88,73,-66,74,45,-7,-60,-78,60,-88,86,127,-61,-36,28,-56,88,-76,126,112,78,-15,110,45,83,33,-2,-52,-56,-123,-88}), WindowFactory::create},
    
};
