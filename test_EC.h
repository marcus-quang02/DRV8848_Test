#ifndef __AFXWIN_H__
#define __AFXWIN_H__

#include "StdAfx.h"

#define DEFAULT_MEASURE_INTERVAL 20
#define DEFAULT_SAMPLES_NUMBER 20

double test_I_VM_slp(int samples_number, int measure_interval);
double test_VINT(int samples_number, int measure_interval);

double test_I_L_BIN1(int samples_number, int measure_interval);
double test_I_L_BIN2(int samples_number, int measure_interval);

double test_I_H_BIN1(int samples_number, int measure_interval);
double test_I_H_BIN2(int samples_number, int measure_interval);

double test_I_L_AIN1(int samples_number, int measure_interval);
double test_I_L_AIN2(int samples_number, int measure_interval);

double test_I_H_AIN1(int samples_number, int measure_interval);
double test_I_H_AIN2(int samples_number, int measure_interval);

double test_I_L_SLP(int samples_number, int measure_interval);

double test_I_H_SLP(int samples_number, int measure_interval);

double test_I_H_nFAULT(int samples_number, int measure_interval);

void input_setup(int AIN1_state, int AIN2_state, int BIN1_state, int BIN2_state);

double test_current_fovi(FOVI *fovi, bool sleep, int input);
double test_current_fpvi(FPVI10 *fovi, bool sleep, int input);

#endif // __AFXWIN_H__
