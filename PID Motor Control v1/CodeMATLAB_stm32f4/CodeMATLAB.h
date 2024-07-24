/*
 * File: CodeMATLAB.h
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

#ifndef RTW_HEADER_CodeMATLAB_h_
#define RTW_HEADER_CodeMATLAB_h_
#ifndef CodeMATLAB_COMMON_INCLUDES_
# define CodeMATLAB_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "waijung_hwdrvlib.h"
#endif                                 /* CodeMATLAB_COMMON_INCLUDES_ */

#include "CodeMATLAB_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  real_T DiscreteTimeIntegrator;       /* '<S17>/Discrete-Time Integrator' */
  real_T PWM;                          /* '<S11>/MATLAB Function' */
  real_T Dir;                          /* '<S11>/MATLAB Function' */
  real_T Sum3;                         /* '<S9>/Sum3' */
  uint32_T EncoderRead_o1;             /* '<S8>/Encoder Read' */
  uint32_T EncoderRead_o2;             /* '<S8>/Encoder Read' */
  real32_T DataStoreRead;              /* '<S2>/Data Store Read' */
  real32_T UARTRx_o2;                  /* '<S2>/UART Rx' */
  real32_T UARTRx_o3;                  /* '<S2>/UART Rx' */
  real32_T UARTRx_o4;                  /* '<S2>/UART Rx' */
  real32_T UARTRx_o5;                  /* '<S2>/UART Rx' */
  real32_T CastToSingle6;              /* '<S2>/Cast To Single6' */
  real32_T CastToSingle5;              /* '<S2>/Cast To Single5' */
  real32_T CastToSingle7;              /* '<S2>/Cast To Single7' */
  real32_T HostSerialRx_o2;            /* '<S7>/Host Serial Rx' */
  real32_T HostSerialRx_o3;            /* '<S7>/Host Serial Rx' */
  real32_T HostSerialRx_o4;            /* '<S7>/Host Serial Rx' */
  real32_T HostSerialRx_o5;            /* '<S7>/Host Serial Rx' */
  uint8_T UARTRx_o1;                   /* '<S2>/UART Rx' */
  uint8_T HostSerialRx_o1;             /* '<S7>/Host Serial Rx' */
  boolean_T DigitalInput_o1;           /* '<S4>/Digital Input' */
  boolean_T DigitalInput_o2;           /* '<S4>/Digital Input' */
  boolean_T DigitalInput_o3;           /* '<S4>/Digital Input' */
} B_CodeMATLAB_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<S17>/Discrete-Time Integrator' */
  real_T UD_DSTATE;                    /* '<S18>/UD' */
  real_T UnitDelay_DSTATE;             /* '<S9>/Unit Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S9>/Unit Delay1' */
  volatile real_T RateTransition2_Buffer[2];/* '<S1>/Rate Transition2' */
  real32_T ITF_SET_POINT;              /* '<Root>/Data Store Memory' */
  volatile int8_T RateTransition2_ActiveBufIdx;/* '<S1>/Rate Transition2' */
  volatile int8_T RateTransition2_semaphoreTaken;/* '<S1>/Rate Transition2' */
} DW_CodeMATLAB_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState Subsystem_Trig_ZCE;       /* '<S4>/Subsystem' */
  ZCSigState EnabledSubsystem1_Trig_ZCE;/* '<S4>/Enabled Subsystem1' */
  ZCSigState EnabledSubsystem_Trig_ZCE;/* '<S4>/Enabled Subsystem' */
} PrevZCX_CodeMATLAB_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real32_T CastToSingle4;        /* '<S7>/Cast To Single4' */
  const real32_T CastToSingle5;        /* '<S7>/Cast To Single5' */
  const real32_T CastToSingle6;        /* '<S7>/Cast To Single6' */
  const real32_T CastToSingle7;        /* '<S7>/Cast To Single7' */
} ConstB_CodeMATLAB_T;

/* Real-time Model Data Structure */
struct tag_RTM_CodeMATLAB_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (default storage) */
extern B_CodeMATLAB_T CodeMATLAB_B;

/* Block states (default storage) */
extern DW_CodeMATLAB_T CodeMATLAB_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_CodeMATLAB_T CodeMATLAB_PrevZCX;
extern const ConstB_CodeMATLAB_T CodeMATLAB_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void CodeMATLAB_initialize(void);
extern void CodeMATLAB_step(void);
extern void CodeMATLAB_terminate(void);

/* Real-time Model object */
extern RT_MODEL_CodeMATLAB_T *const CodeMATLAB_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S18>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Scope' : Unused code path elimination
 * Block '<S7>/Display' : Unused code path elimination
 * Block '<S7>/Display1' : Unused code path elimination
 * Block '<S7>/Display2' : Unused code path elimination
 * Block '<S7>/Display3' : Unused code path elimination
 * Block '<S7>/Display4' : Unused code path elimination
 * Block '<S7>/Scope' : Unused code path elimination
 * Block '<S2>/Cast To Single4' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CodeMATLAB'
 * '<S1>'   : 'CodeMATLAB/Subsystem'
 * '<S2>'   : 'CodeMATLAB/Subsystem1'
 * '<S3>'   : 'CodeMATLAB/Subsystem2'
 * '<S4>'   : 'CodeMATLAB/Subsystem3'
 * '<S5>'   : 'CodeMATLAB/Subsystem4'
 * '<S6>'   : 'CodeMATLAB/Subsystem5'
 * '<S7>'   : 'CodeMATLAB/Subsystem6'
 * '<S8>'   : 'CodeMATLAB/Subsystem/Doc encoder'
 * '<S9>'   : 'CodeMATLAB/Subsystem/Doc encoder/Chong tran xung'
 * '<S10>'  : 'CodeMATLAB/Subsystem1/Subsystem'
 * '<S11>'  : 'CodeMATLAB/Subsystem2/Xuat tin hieu'
 * '<S12>'  : 'CodeMATLAB/Subsystem2/Xuat tin hieu/MATLAB Function'
 * '<S13>'  : 'CodeMATLAB/Subsystem3/Enabled Subsystem'
 * '<S14>'  : 'CodeMATLAB/Subsystem3/Enabled Subsystem1'
 * '<S15>'  : 'CodeMATLAB/Subsystem3/Subsystem'
 * '<S16>'  : 'CodeMATLAB/Subsystem5/PID'
 * '<S17>'  : 'CodeMATLAB/Subsystem5/PID/PI'
 * '<S18>'  : 'CodeMATLAB/Subsystem5/PID/PI/Discrete Derivative'
 */
#endif                                 /* RTW_HEADER_CodeMATLAB_h_ */

/* [EOF] */
