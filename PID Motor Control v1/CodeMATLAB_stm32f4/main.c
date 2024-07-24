/*
 * File: main.c
 *
 * Created with Waijung Blockset
 *
 * Real-Time Workshop code generated for Simulink model CodeMATLAB.
 *
 * Model version                        : 1.27
 * Real-Time Workshop file version      : 9.3 (R2020a) 18-Nov-2019
 * Real-Time Workshop file generated on : Sat Dec 17 13:26:25 2022
 * TLC version                          : 9.3 (Jan 23 2020)
 * C/C++ source code generated on       : Sat Dec 17 13:26:26 2022
 *
 * Target selection: stm32f4.tlc
 * Embedded hardware selection: ARM Compatible->Cortex - M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "waijung_hwdrvlib.h"
#include "CodeMATLAB.h"
#include "rtwtypes.h"                  /* MathWorks types */

/*
 * rt_Onestep is called from a timer ISR at the base sample time of 0.05 sec.
 * The ISR is void SysTick_Handler(void) and is defined in stm32f4xx_it.c
 */
void rt_OneStep(void);
volatile unsigned int systick_count = 1;
static volatile unsigned int systick_active = 0;

/* Main program */
int_T main(void)
{
  /* Initialize model */
  CodeMATLAB_initialize();

  /* Continue indefinitely */
  if (SysTick_Config(SYSTICKRELOADVALUE)) {
    /* Capture error */
    while (1) ;
  }

  while (1) {
    if (systick_active != systick_count) {
      systick_active ++;
      CodeMATLAB_step();

      /* Get model outputs here */

      /* Profiler update */
    }
  }
}

void rt_OneStep(void)
{
  /* Tick counter */
  systick_count++;
}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void)
{
  rt_OneStep();
}

/* [EOF] */
