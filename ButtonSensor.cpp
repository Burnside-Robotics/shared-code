//Example Function For waiting till a button sensor is pressed a number of times 
void WaitForBumper(int amount, int maxTimeMsec)
{
    int doneAmount = 0;
    int doneTime = 0;
    while(doneAmount < amount)
    {
        //Check if Button is Pressed Down
        if(ballBumper.pressing())
        {
            doneAmount++;
            //Wait until Bumper is Released
            while(ballBumper.pressing())
            {
                wait(30, timeUnits::msec);
                doneTime += 30;
                if(doneTime >= maxTimeMsec)
                    break;
            }
        }
        wait(100, timeUnits::msec);
        doneTime += 100;
        if(doneTime >= maxTimeMsec)
            break;
    }
}