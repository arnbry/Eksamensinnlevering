#include "scripting.h"

Scripting::Scripting(GameObject *gameObject, Input *input, QString filename)
{

    QFile scriptFile(filename);

    //tries to open file and gives errors if something is wrong
    if (! scriptFile.exists())
        qDebug("File not found!!!");
    if (!scriptFile.open(QIODevice::ReadOnly))
        qDebug("File not opened!!!");
    //reads the file
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    //close the file, because we don't need it anymore
    scriptFile.close();

    engine.evaluate(contents);

    //    makes a script-version for the script engine:
    QJSValue gameObjectScript = engine.newQObject(gameObject);
    QJSValue inputScript = engine.newQObject(input);


    //Makes a name in the script engine
    engine.globalObject().setProperty("gameobject", gameObjectScript);
    engine.globalObject().setProperty("input", inputScript);

    //Calls a function in script that calls the C-function: ***************************
    QJSValue directStartCall = engine.evaluate("Start");
    directStartCall.call();
}

void Scripting::update()
{
    QJSValue directStartCall = engine.evaluate("Update");
    directStartCall.call();
}



