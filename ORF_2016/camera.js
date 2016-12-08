

function Start()
{

    
}

function Update()
{
    if(input.pressed("left"))
    {
        gameobject.gameObjectDebug(2);
        gameobject.translate(0.2, 0.0, 0.0);
        gameobject.gameObjectDebug(2);
    }
    if(input.pressed("right"))
    {
        gameobject.gameObjectDebug(2);
        gameobject.translate(-0.2, 0.0, 0.0);
    }
    
}

function ConnectToSlot()
{
 // test 1 - call a slot in the class:
 cObject.signalOne.connect(cObject, CallCFunction);
}
