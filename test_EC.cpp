#include "StdAfx.h"
#include "test_EC.h"
#include "resource.h"

#define DEFAULT_VM_12_V 12
#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20
#define DEFAULT_DELAY_TIME_MS 1

#define INPUT_LOGIC_HIGH_VOLTAGE 3.3
#define INPUT_LOGIC_LOW_VOLTAGE 0

typedef struct
{
    char *test_name;
    FPVI10 *fpvi;
    FOVI *fovi;
    bool sleep;
    int input;

    bool VI; // 0 for V, 1 for I
} TestParams;

// This table contains informations required for test cases
TestParams my_table[] = {
    {"I_VM_slp", &VM, nullptr, 0, 0b0000, 1},
    {"VINT", nullptr, &VINT, 1, 0b0101, 0},
    {"I_L_BIN1", nullptr, &BIN1, 1, 0b0000, 1},
    {"I_L_BIN2", nullptr, &BIN2, 1, 0b0000, 1},
    {"I_L_SLP", nullptr, &nSLEEP, 0, 0b0000, 1},
    {"I_H_BIN1", nullptr, &BIN1, 1, 0b0011, 1},
    {"I_H_BIN2", nullptr, &BIN2, 1, 0b0011, 1},
    {"I_H_SLP", nullptr, &nSLEEP, 1, 0b0000, 1},
    {"I_L_AIN1", nullptr, &AIN1, 1, 0b0000, 1},
    {"I_L_AIN2", nullptr, &AIN2, 1, 0b0000, 1},
    {"I_H_AIN1", nullptr, &AIN1, 1, 0b1100, 1},
    {"I_H_AIN2", nullptr, &AIN2, 1, 0b1100, 1},
    {"I_H_nFAULT", nullptr, &nFAULT, 1, 0b0101, 1},
};

DUT_API void test(short funcindex, LPCTSTR funclabel)
{
    for (int i = 0; i < sizeof(my_table) / sizeof(my_table[0]); i++)
    {

        CParam *SetData = StsGetParam(funcindex, my_table[i].test_name);

        if (my_table[i].fpvi != nullptr)
        {
            double result = test_fpvi(my_table[i].fpvi, my_table[i].sleep, my_table[i].input, my_table[i].VI);
            SetData->SetTestResult(SITE_1, 0, result);
        }
        else if (my_table[i].fovi != nullptr)
        {
            double result = test_fovi(my_table[i].fovi, my_table[i].sleep, my_table[i].input, my_table[i].VI);
            SetData->SetTestResult(SITE_1, 0, result);
        }
        else
        {
            break;
            // std:: cout << i << std:: endl;
        }
    }
}

// 0 = logic low, 1 = logic high, -1 = floating
void input_setup(int input)
{

    if (input < 0)
    {
        AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
        AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
        BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
        BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
        delay_ms(1);
        return;
    }

    int AIN1_level = (input >> 3) && 1;
    int AIN2_level = (input >> 2) && 1;
    int BIN1_level = (input >> 1) && 1;
    int BIN2_level = (input >> 0) && 1;

    AIN1.Set(FV, AIN1_level > 0 ? INPUT_LOGIC_HIGH_VOLTAGE : INPUT_LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_ON);
    AIN2.Set(FV, AIN2_level > 0 ? INPUT_LOGIC_HIGH_VOLTAGE : INPUT_LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN1.Set(FV, BIN1_level > 0 ? INPUT_LOGIC_HIGH_VOLTAGE : INPUT_LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_ON);
    BIN2.Set(FV, BIN2_level > 0 ? INPUT_LOGIC_HIGH_VOLTAGE : INPUT_LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_ON);

    return;
}

double test_fovi(FOVI *fovi, bool sleep, int input, bool VI)
{
    // Setup
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set FPVI to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms

    nSLEEP.Set(FV, sleep ? 0 : 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set FOVI to FV mode, output being 0V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    input_setup(input); // Set AIN1, AIN2, BIN1 and BIN2 to logic low, delay 1 ms for relays to settle
    delay_ms(1);

    // Action
    fovi->MeasureVI(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, MEAS_NORMAL);       // 20 samples, 20usS time interval
    double result = fovi->GetMeasResult(SITE_1, VI == 0 ? MVRET : MIRET, AVERAGE_RESULT); // get avarage result of Current by putting retType = MIRET

    // Release
    input_setup(-1); // Set AIN1, AIN2, BIN1 and BIN2 to floating
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return result;
}

double test_fpvi(FPVI10 *fpvi, bool sleep, int input, bool VI)
{

    // Setup
    VM.Set(FV, DEFAULT_VM_12_V, FPVI10_20V, FPVI10_10MA, RELAY_ON); // Set FPVI to FV mode, output being 12 V in range of 20V and 10mA, relays on, rising time set to default 0.2mS
    delay_ms(1);                                                    // delay 1 ms

    nSLEEP.Set(FV, sleep ? 0 : 3.3, FOVI_5V, FOVI_10MA, RELAY_ON); // Set FOVI to FV mode, output being 0V in range of 5 V and 10mA, relays on, rising time set to default 0.1mS
    delay_ms(1);

    input_setup(input); // Set AIN1, AIN2, BIN1 and BIN2 to logic low, delay 1 ms for relays to settle
    delay_ms(1);

    // Action
    fpvi->MeasureVI(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, MEAS_NORMAL);       // 20 samples, 20usS time interval
    double result = fpvi->GetMeasResult(SITE_1, VI == 0 ? MVRET : MIRET, AVERAGE_RESULT); // get avarage result of Current by putting retType = MIRET

    // Release
    input_setup(-1); // Set AIN1, AIN2, BIN1 and BIN2 to floating
    delay_ms(1);

    nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    delay_ms(1);
    VM.Set(FV, 0, FPVI10_20V, FPVI10_10MA, RELAY_OFF);

    return result;
}
