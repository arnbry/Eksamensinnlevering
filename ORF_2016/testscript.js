function Addition(a, b)
{
    return a + b;
}

var myVariable = "Really cool! Regards, The Script.";

function CallCFunction()
{
    //Cool stuff I need to do here...
    var mNum = 24.5;
    cObject.scriptFunction(mNum);
}

function CallPFunction()
{
    cObject.privateFunc();
}

function ConnectToSlot()
{
 // test 1 - call a slot in the class:
 cObject.signalOne.connect(cObject, CallCFunction);
}
