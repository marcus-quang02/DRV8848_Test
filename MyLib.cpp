#include "StdAfx.h"
#include "MyLib.h"

void test_VM_Sleep_Mode_Current(CParam *I_VM_slp)
{

    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set FPVI to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);   // Set FOVI to FV mode, output being 0V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    VM.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 20usS time interval

    buffer[0] = VM.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT); // get avarage result of Current by putting retType = MIRET
    I_VM_slp->SetTestResult(SITE_1, 0, buffer[0]);               // set test result to site_1

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return;
}

void test_VINT_Voltage(CParam *VINT_RES)
{

    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AOUT2.Set(FI, -1e-3, FOVI_20V, FOVI_10MA, RELAY_ON); // AOUT being a 1 mA load in range of 20V 10mA, rising time set to default value of 0.1mS
    // AOUT2.SetClamp();
    delay_us(200);

    VINT.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    buffer[0] = VINT.GetMeasResult(1, MVRET, AVERAGE_RESULT);
    VINT_RES->SetTestResult(SITE_1, 0, buffer[0]);

    AOUT2.Set(FI, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
    delay_us(200);
    AOUT2.Set(FI, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
    delay_us(200);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_us(200);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_us(200);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_us(200);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return;
}

void test_Input_Logic_Low_Current(CParam *I_L_BIN1, CParam *I_L_BIN2)
{
    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

    delay_ms(1);

    BIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 1uS time interval
    BIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 1uS time interval

    buffer[0] = BIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);
    buffer[1] = BIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    I_L_BIN1->SetTestResult(SITE_1, 0, buffer[0]);
    I_L_BIN2->SetTestResult(SITE_1, 0, buffer[1]);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return;
}

void test_Input_Logic_High_Current(CParam *I_H_BIN1, CParam *I_H_BIN2)
{

    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    BIN1.MeasureVI(samples_number, measure_interval); // 20 samples, 20US time interval
    BIN2.MeasureVI(samples_number, measure_interval); // 20 samples, 20US time interval

    buffer[0] = BIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);
    buffer[1] = BIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    I_H_BIN1->SetTestResult(SITE_1, 0, buffer[0]);
    I_H_BIN2->SetTestResult(SITE_1, 0, buffer[1]);

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
}

void test_Input_Logic_Low_Current(CParam *I_L_SLP)
{
    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);   // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    nSLEEP.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 1uS time interval
    buffer[0] = BIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);
    I_L_SLP->SetTestResult(SITE_1, 0, buffer[0]);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
}

void test_Input_Logic_High_Current(CParam *I_H_SLP)
{
    int measure_interval = 20;
	int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);   // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    nSLEEP.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);
    buffer[0] = BIN1.GetMeasResult(1, MIRET, AVERAGE_RESULT);
    I_H_SLP->SetTestResult(1, 0, buffer[0]);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS = 100 us
    delay_us(200);
    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_us(200);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_ON);
    delay_us(200);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
}

void test_TriLevel_Logic_Low_Current(CParam *I_L_AIN1, CParam *I_L_AIN2)
{

    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);
    AIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL);

    buffer[0] = AIN1.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);
    buffer[1] = AIN2.GetMeasResult(SITE_1, MIRET, AVERAGE_RESULT);

    I_L_AIN1->SetTestResult(SITE_1, 0, buffer[0]);
    I_L_AIN2->SetTestResult(SITE_1, 0, buffer[1]);

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

void test_TriLevel_Logic_High_Current(CParam *I_H_AIN1, CParam *I_H_AIN2)
{
    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms

    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    AIN1.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 10uS time interval (10->30000uS is valid range)
    AIN2.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20 samples, 10uS time interval

    buffer[0] = AIN1.GetMeasResult(1, MIRET, AVERAGE_RESULT);
    buffer[1] = AIN2.GetMeasResult(1, MIRET, AVERAGE_RESULT);

    I_H_AIN1->SetTestResult(1, 0, buffer[0]);
    I_H_AIN2->SetTestResult(1, 0, buffer[1]);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    // BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return;
}

void test_Output_Logic_High_Leakage(CParam *I_H_nFAULT)
{

    int measure_interval = 20;
    int samples_number = 20;

    VM.Set(FV, 12, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set VM to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                       // delay 1 ms
    nSLEEP.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set nSLEEP to FV mode, output being 3.3V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, 3.3, FOVI_5V, FOVI_10MA, RELAY_ON);
    delay_ms(1);

    nFAULT.MeasureVI(samples_number, measure_interval, MEAS_NORMAL); // 20x20us = 400uS
    buffer[0] = nFAULT.GetMeasResult(1, MIRET, AVERAGE_RESULT);

    I_H_nFAULT->SetTestResult(SITE_1, 0, buffer[0]);

    AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);

    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);
    delay_ms(1);
    return;
}
