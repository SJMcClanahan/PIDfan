#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
    const double timeStep = 32e-3; // 32 ms
    const double MAXFANSPEED = 200;
    const double goalLow = 30, goalHigh = 35, middle = (goalLow + goalHigh) / 2;
    double kP = 0.25, kI = 1, kD = 0.5;
    double actualTemp = 65, diff = 0;
    double error = 0, lastError = 0;
    double P, I, D;
    double fanSpeed = 0;
    cout.precision(4);
    cout << fixed;

    for (double t = 0;t <= 100; t += timeStep)
    {
        cout << "At t = " << int(t) << ":\ttemp = "
                << actualTemp << "\tfanSpeed = "
                << fanSpeed << endl;
        cout.flush();
        if (actualTemp > middle)
        {
            error = actualTemp - middle;
            P = error;
            I = error / t;
            D = (lastError - error) / timeStep;
            fanSpeed += (P * kP) + (I * kI) + (D * kD);
            lastError = error;
        }
        else
            fanSpeed = 0;
        if (fanSpeed >= MAXFANSPEED)
            fanSpeed = MAXFANSPEED;
        if (fanSpeed < 4)
            fanSpeed = 0;

        actualTemp -= fanSpeed * 0.001;
        if (t < 18 || t > 24)
            actualTemp += (rand() % 10) * 0.001;
        Sleep(5);
    }

    return(0);
}
