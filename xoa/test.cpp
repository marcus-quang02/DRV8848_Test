#include "stdafx.h"
//////////////////////////////////////////////// define variable //////////////////////////////////////////
/*voltage*/
#define LOGIC_HIGH_VOLTAGE 3.3 // logic high voltage = 3.3V
#define LOGIC_LOW_VOLTAGE 0	   // logic low voltage = 0V
#define EC_VM_VOLTAGE 12	   // V_VM = 12V in EC_Measure function

/*time*/
#define TIME_WAIT_US 1000			   // time wait before measure
#define SAMPLE_TIME_MEASURE 200		   // sample time = 200 times, using when use MeasureVI
#define SAMPLE_PERIOD_MEASURE 200	   // sample period = 200 us, using when use MeasureVI
#define SAMPLE_TIME_SHORT_MEASURE 10   // sample time = 10 times, using when want to quick measure
#define SAMPLE_PERIOD_SHORT_MEASURE 10 // sample period = 10 us, using when want to quick measure

/* current */
#define KELVIN_CURRENT_TEST 5e-3 // I = 5mA

// multisite settings should be included here
/*The following code was created for STS PinPlanner,don't modify*/
/****STS_PINPLANNER_CODE_BEGIN****/
#define STS_SITE_NUM 1
/****PIN GROUP DEFINITION****/
FPVI10 VM(0, "VM");
FPVI10 AOUT1(1, "AOUT1");
FPVI10 AOUT2(2, "AOUT2");
FOVI nSLEEP(0, "nSLEEP");
FOVI BOUT2(1, "BOUT2");
FOVI BISEN(2, "BISEN");
FOVI BOUT1(3, "BOUT1");
FOVI BIN1(4, "BIN1");
FOVI BIN2(5, "BIN2");
FOVI VREF(6, "VREF");
FOVI VINT(7, "VINT");
FOVI AIN2(8, "AIN2");
FOVI AIN1(9, "AIN1");
QTMU_PLUS qtmu0(0, "qtmu0");
QTMU_PLUS qtmu1(1, "qtmu1");
QTMU_PLUS qtmu2(2, "qtmu2");
FPVI10 AISEN(3, "AISEN");
FOVI nFAULT(10, "nFAULT");

/****multisite settings should be included here****/
DUT_API void HardWareCfg()
{
	STSSetModuleToSite(MD_FPVI10, SITE_1, 0, 2, 3, 1);
	STSSetModuleToSite(MD_FOVI, SITE_1, 0, 3, 2, 4, 5, 6, 7, 8, 9, 10, 1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, 1, 2);
}
/****STS_PINPLANNER_CODE_END****/

CBIT128 cbit;
// define CBIT channel
#define CBIT_nSLEEP 0  // nSLEEP using CBIT0 to switch between FOVI0 and QTMU_0_L, CBIT0 ON <-> QTMU_0_L
#define CBIT_AOUT1 16  // AOUT1 using CBIT16 to switch between FOVI1 and QTMU_1_L, CBIT16 ON <-> QTMU_1_L
#define CBIT_BOUT1 15  // BOUT1 using CBIT15 to switch between FOVI4 and QTMU_2_L, CBIT15 ON <-> QTMU_2_L
#define CBIT_nFAULT 17 // nFAULT using CBIT17 to switch between FPVI1 and QTMU_0_R, CBIT17 ON <-> QTMU_0_R
#define CBIT_BIN1 8	   // BIN1 using CBIT8 to switch between FOVI5 and DIO1/QTMU_2_R, CBIT8 ON <-> DIO1/QTMU_2_R
#define CBIT_AIN1 6	   // AIN1 using CBIT6 to switch between FOVI10 and DIO0/QTMU_1_R, CBIT6 ON <-> DIO0/QTMU_1_R
/****multisite settings should be included here****/

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

///////////////////////////////////////////////////////// General function //////////////////////////////////////////////////
/*global variable*/
double adresult = 0.0;

/*start for FPVI module*/
void FPVI_set_0V(FPVI10 &pin)
{
	pin.Set(FV, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON);
}
/*end for FPVI module*/
/*start for FOVI module*/
void FOVI_set_0V(FOVI &pin)
{
	pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
}
/*end for FOVI module*/

// Set all pin voltage to 0V
void pin_init()
{
	cbit.SetOn(-1);		 // Turn off all CBIT
	FPVI_set_0V(VM);	 // Set V_VM = 0V
	FPVI_set_0V(AISEN);	 // Set V_AISEN = 0V
	FPVI_set_0V(AOUT1);	 // Set V_AOUT1 = 0V
	FPVI_set_0V(AOUT2);	 // Set V_AOUT2 = 0V
	FOVI_set_0V(nSLEEP); // Set V_nSLEEP = 0V
	FOVI_set_0V(nFAULT); // Set V_nFAULT = 0V
	FOVI_set_0V(BISEN);	 // Set V_BISEN = 0V
	FOVI_set_0V(BOUT2);	 // Set V_BOUT2 = 0V
	FOVI_set_0V(BOUT1);	 // Set V_BOUT1 = 0V
	FOVI_set_0V(BIN1);	 // Set V_BIN1 = 0V
	FOVI_set_0V(BIN2);	 // Set V_BIN2 = 0V
	FOVI_set_0V(VREF);	 // Set V_VREF = 0V
	FOVI_set_0V(VINT);	 // Set V_VINT = 0V
	FOVI_set_0V(AIN1);	 // Set V_AIN1 = 0V
	FOVI_set_0V(AIN2);	 // Set V_AIN2 = 0V
}

/* KELVIN TEST */
/*
	brief: force current to each pin, the measure back the value
*/

double KELVIN_FPVI10(FPVI10 &PIN)
{
	PIN.Set(FI, KELVIN_CURRENT_TEST, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	PIN.MeasureVI(SAMPLE_TIME_SHORT_MEASURE, SAMPLE_PERIOD_SHORT_MEASURE);
	return PIN.GetMeasResult(0, MIRET);
}

double KELVIN_FOVI(FOVI &PIN)
{
	PIN.Set(FI, KELVIN_CURRENT_TEST, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	PIN.MeasureVI(SAMPLE_TIME_SHORT_MEASURE, SAMPLE_PERIOD_SHORT_MEASURE);
	return PIN.GetMeasResult(0, MIRET);
}

double OS_FPVI10(FPVI10 &PIN, double current)
{
	PIN.Set(FI, current, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	PIN.MeasureVI(SAMPLE_TIME_SHORT_MEASURE, SAMPLE_PERIOD_SHORT_MEASURE);
	return PIN.GetMeasResult(0, MIRET);
}

double OS_FOVI(FOVI &PIN, double current)
{
	PIN.Set(FI, current, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	PIN.MeasureVI(SAMPLE_TIME_SHORT_MEASURE, SAMPLE_PERIOD_SHORT_MEASURE);
	return PIN.GetMeasResult(0, MIRET);
}

DUT_API int TEST_KELVIN(short funcindex, LPCTSTR funclabel)
{
	//{{AFX_STS_PARAM_PROTOTYPES
	CParam *R_nSLEEP_KELVIN = StsGetParam(funcindex, "R_nSLEEP_KELVIN");
	CParam *R_AOUT1_KELVIN = StsGetParam(funcindex, "R_AOUT1_KELVIN");
	CParam *R_AOUT2_KELVIN = StsGetParam(funcindex, "R_AOUT2_KELVIN");
	CParam *R_BOUT2_KELVIN = StsGetParam(funcindex, "R_BOUT2_KELVIN");
	CParam *R_BOUT1_KELVIN = StsGetParam(funcindex, "R_BOUT1_KELVIN");

	CParam *R_AISEN_KELVIN = StsGetParam(funcindex, "R_AISEN_KELVIN");
	CParam *R_BISEN_KELVIN = StsGetParam(funcindex, "R_BISEN_KELVIN");
	CParam *R_AIN1_KELVIN = StsGetParam(funcindex, "R_AIN1_KELVIN");
	CParam *R_AIN2_KELVIN = StsGetParam(funcindex, "R_AIN2_KELVIN");
	CParam *R_BIN2_KELVIN = StsGetParam(funcindex, "R_BIN2_KELVIN");
	CParam *R_BIN1_KELVIN = StsGetParam(funcindex, "R_BIN1_KELVIN");

	CParam *R_nFAULT_KELVIN = StsGetParam(funcindex, "R_nFAULT_KELVIN");
	CParam *R_VINT_KELVIN = StsGetParam(funcindex, "R_VINT_KELVIN");
	CParam *R_VM_KELVIN = StsGetParam(funcindex, "R_VM_KELVIN");
	CParam *R_VREF_KELVIN = StsGetParam(funcindex, "R_VREF_KELVIN");
	//}}AFX_STS_PARAM_PROTOTYPES

	// TODO: Add your function code here
	// FPVI pin
	R_VM_KELVIN->SetTestResult(0, 0, KELVIN_FPVI10(VM));
	R_AISEN_KELVIN->SetTestResult(0, 0, KELVIN_FPVI10(AISEN));
	R_AOUT1_KELVIN->SetTestResult(0, 0, KELVIN_FPVI10(AOUT1));
	R_AOUT2_KELVIN->SetTestResult(0, 0, KELVIN_FPVI10(AOUT2));
	// FOVI pin
	R_nSLEEP_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(nSLEEP));
	R_BOUT2_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(BOUT2));
	R_BISEN_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(BISEN));
	R_BOUT1_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(BOUT1));
	R_nFAULT_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(nFAULT));
	R_BIN1_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(BIN1));
	R_BIN2_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(BIN2));
	R_VREF_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(VREF));
	R_VINT_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(VINT));
	R_AIN2_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(AIN2));
	R_AIN1_KELVIN->SetTestResult(0, 0, KELVIN_FOVI(AIN1));
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

	OS_nSLEEP->SetTestResult(0, 0, OS_FOVI(nSLEEP, -1e-3));
	OS_AOUT1->SetTestResult(0, 0, OS_FPVI10(AOUT1, -5e-3));
	OS_AOUT2->SetTestResult(0, 0, OS_FPVI10(AOUT2, -5e-3));
	OS_BOUT1->SetTestResult(0, 0, OS_FOVI(BOUT1, -5e-3));
	OS_BOUT2->SetTestResult(0, 0, OS_FOVI(BOUT2, -5e-3));

	OS_AISEN->SetTestResult(0, 0, OS_FPVI10(AISEN, -1e-3));
	OS_BISEN->SetTestResult(0, 0, OS_FOVI(BISEN, -1e-3));
	OS_nFAULT->SetTestResult(0, 0, OS_FOVI(nFAULT, -1e-3));
	OS_AIN1->SetTestResult(0, 0, OS_FOVI(AIN1, -1e-3));
	OS_AIN2->SetTestResult(0, 0, OS_FOVI(AIN2, -1e-3));
	OS_BIN1->SetTestResult(0, 0, OS_FOVI(BIN1, -1e-3));
	OS_BIN2->SetTestResult(0, 0, OS_FOVI(BIN2, -1e-3));

	OS_VREF->SetTestResult(0, 0, OS_FOVI(VREF, -1e-3));
	OS_VINT->SetTestResult(0, 0, OS_FOVI(VINT, -1e-3));
	OS_VM->SetTestResult(0, 0, OS_FPVI10(VM, -5e-3));

	// TODO: Add your function code here
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

///////////////////////////////////////////////////////// EC MEASURE //////////////////////////////////////////////////////s
// floating AOUT1 & AOUT2
void EC_MEASURE_AOUTx_float()
{
	AOUT1.Set(FV, LOGIC_LOW_VOLTAGE, FPVI10_5V, FPVI10_10MA, RELAY_OFF); // AOUT1 floating
	AOUT2.Set(FV, LOGIC_LOW_VOLTAGE, FPVI10_5V, FPVI10_10MA, RELAY_OFF); // AOUT2 floating
}

// floating BOUT1 & BOUT2
void EC_MEASURE_BOUTx_float()
{
	BOUT1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_OFF); // BOUT1 floating
	BOUT2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_10MA, RELAY_OFF); // BOUT2 floating
}

// setup before start EC_MEASURE
void EC_MEASURE_setup()
{
	pin_init();
	qtmu0.Init();													 // initialize qtmu0 channel
	qtmu1.Init();													 // initialize qtmu1 channel
	qtmu2.Init();													 // initialize qtmu2 channel
	VM.Set(FV, EC_VM_VOLTAGE, FPVI10_20V, FPVI10_1A, RELAY_ON);		 // Set V_VM = 12V
	nFAULT.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_1MA, RELAY_ON); // Set V_nFAULT = LOGIC_HIGH_VOLTAGE, limit current = 1mA
}

// EC_VM operating supply current
void EC_MEASURE_I_VM_setup()
{
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	EC_MEASURE_AOUTx_float(); // AOUTx float
	EC_MEASURE_BOUTx_float(); // BOUTx float
}

/* Input logic low voltage */ /* y=AorB, x=1or2 */
double EC_MEASURE_input_logic_low_voltage(FOVI &yINx, FPVI10 &yOUTx)
{
	double result = 0.0;
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN1   = 0V
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN2	  = 0V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN1	  = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN2	  = 0V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.1 * LOGIC_HIGH_VOLTAGE; // trig voltage = 0.33V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 3.3;						// sweep data from 3.3V to 0V
	double stop_voltage = 0;						// sweep data from 3.3V to 0V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "V_L_yINx", set FV mode.
	yINx.AwgLoader("V_L_yINx", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	yINx.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set BINx to 3.3V
	// Select pattern of "V_L_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	yINx.AwgSelect("V_L_yINx", 0, sam - 1, sam - 1, interval);
	yOUTx.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	yINx.MeasureVI(sam, interval, MEAS_AWG);		// Make sure each step always measure
	STSEnableAWG(&yINx);							// enable AWG pattern for yINx
	STSEnableMeas(&yINx);							// enable measurement for yINx
	STSAWGRun();									// Enable AWG and measurement synchronously
	// measure block
	Trig_Point = yINx.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for yINx
	result = yINx.GetMeasResult(0, MVRET, Trig_Point);		// Read the voltage value of yINx on trigger position
	return result;
}
double EC_MEASURE_input_logic_low_voltage(FOVI &yINx, FOVI &yOUTx)
{
	double result = 0.0;
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN1   = 0V
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN2	  = 0V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN1	  = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN2	  = 0V

	// Prepare AWG Data
	int Trig_Point = 0;								// moment when catch trigger point
	double trig_voltage = 0.1 * LOGIC_HIGH_VOLTAGE; // trig voltage = 0.33V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 3.3;						// sweep data from 3.3V to 0V
	double stop_voltage = 0;						// sweep data from 3.3V to 0V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "V_L_yINx", set FV mode.
	yINx.AwgLoader("V_L_yINx", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	yINx.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set BINx to 3.3V
	// Select pattern of "V_L_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	yINx.AwgSelect("V_L_yINx", 0, sam - 1, sam - 1, interval);
	yOUTx.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	yINx.MeasureVI(sam, interval, MEAS_AWG);		// Make sure each step always measure
	yOUTx.MeasureVI(sam, interval, MEAS_AWG);		// Make sure each step always measure

	STSEnableAWG(&yINx);		  // enable AWG pattern for yINx
	STSEnableMeas(&yINx, &yOUTx); // enable measurement for yINx
	STSAWGRun();				  // Enable AWG and measurement synchronously

	// measure block
	Trig_Point = yOUTx.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for yINx
	result = awg_pattern[Trig_Point];						 // Read the voltage value of yINx on trigger position, use the voltage value in awg_pattern as result because it's more accurate than measure result
	return result;
}
/* Input logic high voltage */ /* y=AorB, x=1or2 */
double EC_MEASURE_input_logic_high_voltage(FOVI &yINx, FPVI10 &yOUTx)
{
	double result = 0.0;
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN1   = 0V
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN2	  = 0V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN1	  = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN2	  = 0V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.9 * LOGIC_HIGH_VOLTAGE; // trig voltage = 2.97V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 0;						// sweep data from 0V to 3.3V
	double stop_voltage = 3.3;						// sweep data from 0V to 3.3V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "V_H_yINx", set FV mode.
	yINx.AwgLoader("V_H_yINx", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	yINx.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set yINx to 3.3V
	// Select pattern of "V_H_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	yINx.AwgSelect("V_H_BINx", 0, sam - 1, sam - 1, interval);
	yOUTx.SetMeasVTrig(trig_voltage, TRIG_RISING); // Set trigger at trig_voltage, rising
	yINx.MeasureVI(sam, interval, MEAS_AWG);	   // Make sure each step always measure
	STSEnableAWG(&yINx);						   // enable AWG pattern for BINx
	STSEnableMeas(&yINx);						   // enable measurement for BINx
	STSAWGRun();								   // Enable AWG and measurement synchronously
	// measure block
	Trig_Point = yINx.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for yINx
	result = yINx.GetMeasResult(0, MVRET, Trig_Point);		// Read the voltage value of yINx on trigger position
	return result;
}
double EC_MEASURE_input_logic_high_voltage(FOVI &yINx, FOVI &yOUTx)
{
	double result = 0.0;
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN1   = 0V
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set AIN2	  = 0V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN1	  = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set BIN2	  = 0V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.9 * LOGIC_HIGH_VOLTAGE; // trig voltage = 2.97V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 0;						// sweep data from 0V to 3.3V
	double stop_voltage = 3.3;						// sweep data from 0V to 3.3V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "V_H_yINx", set FV mode.
	yINx.AwgLoader("V_H_yINx", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	yINx.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set yINx to 3.3V
	// Select pattern of "V_H_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	yINx.AwgSelect("V_H_BINx", 0, sam - 1, sam - 1, interval);
	yOUTx.SetMeasVTrig(trig_voltage, TRIG_RISING); // Set trigger at trig_voltage, rising
	yINx.MeasureVI(sam, interval, MEAS_AWG);	   // Make sure each step always measure
	STSEnableAWG(&yINx);						   // enable AWG pattern for BINx
	STSEnableMeas(&yINx);						   // enable measurement for BINx
	STSAWGRun();								   // Enable AWG and measurement synchronously

	// measure block
	Trig_Point = yINx.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for yINx
	result = yINx.GetMeasResult(0, MVRET, Trig_Point);		// Read the voltage value of yINx on trigger position
	return result;
}
/* Tri level input Hi-Z voltage */
double EC_MEASURE_tri_level_input_hi_z_voltage(FOVI &AINx)
{
	double result = 0.0;
	EC_MEASURE_AOUTx_float();
	EC_MEASURE_BOUTx_float();
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_OFF); // Set AIN1 float
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_OFF); // Set AIN2	float
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	 // Set BIN1	  = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	 // Set BIN2	  = 0V
	delay_us(TIME_WAIT_US);											 // wait before delay
	AINx.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);		 // Measure at AIN pin
	result = AINx.GetMeasResult(0, MVRET);
	return result;
}

/* POWER FET on resistance */
void EC_MEASURE_POWER_FET_on_resistance_setup()
{
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	 // Set AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	 // Set BIN1	= 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	 // Set BIN2	= 0V
	AOUT1.Set(FI, 0.5, FPVI10_10V, FPVI10_1A, RELAY_ON);			 // Force current to AOUT1 <-> connect IDC = 0.5mA to VM
	AOUT2.Set(FI, -0.5, FPVI10_10V, FPVI10_1A, RELAY_ON);			 // Sink current from AOUT2 <-> connect IDC = 0.5mA to GND
}

/* xISEN trip voltage */ /*x = AorB*/ /*FOVI & FPVI*/
double EC_MEASURE_xISEN_trip_voltage(FPVI10 &xISEN, FPVI10 &xOUT)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG data
	double Trig_Point = 0.0;		 // moment when catch trigger point
	double trig_voltage = 6;		 // trig voltage = 6V
	int sam = 100;					 // data size of AWG pattern
	int interval = 10;				 // interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0}; // array save waveform data
	double start_voltage = 0;		 // sweep xISEN from 0V to 0.6V
	double stop_voltage = 0.6;		 // sweep xISEN from 0V to 0.6V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to xISEN, named "V_TRIP_xISEN", set FV mode.
	xISEN.AwgLoader("V_TRIP_xISEN", FV, FPVI10_1V, FPVI10_100MA, awg_pattern, sam);
	xISEN.Set(FV, start_voltage, FPVI10_1V, FPVI10_100MA, RELAY_ON); // Set xISEN to 0V
	// Select pattern of "V_H_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	xISEN.AwgSelect("V_TRIP_xISEN", 0, sam - 1, sam - 1, interval);
	xOUT.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	xISEN.MeasureVI(sam, interval, MEAS_AWG);	   // Make sure each step always measure
	STSEnableAWG(&xISEN);						   // enable AWG pattern for xISEN
	STSEnableMeas(&xISEN);						   // enable measurement for xISEN
	STSAWGRun();								   // Enable AWG and measurement synchronously
	// measure block
	Trig_Point = xISEN.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for xISEN
	result = xISEN.GetMeasResult(0, MVRET, Trig_Point);		 // Read the voltage value of xISEN on trigger position
	return result;
}
double EC_MEASURE_xISEN_trip_voltage(FOVI &xISEN, FOVI &xOUT)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG data
	double Trig_Point = 0.0;		 // moment when catch trigger point
	double trig_voltage = 6;		 // trig voltage = 6V
	int sam = 100;					 // data size of AWG pattern
	int interval = 10;				 // interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0}; // array save waveform data
	double start_voltage = 0;		 // sweep xISEN from 0V to 0.6V
	double stop_voltage = 0.6;		 // sweep xISEN from 0V to 0.6V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to xISEN, named "V_TRIP_xISEN", set FV mode.
	xISEN.AwgLoader("V_TRIP_xISEN", FV, FOVI_1V, FOVI_100MA, awg_pattern, sam);
	xISEN.Set(FV, start_voltage, FOVI_1V, FOVI_100MA, RELAY_ON); // Set xISEN to 0V
	// Select pattern of "V_H_yINx", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	xISEN.AwgSelect("V_TRIP_xISEN", 0, sam - 1, sam - 1, interval);
	xOUT.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	xISEN.MeasureVI(sam, interval, MEAS_AWG);	   // Make sure each step always measure
	STSEnableAWG(&xISEN);						   // enable AWG pattern for xISEN
	STSEnableMeas(&xISEN);						   // enable measurement for xISEN
	STSAWGRun();								   // Enable AWG and measurement synchronously
	// measure block
	Trig_Point = xISEN.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for xISEN
	result = xISEN.GetMeasResult(0, MVRET, Trig_Point);		 // Read the voltage value of xISEN on trigger position
	return result;
}

/* VM undervoltage lockout */
double EC_MEASURE_VVM_falling()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.1 * LOGIC_HIGH_VOLTAGE; // trig voltage = 0.33V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 5;						// sweep data from 5V to 0V
	double stop_voltage = 0;						// sweep data from 5V to 0V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "UVLO_report", set FV mode.
	VM.AwgLoader("UVLO_report", FV, FPVI10_5V, FPVI10_100MA, awg_pattern, sam);
	VM.Set(FV, start_voltage, FPVI10_5V, FPVI10_100MA, RELAY_ON); // Set VM to 5V
	// Select pattern of "UVLO_report", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	VM.AwgSelect("UVLO_report", 0, sam - 1, sam - 1, interval);
	nFAULT.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	VM.MeasureVI(sam, interval, MEAS_AWG);			 // Make sure each step always measure
	STSEnableAWG(&VM);								 // enable AWG pattern for VM
	STSEnableMeas(&VM);								 // enable measurement for VM
	STSAWGRun();									 // Enable AWG and measurement synchronously
	// measure block
	Trig_Point = VM.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for VM
	result = VM.GetMeasResult(0, MVRET, Trig_Point);	  // Read the voltage value of VM on trigger position
	return result;
}

double EC_MEASURE_VVM_rising()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.9 * LOGIC_HIGH_VOLTAGE; // trig voltage = 2.97V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_voltage = 0;						// sweep data from 0V to 5V
	double stop_voltage = 5;						// sweep data from 0V to 5V
	// AWG
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_voltage, stop_voltage);
	// import awg_pattern array to yINx, named "UVLO_recovery", set FV mode.
	VM.AwgLoader("UVLO_recovery", FV, FPVI10_5V, FPVI10_100MA, awg_pattern, sam);
	VM.Set(FV, start_voltage, FPVI10_5V, FPVI10_100MA, RELAY_ON); // Set VM to 5V
																  // Select pattern of "UVLO_recovery", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	VM.AwgSelect("UVLO_recovery", 0, sam - 1, sam - 1, interval);
	nFAULT.SetMeasVTrig(trig_voltage, TRIG_RISING);		  // Set trigger at trig_voltage, rising
	VM.MeasureVI(sam, interval, MEAS_AWG);				  // Make sure each step always measure
	STSEnableAWG(&VM);									  // enable AWG pattern for VM
	STSEnableMeas(&VM);									  // enable measurement for VM
	STSAWGRun();										  // Enable AWG and measurement synchronously
														  // measure block
	Trig_Point = VM.GetMeasResult(0, MVRET, TRIG_RESULT); // Get the position of trigger point for VM
	result = VM.GetMeasResult(0, MVRET, Trig_Point);	  // Read the voltage value of VM on trigger position
	return result;
}

/* Overcurrent protection trip level */
double EC_MEASURE_I_OCP_N()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // nSLEEP = 3.3V
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.1 * LOGIC_HIGH_VOLTAGE; // trig voltage = 0.33V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_value = 0;							// sweep data from 0A to 4A
	double stop_value = 4;							// sweep data from 0A to 4A
	/*AWG*/
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_value, stop_value);
	// import awg_pattern array to AOUT1, name I_OCP_N, set FI mode
	AOUT1.AwgLoader("I_OCP_N", FI, FPVI10_10V, FPVI10_10A, awg_pattern, sam);
	AOUT1.Set(FI, start_value, FPVI10_10V, FPVI10_10A, RELAY_ON);
	// Select pattern of "I_OCP_N", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	AOUT1.AwgSelect("I_OCP_N", 0, sam - 1, sam - 1, interval);
	nFAULT.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	AOUT1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AOUT1);
	STSEnableMeas(&AOUT1);
	STSAWGRun();
	// measure
	Trig_Point = AOUT1.GetMeasResult(0, MIRET, TRIG_RESULT);
	result = AOUT1.GetMeasResult(0, MIRET, Trig_Point); // uint A
	return result;
}

double EC_MEASURE_I_OCP_P()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // nSLEEP = 3.3V
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Prepare AWG Data
	double Trig_Point = 0.0;						// moment when catch trigger point
	double trig_voltage = 0.1 * LOGIC_HIGH_VOLTAGE; // trig voltage = 0.33V
	int sam = 100;									// data size of AWG pattern
	int interval = 10;								// interval time of AWG pattern, unit is uS
	double awg_pattern[100] = {0.0};				// array save waveform data
	double start_value = 0;							// sweep data from 0A to 4A
	double stop_value = -4;							// sweep data from 0A to 4A (using -4 because IC sink current)
	/*AWG*/
	// set an ramp data array, start address start from, data size = 100, begin start_voltage to stop_voltage
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_value, stop_value);
	// import awg_pattern array to AOUT2, name I_OCP_P, set FI mode
	AOUT2.AwgLoader("I_OCP_P", FI, FPVI10_10V, FPVI10_10A, awg_pattern, sam);
	AOUT2.Set(FI, start_value, FPVI10_10V, FPVI10_10A, RELAY_ON);
	// Select pattern of "I_OCP_P", start step = 0, stop = sam - 1, loop = sam - 1, interval time (each step) = 10us
	AOUT2.AwgSelect("I_OCP_P", 0, sam - 1, sam - 1, interval);
	nFAULT.SetMeasVTrig(trig_voltage, TRIG_FALLING); // Set trigger at trig_voltage, falling
	AOUT2.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AOUT2);
	STSEnableMeas(&AOUT2);
	STSAWGRun();
	// measure
	Trig_Point = AOUT2.GetMeasResult(0, MIRET, TRIG_RESULT);
	result = AOUT2.GetMeasResult(0, MIRET, Trig_Point);
	return result;
}

/*Sleep time*/
// double EC_MEASURE_sleep_time() {
//	EC_MEASURE_BOUTx_float();
//	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);			// AIN1 = 0V
//	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);		// AIN2 = 3.3V
//	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);			// BIN1 = 0V
//	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);		// BIN2 = 3.3V
//	AOUT1.Set(FI, 1e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);					// Force current = 1mA to AOUT1
//	AOUT2.Set(FI, -1e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);					// Sink current = 1mA from AOUT2
//	// Prepare AWG Data
//	double Trig_Point = 0.0;												// moment when catch trigger point
//	double trig_voltage_nSLEEP = 1.6;										// trig voltage for nSLEEP = 1.6V
//	double trip_voltage_AOUT1 = 0.1 * LOGIC_HIGH_VOLTAGE;					// trig voltage for AOUT1 = 0.33V (HIGH to LOW)
//	int sam = 100;															// data size of AWG pattern
//	int interval = 10;														// interval time of AWG pattern, unit is uS
//	double awg_pattern[100] = { 0.0 };										// array save waveform data
//	double start_voltage = 3.3;												// sweep data from 3.3V to 0V
//	double stop_voltage = 0;												// sweep data from 3.3V to 0V
//	//
// }

/* Output logic low voltage */
double EC_MEASURE_V_L_nFAULT()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // float AOUTx
	EC_MEASURE_BOUTx_float();										   // float BOUTx
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	AISEN.Set(FV, 0, FPVI10_1V, FPVI10_10A, RELAY_ON);				   // Set AISEN = 0V, CURRENT_LIMIT = 10A ?????
	delay_us(TIME_WAIT_US);
	AISEN.Set(FV, 1, FPVI10_1V, FPVI10_10A, RELAY_ON);	 // Set AISEN = 1V, CURRENT_LIMIT = 10A ?????
	nFAULT.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON); // Sink current from nFAULT pin = 5mA
	delay_us(TIME_WAIT_US);
	nFAULT.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	return result = nFAULT.GetMeasResult(0, MVRET);
}

/* Output rise time */
double EC_MEASURE_output_time(double start_trigger, double stop_trigger, bool rising)
{
	double result = 0.0;
	cbit.SetOn(CBIT_AOUT1, -1);										   // Switch AOUT1 to qtmu block
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // Set AOUTx float
	EC_MEASURE_BOUTx_float();										   // Set BOUTx float
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN2 = 0V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN2 = 0V
	// QTMU Prepare
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	if (rising)
	{
		qtmu0.SetStartTrigger(start_trigger, QTMU_PLUS_POS_SLOPE);
		qtmu0.SetStopTrigger(stop_trigger, QTMU_PLUS_POS_SLOPE);
	}
	else
	{
		qtmu0.SetStartTrigger(start_trigger, QTMU_PLUS_NEG_SLOPE);
		qtmu0.SetStopTrigger(stop_trigger, QTMU_PLUS_NEG_SLOPE);
		AOUT1.Set(FV, LOGIC_HIGH_VOLTAGE, FPVI10_5V, FPVI10_1A, RELAY_ON);
	}
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);
	qtmu0.ChannelSetup(QTMU_PLUS_CHA_START);
	qtmu0.Connect(); // Connect output relay of qtmu0
	delay_us(TIME_WAIT_US);
	// Start measure
	if (rising)
	{
		AOUT1.Set(FV, LOGIC_HIGH_VOLTAGE, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.1);
	}
	else
	{
		AOUT1.Set(FV, LOGIC_LOW_VOLTAGE, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.1);
	}
	qtmu0.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_NS);
	result = qtmu0.GetMeasureResult(0); // return value in uS
	return result * 1000;				// change result units to ns
}

/* Sleep time */ /* Wake time */
double EC_MEASURE_TIME(double start_value, double stop_value, double trig_nSLEEP, double trig_AOUT, bool rising)
{
	double result = 0.0;
	EC_MEASURE_BOUTx_float();								 // float BOUTx
	AOUT1.Set(FI, 1e-3, FPVI10_5V, FPVI10_100MA, RELAY_ON);	 // AOUT1 connect IDC1 = 1mA to VM
	AOUT2.Set(FI, -1e-3, FPVI10_5V, FPVI10_100MA, RELAY_ON); // AOUT2 connect IDC2 = 1mA to GND
	AIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // AIN1 = 0V
	AIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // AIN2 = 3.3V
	BIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // BIN1 = 0V
	BIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // BIN2 = 0V
	// AWG prepare
	int trig_point_nsleep = 0, trig_point_aout = 0;
	int sam = 100;	   // sample = 100
	int interval = 10; // interval = 10us
	double awg_pattern[100];
	// AWG setup data
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_value, stop_value); // define a ramp data from start_value to stop_value
	nSLEEP.AwgLoader("nSleep", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);	// import 100 points of awg_pattern into RAM
	nSLEEP.Set(FV, start_value, FOVI_5V, FOVI_100MA, RELAY_ON);				// Set the Vrange, Irange must be consistent with the AwgLoader
	nSLEEP.AwgSelect("nSleep", 0, sam - 1, sam - 1, interval);
	if (rising)
	{
		nSLEEP.SetMeasVTrig(trig_nSLEEP, TRIG_RISING);
		AOUT1.SetMeasVTrig(trig_AOUT, TRIG_RISING);
	}
	else
	{
		nSLEEP.SetMeasVTrig(trig_nSLEEP, TRIG_FALLING);
		AOUT1.SetMeasVTrig(trig_AOUT, TRIG_FALLING);
	}
	nSLEEP.MeasureVI(sam, interval, MEAS_AWG);
	AOUT1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&nSLEEP);			// enable synchoronous awg for VIN
	STSEnableMeas(&nSLEEP, &AOUT1); // enable synchronouse measurement for VIN
	STSAWGRun();					// start AWG and measure synchronously
	// Measure
	trig_point_nsleep = nSLEEP.GetMeasResult(0, MVRET, TRIG_RESULT);
	trig_point_aout = nSLEEP.GetMeasResult(0, MVRET, TRIG_RESULT);
	result = (trig_point_aout - trig_point_nsleep) * 10; // * 10 <-> interval = 10us, result uint is us
	return result;
}

/* Power on time */
double EC_MEASURE_power_on_time()
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	EC_MEASURE_BOUTx_float();								 // float BOUTx
	AOUT1.Set(FI, 1e-3, FPVI10_5V, FPVI10_100MA, RELAY_ON);	 // AOUT1 connect IDC1 = 1mA to VM
	AOUT2.Set(FI, -1e-3, FPVI10_5V, FPVI10_100MA, RELAY_ON); // AOUT2 connect IDC2 = 1mA to GND
	AIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // AIN1 = 0V
	AIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // AIN2 = 3.3V
	BIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // BIN1 = 0V
	BIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);			 // BIN2 = 0V
	// AWG prepare
	double trig_point_nfault = 0, trig_point_aout = 0;
	double trig_nFault_value = 3.0, trig_aout_value = 0.9 * LOGIC_HIGH_VOLTAGE;
	int sam = 100;
	int interval = 10; // interval = 10us
	double awg_pattern[100] = {0.0};

	// AWG setup
	STSAWGCreateSineData(&awg_pattern[0], sam, 1, 0, 12);
	VM.AwgLoader("VM", FV, FPVI10_20V, FPVI10_1A, awg_pattern, sam);
	VM.Set(FV, 0, FPVI10_20V, FPVI10_1A, RELAY_ON);
	VM.AwgSelect("VM", 0, sam - 1, sam - 1, interval);

	nFAULT.SetMeasVTrig(trig_nFault_value, TRIG_RISING);
	AOUT1.SetMeasVTrig(trig_aout_value, TRIG_RISING);

	nFAULT.MeasureVI(sam, interval, MEAS_AWG);
	AOUT1.MeasureVI(sam, interval, MEAS_AWG);

	STSEnableAWG(&VM);
	STSEnableMeas(&nFAULT, &AOUT1);
	STSAWGRun();

	// Measure
	trig_point_nfault = nFAULT.GetMeasResult(0, MVRET, TRIG_RESULT);
	trig_point_aout = AOUT1.GetMeasResult(0, MVRET, TRIG_RESULT);
	result = (trig_point_aout - trig_point_nfault) * 10;
	return result;
}

/* Propagation delay */
double EC_MEASURE_propagation_delay(FOVI &INx, FPVI10 &OUTx, double start_point, double stop_point, double trig_in, double trig_out)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	EC_MEASURE_AOUTx_float();						// float AOUTx
	EC_MEASURE_BOUTx_float();						// float BOUTx
	AIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // AIN1 = 0V
	AIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // AIN2 = 0V
	BIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // BIN1 = 0V
	BIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // BIN2 = 0V
	// AWG Prepare
	int trig_point_in = 0, trig_point_out = 0;
	int sam = 100;
	int interval = 10;
	double awg_pattern[100] = {0.0};
	// AWG setup
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_point, stop_point);
	INx.AwgLoader("t_PROP", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	INx.Set(FV, start_point, FOVI_5V, FOVI_100MA, RELAY_ON);
	INx.AwgSelect("t_PROP", 0, sam - 1, sam - 1, interval);
	INx.SetMeasVTrig(trig_in, TRIG_RISING);
	OUTx.SetMeasVTrig(trig_out, TRIG_RISING);
	INx.MeasureVI(sam, interval, MEAS_AWG);
	OUTx.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&INx);
	STSEnableMeas(&INx, &OUTx);
	STSAWGRun();
	trig_point_in = INx.GetMeasResult(0, MVRET, TRIG_RESULT);
	trig_point_out = OUTx.GetMeasResult(0, MVRET, TRIG_RESULT);
	result = (trig_point_out - trig_point_in) * 10;
	return result;
}
double EC_MEASURE_propagation_delay(FOVI &INx, FOVI &OUTx, double start_point, double stop_point, double trig_in, double trig_out)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	EC_MEASURE_AOUTx_float();						// float AOUTx
	EC_MEASURE_BOUTx_float();						// float BOUTx
	AIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // AIN1 = 0V
	AIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // AIN2 = 0V
	BIN1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // BIN1 = 0V
	BIN2.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // BIN2 = 0V
	// AWG Prepare
	int trig_point_in = 0, trig_point_out = 0;
	int sam = 100;
	int interval = 10;
	double awg_pattern[100] = {0.0};
	// AWG setup
	STSAWGCreateRampData(&awg_pattern[0], sam, 1, start_point, stop_point);
	INx.AwgLoader("t_PROP", FV, FOVI_5V, FOVI_100MA, awg_pattern, sam);
	INx.Set(FV, start_point, FOVI_5V, FOVI_100MA, RELAY_ON);
	INx.AwgSelect("t_PROP", 0, sam - 1, sam - 1, interval);
	INx.SetMeasVTrig(trig_in, TRIG_RISING);
	OUTx.SetMeasVTrig(trig_out, TRIG_RISING);
	INx.MeasureVI(sam, interval, MEAS_AWG);
	OUTx.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&INx);
	STSEnableMeas(&INx, &OUTx);
	STSAWGRun();
	trig_point_in = INx.GetMeasResult(0, MVRET, TRIG_RESULT);
	trig_point_out = OUTx.GetMeasResult(0, MVRET, TRIG_RESULT);
	result = (trig_point_out - trig_point_in) * 10;
	return result;
}

/* Current sense blanking time */
void EC_MEASURE_current_sense_blanking_time(double &freq, double &duty)
{
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // Set AOUTx float
	EC_MEASURE_BOUTx_float();										   // Set BOUTx float
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN2 = 0V
	VREF.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // Set VREF = 0V
	delay_us(TIME_WAIT_US);
	// Setup QTMU and CBIT to measure
	cbit.SetOn(CBIT_AOUT1, -1); // Switch to qtmu on aout1
	qtmu1.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu1.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu1.SetInSource(QTMU_PLUS_SINGLE_SOURCE);
	qtmu1.Connect();
	delay_us(TIME_WAIT_US);
	// COARSE mode, period number = 10, timout = 10ms
	qtmu1.MeasureFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 10, 10);
	freq = qtmu1.GetMeasureResult(0); // return frequency unit KHz
	delay_us(TIME_WAIT_US);
	// trigger = 0.9 * LOGIC_HIGH_VOLTAGE, timeout = 10ms, read duty cycle
	qtmu1.MeasDutyCycle(0.9 * LOGIC_HIGH_VOLTAGE, QTMU_PLUS_LOW_DUTY, 10);
	// Measure time
	duty = qtmu1.GetMeasureResult(0); // return duty cycle unit %
	delay_us(TIME_WAIT_US);
	qtmu1.Disconnect();
	cbit.SetOn(-1); // Turn off all;
}

/* Overcurrent deglitch time */
void EC_MEASURE_overcurrent_deglitch_time(double &freq, double &duty)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON); // Set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();										   // Set AOUTx float
	EC_MEASURE_BOUTx_float();										   // Set BOUTx float
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);	   // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);   // BIN2 = 3.3V
	// Setup measure QTMU
	cbit.SetOn(CBIT_nFAULT, -1); // Change nFAULT pin to QTMU
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStartTrigger(0.9 * LOGIC_HIGH_VOLTAGE, QTMU_PLUS_POS_SLOPE);
	qtmu0.SetStopTrigger(0.9 * LOGIC_HIGH_VOLTAGE, QTMU_PLUS_POS_SLOPE);
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE_CHB); // Only using channel B to measure
	qtmu0.ChannelSetup(QTMU_PLUS_CHA_STOP);			// select CHB to read freq
	qtmu0.Connect();
	delay_us(TIME_WAIT_US);
	// COARSE mode, period number = 5, timeout = 1ms
	qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 5, 1);
	freq = qtmu0.GetMeasureResult(0); // unit KHz
	delay_us(TIME_WAIT_US);
	// trigger = 0.9 * LOGIC_HIGH_VOLTAGE, timeout = 10ms,
	qtmu0.MeasDutyCycle(0.9 * LOGIC_HIGH_VOLTAGE, QTMU_PLUS_LOW_DUTY, 10);
	duty = qtmu0.GetMeasureResult(0); // unit %
	qtmu0.Disconnect();
	cbit.SetOn(-1); // Turn Off all cbit
}

/* Overcurrent protection period */
double EC_MEASURE_overcurrent_protection_period(double i_ocp_n)
{
	double result = 0.0;
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);		 // Set nSLEEP = 3.3V
	EC_MEASURE_AOUTx_float();												 // Set AOUTx float
	EC_MEASURE_BOUTx_float();												 // Set BOUTx float
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);			 // AIN1 = 0V
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);		 // AIN2 = 3.3V
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);			 // BIN1 = 0V
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);		 // BIN2 = 3.3V
	AISEN.Set(FI, (i_ocp_n + 0.1) * 0.25, FPVI10_10V, FPVI10_10A, RELAY_ON); // Set AISEN = (I_OCP_N + 0.1) * 0.25
	// QTMU setup
	cbit.SetOn(CBIT_nFAULT, -1); // Change nFAULT pin to QTMU
	qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE_CHB); // Only using channel B to measure
	qtmu0.ChannelSetup(QTMU_PLUS_CHA_STOP);			// select CHB to read freq
	qtmu0.Connect();
	delay_us(TIME_WAIT_US);
	// COARSE mode, period number = 5, timeout = 1ms
	qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 5, 1);
	result = qtmu0.GetMeasureResult(0); // unit KHz
	delay_us(TIME_WAIT_US);
	return result;
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

	// TODO: Add your function code here
	EC_MEASURE_setup();

	/*2.I_VM */
	// 2.1.I_VM_01	(AIN1 = 0V, AIN2 = 3.3V, BIN1 = 0V, BIN2 = 3.3V)
	AIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN1.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	VM.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE); // 200 samples, 200us period
	adresult = VM.GetMeasResult(0, MIRET);					  // Measure I_VM
	I_VM_01->SetTestResult(0, 0, adresult * 1000);			  // Change unit from A to mA

	// 2.2 I_VM_10 (AIN1 = 3.3V, AIN2 = 0V, BIN1 = 3.3V, BIN2 = 0V)
	AIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	AIN1.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN2.Set(FV, LOGIC_LOW_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN1.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	VM.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	adresult = VM.GetMeasResult(0, MIRET);		   // Measure I_VM
	I_VM_10->SetTestResult(0, 0, adresult * 1000); // Change unit from A to mA

	// 2.3 I_VM_11 (AIN1 = 3.3V, AIN2 = 3.3V, BIN1 = 3.3V, BIN2 = 3.3V)
	AIN1.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	AIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN1.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	BIN2.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	VM.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	adresult = VM.GetMeasResult(0, MIRET);		   // Measure I_VM
	I_VM_11->SetTestResult(0, 0, adresult * 1000); // Change unit from A to mA

	/*4.Sleep time */

	/*5. Wake time */

	/*6. Power on time */

	/*7. VINT Voltage */

	/*8. V_L_BIN1 */

	/*9. V_L_BIN2 */

	/*10. V_L_nSLP */
	double v_l_bin1 = EC_MEASURE_input_logic_low_voltage(BIN1, BOUT1);
	double v_l_bin2 = EC_MEASURE_input_logic_low_voltage(BIN2, BOUT2);
	double v_l_nslp = EC_MEASURE_input_logic_low_voltage(nSLEEP, BOUT2);
	V_L_BIN1->SetTestResult(0, 0, v_l_bin1);
	V_L_BIN2->SetTestResult(0, 0, v_l_bin2);
	V_L_nSLP->SetTestResult(0, 0, v_l_nslp);
	/*11. V_H_BIN1 */
	/*12. V_H_BIN2 */
	/*13. V_H_nSLP */
	double v_h_bin1 = EC_MEASURE_input_logic_high_voltage(BIN1, BOUT1);
	double v_h_bin2 = EC_MEASURE_input_logic_high_voltage(BIN2, BOUT2);
	double v_h_nslp = EC_MEASURE_input_logic_high_voltage(nSLEEP, BOUT2);
	V_H_BIN1->SetTestResult(0, 0, v_h_bin1);
	V_H_BIN2->SetTestResult(0, 0, v_h_bin2);
	V_H_nSLP->SetTestResult(0, 0, v_h_nslp);
	/*14. V_hys_B */
	V_hys_BIN1->SetTestResult(0, 0, v_h_bin1 - v_l_bin1);
	V_hys_BIN2->SetTestResult(0, 0, v_h_bin2 - v_l_bin2);
	V_hys_nSLP->SetTestResult(0, 0, v_h_nslp - v_l_nslp);
	/*15. I_L_BIN1 & I_L_BIN2 */
	/*16. I_L_nSLP */
	/*17. I_H_BIN1 & I_H_BIN2 */
	/*18. I_H_nSLP */

	/* input logic low voltage */

	/* Input logic high voltage */

	/* Input logic hysteresis */

	/* Tri level input logic low voltage */
	double v_l_ain1 = EC_MEASURE_input_logic_low_voltage(AIN1, AOUT1);
	double v_l_ain2 = EC_MEASURE_input_logic_low_voltage(AIN2, AOUT2);
	V_L_AIN1->SetTestResult(0, 0, v_l_ain1);
	V_L_AIN2->SetTestResult(0, 0, v_l_ain2);

	/* tri level input Hi-Z voltage */
	V_Z_AIN1->SetTestResult(0, 0, EC_MEASURE_tri_level_input_hi_z_voltage(AIN1));
	V_Z_AIN2->SetTestResult(0, 0, EC_MEASURE_tri_level_input_hi_z_voltage(AIN2));

	/* tri level input logic high voltage */
	double v_h_ain1 = EC_MEASURE_input_logic_high_voltage(AIN1, AOUT1);
	double v_h_ain2 = EC_MEASURE_input_logic_high_voltage(AIN2, AOUT2);
	V_H_AIN1->SetTestResult(0, 0, v_h_ain1);
	V_H_AIN2->SetTestResult(0, 0, v_h_ain2);

	/* Tri level input hysteresis */
	V_HYS_AIN1->SetTestResult(0, 0, v_h_ain1 - v_l_ain1);
	V_HYS_AIN2->SetTestResult(0, 0, v_h_ain2 - v_l_ain2);

	/* POWER FET on resistance */
	EC_MEASURE_POWER_FET_on_resistance_setup();
	delay_us(TIME_WAIT_US);
	// RDS_V_VM
	VM.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	double rds_v_vm = VM.GetMeasResult(0, MVRET);
	RDS_V_VM->SetTestResult(0, 0, rds_v_vm);
	// RDS_V_AOUT1 & RDS_I_AOUT1
	AOUT1.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	double rds_v_aout1 = AOUT1.GetMeasResult(0, MVRET);
	RDS_V_AOUT1->SetTestResult(0, 0, rds_v_aout1);
	double rds_i_aout1 = AOUT1.GetMeasResult(0, MIRET);
	RDS_I_AOUT1->SetTestResult(0, 0, rds_i_aout1);
	// RDS_V_AOUT2
	AOUT2.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	double rds_v_aout2 = AOUT2.GetMeasResult(0, MVRET);
	RDS_V_AOUT2->SetTestResult(0, 0, rds_v_aout2);

	// RDS_V_AISEN
	AISEN.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	double rds_v_aisen = AISEN.GetMeasResult(0, MVRET);
	RDS_V_AISEN->SetTestResult(0, 0, rds_v_aisen);
	// RDS_HS
	RDS_HS->SetTestResult(0, 0, (rds_v_vm - rds_v_aout1) / rds_i_aout1);
	// RDS_LS
	RDS_LS->SetTestResult(0, 0, (rds_v_aout2 - rds_v_aisen) / rds_i_aout1);

	/* Externally applied VREF input current */
	nSLEEP.Set(FV, LOGIC_HIGH_VOLTAGE, FOVI_5V, FOVI_100MA, RELAY_ON);
	// VREF = 1V
	VREF.Set(FV, 1, FOVI_2V, FOVI_100MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	VREF.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	I_REF_1->SetTestResult(0, 0, VREF.GetMeasResult(0, MIRET));
	// VREF = 3.3V
	VREF.Set(FV, 3.3, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(TIME_WAIT_US);
	VREF.MeasureVI(SAMPLE_TIME_MEASURE, SAMPLE_PERIOD_MEASURE);
	I_REF_3_3->SetTestResult(0, 0, VREF.GetMeasResult(0, MIRET));

	/* xISEN trip voltage */
	V_TRIP_AISEN->SetTestResult(0, 0, EC_MEASURE_xISEN_trip_voltage(AISEN, AOUT2));
	V_TRIP_BISEN->SetTestResult(0, 0, EC_MEASURE_xISEN_trip_voltage(BISEN, BOUT2));

	/* VM undervoltagew lockout */
	double vm_uvlo_report = EC_MEASURE_VVM_falling();
	VM_UVLO_report->SetTestResult(0, 0, vm_uvlo_report);
	VM_UVLO_recovery->SetTestResult(0, 0, EC_MEASURE_VVM_rising());

	/* Overcurrent protection trip level */
	double i_ocp_n = EC_MEASURE_I_OCP_N();
	I_OCP_N->SetTestResult(0, 0, i_ocp_n);
	I_OCP_P->SetTestResult(0, 0, EC_MEASURE_I_OCP_P());

	/* Output logic low voltage */
	V_L_nFAULT->SetTestResult(0, 0, EC_MEASURE_V_L_nFAULT());

	/* Ouput rise time */
	t_RISE->SetTestResult(0, 0, EC_MEASURE_output_time(0.1 * LOGIC_HIGH_VOLTAGE, 0.9 * LOGIC_HIGH_VOLTAGE, true));
	t_FALL->SetTestResult(0, 0, EC_MEASURE_output_time(0.9 * LOGIC_HIGH_VOLTAGE, 0.1 * LOGIC_HIGH_VOLTAGE, false));

	/* Sleep time */
	t_SLEEP->SetTestResult(0, 0, EC_MEASURE_TIME(3.3, 0, v_l_nslp, 0.1 * LOGIC_HIGH_VOLTAGE, false));
	/* Wake time*/
	t_WAKE->SetTestResult(0, 0, EC_MEASURE_TIME(0, 3.3, v_h_nslp, 0.9 * LOGIC_HIGH_VOLTAGE, true));
	/* Power on time */
	ton->SetTestResult(0, 0, EC_MEASURE_power_on_time());

	/* Propagation delay */
	t_PROP_A->SetTestResult(0, 0, EC_MEASURE_propagation_delay(AIN1, AOUT1, 0, 3.3, 1.6, 0.9 * LOGIC_HIGH_VOLTAGE));
	t_PROP_B->SetTestResult(0, 0, EC_MEASURE_propagation_delay(BIN1, BOUT1, 0, 3.3, 1.6, 0.9 * LOGIC_HIGH_VOLTAGE));

	/* Current sense blanking time */
	double freq = 0.0, duty = 0.0;
	EC_MEASURE_current_sense_blanking_time(freq, duty);
	double period = 1 / (freq * 1e3);							   // unit s (second)
	t_BLANK->SetTestResult(0, 0, period * duty * 1e6);			   // change unit to us
	t_OFF_const->SetTestResult(0, 0, period * (100 - duty) * 1e6); // t_off = period * (100 - duty) and change uint to us

	/* Overcurrent deglitch time */
	EC_MEASURE_overcurrent_deglitch_time(freq, duty);
	period = 1 / (freq * 1e3);						 // unit s(second)
	t_DEG->SetTestResult(0, 0, period * duty * 1e6); // change uint to us

	/* Overcurrent protection period */
	freq = EC_MEASURE_overcurrent_protection_period(i_ocp_n);
	period = 1 / (freq * 1e3);				  // change uint to s
	t_OCP->SetTestResult(0, 0, period * 1e3); // change uint to ms

	return 0;
}
