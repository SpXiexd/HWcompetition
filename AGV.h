//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: AGV.h
//
// Code generated for Simulink model 'AGV'.
//
// Model version                  : 1.36
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Fri Mar 24 11:37:43 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_AGV_h_
#define RTW_HEADER_AGV_h_
#include <stddef.h>
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
extern double pid_ppp;
// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

extern "C" {
  static real_T rtGetNaN(void);
  static real32_T rtGetNaNF(void);
}                                      // extern "C"
  extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  static void rt_InitInfAndNaN(size_t realSize);
  static boolean_T rtIsInf(real_T value);
  static boolean_T rtIsInfF(real32_T value);
  static boolean_T rtIsNaN(real_T value);
  static boolean_T rtIsNaNF(real32_T value);
  struct BigEndianIEEEDouble {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  };

  struct LittleEndianIEEEDouble {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  };

  struct IEEESingle {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  };
}                                      // extern "C"

extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  // Class declaration for model AGV
  class AGVModelClass
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_AGV_T {
    real_T Integrator_DSTATE;          // '<S37>/Integrator'
    real_T Filter_DSTATE;              // '<S32>/Filter'
    real_T Integrator_DSTATE_n;        // '<S85>/Integrator'
    real_T Filter_DSTATE_f;            // '<S80>/Filter'
    real_T Divide_DWORK4;              // '<S2>/Divide'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_AGV_T {
    real_T position_X;                 // '<Root>/position_X'
    real_T position_Y;                 // '<Root>/position_Y'
    real_T Target_position_X;          // '<Root>/Target_position_X'
    real_T Target_position_Y;          // '<Root>/Target_position_Y'
    real_T Vehicle_line_velocity;      // '<Root>/Vehicle_line_velocity'
    real_T Vehicle_angular_velocity;   // '<Root>/Vehicle_angular_velocity'
    real_T Vehicle_heading;            // '<Root>/Vehicle_heading'
    real_T Vehicle_mass;               // '<Root>/Vehicle_mass'
    real_T Vehicle_rotational_inertial;// '<Root>/Vehicle_rotational_inertial'
    real_T Delta_time;                 // '<Root>/Delta_time'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_AGV_T {
    real_T Forward_velocity;           // '<Root>/Forward_velocity'
    real_T Rotate_velocity;            // '<Root>/Rotate_velocity'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_AGV_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  AGVModelClass(AGVModelClass const&) =delete;

  // Assignment Operator
  AGVModelClass& operator= (AGVModelClass const&) & = delete;

  // Real-Time Model get method
  AGVModelClass::RT_MODEL_AGV_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_AGV_T *pExtU_AGV_T)
  {
    AGV_U = *pExtU_AGV_T;
  }

  // Root outports get method
  const ExtY_AGV_T &getExternalOutputs() const
  {
    return AGV_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  AGVModelClass();

  // Destructor
  ~AGVModelClass();

  // private data and function members
 private:
  // External inputs
  ExtU_AGV_T AGV_U;

  // External outputs
  ExtY_AGV_T AGV_Y;

  // Block states
  DW_AGV_T AGV_DW;

  // Real-Time Model
  RT_MODEL_AGV_T AGV_M;
}

;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Constant1' : Unused code path elimination
//  Block '<S2>/Scope8' : Unused code path elimination
//  Block '<S3>/Scope1' : Unused code path elimination
//  Block '<S3>/Scope8' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'AGV'
//  '<S1>'   : 'AGV/pidrun'
//  '<S2>'   : 'AGV/pidrun/Subsystem4'
//  '<S3>'   : 'AGV/pidrun/Subsystem4/Subsystem3'
//  '<S4>'   : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1'
//  '<S5>'   : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2'
//  '<S6>'   : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Anti-windup'
//  '<S7>'   : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/D Gain'
//  '<S8>'   : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Filter'
//  '<S9>'   : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Filter ICs'
//  '<S10>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/I Gain'
//  '<S11>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Ideal P Gain'
//  '<S12>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Ideal P Gain Fdbk'
//  '<S13>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Integrator'
//  '<S14>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Integrator ICs'
//  '<S15>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/N Copy'
//  '<S16>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/N Gain'
//  '<S17>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/P Copy'
//  '<S18>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Parallel P Gain'
//  '<S19>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Reset Signal'
//  '<S20>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Saturation'
//  '<S21>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Saturation Fdbk'
//  '<S22>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Sum'
//  '<S23>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Sum Fdbk'
//  '<S24>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tracking Mode'
//  '<S25>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tracking Mode Sum'
//  '<S26>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tsamp - Integral'
//  '<S27>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tsamp - Ngain'
//  '<S28>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/postSat Signal'
//  '<S29>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/preSat Signal'
//  '<S30>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Anti-windup/Passthrough'
//  '<S31>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/D Gain/Internal Parameters'
//  '<S32>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Filter/Disc. Forward Euler Filter'
//  '<S33>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S34>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/I Gain/Internal Parameters'
//  '<S35>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Ideal P Gain/Passthrough'
//  '<S36>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S37>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Integrator/Discrete'
//  '<S38>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Integrator ICs/Internal IC'
//  '<S39>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/N Copy/Disabled'
//  '<S40>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/N Gain/Internal Parameters'
//  '<S41>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/P Copy/Disabled'
//  '<S42>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S43>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Reset Signal/Disabled'
//  '<S44>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Saturation/Enabled'
//  '<S45>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Saturation Fdbk/Disabled'
//  '<S46>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Sum/Sum_PID'
//  '<S47>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Sum Fdbk/Disabled'
//  '<S48>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tracking Mode/Disabled'
//  '<S49>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S50>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tsamp - Integral/Passthrough'
//  '<S51>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S52>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/postSat Signal/Forward_Path'
//  '<S53>'  : 'AGV/pidrun/Subsystem4/λ�ÿ���PID Controller1/preSat Signal/Forward_Path'
//  '<S54>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Anti-windup'
//  '<S55>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/D Gain'
//  '<S56>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Filter'
//  '<S57>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Filter ICs'
//  '<S58>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/I Gain'
//  '<S59>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Ideal P Gain'
//  '<S60>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Ideal P Gain Fdbk'
//  '<S61>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Integrator'
//  '<S62>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Integrator ICs'
//  '<S63>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/N Copy'
//  '<S64>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/N Gain'
//  '<S65>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/P Copy'
//  '<S66>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Parallel P Gain'
//  '<S67>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Reset Signal'
//  '<S68>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Saturation'
//  '<S69>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Saturation Fdbk'
//  '<S70>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Sum'
//  '<S71>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Sum Fdbk'
//  '<S72>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tracking Mode'
//  '<S73>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tracking Mode Sum'
//  '<S74>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tsamp - Integral'
//  '<S75>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tsamp - Ngain'
//  '<S76>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/postSat Signal'
//  '<S77>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/preSat Signal'
//  '<S78>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Anti-windup/Passthrough'
//  '<S79>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/D Gain/Internal Parameters'
//  '<S80>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Filter/Disc. Forward Euler Filter'
//  '<S81>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S82>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/I Gain/Internal Parameters'
//  '<S83>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Ideal P Gain/Passthrough'
//  '<S84>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S85>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Integrator/Discrete'
//  '<S86>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Integrator ICs/Internal IC'
//  '<S87>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/N Copy/Disabled'
//  '<S88>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/N Gain/Internal Parameters'
//  '<S89>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/P Copy/Disabled'
//  '<S90>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S91>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Reset Signal/Disabled'
//  '<S92>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Saturation/Enabled'
//  '<S93>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Saturation Fdbk/Disabled'
//  '<S94>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Sum/Sum_PID'
//  '<S95>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Sum Fdbk/Disabled'
//  '<S96>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tracking Mode/Disabled'
//  '<S97>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S98>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tsamp - Integral/Passthrough'
//  '<S99>'  : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S100>' : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/postSat Signal/Forward_Path'
//  '<S101>' : 'AGV/pidrun/Subsystem4/�Ƕȿ���PID Controller2/preSat Signal/Forward_Path'

#endif                                 // RTW_HEADER_AGV_h_

//
// File trailer for generated code.
//
// [EOF]
//
