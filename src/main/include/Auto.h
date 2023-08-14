// #include "Drive.h"
#include "Robot.h"
#include <thread>
#include <chrono>

/** @brief This class is used for all things Auto related.*/
class Auto
{
private:
    /* data */
    
public:
    Auto(/* args */);

    
	void TimedAutoMecDrive(int timeMS, double speedX, double speedY, double rotationZ, double fieldOrient);
	void TimedAutoTrainDrive(int timeMS, double speedL, double speedR);
    void TimedAutoIntake(int timeMS, double speed);
    void TimedAutoArmBendTwo(int timeMS, double speed);

};

