#ifndef SCRIPTING_H
#define SCRIPTING_H


//Reading from file
#include <QFile>

//Must have for scripts:
#include <QJSEngine>

//The object I want to use in script
#include "gameobject.h"
#include "input.h"
/**
 * @brief The Scripting class
 */


class Scripting
{
public:
    /**
     * @brief Scripting
     * @param gameObject
     * @param input
     * @param filename
     */
    Scripting(GameObject* gameObject, Input* input, QString filename);
    /**
     * @brief update
     */
    void update();
    /**
     * @brief engine
     */
    QJSEngine engine;
};

#endif // SCRIPTING_H
