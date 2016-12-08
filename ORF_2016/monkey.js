var yAkse = 1.0;
var change = 0.1;

function Start()
{
    //Cool stuff I need to do here...
    var mNum = 13.5;
    gameobject.gameObjectDebug(mNum);

}

function Update()
{
    gameobject.translate(0,yAkse,0);
}

function ConnectToSlot()
{
 // test 1 - call a slot in the class:
 cObject.signalOne.connect(cObject, CallCFunction);
}
