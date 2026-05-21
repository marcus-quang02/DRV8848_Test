#pragma once
#include "StdAfx.h"

FPVI10 VM(0, "VM");
FPVI10 nFAULT(1, "nFAULT");
FPVI10 AISEN(2, "AISEN");
FPVI10 BISEN(3, "BISEN");

FOVI nSLEEP(0, "nSLEEP");
FOVI AOUT1(1, "AOUT1");
FOVI AOUT2(2, "AOUT2");
FOVI BOUT2(3, "BOUT2");

FOVI BOUT1(4, "BOUT1");
FOVI BIN1(5, "BIN1");
FOVI BIN2(6, "BIN2");
FOVI VREF(7, "VREF");

FOVI VINT(8, "VINT");
FOVI AIN2(9, "AIN2");
FOVI AIN1(10, "AIN1");

QTMU_PLUS qtmu0(0, "qtmu0");
QTMU_PLUS qtmu1(1, "qtmu1");
QTMU_PLUS qtmu2(2, "qtmu2");

double buffer[4] = {0};

void test_VM_Sleep_Mode_Current(CParam *);
void test_VINT_Voltage(CParam *param);


void test_Input_Logic_Low_Current(CParam *param);
void test_Input_Logic_High_Current(CParam *param);


void test_Input_Logic_Low_Current(CParam *param, CParam *param1);
void test_Input_Logic_High_Current(CParam *param, CParam *param1);


void test_TriLevel_Logic_Low_Current(CParam *param, CParam *param1);
void test_TriLevel_Logic_High_Current(CParam *param, CParam *param1);

void test_Output_Logic_High_Leakage(CParam *param);

