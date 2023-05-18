//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Collision_detector.h
//
// Code generated for Simulink model 'Collision_detector'.
//
// Model version                  : 1.3
// Simulink Coder version         : 9.6 (R2021b) 14-May-2021
// C/C++ source code generated on : Sat Mar 25 17:36:47 2023
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#pragma once
#ifndef RTW_HEADER_Collision_detector_h_
#define RTW_HEADER_Collision_detector_h_
#include <stddef.h>
#include <math.h>
#include "rtwtypes.h"
#include "AGV.h"
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
 /* struct BigEndianIEEEDouble {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  };*/

  //struct LittleEndianIEEEDouble {
  //  struct {
  //    uint32_T wordL;
  //    uint32_T wordH;
  //  } words;
  //};

/*  struct IEEESingle {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  };*/ 
}                                     // extern "C"

extern "C" {
  static real_T rtGetInf(void);
  static real32_T rtGetInfF(void);
  static real_T rtGetMinusInf(void);
  static real32_T rtGetMinusInfF(void);
}                                      // extern "C"
  // Class declaration for model Collision_detector
  class Collision_detectorModelClass
{
  // public data and function members
 public:
  // Block states (default storage) for system '<Root>'
  struct DW_Collision_detector_T {
    real_T Divide_DWORK4;              // '<S1>/Divide'
    real_T Divide1_DWORK4;             // '<S1>/Divide1'
    real_T Divide2_DWORK4;             // '<S1>/Divide2'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Collision_detector_T {
    real_T A_position_X;               // '<Root>/A_position_X'
    real_T B_position_X;               // '<Root>/B_position_X'
    real_T A_position_Y;               // '<Root>/A_position_Y'
    real_T B_position_Y;               // '<Root>/B_position_Y'
    real_T A_Vehicle_line_velocity;    // '<Root>/A_Vehicle_line_velocity'
    real_T A_Vehicle_heading;          // '<Root>/A_Vehicle_heading'
    real_T B_Vehicle_line_velocity;    // '<Root>/B_Vehicle_line_velocity'
    real_T B_Vehicle_heading;          // '<Root>/B_Vehicle_heading'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Collision_detector_T {
    real_T distance_a_b;               // '<Root>/distance_a_b'
    real_T angle_Velocity_Position;    // '<Root>/angle_Velocity_Position'
    real_T opposite_directions_angle_A_pos;
                             // '<Root>/opposite_directions_angle_A_position_0'
    real_T opposite_directions_angle_B_pos;
                            // '<Root>/opposite_directions_angle_B_position_pi'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Collision_detector_T {
    const char_T * volatile errorStatus;
  };

  // Copy Constructor
  Collision_detectorModelClass(Collision_detectorModelClass const&) =delete;

  // Assignment Operator
  Collision_detectorModelClass& operator= (Collision_detectorModelClass const&)
    & = delete;

  // Real-Time Model get method
  Collision_detectorModelClass::RT_MODEL_Collision_detector_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_Collision_detector_T
    *pExtU_Collision_detector_T)
  {
    Collision_detector_U = *pExtU_Collision_detector_T;
  }

  // Root outports get method
  const ExtY_Collision_detector_T &getExternalOutputs() const
  {
    return Collision_detector_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Collision_detectorModelClass();

  // Destructor
  ~Collision_detectorModelClass();

  // private data and function members
 private:
  // External inputs
  ExtU_Collision_detector_T Collision_detector_U;

  // External outputs
  ExtY_Collision_detector_T Collision_detector_Y;

  // Block states
  DW_Collision_detector_T Collision_detector_DW;

  // Real-Time Model
  RT_MODEL_Collision_detector_T Collision_detector_M;
}

;

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
//  '<Root>' : 'Collision_detector'
//  '<S1>'   : 'Collision_detector/Subsystem'

#endif                                 // RTW_HEADER_Collision_detector_h_

//
// File trailer for generated code.
//
// [EOF]
//
