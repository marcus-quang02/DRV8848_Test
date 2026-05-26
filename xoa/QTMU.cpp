#include "stdafx.h"
#define SITENUM 4

DVI400 dvi0(0);
QTMU_PLUS qtmu0(0);

// multisite settings should be included here
DUT_API void HardWareCfg()
{
    StsSetModuleToSite(MD_DVI400, SITE_1, 0, -1); // set channels 0 to SITE1
    StsSetModuleToSite(MD_DVI400, SITE_2, 1, -1); // set channels 1 to SITE2
    StsSetModuleToSite(MD_DVI400, SITE_3, 2, -1); // set channels 2 to SITE3
    StsSetModuleToSite(MD_DVI400, SITE_4, 3, -1); // set channels 3 to SITE4

    StsSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, -1); // set channel 0 to SITE1
    StsSetModuleToSite(MD_QTMUPLUS, SITE_2, 1, -1); // set channel 1 to SITE2
    StsSetModuleToSite(MD_QTMUPLUS, SITE_3, 2, -1); // set channel 2 to SITE3
    StsSetModuleToSite(MD_QTMUPLUS, SITE_4, 3, -1); // set channel 3 to SITE4
}
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

DUT_API int test_Freq(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Freq1 = StsGetParam(funcindex, "Freq1");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.1.1

    double val[4] = {0};
    int i = 0;

    // 1 mega ohm input inpedance, voltage range connected of the signal that to be measured is 5V, turn off filter
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);

    // trigger level is 2V, rising edge trigger
    qtmu0.SetStartTrigger(2, QTMU_PLUS_POS_SLOPE);

    // select single source,
    qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);

    // connect relays
    qtmu0.Connect();
    delay_ms(1);

    // measure frequency with low resolution mode, time range is microsecond, cycle number=10, timeout=10ms
    qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10, 10); // cycle number=10£¬timeout=10ms

    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        Freq1->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}

DUT_API int test_Duty(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Duty = StsGetParam(funcindex, "Duty");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.2

    double val[4] = {0};
    int i = 0;

    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE); // SINGLE_SOURCE
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.MeasDC(2, QTMU_PLUS_HIGH_DUTY, 10); // trigger=2V, timeout=10ms, read Dutycycle
    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        Duty->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}

DUT_API int test_ChannelSetup(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Freq2 = StsGetParam(funcindex, "Freq2");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.1.2

    double f[4] = {0};
    int i = 0;
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(1.5, QTMU_PLUS_POS_SLOPE); // CHA trigger level=1.5V, Rising edge
    qtmu0.SetStopTrigger(1.5, QTMU_PLUS_POS_SLOPE);  // CHB trigger level=1.5V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_DUAL_SOURCE);        // DUAL_SOURCE
    qtmu0.ChannelSetup(QTMU_PLUS_CHA_STOP);          // select CHB to read Freq
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 5, 1); // cycle number=5£¬timeout=1ms
    for (i = 0; i < SITENUM; i++)
    {
        f[i] = qtmu0.GetMeasureResult(i);
        Freq2->SetTestResult(i, 0, f[i]);
    }
    qtmu0.ChannelSetup(QTMU_PLUS_CHA_START); // select CHA to read Freq
    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}

DUT_API int test_TrTf(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Tr1 = StsGetParam(funcindex, "Tr1");
    CParam *Tr2 = StsGetParam(funcindex, "Tr2");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.3

    ///////////////////////////////// for Tr/Tf test ////////////////////////////////////

    double val[4] = {0};
    int i = 0;

    /////////////////////////periodic signal: Meas////////////////////////////////////
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(2.1, QTMU_PLUS_POS_SLOPE); // trigger=2.1V, Rising edge
    qtmu0.SetStopTrigger(13.3, QTMU_PLUS_POS_SLOPE); // trigger=13.3V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);      // SINGLE_SOURCE
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10); // timeout=10ms
    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        Tr1->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    /////////////////////aperiodic signal: SinglePlsMeas/////////////////////
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(2.1, QTMU_PLUS_POS_SLOPE); // trigger=2.1V, Rising edge
    qtmu0.SetStopTrigger(13.3, QTMU_PLUS_POS_SLOPE); // trigger=13.3V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE);      // SINGLE_SOURCE
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 0);
    qtmu0.SetTimeOut(10); // timeout=10ms

    // set the trigger signal here

    qtmu0.SinglePlsMeas(0);
    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        Tr2->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}

DUT_API int test_TPLH(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *TPLH1 = StsGetParam(funcindex, "TPLH1");
    CParam *TPLH2 = StsGetParam(funcindex, "TPLH2");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.4 and 7.16.5

    ///////////////////////////////// for time interval test ////////////////////////////////////

    double val[4] = {0};
    int i = 0;

    ///////////////////////// periodic signal: Meas ////////////////////////////////////
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(2.5, QTMU_PLUS_NEG_SLOPE); // trigger=2.5V, Falling edge
    qtmu0.SetStopTrigger(7.7, QTMU_PLUS_POS_SLOPE);  // trigger=7.7V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_DUAL_SOURCE);        // DUAL_SOURCE
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10); // timeout=10ms

    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        TPLH1->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    ///////////////////// aperiodic signal: SinglePlsMeas /////////////////////
    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(2.5, QTMU_PLUS_NEG_SLOPE); // trigger=2.5V, Falling edge
    qtmu0.SetStopTrigger(7.7, QTMU_PLUS_POS_SLOPE);  // trigger=7.7V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_DUAL_SOURCE);
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 0);
    qtmu0.SetTimeOut(10); // timeout=10ms

    // set the trigger signal here

    qtmu0.SinglePlsMeas(0);
    for (i = 0; i < SITENUM; i++)
    {
        val[i] = qtmu0.GetMeasureResult(i);
        TPLH2->SetTestResult(i, 0, val[i]);
    }
    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}

DUT_API int test_SerialTest(short funcindex, LPCTSTR funclabel)
{
    //{{AFX_STS_PARAM_PROTOTYPES
    CParam *Tr = StsGetParam(funcindex, "Tr");
    //}}AFX_STS_PARAM_PROTOTYPES

    // for more details, please check STS8200 Programming Manual 7.16.6

    int i = 0;
    double val[4] = {0.0};

    qtmu0.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_25V, QTMU_PLUS_FILTER_PASS);
    qtmu0.SetStartTrigger(2.1, QTMU_PLUS_POS_SLOPE);
    // trigger=2.1V, Rising edge
    qtmu0.SetStopTrigger(13.3, QTMU_PLUS_POS_SLOPE);
    // trigger=13.3V, Rising edge
    qtmu0.SetInSource(QTMU_PLUS_SINGLE_SOURCE); // SINGLE_SOURCE
    qtmu0.Connect();
    delay_ms(1);
    qtmu0.SetSinglePulseMeas(QTMU_PLUS_FINE, QTMU_PLUS_TIME_NS, i);

    dvi0.Set(FV, 5, DVI400_20V, DVI400_40MA, RELAY_ON);
    delay_ms(1);
    for (i = 0; i < SITENUM; i++)
    {
        BEGIN_SINGLE_SITE(i)

        qtmu0.SetTimeOut(10); // timeout=10ms

        // trigger signal A
        dvi0.Set(FV, 5, DVI400_20V, DVI400_40MA, RELAY_ON);
        delay_ms(1);
        dvi0.Set(FV, 0, DVI400_20V, DVI400_40MA, RELAY_ON);

        qtmu0.SinglePlsMeas(i);
        val[i] = qtmu0.GetMeasureResult(i);
        Tr->SetTestResult(i, 0, val[i]);

        END_SINGLE_SITE()
    }

    qtmu0.Disconnect();

    // TODO: Add your function code here
    return 0;
}
