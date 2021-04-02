#ifndef __RTC_HPP_
#define __RTC_HPP_

/*
    See: https://www.lowlevel.eu/wiki/CMOS#Statusregister_A
    Frequencies:
    0 ->        no interrupt
    3 ->        8192 Hz 	 122.070  us
    4 ->        4096 Hz 	 244.141  µs
    5 ->        2048 Hz 	 488.281  µs
    6 ->        1024 Hz 	 976.562  µs
    7 ->         512 Hz 	 1.953125 ms
    8 ->         256 Hz 	 3.90625  ms
    9 ->         128 Hz 	 7.8125   ms
    10 ->         64 Hz 	 15.625   ms
    11 ->         32 Hz 	 31.25    ms
    12 ->         16 Hz 	 62.5     ms
    13 ->          8 Hz 	 125      ms
    14 ->          4 Hz 	 250      ms
    15 ->          2 Hz 	 500      ms
*/

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
