#include "stdafx.h"

#include "test_EC.h"
#include "test_OS.h"
#include "test_Kelvin.h"

#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20
#define DEFAULT_CURRENT_TEST_OS -5e-3
#define DEFAULT_DELAY_TIME_MS 1

#define DEFAULT_CURRENT_TEST_KELVIN -5e-3

// multisite settings should be included here
/*The following code was created for STS PinPlanner,don't modify*/
/****STS_PINPLANNER_CODE_BEGIN****/
#define STS_SITE_NUM 1
/****PIN GROUP DEFINITION****/

/*

FPVI10 fpvi_objects[4] = { FPVI10(0, "VM"),FPVI10(1, "nFAULT"), FPVI10(2, "AISEN"), FPVI10(3, "BISEN") };


FOVI fovi_objects[11] = {	FOVI(0,"nSLEEP"), FOVI(1,"AOUT1"),FOVI(2,"AOUT2"),
FOVI (3,"BOUT2"), FOVI (4,"BOUT1"),FOVI(5,"BIN1"),
FOVI(6,"BIN2"),FOVI (7,"VREF"),FOVI (8,"VINT"),
FOVI(9,"AIN2"), FOVI (10,"AIN1")} ;

*/

/****multisite settings should be included here****/
DUT_API void HardWareCfg()
{
	STSSetModuleToSite(MD_FPVI10, SITE_1, 0, 1, 2, 3);
	STSSetModuleToSite(MD_FOVI, SITE_1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, 1, 2);
}
/****STS_PINPLANNER_CODE_END****/

/************************************************************************/
/*                                                                      */
/************************************************************************/
// initialize function will be called before all the test functions.
DUT_API void InitBeforeTestFlow()
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
// initializefunction will be called after all the test functions.
DUT_API void InitAfterTestFlow()
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
// Fail site hardware set function will be called after failed params, it can be called for serveral times.
DUT_API void SetupFailSite(const unsigned char *byFailSite)
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

DUT_API int TEST_KELVIN(short funcindex, LPCTSTR funclabel)
{
	//{{AFX_STS_PARAM_PROTOTYPES

	CParam *R_nSLEEP_KELVIN = StsGetParam(funcindex, "R_nSLEEP_KELVIN");
	CParam *R_nFAULT_KELVIN = StsGetParam(funcindex, "R_nFAULT_KELVIN");
	CParam *R_AISEN_KELVIN = StsGetParam(funcindex, "R_AISEN_KELVIN");
	CParam *R_BISEN_KELVIN = StsGetParam(funcindex, "R_BISEN_KELVIN");

	CParam *R_AOUT1_KELVIN = StsGetParam(funcindex, "R_AOUT1_KELVIN");
	CParam *R_AOUT2_KELVIN = StsGetParam(funcindex, "R_AOUT2_KELVIN");
	CParam *R_BOUT2_KELVIN = StsGetParam(funcindex, "R_BOUT2_KELVIN");
	CParam *R_BOUT1_KELVIN = StsGetParam(funcindex, "R_BOUT1_KELVIN");

	CParam *R_AIN1_KELVIN = StsGetParam(funcindex, "R_AIN1_KELVIN");
	CParam *R_AIN2_KELVIN = StsGetParam(funcindex, "R_AIN2_KELVIN");
	CParam *R_BIN2_KELVIN = StsGetParam(funcindex, "R_BIN2_KELVIN");
	CParam *R_BIN1_KELVIN = StsGetParam(funcindex, "R_BIN1_KELVIN");

	CParam *R_VINT_KELVIN = StsGetParam(funcindex, "R_VINT_KELVIN");
	CParam *R_GND_KELVIN = StsGetParam(funcindex, "R_GND_KELVIN");
	CParam *R_VM_KELVIN = StsGetParam(funcindex, "R_VM_KELVIN");
	CParam *R_VREF_KELVIN = StsGetParam(funcindex, "R_VREF_KELVIN");

	//}}AFX_STS_PARAM_PROTOTYPES

	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/

	/*
	for (int i = 0; i <4; i++)
	{
		fpvi_objects[i].Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);

		delay_ms(1);	// Đợi 1ms
		fpvi_objects[i].MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = fpvi_objects[i].GetMeasResult(0, MVRET); // Lưu giá trị điện áp vào bộ nhớ đệm

			//--------------------------------------------------//
			// R_nFAULT_KELVIN->SetTestResult(0, 0, buffer[0]); //
			//--------------------------------------------------//
		}

		fpvi_objects[i].Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		fpvi_objects[i].Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		fpvi_objects[i].Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	for (int i = 0; i < 11; i++) {
		fovi_objects[i].Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		fovi_objects[i].MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = fovi_objects[i].GetMeasResult(0, MVRET); //
			// R_nSLEEP_KELVIN->SetTestResult(0, 0, buffer[0]);
		}

		fovi_objects[i].Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		fovi_objects[i].Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		fovi_objects[i].Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	*/

	// NFAULT

	R_nFAULT_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_nFault(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_AOUT1_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_AOUT1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_AISEN_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_AISEN(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_AOUT2_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_AOUT2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_BOUT2_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_BOUT2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_BISEN_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_BISEN(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_BOUT1_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_BOUT1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_nSLEEP_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_nSLEEP(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_AIN1_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_AIN1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_AIN2_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_AIN2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_VINT_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_VINT(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_VM_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_VM(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_VREF_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_VREF(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_BIN2_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_BIN2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));
	R_BIN1_KELVIN->SetTestResult(SITE_1, 0, test_KELVIN_BIN1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_KELVIN, DEFAULT_DELAY_TIME_MS));

	// TODO: Add your function code here
	return 0;
}

DUT_API int TEST_OPEN_SHORT(short funcindex, LPCTSTR funclabel)
{
	//{{AFX_STS_PARAM_PROTOTYPES
	CParam *OS_nSLEEP = StsGetParam(funcindex, "OS_nSLEEP");
	CParam *OS_AOUT1 = StsGetParam(funcindex, "OS_AOUT1");
	CParam *OS_AISEN = StsGetParam(funcindex, "OS_AISEN");
	CParam *OS_AOUT2 = StsGetParam(funcindex, "OS_AOUT2");
	CParam *OS_BOUT2 = StsGetParam(funcindex, "OS_BOUT2");
	CParam *OS_BISEN = StsGetParam(funcindex, "OS_BISEN");
	CParam *OS_BOUT1 = StsGetParam(funcindex, "OS_BOUT1");
	CParam *OS_nFAULT = StsGetParam(funcindex, "OS_nFAULT");
	CParam *OS_AIN1 = StsGetParam(funcindex, "OS_AIN1");
	CParam *OS_AIN2 = StsGetParam(funcindex, "OS_AIN2");
	CParam *OS_VINT = StsGetParam(funcindex, "OS_VINT");
	CParam *OS_VM = StsGetParam(funcindex, "OS_VM");
	CParam *OS_VREF = StsGetParam(funcindex, "OS_VREF");
	CParam *OS_BIN2 = StsGetParam(funcindex, "OS_BIN2");
	CParam *OS_BIN1 = StsGetParam(funcindex, "OS_BIN1");
	//}}AFX_STS_PARAM_PROTOTYPES

	// NFAULT

	OS_nFAULT->SetTestResult(SITE_1, 0, test_OS_nFault(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_AOUT1->SetTestResult(SITE_1, 0, test_OS_AOUT1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_AISEN->SetTestResult(SITE_1, 0, test_OS_AISEN(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_AOUT2->SetTestResult(SITE_1, 0, test_OS_AOUT2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_BOUT2->SetTestResult(SITE_1, 0, test_OS_BOUT2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_BISEN->SetTestResult(SITE_1, 0, test_OS_BISEN(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_BOUT1->SetTestResult(SITE_1, 0, test_OS_BOUT1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_nSLEEP->SetTestResult(SITE_1, 0, test_OS_nSLEEP(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_AIN1->SetTestResult(SITE_1, 0, test_OS_AIN1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_AIN2->SetTestResult(SITE_1, 0, test_OS_AIN2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_VINT->SetTestResult(SITE_1, 0, test_OS_VINT(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_VM->SetTestResult(SITE_1, 0, test_OS_VM(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_VREF->SetTestResult(SITE_1, 0, test_OS_VREF(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_BIN2->SetTestResult(SITE_1, 0, test_OS_BIN2(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));
	OS_BIN1->SetTestResult(SITE_1, 0, test_OS_BIN1(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL, DEFAULT_CURRENT_TEST_OS, DEFAULT_DELAY_TIME_MS));

	return 0;
}

DUT_API int TRIM(short funcindex, LPCTSTR funclabel)
{
	//{{AFX_STS_PARAM_PROTOTYPES
	CParam *TM1_V_nFAULT_1 = StsGetParam(funcindex, "TM1_V_nFAULT_1");
	CParam *TM1_V_nFAULT_2 = StsGetParam(funcindex, "TM1_V_nFAULT_2");
	CParam *TM2_V_nFAULT_1 = StsGetParam(funcindex, "TM2_V_nFAULT_1");
	CParam *TM2_V_nFAULT_2 = StsGetParam(funcindex, "TM2_V_nFAULT_2");
	CParam *TM3_V_VINT = StsGetParam(funcindex, "TM3_V_VINT");
	CParam *TM4_I_nFAULT = StsGetParam(funcindex, "TM4_I_nFAULT");
	CParam *TM5_V_nFAULT = StsGetParam(funcindex, "TM5_V_nFAULT");
	CParam *TM6_V_nFAULT_1 = StsGetParam(funcindex, "TM6_V_nFAULT_1");
	CParam *TM6_V_nFAULT_2 = StsGetParam(funcindex, "TM6_V_nFAULT_2");
	CParam *TM7_V_nFAULT_1 = StsGetParam(funcindex, "TM7_V_nFAULT_1");
	CParam *TM7_V_nFAULT_2 = StsGetParam(funcindex, "TM7_V_nFAULT_2");
	//}}AFX_STS_PARAM_PROTOTYPES

	// TODO: Add your function code here

	return 0;
}

DUT_API int EC_MEASURE(short funcindex, LPCTSTR funclabel)
{
	//{{AFX_STS_PARAM_PROTOTYPES
	CParam *I_VM_01 = StsGetParam(funcindex, "I_VM_01");
	CParam *I_VM_10 = StsGetParam(funcindex, "I_VM_10");
	CParam *I_VM_11 = StsGetParam(funcindex, "I_VM_11");
	CParam *I_VM_slp = StsGetParam(funcindex, "I_VM_slp");
	CParam *t_SLEEP = StsGetParam(funcindex, "t_SLEEP");
	CParam *t_WAKE = StsGetParam(funcindex, "t_WAKE");
	CParam *ton = StsGetParam(funcindex, "ton");
	CParam *VINT = StsGetParam(funcindex, "VINT");
	CParam *V_L_BIN1 = StsGetParam(funcindex, "V_L_BIN1");
	CParam *V_L_BIN2 = StsGetParam(funcindex, "V_L_BIN2");
	CParam *V_L_nSLP = StsGetParam(funcindex, "V_L_nSLP");
	CParam *V_H_BIN1 = StsGetParam(funcindex, "V_H_BIN1");
	CParam *V_H_BIN2 = StsGetParam(funcindex, "V_H_BIN2");
	CParam *V_H_nSLP = StsGetParam(funcindex, "V_H_nSLP");
	CParam *V_hys_BIN1 = StsGetParam(funcindex, "V_hys_BIN1");
	CParam *V_hys_BIN2 = StsGetParam(funcindex, "V_hys_BIN2");
	CParam *V_hys_nSLP = StsGetParam(funcindex, "V_hys_nSLP");
	CParam *I_L_BIN1 = StsGetParam(funcindex, "I_L_BIN1");
	CParam *I_L_BIN2 = StsGetParam(funcindex, "I_L_BIN2");
	CParam *I_L_SLP = StsGetParam(funcindex, "I_L_SLP");
	CParam *I_H_BIN1 = StsGetParam(funcindex, "I_H_BIN1");
	CParam *I_H_BIN2 = StsGetParam(funcindex, "I_H_BIN2");
	CParam *I_H_SLP = StsGetParam(funcindex, "I_H_SLP");
	CParam *R_PD_BIN1 = StsGetParam(funcindex, "R_PD_BIN1");
	CParam *R_PD_BIN2 = StsGetParam(funcindex, "R_PD_BIN2");
	CParam *R_PD_SLP = StsGetParam(funcindex, "R_PD_SLP");
	CParam *t_DEG_A = StsGetParam(funcindex, "t_DEG_A");
	CParam *t_DEG_B = StsGetParam(funcindex, "t_DEG_B");
	CParam *t_PROP_A = StsGetParam(funcindex, "t_PROP_A");
	CParam *t_PROP_B = StsGetParam(funcindex, "t_PROP_B");
	CParam *V_L_AIN1 = StsGetParam(funcindex, "V_L_AIN1");
	CParam *V_L_AIN2 = StsGetParam(funcindex, "V_L_AIN2");
	CParam *V_Z_AIN1 = StsGetParam(funcindex, "V_Z_AIN1");
	CParam *V_Z_AIN2 = StsGetParam(funcindex, "V_Z_AIN2");
	CParam *V_H_AIN1 = StsGetParam(funcindex, "V_H_AIN1");
	CParam *V_H_AIN2 = StsGetParam(funcindex, "V_H_AIN2");
	CParam *V_HYS_AIN1 = StsGetParam(funcindex, "V_HYS_AIN1");
	CParam *V_HYS_AIN2 = StsGetParam(funcindex, "V_HYS_AIN2");
	CParam *I_L_AIN1 = StsGetParam(funcindex, "I_L_AIN1");
	CParam *I_L_AIN2 = StsGetParam(funcindex, "I_L_AIN2");
	CParam *I_H_AIN1 = StsGetParam(funcindex, "I_H_AIN1");
	CParam *I_H_AIN2 = StsGetParam(funcindex, "I_H_AIN2");
	CParam *R_PD_AIN1 = StsGetParam(funcindex, "R_PD_AIN1");
	CParam *R_PD_AIN2 = StsGetParam(funcindex, "R_PD_AIN2");
	CParam *R_PU_AIN1 = StsGetParam(funcindex, "R_PU_AIN1");
	CParam *R_PU_AIN2 = StsGetParam(funcindex, "R_PU_AIN2");
	CParam *V_L_nFAULT = StsGetParam(funcindex, "V_L_nFAULT");
	CParam *I_H_nFAULT = StsGetParam(funcindex, "I_H_nFAULT");
	CParam *RDS_V_VM = StsGetParam(funcindex, "RDS_V_VM");
	CParam *RDS_V_AOUT1 = StsGetParam(funcindex, "RDS_V_AOUT1");
	CParam *RDS_V_AOUT2 = StsGetParam(funcindex, "RDS_V_AOUT2");
	CParam *RDS_V_AISEN = StsGetParam(funcindex, "RDS_V_AISEN");
	CParam *RDS_I_AOUT1 = StsGetParam(funcindex, "RDS_I_AOUT1");
	CParam *RDS_HS = StsGetParam(funcindex, "RDS_HS");
	CParam *RDS_LS = StsGetParam(funcindex, "RDS_LS");
	CParam *I_LEAK = StsGetParam(funcindex, "I_LEAK");
	CParam *t_RISE = StsGetParam(funcindex, "t_RISE");
	CParam *t_FALL = StsGetParam(funcindex, "t_FALL");
	CParam *I_REF_1 = StsGetParam(funcindex, "I_REF_1");
	CParam *I_REF_3_3 = StsGetParam(funcindex, "I_REF_3_3");
	CParam *V_TRIP_AISEN = StsGetParam(funcindex, "V_TRIP_AISEN");
	CParam *V_TRIP_BISEN = StsGetParam(funcindex, "V_TRIP_BISEN");
	CParam *t_BLANK = StsGetParam(funcindex, "t_BLANK");
	CParam *A_V_AISEN = StsGetParam(funcindex, "A_V_AISEN");
	CParam *A_V_BISEN = StsGetParam(funcindex, "A_V_BISEN");
	CParam *A_V_VINT = StsGetParam(funcindex, "A_V_VINT");
	CParam *A_ISENSE = StsGetParam(funcindex, "A_ISENSE");
	CParam *B_ISENSE = StsGetParam(funcindex, "B_ISENSE");
	CParam *t_OFF_const = StsGetParam(funcindex, "t_OFF_const");
	CParam *VM_UVLO_report = StsGetParam(funcindex, "VM_UVLO_report");
	CParam *VM_UVLO_recovery = StsGetParam(funcindex, "VM_UVLO_recovery");
	CParam *I_OCP_N = StsGetParam(funcindex, "I_OCP_N");
	CParam *I_OCP_P = StsGetParam(funcindex, "I_OCP_P");
	CParam *t_DEG = StsGetParam(funcindex, "t_DEG");
	CParam *t_OCP = StsGetParam(funcindex, "t_OCP");
	//}}AFX_STS_PARAM_PROTOTYPES

	// Power Supplies (VM, VINT)------Start---------------------------//
	// Test number 3

	I_VM_slp->SetTestResult(SITE_1, 0, test_I_VM_slp(DEFAULT_SAMPLES_NUMBER, DEFAULT_MEASURE_INTERVAL));

	return 0;
}
