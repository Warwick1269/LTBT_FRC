#include "Drive.h"
#include <thread>
#include <chrono>

class Auto
{
private:
    /* data */
public:
    Auto(/* args */);
    void TimedAutoMecDrive(int timeMS, double speedX, double speedY, double rotationZ, double fieldOrient);
    void TimedAutoTrainDrive(int timeMS, double speedL, double speedR);
    ~Auto();
};

