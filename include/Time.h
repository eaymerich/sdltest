#ifndef TIME_H
#define TIME_H

#include <stdint.h>

class Time {
public:
    Time();
    virtual ~Time() = default;
    virtual void update();
    static float getElapsedTime() {
        return elapsedTime;
    }

protected:

private:
    uint32_t lastTicks;
    static float elapsedTime;
};

#endif // TIME_H
