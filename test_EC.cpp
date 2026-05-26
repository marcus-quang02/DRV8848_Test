#include "StdAfx.h"
#include "test_EC.h"
#include "resource.h"

#define DEFAULT_VM_12_V 12
#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20

#define DEFAULT_DELAY_TIME_MS 1

double TEST_EC_BUFFER[4] = {0.0};

double test_I_VM_slp(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set FPVI to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);                // Set FOVI to FV mode, output being 0V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

    delay_ms(1);

    VM.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);         // 20 samples, 20usS time interval
    TEST_EC_BUFFER[0] = VM.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT); // get avarage result of Current by putting retType = MIRET

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return TEST_EC_BUFFER[0];
}

double test_VINT(int samples_number = DEFAULT_SAMPLES_NUMBER,
                 int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    VINT.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);
    TEST_EC_BUFFER[0] = VINT.GetMeasResult(1, MVRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return TEST_EC_BUFFER[0];
}

double test_I_L_BIN1(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    BIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);
    TEST_EC_BUFFER[0] = BIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}

double test_I_L_BIN2(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

    delay_ms(1);

    BIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 1uS time interval
    TEST_EC_BUFFER[0] = BIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}

double test_I_H_BIN1(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    BIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 20US time interval
    TEST_EC_BUFFER[0] = BIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);

    return TEST_EC_BUFFER[0];
}

double test_I_H_BIN2(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    BIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 20US time interval
    TEST_EC_BUFFER[0] = BIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);

    return TEST_EC_BUFFER[0];
}

double test_I_L_SLP(int samples_number = DEFAULT_SAMPLES_NUMBER,
                    int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);                // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    nSLEEP.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 1uS time interval
    TEST_EC_BUFFER[0] = nSLEEP.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}

double test_I_H_SLP(int samples_number = DEFAULT_SAMPLES_NUMBER,
                    int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);                // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    nSLEEP.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);
    TEST_EC_BUFFER[0] = nSLEEP.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS = 100 us
    delay_ms(1);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);

    return TEST_EC_BUFFER[0];
}

double test_I_L_AIN1(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    TEST_EC_BUFFER[0] = AIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return;
}

double test_I_L_AIN2(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    TEST_EC_BUFFER[0] = AIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return TEST_EC_BUFFER[0];
}

double test_I_H_AIN1(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms

    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    TEST_EC_BUFFER[0] = AIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}

double test_I_H_AIN2(int samples_number = DEFAULT_SAMPLES_NUMBER,
                     int measure_interval = DEFAULT_MEASURE_INTERVAL)
{
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms

    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    TEST_EC_BUFFER[0] = AIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}

double test_I_H_nFAULT(int samples_number = DEFAULT_SAMPLES_NUMBER,
                       int measure_interval = DEFAULT_MEASURE_INTERVAL)
{

    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);              // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    nFAULT.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20x20us = 400uS
    TEST_EC_BUFFER[0] = nFAULT.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return TEST_EC_BUFFER[0];
}
