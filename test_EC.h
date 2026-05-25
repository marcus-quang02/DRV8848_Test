#ifndef __AFXWIN_H__
#define __AFXWIN_H__

#include "StdAfx.h"

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

#endif // __AFXWIN_H__
