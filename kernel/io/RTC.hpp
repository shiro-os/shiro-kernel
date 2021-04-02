#ifndef __RTC_HPP_
#define __RTC_HPP_

class RTC {
public:
    static long getTick();
    static long getCurrentTime();
    static void enableIrq08();
    static void onIrq08();
    static void setFrequency(unsigned char frequency);
private:
    static long currentTime;
    static long currentTick;
};

#endif
