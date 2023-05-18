//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Collision_detector.cpp
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
#include "Collision_detector.h"
#include "AGV.h"
#define NumBitsPerChar                 8U

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_hypotd_snf(real_T u0, real_T u1);

//===========*
//  Constants *
// ===========
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

//
//  UNUSED_PARAMETER(x)
//    Used to specify that a function parameter (argument) is required but not
//    accessed by the function body.

#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      // do nothing
#else

//
//  This is the semi-ANSI standard way of indicating that an
//  unused function parameter is required.

#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

//extern "C" {
//  real_T rtInf;
//  real_T rtMinusInf;
//  real_T rtNaN;
//  real32_T rtInfF;
//  real32_T rtMinusInfF;
//  real32_T rtNaNF;
//}
  extern "C"
{
  //
  // Initialize rtNaN needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetNaN(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T nan{ 0.0 };

    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  //
  // Initialize rtNaNF needed by the generated code.
  // NaN is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetNaNF(void)
  {
    IEEESingle nanF{ { 0.0F } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}

extern "C" {
  //
  // Initialize the rtInf, rtMinusInf, and rtNaN needed by the
  // generated code. NaN is initialized as non-signaling. Assumes IEEE.
  //
  static void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  // Test if value is infinite
  static boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  // Test if single-precision value is infinite
  static boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  // Test if value is not a number
  static boolean_T rtIsNaN(real_T value)
  {
    boolean_T result{ (boolean_T) 0 };

    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  // Test if single-precision value is not a number
  static boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}
  extern "C"
{
  //
  // Initialize rtInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T inf{ 0.0 };

    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  //
  // Initialize rtInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  //
  // Initialize rtMinusInf needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal{ sizeof(real_T) * (NumBitsPerChar) };

    real_T minf{ 0.0 };

    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  //
  // Initialize rtMinusInfF needed by the generated code.
  // Inf is initialized as non-signaling. Assumes IEEE.
  //
  static real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}
//
//real_T rt_atan2d_snf(real_T u0, real_T u1)
//{
//  real_T y;
//  if (std::isnan(u0) || std::isnan(u1)) {
//    y = (rtNaN);
//  } else if (std::isinf(u0) && std::isinf(u1)) {
//    int32_T u0_0;
//    int32_T u1_0;
//    if (u0 > 0.0) {
//      u0_0 = 1;
//    } else {
//      u0_0 = -1;
//    }
//
//    if (u1 > 0.0) {
//      u1_0 = 1;
//    } else {
//      u1_0 = -1;
//    }
//
//    y = std::atan2(static_cast<real_T>(u0_0), static_cast<real_T>(u1_0));
//  } else if (u1 == 0.0) {
//    if (u0 > 0.0) {
//      y = RT_PI / 2.0;
//    } else if (u0 < 0.0) {
//      y = -(RT_PI / 2.0);
//    } else {
//      y = 0.0;
//    }
//  } else {
//    y = std::atan2(u0, u1);
//  }
//
//  return y;
//}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T y;
  a = std::fabs(u0);
  y = std::fabs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = std::sqrt(y * y + 1.0) * a;
  } else if (!std::isnan(y)) {
    y = a * 1.4142135623730951;
  }

  return y;
}

// Model step function
void Collision_detectorModelClass::step()
{
  real_T ai;
  real_T ar;
  real_T bim;
  real_T brm;
  real_T rtb_Add_im;
  real_T rtb_Add_re;
  real_T rtb_Divide_re;
  real_T rtb_MagnitudeAngletoComplex1_im;
  real_T rtb_MagnitudeAngletoComplex1_re;
  real_T rtb_MagnitudeAngletoComplex2_im;
  real_T rtb_MagnitudeAngletoComplex2_re;
  real_T sgnbi;

  // MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex1' incorporates:
  //   Inport: '<Root>/A_Vehicle_heading'
  //   Inport: '<Root>/A_Vehicle_line_velocity'

  rtb_MagnitudeAngletoComplex1_re = Collision_detector_U.A_Vehicle_line_velocity
    * std::cos(Collision_detector_U.A_Vehicle_heading);
  rtb_MagnitudeAngletoComplex1_im = Collision_detector_U.A_Vehicle_line_velocity
    * std::sin(Collision_detector_U.A_Vehicle_heading);

  // MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex2' incorporates:
  //   Inport: '<Root>/B_Vehicle_heading'
  //   Inport: '<Root>/B_Vehicle_line_velocity'

  rtb_MagnitudeAngletoComplex2_re = Collision_detector_U.B_Vehicle_line_velocity
    * std::cos(Collision_detector_U.B_Vehicle_heading);
  rtb_MagnitudeAngletoComplex2_im = Collision_detector_U.B_Vehicle_line_velocity
    * std::sin(Collision_detector_U.B_Vehicle_heading);

  // Sum: '<S1>/Add' incorporates:
  //   Inport: '<Root>/A_position_X'
  //   Inport: '<Root>/A_position_Y'
  //   Inport: '<Root>/B_position_X'
  //   Inport: '<Root>/B_position_Y'

  rtb_Add_re = Collision_detector_U.B_position_X -
    Collision_detector_U.A_position_X;
  rtb_Add_im = Collision_detector_U.B_position_Y -
    Collision_detector_U.A_position_Y;

  // Product: '<S1>/Divide' incorporates:
  //   Inport: '<Root>/A_position_X'
  //   Inport: '<Root>/A_position_Y'
  //   Inport: '<Root>/B_position_X'
  //   Inport: '<Root>/B_position_Y'
  //   MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex1'
  //   MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex2'
  //   Sum: '<S1>/Add'
  //   Sum: '<S1>/Add1'
  //   Sum: '<S1>/Add2'
  //   Sum: '<S1>/Add3'

  ar = (Collision_detector_U.B_position_X + rtb_MagnitudeAngletoComplex2_re) -
    (Collision_detector_U.A_position_X + rtb_MagnitudeAngletoComplex1_re);
  ai = (Collision_detector_U.B_position_Y + rtb_MagnitudeAngletoComplex2_im) -
    (Collision_detector_U.A_position_Y + rtb_MagnitudeAngletoComplex1_im);
  if (rtb_Add_im == 0.0) {
    if (ai == 0.0) {
      rtb_Divide_re = ar / rtb_Add_re;
      brm = 0.0;
    } else if (ar == 0.0) {
      rtb_Divide_re = 0.0;
      brm = ai / rtb_Add_re;
    } else {
      rtb_Divide_re = ar / rtb_Add_re;
      brm = ai / rtb_Add_re;
    }
  } else if (rtb_Add_re == 0.0) {
    if (ar == 0.0) {
      rtb_Divide_re = ai / rtb_Add_im;
      brm = 0.0;
    } else if (ai == 0.0) {
      rtb_Divide_re = 0.0;
      brm = -(ar / rtb_Add_im);
    } else {
      rtb_Divide_re = ai / rtb_Add_im;
      brm = -(ar / rtb_Add_im);
    }
  } else {
    brm = std::fabs(rtb_Add_re);
    bim = std::fabs(rtb_Add_im);
    if (brm > bim) {
      brm = rtb_Add_im / rtb_Add_re;
      bim = brm * rtb_Add_im + rtb_Add_re;
      rtb_Divide_re = (brm * ai + ar) / bim;
      brm = (ai - brm * ar) / bim;
    } else if (bim == brm) {
      bim = rtb_Add_re > 0.0 ? 0.5 : -0.5;
      sgnbi = rtb_Add_im > 0.0 ? 0.5 : -0.5;
      rtb_Divide_re = (ar * bim + ai * sgnbi) / brm;
      brm = (ai * bim - ar * sgnbi) / brm;
    } else {
      brm = rtb_Add_re / rtb_Add_im;
      bim = brm * rtb_Add_re + rtb_Add_im;
      rtb_Divide_re = (brm * ar + ai) / bim;
      brm = (brm * ai - ar) / bim;
    }
  }

  // Outport: '<Root>/angle_Velocity_Position' incorporates:
  //   ComplexToMagnitudeAngle: '<S1>/Complex to Magnitude-Angle1'
  //   Product: '<S1>/Divide'

  Collision_detector_Y.angle_Velocity_Position = rt_atan2d_snf(brm,
    rtb_Divide_re);

  // Outport: '<Root>/distance_a_b' incorporates:
  //   ComplexToMagnitudeAngle: '<S1>/Complex to Magnitude-Angle2'
  //   Sum: '<S1>/Add'

  Collision_detector_Y.distance_a_b = rt_hypotd_snf(rtb_Add_re, rtb_Add_im);

  // Product: '<S1>/Divide1' incorporates:
  //   MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex1'
  //   MagnitudeAngleToComplex: '<S1>/Magnitude-Angle to Complex2'
  //   Product: '<S1>/Divide2'
  //   Sum: '<S1>/Add'

  if (rtb_Add_im == 0.0) {
    if (rtb_MagnitudeAngletoComplex1_im == 0.0) {
      ar = rtb_MagnitudeAngletoComplex1_re / rtb_Add_re;
      rtb_MagnitudeAngletoComplex1_im = 0.0;
    } else if (rtb_MagnitudeAngletoComplex1_re == 0.0) {
      ar = 0.0;
      rtb_MagnitudeAngletoComplex1_im /= rtb_Add_re;
    } else {
      ar = rtb_MagnitudeAngletoComplex1_re / rtb_Add_re;
      rtb_MagnitudeAngletoComplex1_im /= rtb_Add_re;
    }

    if (rtb_MagnitudeAngletoComplex2_im == 0.0) {
      rtb_MagnitudeAngletoComplex1_re = rtb_MagnitudeAngletoComplex2_re /
        rtb_Add_re;
      rtb_MagnitudeAngletoComplex2_im = 0.0;
    } else if (rtb_MagnitudeAngletoComplex2_re == 0.0) {
      rtb_MagnitudeAngletoComplex1_re = 0.0;
      rtb_MagnitudeAngletoComplex2_im /= rtb_Add_re;
    } else {
      rtb_MagnitudeAngletoComplex1_re = rtb_MagnitudeAngletoComplex2_re /
        rtb_Add_re;
      rtb_MagnitudeAngletoComplex2_im /= rtb_Add_re;
    }
  } else {
    if (rtb_Add_re == 0.0) {
      if (rtb_MagnitudeAngletoComplex1_re == 0.0) {
        ar = rtb_MagnitudeAngletoComplex1_im / rtb_Add_im;
        rtb_MagnitudeAngletoComplex1_im = 0.0;
      } else if (rtb_MagnitudeAngletoComplex1_im == 0.0) {
        ar = 0.0;
        rtb_MagnitudeAngletoComplex1_im = -(rtb_MagnitudeAngletoComplex1_re /
          rtb_Add_im);
      } else {
        ar = rtb_MagnitudeAngletoComplex1_im / rtb_Add_im;
        rtb_MagnitudeAngletoComplex1_im = -(rtb_MagnitudeAngletoComplex1_re /
          rtb_Add_im);
      }
    } else {
      brm = std::fabs(rtb_Add_re);
      bim = std::fabs(rtb_Add_im);
      if (brm > bim) {
        brm = rtb_Add_im / rtb_Add_re;
        bim = brm * rtb_Add_im + rtb_Add_re;
        ar = (brm * rtb_MagnitudeAngletoComplex1_im +
              rtb_MagnitudeAngletoComplex1_re) / bim;
        rtb_MagnitudeAngletoComplex1_im = (rtb_MagnitudeAngletoComplex1_im - brm
          * rtb_MagnitudeAngletoComplex1_re) / bim;
      } else if (bim == brm) {
        bim = rtb_Add_re > 0.0 ? 0.5 : -0.5;
        sgnbi = rtb_Add_im > 0.0 ? 0.5 : -0.5;
        ar = (rtb_MagnitudeAngletoComplex1_re * bim +
              rtb_MagnitudeAngletoComplex1_im * sgnbi) / brm;
        rtb_MagnitudeAngletoComplex1_im = (rtb_MagnitudeAngletoComplex1_im * bim
          - rtb_MagnitudeAngletoComplex1_re * sgnbi) / brm;
      } else {
        brm = rtb_Add_re / rtb_Add_im;
        bim = brm * rtb_Add_re + rtb_Add_im;
        ar = (brm * rtb_MagnitudeAngletoComplex1_re +
              rtb_MagnitudeAngletoComplex1_im) / bim;
        rtb_MagnitudeAngletoComplex1_im = (brm * rtb_MagnitudeAngletoComplex1_im
          - rtb_MagnitudeAngletoComplex1_re) / bim;
      }
    }

    if (rtb_Add_re == 0.0) {
      if (rtb_MagnitudeAngletoComplex2_re == 0.0) {
        rtb_MagnitudeAngletoComplex1_re = rtb_MagnitudeAngletoComplex2_im /
          rtb_Add_im;
        rtb_MagnitudeAngletoComplex2_im = 0.0;
      } else if (rtb_MagnitudeAngletoComplex2_im == 0.0) {
        rtb_MagnitudeAngletoComplex1_re = 0.0;
        rtb_MagnitudeAngletoComplex2_im = -(rtb_MagnitudeAngletoComplex2_re /
          rtb_Add_im);
      } else {
        rtb_MagnitudeAngletoComplex1_re = rtb_MagnitudeAngletoComplex2_im /
          rtb_Add_im;
        rtb_MagnitudeAngletoComplex2_im = -(rtb_MagnitudeAngletoComplex2_re /
          rtb_Add_im);
      }
    } else {
      brm = std::fabs(rtb_Add_re);
      bim = std::fabs(rtb_Add_im);
      if (brm > bim) {
        brm = rtb_Add_im / rtb_Add_re;
        bim = brm * rtb_Add_im + rtb_Add_re;
        rtb_MagnitudeAngletoComplex1_re = (brm * rtb_MagnitudeAngletoComplex2_im
          + rtb_MagnitudeAngletoComplex2_re) / bim;
        rtb_MagnitudeAngletoComplex2_im = (rtb_MagnitudeAngletoComplex2_im - brm
          * rtb_MagnitudeAngletoComplex2_re) / bim;
      } else if (bim == brm) {
        bim = rtb_Add_re > 0.0 ? 0.5 : -0.5;
        sgnbi = rtb_Add_im > 0.0 ? 0.5 : -0.5;
        rtb_MagnitudeAngletoComplex1_re = (rtb_MagnitudeAngletoComplex2_re * bim
          + rtb_MagnitudeAngletoComplex2_im * sgnbi) / brm;
        rtb_MagnitudeAngletoComplex2_im = (rtb_MagnitudeAngletoComplex2_im * bim
          - rtb_MagnitudeAngletoComplex2_re * sgnbi) / brm;
      } else {
        brm = rtb_Add_re / rtb_Add_im;
        bim = brm * rtb_Add_re + rtb_Add_im;
        rtb_MagnitudeAngletoComplex1_re = (brm * rtb_MagnitudeAngletoComplex2_re
          + rtb_MagnitudeAngletoComplex2_im) / bim;
        rtb_MagnitudeAngletoComplex2_im = (brm * rtb_MagnitudeAngletoComplex2_im
          - rtb_MagnitudeAngletoComplex2_re) / bim;
      }
    }
  }

  // Outport: '<Root>/opposite_directions_angle_A_position_0' incorporates:
  //   ComplexToMagnitudeAngle: '<S1>/Complex to Magnitude-Angle3'
  //   Product: '<S1>/Divide1'

  Collision_detector_Y.opposite_directions_angle_A_pos = rt_atan2d_snf
    (rtb_MagnitudeAngletoComplex1_im, ar);

  // Outport: '<Root>/opposite_directions_angle_B_position_pi' incorporates:
  //   ComplexToMagnitudeAngle: '<S1>/Complex to Magnitude-Angle4'
  //   Product: '<S1>/Divide2'

  Collision_detector_Y.opposite_directions_angle_B_pos = rt_atan2d_snf
    (rtb_MagnitudeAngletoComplex2_im, rtb_MagnitudeAngletoComplex1_re);
}

// Model initialize function
void Collision_detectorModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Model terminate function
void Collision_detectorModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
Collision_detectorModelClass::Collision_detectorModelClass() :
  Collision_detector_U(),
  Collision_detector_Y(),
  Collision_detector_DW(),
  Collision_detector_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
Collision_detectorModelClass::~Collision_detectorModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Collision_detectorModelClass::RT_MODEL_Collision_detector_T
  * Collision_detectorModelClass::getRTM()
{
  return (&Collision_detector_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
