#include "test_OS.h"
#include "resource.h"

#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20

#define DEFAULT_CURRENT_TEST_OS -5e-3
#define DEFAULT_DELAY_TIME_MS 1

double test_OS_buffer[SITE_COUNT] = {0};

//  1. FPVIO10/FOVI: PIN
//  2. measure interval: tần suất lấy mẫu
//  3. samples_number : số lần lấy mẫu
//  4. current: dòng cấp
//  5. dealy_time: thời gian chờ giữa các thao tác
double test_OS_FPVI(FPVI10 &pin, int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    pin.Set(FI, current, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                   // Đợi delay_time ms
    pin.MeasureVI(measure_interval, samples_number);        // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = pin.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    pin.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    pin.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    delay_ms(delay_time); // Đợi delay_time ms
    pin.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_FOVI(FOVI &pin, int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    pin.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                               // Đợi delay_time ms
    pin.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = pin.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    pin.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time); // Đợi delay_time ms
    pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}