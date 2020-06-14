#pragma once
class TcpClient;
class PolishClient;
class PolishObject
{
    public:
        virtual void Process(PolishClient* polish)=0;
};