#pragma once
#include <math.h>

/*
f(t)=A*sin(B*t)+C

In this equation:

    tt represents time.
    AA is the amplitude, controlling how far the function oscillates above and below its central value.
    BB is the frequency, determining how fast the oscillation occurs.
    CC is a constant that represents the central value or offset of the pulsation.
*/
float PulsateFunction(float T, float A, float B, float C) {
    return A * sin(B * T) + C;
}

