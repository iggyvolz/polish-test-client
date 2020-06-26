#include "ContractChecker.hpp"
#include "../PolishClient.hpp"
ContractChecker::ContractChecker(PolishClient* polish):polish(polish)
{

}

PolishObjectTypes ContractChecker::GetType()
{
    return T_ContractChecker;
}

Suspendable ContractChecker::Process()
{
    char contract[32];
    WAIT_FOR(polish->socket->Read(contract, 32));
    char recognizesContract = (contracts.find(contract) == contracts.end()) ? 0 : 1;
    // Respond with: object ID
    WAIT_FOR(polish->socket->Write(1));
    // Identifier to be checked
    WAIT_FOR(polish->socket->Write(contract, 32));
    // Whether contract was recognized
    WAIT_FOR(polish->socket->Write(recognizesContract));
}