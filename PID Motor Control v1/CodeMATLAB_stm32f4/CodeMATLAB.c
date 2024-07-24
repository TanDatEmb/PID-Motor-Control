/*
 * File: CodeMATLAB.c
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

#include "CodeMATLAB.h"
#include "CodeMATLAB_private.h"

/* Block signals (default storage) */
B_CodeMATLAB_T CodeMATLAB_B;

/* Block states (default storage) */
DW_CodeMATLAB_T CodeMATLAB_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_CodeMATLAB_T CodeMATLAB_PrevZCX;

/* Real-time model */
RT_MODEL_CodeMATLAB_T CodeMATLAB_M_;
RT_MODEL_CodeMATLAB_T *const CodeMATLAB_M = &CodeMATLAB_M_;
static void rate_scheduler(void);

/* ########################################################################
 * Block Name: <S1>/Timer (Time Base) IRQ
 * Block ID: SubsystemTimerTimeBaseIRQ
 * ########################################################################
 * Function call: SubsystemTimerTimeBaseIRQ IRQ
 */
void SubsystemTimerTimeBaseIRQ_irq(void)
{
  /* Call the system: <S1>/Doc encoder */
  {
    /* S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

    /* Output and update for function-call system: '<S1>/Doc encoder' */
    {
      real_T rtb_CastToDouble1_c;
      int32_T rtb_Gain;

      /* S-Function (stm32f4_encoderread): '<S8>/Encoder Read' */

      /* S-Function Block: <S8>/Encoder Read (stm32f4_encoderread) */
      CodeMATLAB_B.EncoderRead_o1 = (TIM1->CR1 & 0x10) >> 4;
      CodeMATLAB_B.EncoderRead_o2 = (uint32_t) TIM_GetCounter(TIM1);

      /* Sum: '<S9>/Sum' incorporates:
       *  DataTypeConversion: '<S8>/Cast To Double1'
       *  UnitDelay: '<S9>/Unit Delay'
       */
      rtb_CastToDouble1_c = (real_T)CodeMATLAB_B.EncoderRead_o2 -
        CodeMATLAB_DW.UnitDelay_DSTATE;

      /* DataTypeConversion: '<S9>/Cast To Double' incorporates:
       *  Constant: '<S9>/Constant'
       *  RelationalOperator: '<S9>/Relational Operator'
       */
      rtb_Gain = (rtb_CastToDouble1_c < -32768.0);

      /* DataTypeConversion: '<S9>/Cast To Double1' incorporates:
       *  Constant: '<S9>/Constant1'
       *  RelationalOperator: '<S9>/Relational Operator1'
       */
      rtb_CastToDouble1_c = (rtb_CastToDouble1_c > 32767.0);

      /* Gain: '<S9>/Gain' incorporates:
       *  Sum: '<S9>/Sum1'
       */
      rtb_Gain = (rtb_Gain - (int32_T)rtb_CastToDouble1_c) * 65535;

      /* Sum: '<S9>/Sum3' incorporates:
       *  DataTypeConversion: '<S8>/Cast To Double1'
       *  Sum: '<S9>/Sum2'
       *  UnitDelay: '<S9>/Unit Delay1'
       */
      CodeMATLAB_B.Sum3 = ((real_T)CodeMATLAB_B.EncoderRead_o2 + (real_T)
                           rtb_Gain) + CodeMATLAB_DW.UnitDelay1_DSTATE;

      /* Sum: '<S9>/Sum4' incorporates:
       *  UnitDelay: '<S9>/Unit Delay1'
       */
      CodeMATLAB_DW.UnitDelay1_DSTATE += (real_T)rtb_Gain;

      /* Update for UnitDelay: '<S9>/Unit Delay' incorporates:
       *  DataTypeConversion: '<S8>/Cast To Double1'
       */
      CodeMATLAB_DW.UnitDelay_DSTATE = CodeMATLAB_B.EncoderRead_o2;
    }

    /* End of Outputs for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

    /* RateTransition: '<S1>/Rate Transition2' */
    CodeMATLAB_DW.RateTransition2_Buffer[CodeMATLAB_DW.RateTransition2_semaphoreTaken
      == 0] = CodeMATLAB_B.Sum3;
    CodeMATLAB_DW.RateTransition2_ActiveBufIdx = (int8_T)
      (CodeMATLAB_DW.RateTransition2_semaphoreTaken == 0);
  }
}

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (CodeMATLAB_M->Timing.TaskCounters.TID[1])++;
  if ((CodeMATLAB_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.1s, 0.0s] */
    CodeMATLAB_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function */
void CodeMATLAB_step(void)
{
  real_T rtb_RateTransition2;
  real_T rtb_TSamp;
  real_T Sum;

  /* DataStoreRead: '<S2>/Data Store Read' */
  CodeMATLAB_B.DataStoreRead = CodeMATLAB_DW.ITF_SET_POINT;

  /* S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */
  /* S-Function Block: <S1>/Timer (Time Base) IRQ */

  /* End of Outputs for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* RateTransition: '<S1>/Rate Transition2' */
  CodeMATLAB_DW.RateTransition2_semaphoreTaken =
    CodeMATLAB_DW.RateTransition2_ActiveBufIdx;
  rtb_RateTransition2 =
    CodeMATLAB_DW.RateTransition2_Buffer[CodeMATLAB_DW.RateTransition2_semaphoreTaken];

  /* Sum: '<S17>/Sum' incorporates:
   *  DataStoreRead: '<S6>/Data Store Read'
   */
  Sum = CodeMATLAB_DW.ITF_SET_POINT - rtb_RateTransition2;

  /* S-Function (stm32f4_usart): '<S2>/UART Rx' */

  /* Subsystem1UARTRx: '<S2>/UART Rx' */
  if (Subsystem1UARTRx_Receive(&UART6_Temp_Buffer[0], URX6_BUFFER_SIZE)) {/* Non-Blocking */
    CodeMATLAB_B.UARTRx_o2 = Subsystem1UARTRx_data0;/* D0 */
    CodeMATLAB_B.UARTRx_o3 = Subsystem1UARTRx_data1;/* D1 */
    CodeMATLAB_B.UARTRx_o4 = Subsystem1UARTRx_data2;/* D2 */
    CodeMATLAB_B.UARTRx_o5 = Subsystem1UARTRx_data3;/* D3 */
    CodeMATLAB_B.UARTRx_o1 = 1;        /* READY */
  } else {
    CodeMATLAB_B.UARTRx_o1 = 0;        /* Not READY */
  }

  if (CodeMATLAB_M->Timing.TaskCounters.TID[1] == 0) {
    /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    CodeMATLAB_B.DiscreteTimeIntegrator =
      CodeMATLAB_DW.DiscreteTimeIntegrator_DSTATE;
  }

  /* SampleTimeMath: '<S18>/TSamp'
   *
   * About '<S18>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  rtb_TSamp = Sum * 20.0;

  /* Sum: '<S17>/Add' incorporates:
   *  Product: '<S17>/Product'
   *  Product: '<S17>/Product1'
   *  Product: '<S17>/Product2'
   *  Sum: '<S18>/Diff'
   *  UnitDelay: '<S18>/UD'
   *
   * Block description for '<S18>/Diff':
   *
   *  Add in CPU
   *
   * Block description for '<S18>/UD':
   *
   *  Store in Global RAM
   */
  CodeMATLAB_B.PWM = (CodeMATLAB_B.UARTRx_o3 * Sum + CodeMATLAB_B.UARTRx_o4 *
                      CodeMATLAB_B.DiscreteTimeIntegrator) + (rtb_TSamp -
    CodeMATLAB_DW.UD_DSTATE) * CodeMATLAB_B.UARTRx_o5;

  /* Saturate: '<S16>/Limit' */
  if (CodeMATLAB_B.PWM > 95.0) {
    /* Sum: '<S17>/Add' */
    CodeMATLAB_B.PWM = 95.0;
  } else {
    if (CodeMATLAB_B.PWM < -95.0) {
      /* Sum: '<S17>/Add' */
      CodeMATLAB_B.PWM = -95.0;
    }
  }

  /* End of Saturate: '<S16>/Limit' */

  /* DataTypeConversion: '<S2>/Cast To Single6' */
  CodeMATLAB_B.CastToSingle6 = (real32_T)CodeMATLAB_B.PWM;

  /* DataTypeConversion: '<S2>/Cast To Single5' */
  CodeMATLAB_B.CastToSingle5 = (real32_T)rtb_RateTransition2;

  /* DataTypeConversion: '<S2>/Cast To Single7' */
  CodeMATLAB_B.CastToSingle7 = (real32_T)Sum;

  /* S-Function (stm32f4_usart): '<S2>/UART Tx1' */

  /* Subsystem1UARTTx1: '<S2>/UART Tx1' */
  {
    UART6_FlushTxBuffer();/* Flush tx, so we can print to DMA buffer directly */
    sprintf((char*)UART6_Tx_Buffer, "%f,%f,%f,%f\n" ,CodeMATLAB_B.DataStoreRead ,
            CodeMATLAB_B.CastToSingle5 ,CodeMATLAB_B.CastToSingle6 ,
            CodeMATLAB_B.CastToSingle7 );
    UART6_TxUpdate(strlen((char*)UART6_Tx_Buffer));
  }

  /* MATLAB Function: '<S11>/MATLAB Function' */
  if (CodeMATLAB_B.PWM >= 0.0) {
    CodeMATLAB_B.Dir = 1.0;
  } else {
    /* Sum: '<S17>/Add' */
    CodeMATLAB_B.PWM = -CodeMATLAB_B.PWM;
    CodeMATLAB_B.Dir = 0.0;
  }

  /* End of MATLAB Function: '<S11>/MATLAB Function' */

  /* S-Function (stm32f4_basicpwm): '<S11>/Basic PWM' */

  /* S-Function Block: <S11>/Basic PWM (stm32f4_basicpwm) */
  TIM2->CCR3 = (uint32_t) (CodeMATLAB_B.PWM * Subsystem2XuattinhieuBasicPWM_SF);

  /* S-Function (stm32f4_digital_output): '<S11>/Digital Output' */

  /* Subsystem2XuattinhieuDigitalOutput */
  {
    *Subsystem2XuattinhieuDigitalOutput_A4 = (boolean_T) CodeMATLAB_B.Dir;
  }

  /* S-Function (stm32f4_digital_input): '<S4>/Digital Input' */
  CodeMATLAB_B.DigitalInput_o1 = *Subsystem3DigitalInput_D0;
  CodeMATLAB_B.DigitalInput_o2 = *Subsystem3DigitalInput_D2;
  CodeMATLAB_B.DigitalInput_o3 = *Subsystem3DigitalInput_D4;

  /* Outputs for Enabled SubSystem: '<S2>/Subsystem' incorporates:
   *  EnablePort: '<S10>/Enable'
   */
  if (CodeMATLAB_B.UARTRx_o1 > 0) {
    /* DataStoreWrite: '<S10>/Data Store Write' */
    CodeMATLAB_DW.ITF_SET_POINT = CodeMATLAB_B.UARTRx_o2;
  }

  /* End of Outputs for SubSystem: '<S2>/Subsystem' */

  /* Outputs for Triggered SubSystem: '<S4>/Enabled Subsystem' incorporates:
   *  TriggerPort: '<S13>/Trigger'
   */
  if (CodeMATLAB_B.DigitalInput_o1 &&
      (CodeMATLAB_PrevZCX.EnabledSubsystem_Trig_ZCE != 1)) {
    /* Saturate: '<S13>/Saturation' incorporates:
     *  Constant: '<S13>/Constant'
     *  DataStoreRead: '<S4>/Data Store Read'
     *  Sum: '<S13>/Sum'
     */
    if (CodeMATLAB_DW.ITF_SET_POINT + 100.0 > 800.0) {
      /* DataTypeConversion: '<S13>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S13>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = 800.0F;
    } else if (CodeMATLAB_DW.ITF_SET_POINT + 100.0 < -800.0) {
      /* DataTypeConversion: '<S13>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S13>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = -800.0F;
    } else {
      /* DataTypeConversion: '<S13>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S13>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = (real32_T)(CodeMATLAB_DW.ITF_SET_POINT +
        100.0);
    }

    /* End of Saturate: '<S13>/Saturation' */
  }

  CodeMATLAB_PrevZCX.EnabledSubsystem_Trig_ZCE = CodeMATLAB_B.DigitalInput_o1;

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem' */

  /* Outputs for Triggered SubSystem: '<S4>/Enabled Subsystem1' incorporates:
   *  TriggerPort: '<S14>/Trigger'
   */
  if (CodeMATLAB_B.DigitalInput_o2 &&
      (CodeMATLAB_PrevZCX.EnabledSubsystem1_Trig_ZCE != 1)) {
    /* Saturate: '<S14>/Saturation' incorporates:
     *  Constant: '<S14>/Constant'
     *  DataStoreRead: '<S4>/Data Store Read1'
     *  Sum: '<S14>/Sum'
     */
    if (CodeMATLAB_DW.ITF_SET_POINT - 100.0 > 800.0) {
      /* DataTypeConversion: '<S14>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S14>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = 800.0F;
    } else if (CodeMATLAB_DW.ITF_SET_POINT - 100.0 < -800.0) {
      /* DataTypeConversion: '<S14>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S14>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = -800.0F;
    } else {
      /* DataTypeConversion: '<S14>/Cast To Single' incorporates:
       *  DataStoreWrite: '<S14>/Data Store Write1'
       */
      CodeMATLAB_DW.ITF_SET_POINT = (real32_T)(CodeMATLAB_DW.ITF_SET_POINT -
        100.0);
    }

    /* End of Saturate: '<S14>/Saturation' */
  }

  CodeMATLAB_PrevZCX.EnabledSubsystem1_Trig_ZCE = CodeMATLAB_B.DigitalInput_o2;

  /* End of Outputs for SubSystem: '<S4>/Enabled Subsystem1' */

  /* Outputs for Triggered SubSystem: '<S4>/Subsystem' incorporates:
   *  TriggerPort: '<S15>/Trigger'
   */
  if (CodeMATLAB_B.DigitalInput_o3 && (CodeMATLAB_PrevZCX.Subsystem_Trig_ZCE !=
       1)) {
    /* S-Function (stm32f4_reset): '<S15>/System Reset' */

    /* Subsystem3SubsystemSystemReset: '<S15>/System Reset' */
    Subsystem3SubsystemSystemReset_Exec();
  }

  CodeMATLAB_PrevZCX.Subsystem_Trig_ZCE = CodeMATLAB_B.DigitalInput_o3;

  /* End of Outputs for SubSystem: '<S4>/Subsystem' */
  if (CodeMATLAB_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    CodeMATLAB_DW.DiscreteTimeIntegrator_DSTATE += 0.1 * Sum;
  }

  /* Update for UnitDelay: '<S18>/UD'
   *
   * Block description for '<S18>/UD':
   *
   *  Store in Global RAM
   */
  CodeMATLAB_DW.UD_DSTATE = rtb_TSamp;
  rate_scheduler();
}

/* Model initialize function */
void CodeMATLAB_initialize(void)
{
  CodeMATLAB_PrevZCX.EnabledSubsystem_Trig_ZCE = POS_ZCSIG;

  /* SystemInitialize for Triggered SubSystem: '<S4>/Enabled Subsystem1' */
  CodeMATLAB_PrevZCX.EnabledSubsystem1_Trig_ZCE = ZERO_ZCSIG;

  /* End of SystemInitialize for SubSystem: '<S4>/Enabled Subsystem1' */

  /* SystemInitialize for Triggered SubSystem: '<S4>/Subsystem' */
  CodeMATLAB_PrevZCX.Subsystem_Trig_ZCE = ZERO_ZCSIG;

  /* End of SystemInitialize for SubSystem: '<S4>/Subsystem' */

  /* Enable for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* Level2 S-Function Block: '<S1>/Timer (Time Base) IRQ' (stm32f4_bttbisr) */
  enable_SubsystemTimerTimeBaseIRQ();

  /* End of Enable for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* Enable for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' incorporates:
   *  SubSystem: '<S1>/Doc encoder'
   */

  /* Enable for function-call system: '<S1>/Doc encoder' */

  /* Enable for S-Function (stm32f4_encoderread): '<S8>/Encoder Read' */
  /* Level2 S-Function Block: '<S8>/Encoder Read' (stm32f4_encoderread) */
  enable_SubsystemDocencoderEncoderRead();

  /* End of Enable for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* Enable for S-Function (stm32f4_usart): '<S2>/UART Rx' */
  /* Level2 S-Function Block: '<S2>/UART Rx' (stm32f4_usart) */
  enable_Subsystem1UARTRx();

  /* Enable for S-Function (stm32f4_usart): '<S2>/UART Tx1' */
  /* Level2 S-Function Block: '<S2>/UART Tx1' (stm32f4_usart) */
  enable_Subsystem1UARTTx1();

  /* Enable for S-Function (stm32f4_basicpwm): '<S11>/Basic PWM' */
  /* Level2 S-Function Block: '<S11>/Basic PWM' (stm32f4_basicpwm) */
  enable_Subsystem2XuattinhieuBasicPWM();

  /* Enable for S-Function (stm32f4_digital_output): '<S11>/Digital Output' */
  /* Level2 S-Function Block: '<S11>/Digital Output' (stm32f4_digital_output) */
  enable_Subsystem2XuattinhieuDigitalOutput();

  /* Enable for S-Function (stm32f4_digital_input): '<S4>/Digital Input' */
  /* Level2 S-Function Block: '<S4>/Digital Input' (stm32f4_digital_input) */
  enable_Subsystem3DigitalInput();

  /* Enable for S-Function (stm32f4_usart): '<S5>/UART Setup1' */
  /* Level2 S-Function Block: '<S5>/UART Setup1' (stm32f4_usart) */
  enable_Subsystem4UARTSetup1();
}

/* Model terminate function */
void CodeMATLAB_terminate(void)
{
  /* Terminate for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* terminate_SubsystemTimerTimeBaseIRQ(); */

  /* End of Terminate for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* Terminate for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' incorporates:
   *  SubSystem: '<S1>/Doc encoder'
   */

  /* Termination for function-call system: '<S1>/Doc encoder' */

  /* Terminate for S-Function (stm32f4_encoderread): '<S8>/Encoder Read' */

  /* terminate_SubsystemDocencoderEncoderRead(); */

  /* End of Terminate for S-Function (stm32f4_bttbisr): '<S1>/Timer (Time Base) IRQ' */

  /* Terminate for S-Function (stm32f4_basicpwm): '<S11>/Basic PWM' */

  /* terminate_Subsystem2XuattinhieuBasicPWM(); */

  /* Terminate for S-Function (stm32f4_digital_output): '<S11>/Digital Output' */

  /* terminate_Subsystem2XuattinhieuDigitalOutput(); */

  /* Terminate for S-Function (stm32f4_digital_input): '<S4>/Digital Input' */

  /* terminate_Subsystem3DigitalInput(); */
}

/* [EOF] */
