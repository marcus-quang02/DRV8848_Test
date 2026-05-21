#include "stdafx.h"
#include "MyLib.h"

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
	{

		nFAULT.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
		delay_ms(1);											 // Đợi 1ms
		nFAULT.MeasureVI(20, 20);								 // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = nFAULT.GetMeasResult(0, MVRET);		 // Lưu giá trị điện áp vào bộ nhớ đệm
			R_nFAULT_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		nFAULT.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	// AISEN
	{

		AISEN.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
		delay_ms(1);											// Đợi 1ms
		AISEN.MeasureVI(20, 20);								// Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AISEN.GetMeasResult(0, MVRET);		// Lưu giá trị điện áp vào bộ nhớ đệm
			R_AISEN_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		AISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	// BISEN
	{

		BISEN.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
		delay_ms(1);											// Đợi 1ms
		BISEN.MeasureVI(20, 20);								// Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BISEN.GetMeasResult(0, MVRET);		// Lưu giá trị điện áp vào bộ nhớ đệm
			R_BISEN_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		BISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/

	// NSLEEP
	{
		nSLEEP.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		nSLEEP.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = nSLEEP.GetMeasResult(0, MVRET);		 //
			R_nSLEEP_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		nSLEEP.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AOUT1
	{
		AOUT1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AOUT1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AOUT1.GetMeasResult(0, MVRET);		//
			R_AOUT1_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		AOUT1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AOUT2
	{
		AOUT2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AOUT2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AOUT2.GetMeasResult(0, MVRET);		//
			R_AOUT2_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		AOUT2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BOUT2
	{
		BOUT2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BOUT2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BOUT2.GetMeasResult(0, MVRET);		//
			R_BOUT2_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		BOUT2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BOUT1
	{
		BOUT1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BOUT1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BOUT1.GetMeasResult(0, MVRET);		//
			R_BOUT1_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		BOUT1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AIN1
	{
		AIN1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AIN1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AIN1.GetMeasResult(0, MVRET);	   //
			R_AIN1_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		AIN1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AIN2
	{
		AIN2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AIN2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AIN2.GetMeasResult(0, MVRET);	   //
			R_AIN2_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		AIN2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BIN1
	{
		BIN1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BIN1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BIN1.GetMeasResult(0, MVRET);	   //
			R_BIN1_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		BIN1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BIN2
	{
		BIN2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BIN2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BIN2.GetMeasResult(0, MVRET);	   //
			R_BIN2_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		BIN2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// VREF
	{
		VREF.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		VREF.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = VREF.GetMeasResult(0, MVRET);	   //
			R_VREF_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		VREF.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// VINT
	{
		VINT.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		VINT.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = VINT.GetMeasResult(0, MVRET);	   //
			R_VINT_KELVIN->SetTestResult(0, 0, buffer[0]); //
		}

		VINT.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

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
	{

		nFAULT.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA, 0.2/0.1 ms
		delay_ms(1);											 // Đợi 1ms
		nFAULT.MeasureVI(20, 20);								 // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = nFAULT.GetMeasResult(0, MVRET); // Lưu giá trị điện áp vào bộ nhớ đệm
			OS_nFAULT->SetTestResult(0, 0, buffer[0]);	//
		}

		nFAULT.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		nFAULT.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	// AISEN
	{

		AISEN.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
		delay_ms(1);											// Đợi 1ms
		AISEN.MeasureVI(20, 20);								// Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AISEN.GetMeasResult(0, MVRET); // Lưu giá trị điện áp vào bộ nhớ đệm
			OS_AISEN->SetTestResult(0, 0, buffer[0]);  //
		}

		AISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		AISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	// BISEN
	{

		BISEN.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON); // Cấp dòng ngược 5mA
		delay_ms(1);											// Đợi 1ms
		BISEN.MeasureVI(20, 20);								// Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BISEN.GetMeasResult(0, MVRET); // Lưu giá trị điện áp vào bộ nhớ đệm
			OS_BISEN->SetTestResult(0, 0, buffer[0]);  //
		}

		BISEN.Set(FI, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
		delay_us(500);
		BISEN.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	}

	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------------------------------------*/

	// NSLEEP
	{
		nSLEEP.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		nSLEEP.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = nSLEEP.GetMeasResult(0, MVRET); //
			OS_nSLEEP->SetTestResult(0, 0, buffer[0]);	//
		}

		nSLEEP.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		nSLEEP.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AOUT1
	{
		AOUT1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AOUT1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AOUT1.GetMeasResult(0, MVRET); //
			OS_AOUT1->SetTestResult(0, 0, buffer[0]);  //
		}

		AOUT1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AOUT2
	{
		AOUT2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AOUT2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AOUT2.GetMeasResult(0, MVRET); //
			OS_AOUT2->SetTestResult(0, 0, buffer[0]);  //
		}

		AOUT2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BOUT2
	{
		BOUT2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BOUT2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BOUT2.GetMeasResult(0, MVRET); //
			OS_BOUT2->SetTestResult(0, 0, buffer[0]);  //
		}

		BOUT2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BOUT2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BOUT1
	{
		BOUT1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BOUT1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BOUT1.GetMeasResult(0, MVRET); //
			OS_BOUT1->SetTestResult(0, 0, buffer[0]);  //
		}

		BOUT1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BOUT1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AIN1
	{
		AIN1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AIN1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AIN1.GetMeasResult(0, MVRET); //
			OS_AIN1->SetTestResult(0, 0, buffer[0]);  //
		}

		AIN1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// AIN2
	{
		AIN2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AIN2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = AIN2.GetMeasResult(0, MVRET); //
			OS_AIN2->SetTestResult(0, 0, buffer[0]);  //
		}

		AIN2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		AIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BIN1
	{
		BIN1.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BIN1.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BIN1.GetMeasResult(0, MVRET); //
			OS_BIN1->SetTestResult(0, 0, buffer[0]);  //
		}

		BIN1.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BIN1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// BIN2
	{
		BIN2.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		BIN2.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = BIN2.GetMeasResult(0, MVRET); //
			OS_BIN2->SetTestResult(0, 0, buffer[0]);  //
		}

		BIN2.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		BIN2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// VREF
	{
		VREF.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		VREF.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = VREF.GetMeasResult(0, MVRET); //
			OS_VREF->SetTestResult(0, 0, buffer[0]);  //
		}

		VREF.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		VREF.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

	// VINT
	{
		VINT.Set(FI, -5e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		VINT.MeasureVI(20, 20); // Number of samples: 20 , sample interval: 20us = 400 us

		{
			buffer[0] = VINT.GetMeasResult(0, MVRET); //
			OS_VINT->SetTestResult(0, 0, buffer[0]);  //
		}

		VINT.Set(FI, 0.0, FOVI_5V, FOVI_10MA, RELAY_ON);
		VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_us(500);
		VINT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	}

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
	test_VM_Sleep_Mode_Current(I_VM_slp);

	// Test number 7
	test_VINT_Voltage(VINT);
	//------------------------------END------------------------------//

	// Logic-level inputs (BIN1, BIN2, nSLEEP)--------Start--------------//
	// Test number 15
	test_Input_Logic_Low_Current(I_L_BIN1, I_L_BIN2);

	// Test number 17
	test_Input_Logic_High_Current(I_H_BIN1, I_L_BIN2);

	// Test number 19
	R_PD_BIN1->SetTestResult(1, 0, 5 / buffer[0]); // R_PD_BIN1 = 5 / I_H_BIN1
	R_PD_BIN2->SetTestResult(1, 0, 5 / buffer[1]); // R_PD_BIN2 = 5 / I_H_BIN2

	// Test number 16
	test_Input_Logic_Low_Current(I_L_SLP);

	// Test number 17
	test_Input_Logic_High_Current(I_H_SLP);

	// Test number 19
	R_PD_SLP->SetTestResult(1, 0, 5 / buffer[0]); // R_PD_SLP = 5 / I_H_SLP
	//-----------------------------END---------------------------------------//

	// Tri-level logic inputs (AIN1, AIN2)---------Start-----------------//
	// Test number 28
	test_TriLevel_Logic_Low_Current(I_L_AIN1, I_L_AIN2);

	// Test number 31 ??????????????????????????
	R_PU_AIN1->SetTestResult(1, 0, 5 / buffer[0]);
	R_PU_AIN2->SetTestResult(1, 0, 5 / buffer[1]);

	// Test number 29
	test_TriLevel_Logic_High_Current(I_H_AIN1, I_H_AIN2);

	// Test number 30
	R_PD_AIN1->SetTestResult(1, 0, 5 / buffer[0]);
	R_PD_AIN2->SetTestResult(1, 0, 5 / buffer[1]);

	//---------------------------------END--------------------------------------//

	return 0;
}
