#ifndef DEBUG_H
#define DEBUG_H

#include "qobject.h"
#include "qdebug.h"


using namespace std;

class Debug : public QObject
{
    Q_OBJECT
public:
    Debug();

public slots:
    void Log(float message);
    void Log(bool messages);
    void Log(int message);
    void Log(string message);


};

#endif // DEBUG_H
