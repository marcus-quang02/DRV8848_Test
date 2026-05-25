#include "test_OS.h"
#include "resource.h"

#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20

#define DEFAULT_CURRENT_TEST_OS -5e-3
#define DEFAULT_DELAY_TIME_MS 1

double test_OS_buffer[SITE_COUNT] = {0};

double test_OS_nFault(int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                      double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    nFAULT.Set(FI, current, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                      // Đợi delay_time ms
    nFAULT.MeasureVI(measure_interval, samples_number);        // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = nFAULT.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    nFAULT.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    delay_ms(delay_time); // Đợi delay_time ms
    nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_AISEN(int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    AISEN.Set(FI, current, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                     // Đợi delay_time ms
    AISEN.MeasureVI(measure_interval, samples_number);        // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = AISEN.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    AISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    delay_ms(delay_time);
    AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_nSLEEP(int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                      double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    nSLEEP.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                  // Đợi delay_time ms
    nSLEEP.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = nSLEEP.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    nSLEEP.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_BISEN(int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    BISEN.Set(FI, current, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                     // Đợi delay_time ms
    BISEN.MeasureVI(measure_interval, samples_number);        // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = BISEN.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    BISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
    delay_ms(delay_time);
    BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_AOUT1(int measure_interval = DEFAULT_MEASURE_INTERVAL, int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS, int delay_time = DEFAULT_DELAY_TIME_MS)
{

    AOUT1.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                 // Đợi delay_time ms
    AOUT1.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = AOUT1.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    AOUT1.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_AOUT2(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                     int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS,
                     int delay_time = DEFAULT_DELAY_TIME_MS)
{

    AOUT2.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                 // Đợi delay_time ms
    AOUT2.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = AOUT2.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    AOUT2.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_BOUT1(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                     int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS,
                     int delay_time = DEFAULT_DELAY_TIME_MS)
{

    BOUT1.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                 // Đợi delay_time ms
    BOUT1.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = BOUT1.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    BOUT1.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_BOUT2(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                     int samples_number = DEFAULT_SAMPLES_NUMBER,
                     double current = DEFAULT_CURRENT_TEST_OS,
                     int delay_time = DEFAULT_DELAY_TIME_MS)
{

    BOUT2.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                 // Đợi delay_time ms
    BOUT2.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = BOUT2.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    BOUT2.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_AIN1(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{

    AIN1.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                // Đợi delay_time ms
    AIN1.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = AIN1.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    AIN1.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_AIN2(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{

    AIN2.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                // Đợi delay_time ms
    AIN2.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = AIN2.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    AIN2.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_BIN1(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{

    BIN1.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                // Đợi delay_time ms
    BIN1.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = BIN1.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    BIN1.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_BIN2(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{

    BIN2.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                // Đợi delay_time ms
    BIN2.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = BIN2.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    BIN2.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_VREF(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{

    VREF.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON); // Cấp dòng ngược 5mA
    delay_ms(delay_time);                                // Đợi delay_time ms
    VREF.MeasureVI(measure_interval, samples_number);    // Number of samples: 20 , sample interval: 20us = 400 us

    test_OS_buffer[SITE_1] = VREF.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); // Lưu giá trị điện áp vào bộ nhớ đệm

    VREF.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}

double test_OS_VINT(int measure_interval = DEFAULT_MEASURE_INTERVAL,
                    int samples_number = DEFAULT_SAMPLES_NUMBER,
                    double current = DEFAULT_CURRENT_TEST_OS,
                    int delay_time = DEFAULT_DELAY_TIME_MS)
{
    VINT.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    VINT.MeasureVI(measure_interval, samples_number);

    test_OS_buffer[SITE_1] = VINT.GetMeasResult(SITE_1, MVRET, AVERAGE_RESULT); //

    VINT.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
    VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(delay_time);
    VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

    return test_OS_buffer[SITE_1];
}