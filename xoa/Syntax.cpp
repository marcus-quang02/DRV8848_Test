#include "stdafx.h"
#include "math.h"
#define SITENUM   1

// I.IC Setting variable 
#define t_deg 200          
#define t_neg 400           
#define t_brn 5500   
#define t_byp 400          
#define t_en  400            
#define t_off 200           
#define t_on  600            
#define V_meas 0.0005      
#define VST  3.3
#define V_LO 3.12
#define V_HI 3.48

#define LSB1 0.02178
#define LSB2 0.01815
#define V_TLO 3.267
#define V_THI 3.333
#define V_VLO 3.291
#define V_VHI 3.309

// II. Electrical measurement variable
#define Vin_Min				2.4
#define Vin_UVLO_falling	1.8
//#define Iq			48			
//#define I_sd			2
//#define Vout_acc		1.5
#define Iout_Typ 		-0.4  		
#define Iout_Max 		-0.43  		

// Other variable	
#define t_ss 	400
#define VDD 	5.5
#define Iout_TM -0.05    	
#define VDD_para 3.6
#define Site_id 0       // Site 1 is used

// Assign source to IC pin
CBIT128 cbit;   				// define a CBIT128
DIO di0(0);     				// define a DIO
FPVI10 Vin(0);                  // Input voltage PVI10 chanel 1
FPVI10 Vout(1);                 // Output Voltage PVI10 chanel 2
FOVI EN_pin(0);                 // Enable signal
FOVI NC_pin(1);                 // NC signal   
FOVI Check_Site(7);             // Check site signal                         
GPFPVI10 Vin_Out_Gp("Vin_Out_Gp", Vin, Vout);
BYTE K1 = 1;

// Temporary variable
int i = 0, z = 0;

int IC_pass = 1;
int tmp1 = 0;
int tmp2 = 0;
int error_code = 0;
double Vout1_save = 0;
double Vout2_save = 0;
double Vout3_save = 0;
double V_Softview = { 0 };
double Vout_temp, Vintemp, Vintempset, V_drop, LSB_temp;
double Isd, Iq, Vout_MaxLoad, Vout_NoLoad, Vout_MaxLoad_MaxVDD;
double Vout_mesure[7] = { 0.0 };
double block_read_result[7][50] = { 0.0 };

double adresult[4] = {0};

DUT_API void UserLoad()
{

}

//multisite settings should be included here
DUT_API void HardWareCfg()
{
	/*For example: four channels dvi to config two sites*/
	/*StsSetModuleToSite(MD_DVI400,SITE_1,0,1,-1);
	StsSetModuleToSite(MD_DVI400,SITE_2,2,3,-1);*/
	StsSetModuleToSite(MD_FPVI10, SITE_1, 0, 1, -1);//set channels 0-1 to SITE1
//	StsSetModuleToSite(MD_FPVI10, SITE_2, 2, 3, -1);//set channels 2-3 to SITE2
//	StsSetModuleToSite(MD_FPVI10, SITE_3, 4, 5, -1);//set channels 0-1 to SITE1
//	StsSetModuleToSite(MD_FPVI10, SITE_4, 6, 7, -1);//set channels 2-3 to SITE2

	StsSetModuleToSite(MD_FOVI, SITE_1, 0, 1, 2, 3, 4, 5, 6, 7, -1);//set channels 0-7 to SITE1
//	StsSetModuleToSite(MD_FOVI, SITE_2, 8, 9, 10, 11, 12, 13, 14, 15, -1);//set channels 8-15 to SITE2
//	StsSetModuleToSite(MD_FOVI, SITE_3, 16, 17, 18, 19, 20, 21, 22, 23, -1);//set channels 0-7 to SITE1
//	StsSetModuleToSite(MD_FOVI, SITE_4, 24, 25, 26, 27, 28, 29, 30, 31, -1);//set channels 8-15 to SITE2

	StsSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, -1);//set channel 0 to SITE1
//	StsSetModuleToSite(MD_QTMUPLUS, SITE_2, 1, -1);//set channel 1 to SITE2
//	StsSetModuleToSite(MD_QTMUPLUS, SITE_3, 2, -1);//set channel 2 to SITE3
//	StsSetModuleToSite(MD_QTMUPLUS, SITE_4, 3, -1);//set channel 3 to SITE4
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initialize function will be called before all the test functions.
DUT_API void InitBeforeTestFlow()
{
	/*Vin.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	Vout.Set(FV, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(500);

	Vin.Set(FV, 0, FPVI10_5V, FPVI10_1A, RELAY_OFF);
	Vout.Set(FV, 0, FPVI10_5V, FPVI10_1A, RELAY_OFF);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);*/
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initializefunction will be called after all the test functions.
DUT_API void InitAfterTestFlow()
{
	/*Vin.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	Vout.Set(FV, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(500);

	Vin.Set(FV, 0, FPVI10_5V, FPVI10_1A, RELAY_OFF);
	Vout.Set(FV, 0, FPVI10_5V, FPVI10_1A, RELAY_OFF);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);*/
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Fail site hardware set function will be called after failed params, it can be called for serveral times. 
DUT_API void SetupFailSite(const unsigned char* byFailSite)
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

///////////////////////////////// Function ///////////////////////////////

// Gerate pulse at NC pin: -0.8V in t_neg(s), then 0V in t_byp(s) if i = 0 or VDD in t_brn(s) if i = 1
void Pulse_NC_1(int val)
{
	i = 0;
	for (i = 0; i < 4; i++)
	{
		NC_pin.Set(FV, -0.8, FOVI_10V, FOVI_100MA, RELAY_ON, 0.1);
		delay_us(t_neg);
		if ((val & 1 << i) != 0)
		{
			NC_pin.Set(FV, VDD, FOVI_10V, FOVI_100MA, RELAY_ON, 0.1);
			delay_us(t_brn);
		}
		else
		{
			NC_pin.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.1);
			delay_us(t_byp);
		}
	}

}

// Generate 1 pulse at NC pin: -0.8V in t_neg(s), then 0V in t_byp(s)
void Pulse_NC_2(int Pulse_num)
{
	i = 0;
	for (i = 0; i < Pulse_num; i++)
	{
		NC_pin.Set(FV, -0.8, FOVI_1V, FOVI_100MA, RELAY_ON);
		delay_us(t_neg);
		NC_pin.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
		delay_us(t_byp);
	}
}

// Generate pulse at EN pin: 0V in t_en(s), then VDD in t_en(s); then check if VOUT in range, if not generate an other pulse until satisfy
int Set_En_Compare(int max, double VL, double VH)
{
	int tmp = 1;
	double Vout_mes;
	z = 0;
	while (tmp < max + 1)
	{
		//EN_pin.Set(FV, VDD, FOVI_10V, FOVI_100MA, RELAY_ON);
		EN_pin.Set(FV, 3.3, FOVI_5V, FOVI_100MA, RELAY_ON, 0.3);
		delay_us(t_en);
		EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON, 0.3);
		delay_us(t_en);
		Vout.MeasureVI(400, 2, MEAS_NORMAL);
		Vout_mes = Vout.GetMeasResult(0, MVRET);
		Vout_mesure[z] = Vout_mes;
		z = z + 1;
		if (Vout_mes > VL && Vout_mes < VH) {

			break;
		}
		else tmp = tmp + 1;
	}
	return tmp;
}

// Reset FPVI, FOVI source to 0
void inti_All()
{
	Vout.Set(FI, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON, 0.25);
	Vin.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(400);
	//Vout.Set(FI, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON, 0.25);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
}

// Measure voltage at VOUT pin
double Measure_Vout(int time_us, bool x10)
{
	int set = 0;
	int intval = 2;
	if (x10)
	{
		set = time_us / 20;
		intval = 20;
	}
	set = time_us / 2;

	Vout.MeasureVI(set, 2, MEAS_NORMAL);
	return  Vout.GetMeasResult(0, MVRET);
}

// Measure current at VIN pin

double Iin_Measure()
{
	Vin.MeasureVI(500, 2, MEAS_NORMAL);
	return Vin.GetMeasResult(0, MIRET);
}


DUT_API int SITE_CHECK(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *SITE_CHECK = StsGetParam(funcindex,"SITE_CHECK");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	Check_Site.Set(FI, -1e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	Check_Site.MeasureVI(10, 10);

	for(i=0;i<SITENUM;i++)
	{
		adresult[i]=-Check_Site.GetMeasResult(i,MVRET);
		SITE_CHECK->SetTestResult(i, 0, adresult[i]/(i+1));
	}

	Check_Site.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	Check_Site.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	Check_Site.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
    return 0;
}


DUT_API int FUN_OS(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *VIN_OS = StsGetParam(funcindex,"VIN_OS");
    CParam *EN_OS = StsGetParam(funcindex,"EN_OS");
    CParam *NC_OS = StsGetParam(funcindex,"NC_OS");
    CParam *VOUT_OS = StsGetParam(funcindex,"VOUT_OS");
    //}}AFX_STS_PARAM_PROTOTYPES

    // TODO: Add your function code here

	//VIN_OS
	Vin.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(900);
	Vin.MeasureVI(20, 20);
	for(i=0;i<SITENUM;i++)
	{
		adresult[i]=Vin.GetMeasResult(i,MVRET);
		VIN_OS->SetTestResult(i, 0, adresult[i]);
	}

	Vin.Set(FI, 0.0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	Vin.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(500);
    Vin.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	
	//EN_OS
	EN_pin.Set(FI, -1e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	EN_pin.MeasureVI(20, 20);

	for(i=0;i<SITENUM;i++)
	{
		adresult[i]=EN_pin.GetMeasResult(i,MVRET);
		EN_OS->SetTestResult(i, 0, adresult[i]);
	}

	EN_pin.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	EN_pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	
	//NC_OS
	NC_pin.Set(FI, -1e-3, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	NC_pin.MeasureVI(20, 20);

	for(i=0;i<SITENUM;i++)
	{
		adresult[i]=NC_pin.GetMeasResult(i,MVRET);
		NC_OS->SetTestResult(i, 0, adresult[i]);
	}

	NC_pin.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

	NC_pin.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

	//VOUT_OS
	Vout.Set(FI, -5e-3, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(900);
	Vout.MeasureVI(20, 20);
	for(i=0;i<SITENUM;i++)
	{
		adresult[i]=Vout.GetMeasResult(i,MVRET);
		VOUT_OS->SetTestResult(i, 0, adresult[i]);
	}

	Vout.Set(FI, 0.0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	Vout.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_us(500);
    Vout.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

    return 0;
}


DUT_API int FUNCTION(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *V_TM2 = StsGetParam(funcindex,"V_TM2");
    CParam *V_TM3 = StsGetParam(funcindex,"V_TM3");
    CParam *Tmp_T = StsGetParam(funcindex,"Tmp_T");
    CParam *M_LSBT = StsGetParam(funcindex,"M_LSBT");
    CParam *Vout_Save1 = StsGetParam(funcindex,"Vout_Save1");
    CParam *V_TM5 = StsGetParam(funcindex,"V_TM5");
    CParam *V_TM6 = StsGetParam(funcindex,"V_TM6");
    CParam *Tmp_V = StsGetParam(funcindex,"Tmp_V");
    CParam *M_LSBV = StsGetParam(funcindex,"M_LSBV");
    CParam *Vout_Save2 = StsGetParam(funcindex,"Vout_Save2");
    CParam *Vout_EN = StsGetParam(funcindex,"Vout_EN");
    CParam *I_sd = StsGetParam(funcindex,"I_sd");
    CParam *V_TM7 = StsGetParam(funcindex,"V_TM7");
    CParam *Iq_Range1mA = StsGetParam(funcindex,"Iq_Range1mA");
    CParam *Vout_NL = StsGetParam(funcindex,"Vout_NL");
    CParam *Vout_FL = StsGetParam(funcindex,"Vout_FL");
    CParam *Vout_LR = StsGetParam(funcindex,"Vout_LR");
    CParam *Vout_FLL = StsGetParam(funcindex,"Vout_FLL");
    CParam *Vout_LNR = StsGetParam(funcindex,"Vout_LNR");
    CParam *V_Imax = StsGetParam(funcindex,"V_Imax");
    CParam *V_DO = StsGetParam(funcindex,"V_DO");
    CParam *Er_Code = StsGetParam(funcindex,"Er_Code");
    CParam *Time_Ch = StsGetParam(funcindex,"Time_Ch");
    //}}AFX_STS_PARAM_PROTOTYPES
   // TODO: Add your function code here


 	//// Set Var to intinial
	 tmp1 = 0;
 	 tmp2 = 0;

 	////////////////////// I.IC Setting variable  /////////////////////////
 	STSSetTimeCheck(0);
 	cbit.SetCBITOn(K1);  // On the relay K1
 	Vin.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_OFF);
 	Vout.Set(FV, 0, FPVI10_5V, FPVI10_100MA, RELAY_OFF);
 	EN_pin.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	delay_us(1000);

	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.25);		// Set Vin to 5.5V rise time =0.25ms range current 1A
	EN_pin.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(t_deg);
	Vout.Set(FI, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON);
	Vout.SetClamp(80, 10);   	// set clamp to +4V and -0.5V(minimum is 10%)

 	delay_us(t_on);

	/// 1st NC negative pulse	
 	Pulse_NC_1(15);

	/// 5th NC negative pulse
 	Pulse_NC_2(1);
 	Vout.Set(FI, Iout_TM, FPVI10_5V, FPVI10_100MA, RELAY_ON, 0.5);
 	Vout_temp = Measure_Vout(200,false);
 	V_TM2->SetTestResult(Site_id, 0, Vout_temp);
 	if (Vout_temp > V_HI || Vout_temp < V_LO) {
		Er_Code->SetTestResult(Site_id, 0, 1);
		inti_All();
 		return 0;
 	}
 	if (Vout_temp < VST - 1.2 * LSB1) {
 		tmp1 = Set_En_Compare(7, V_TLO, V_THI);	// Generate max 7 pulse EN, and get tmp result, LSB result
 		Tmp_T->SetTestResult(Site_id, 0, z);												// Set Tmp_T
		M_LSBT->SetTestResult(Site_id, 0, 1000 * (Vout_mesure[z-1] - Vout_temp) / (z));		// Set M_LSBT
 		if (tmp1 > 7) {
			Er_Code->SetTestResult(Site_id, 0, 2);											// Set error code
			inti_All();
			return 0;
 		} // IC not pass 
 	}

 	/// 6th NC negative pulse
 	Pulse_NC_2(1);
 	Vout_temp = Measure_Vout(200,false);
 	V_TM3->SetTestResult(Site_id, 0, Vout_temp);											// Set V_TM3
	if (Vout_temp > VST + 1.2 * LSB1) {
		tmp1 = Set_En_Compare(7, V_TLO, V_THI); // Generate max 7 pulse EN, and get tmp result
		Tmp_T->SetTestResult(Site_id, 0, z);												// Set Tmp_T
		M_LSBT->SetTestResult(Site_id, 0, 1000 * (Vout_mesure[z-1] - Vout_temp) / (z));	// Set M_LSBT
 		if (tmp1 > 7) {
			Er_Code->SetTestResult(Site_id, 0, 3);											// Set error code
			inti_All();
			return 0;
		} // IC not pass
	}
 	Vout1_save = Measure_Vout(200, false);
	Vout_Save1->SetTestResult(Site_id, 0, Vout1_save);										// Set Vout_Save1 

 	/// 7th NC negative pulse
	Pulse_NC_2(1);
	if (tmp1 > 0) {
 		Vout_temp = Measure_Vout(200, false);
 		delay_us(t_brn);
 	}

 	// Reset
 	if (tmp1 > 0)
 	{
		inti_All();
 		Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.25);
 		Pulse_NC_2(7);
 		Vout.Set(FI, Iout_TM, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.25);
		delay_us(100);
 	}

 	/// 8th NC negative pulse
 	Pulse_NC_2(1);
 	Vout_temp = Measure_Vout(200, false);
	V_TM5->SetTestResult(Site_id, 0, Vout_temp);											// Set V_TM5
 	if (Vout_temp<Vout1_save - V_meas * Vout_temp || Vout_temp>Vout1_save + V_meas * Vout_temp) {
		// Confirm Vout change or not -> If not, not pass
		//Er_Code->SetTestResult(Site_id, 0, 4);												// Set error code
 	}

	if (Vout_temp < VST - LSB2) {
		tmp2 = Set_En_Compare(3, V_VLO, V_VHI);
 		Tmp_V->SetTestResult(Site_id, 0, z);	// Set value to Tmp_V value = tmp2			// Set Tmp_V
		M_LSBV->SetTestResult(Site_id, 0, 1000 * (Vout_mesure[z-1] - Vout_temp) / (z));	// Set M_LSBV
		if (tmp2 > 3) {
 			Er_Code->SetTestResult(Site_id, 0, 5);											// Set error code
			inti_All();
			return 0; // IC not pass
		}
 	}

 	/// 9th NC negative pulse
	Pulse_NC_2(1);
	Vout_temp = Measure_Vout(200, false);
	V_TM6->SetTestResult(Site_id, 0, Vout_temp);											// Set V_TM6
 	if (Vout_temp > VST + LSB2) {
 		tmp2 = Set_En_Compare(3, V_VLO, V_VHI);
		Tmp_V->SetTestResult(Site_id, 0, z);												// Set Tmp_V
 		M_LSBV->SetTestResult(Site_id, 0, 1000 * (Vout_mesure[z-1] - Vout_temp) / (z));	// Set M_LSBV
 		if (tmp2 > 3) {
 			Er_Code->SetTestResult(Site_id, 0, 6);											// Set error code
 			inti_All();
			return 0;
		} // IC not pass
 	}
 	Vout_temp = Measure_Vout(200, false);
 	Vout2_save = Vout_temp;
 	Vout_Save2->SetTestResult(Site_id, 0, Vout2_save);										// Set Vout_save2

 	/// 10th NC negative pulse
	Pulse_NC_2(1);
 	Vout_temp = Measure_Vout(200, false);
	V_TM7->SetTestResult(Site_id, 0, Vout_temp);
 	if (tmp2 > 0) { delay_us(t_brn); }

 	/// Power OFF
 	Vin.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_OFF, 0.25);        	// Should be Rise Time to 0.25
	Vout.Set(FI, 0, FPVI10_5V, FPVI10_10UA, RELAY_ON);			// Set Iload =0
	EN_pin.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);				// Set En =0
 	NC_pin.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
 	delay_us(1000);
	delay_us(t_off);

	/// Power ON1
 	
 	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_10MA, RELAY_ON,0.25);
 	//delay_us(5000);
 	//Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1MA, RELAY_ON,2);
	delay_us(1000);
 	//Vin_Out_Gp.MeasureVI(3016, 100);
 	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1MA, RELAY_ON,0.5);
 	delay_ms(8);
 	delay_us(400);
	//delay_ms(8); // Delay for 1uF Cin
 	//////////////// II.Electrical Measurement ////////////////
	// Function compare measure value with given value is not include

	//Isd  
 	Vin_Out_Gp.MeasureVI(2000, 2);
 	Isd = Vin.GetMeasResult(Site_id, MIRET);
 	//Isd = Iin_Measure();
 	I_sd->SetTestResult(Site_id, 0, Isd * 1000000);

 	/// Iq
 	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.25);
 	delay_us(500);
 	//EN_pin.Set(FV, VDD, FOVI_10V, FOVI_100MA, RELAY_ON);
 	EN_pin.Set(FV, 3.6, FOVI_5V, FOVI_1A, RELAY_ON, 0.35);
	delay_us(t_ss);
 	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_100MA, RELAY_ON,0.25);
	delay_us(100);
 	//Vin.Set(FV, VDD, FPVI10_10V, FPVI10_10MA, RELAY_ON,0.25);
 	//delay_us(100);
 	//Vin_Out_Gp.MeasureVI(1000,2);
 	//Vin.MeasureVI(500, 2);
 	//Iq = Vin.GetMeasResult(Site_id, MIRET);
	//Iq_Range10mA->SetTestResult(Site_id, 0, Iq * 1000000);

	Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1MA, RELAY_ON,3);
	delay_ms(5);	// Delay for 1uF Cin
 	Vin_Out_Gp.MeasureVI(1000, 2);
	//Vin.MeasureVI(500, 20);
 	Iq = Vin.GetMeasResult(Site_id, MIRET);
	Iq_Range1mA->SetTestResult(Site_id, 0, Iq * 1000000);
 	 
	/// Compare V_out with VOUT2(V)
 	//Vin.Set(FV, VDD, FPVI10_10V, FPVI10_1A, RELAY_ON);
 	//delay_us(200);
 	//Vout.Set(FI, -0.001, FPVI10_5V, FPVI10_100MA, RELAY_ON);
 	//Vin_Out_Gp.MeasureVI(4000, 20);
 	//delay_us(100);
 	//Vout.Set(FI, 0, FPVI10_5V, FPVI10_100MA, RELAY_ON);
	//delay_us(500);
 	//Vin_Out_Gp.MeasureVI(4000, 20);
	//Vout_temp = Measure_Vout(2000, true);
 	Vout_temp = Vout.GetMeasResult(Site_id, MVRET);
 	Vout_EN->SetTestResult(Site_id, 0, Vout_temp);
 	if ((Vout_temp > Vout_temp * V_meas + Vout2_save) || (Vout_temp < Vout2_save - Vout_temp * V_meas))
 	{
 		//Er_Code->SetTestResult(Site_id, 0, 7);
 		//inti_All();
 		//return 0;
 	}

 	/// Vout_FLL
 	Vin.Set(FV, 5.5, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.3);
 	delay_us(1000);
 	Vout.Set(FI, -0.1, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.3);
 	//Vout.Set(FI, Iout_Typ, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);
 	delay_us(t_on);
 	//Vin_Out_Gp.MeasureVI(500, 2);
 	Vin_Out_Gp.MeasureVI(400, 2);
 	//EN_pin.MeasureVI(2000, 20);
 	//Vout.Set(FI, 0, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);
 	Vout_MaxLoad_MaxVDD = Vout.GetMeasResult(Site_id, MVRET);
 	Vout_FLL->SetTestResult(Site_id, 0, Vout_MaxLoad_MaxVDD);

 	/// Vout_FL
 	Vout.Set(FI, Iout_Typ, FPVI10_5V, FPVI10_1A, RELAY_ON);
 	Vin.Set(FV, VDD_para, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.3);
 	delay_us(t_on);
 	Vout_MaxLoad = Measure_Vout(1000, false);
 		Vout_FL->SetTestResult(Site_id, 0, Vout_MaxLoad);

 	/// Iout_Max
	Vout.Set(FI, Iout_Max, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.4);
 	delay_us(t_on);
	Vout_temp = Measure_Vout(1000, false);
 	//Vin_Out_Gp.MeasureVI(2000, 20);
 	V_Imax->SetTestResult(Site_id, 0, Vout_temp);
 	if (Vout_temp < VST * 0.95)
 	{
		Er_Code->SetTestResult(Site_id, 0, 8);
 		inti_All();
 		return 0;
 	}

	/// Vout_NL
 	Vin.Set(FV, VDD_para, FPVI10_10V, FPVI10_1A, RELAY_ON, 0.25);
 	Vout.Set(FI, -0.05, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);
 	delay_us(1000); 
 	Vout.Set(FI, 0, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);
 	delay_us(1000);
 	Vout_NoLoad = Measure_Vout(500, false);
 	Vout_NL->SetTestResult(Site_id, 0, Vout_NoLoad);

 	/// Vout_LR
 	Vout_LR->SetTestResult(Site_id, 0, (Vout_MaxLoad - Vout_NoLoad) * 1000);	// Set Vout_LR

 	/// Vout_LNR
 	Vout_LNR->SetTestResult(Site_id, 0, (Vout_MaxLoad_MaxVDD - Vout_MaxLoad) * 1000);	// Set Vout_LNR

 	/// V_DO
 	Vintempset = VST - 0.1;
 	if (Vintempset > Vin_Min)
 	{
 		Vout.Set(FI, Iout_Typ, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);
		Vin.Set(FV, Vintempset, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.25);  // Set Vin = Vout-0.1 to get V_drop;
 		delay_us(t_on);
 		Vout_temp = Measure_Vout(100, false);
 		Vin.MeasureVI(100, 2, MEAS_NORMAL);
 		Vintemp = Vin.GetMeasResult(0, MVRET);
 		V_drop = Vintemp - Vout_temp;
		V_DO->SetTestResult(Site_id, 0, V_drop * 1000);
 	}
 	/// Vin_Min
 	Vout.Set(FI, -0.05, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.3);
 	Vin.Set(FV, Vin_UVLO_falling, FPVI10_5V, FPVI10_1A, RELAY_ON, 0.3);
	delay_us(1000);
 	if (Measure_Vout(100, false) > 0.6)
 	{
 		Er_Code->SetTestResult(Site_id, 0, 9);
		inti_All();
		return 0;
 	}

	// intinial all
	Time_Ch->SetTestResult(Site_id, 0, STSGetTimeElapsed(0));
 	inti_All();
    return 0;
}
