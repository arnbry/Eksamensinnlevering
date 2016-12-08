#include "debug.h"

Debug::Debug()
{

}

void Debug::Log(float message)
{
    qDebug()<< message;
}

void Debug::Log(bool messages)
{
    if (messages)
    {
        qDebug()<< "True";
    }
    else
    {
        qDebug()<< "False";
    }
}

void Debug::Log(int message)
{
    qDebug()<< message;
}

void Debug::Log(string message)
{
    qDebug()<< "" << message.c_str();
}
