//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: AGV.cpp
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
#include "AGV.h"
#define NumBitsPerChar                 8U

extern real_T rt_atan2d_snf(real_T u0, real_T u1);

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

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}
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

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T u0_0;
    int32_T u1_0;
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(u0_0), static_cast<real_T>(u1_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

// Model step function
void AGVModelClass::step()
{
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_i;
  real_T rtb_Filter_i;
  real_T rtb_Integrator_b_tmp;
  real_T rtb_Integrator_g;
  real_T rtb_Saturation;
  real_T u0;
  int32_T rtb_Filter_i_0;

  // Sum: '<S2>/Sum4' incorporates:
  //   Inport: '<Root>/Target_position_X'
  //   Inport: '<Root>/position_X'

  rtb_Saturation = AGV_U.Target_position_X - AGV_U.position_X;

  // Sum: '<S2>/Sum5' incorporates:
  //   Inport: '<Root>/Target_position_Y'
  //   Inport: '<Root>/position_Y'

  rtb_Filter_i = AGV_U.Target_position_Y - AGV_U.position_Y;

  // Trigonometry: '<S2>/Cos' incorporates:
  //   Inport: '<Root>/Vehicle_heading'
  //   MagnitudeAngleToComplex: '<S2>/Magnitude-Angle to Complex1'

  rtb_Integrator_b_tmp = std::cos(AGV_U.Vehicle_heading);

  // Trigonometry: '<S2>/Sin' incorporates:
  //   Inport: '<Root>/Vehicle_heading'
  //   MagnitudeAngleToComplex: '<S2>/Magnitude-Angle to Complex1'

  rtb_FilterCoefficient_i = std::sin(AGV_U.Vehicle_heading);

  // Sum: '<S2>/Add' incorporates:
  //   Product: '<S2>/Product3'
  //   Product: '<S2>/Product4'
  //   Trigonometry: '<S2>/Cos'
  //   Trigonometry: '<S2>/Sin'

  rtb_Integrator_g = rtb_Saturation * rtb_Integrator_b_tmp + rtb_Filter_i *
    rtb_FilterCoefficient_i;

  // Gain: '<S40>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S32>/Filter'
  //   Gain: '<S31>/Derivative Gain'
  //   Sum: '<S32>/SumD'

  rtb_FilterCoefficient = (-0.214667987867616 * rtb_Integrator_g -
    AGV_DW.Filter_DSTATE) * 1.60376084607361;

  // Sum: '<S46>/Sum' incorporates:
  //   DiscreteIntegrator: '<S37>/Integrator'
  //   Gain: '<S42>/Proportional Gain'

  u0 = (pid_ppp * rtb_Integrator_g + AGV_DW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  // Saturate: '<S44>/Saturation'
  if (u0 > 6.0) {
    u0 = 6.0;
  } else if (u0 < -2.0) {
    u0 = -2.0;
  }

  // End of Saturate: '<S44>/Saturation'

  // Outport: '<Root>/Forward_velocity' incorporates:
  //   Inport: '<Root>/Vehicle_line_velocity'
  //   Sum: '<S2>/Sum'

  AGV_Y.Forward_velocity = u0; //- AGV_U.Vehicle_line_velocity

  // Product: '<S2>/Product1' incorporates:
  //   Math: '<S3>/Square'
  //   Math: '<S3>/Square1'
  //   Product: '<S2>/Reciprocal'
  //   Sqrt: '<S3>/Square Root'
  //   Sum: '<S3>/Add'

  u0 = 1.0 / std::sqrt(rtb_Saturation * rtb_Saturation + rtb_Filter_i *
                       rtb_Filter_i) * rtb_Saturation;

  // Switch: '<S2>/Switch2' incorporates:
  //   Constant: '<S2>/Constant7'
  //   Constant: '<S2>/Constant8'

  if (rtb_Filter_i >= 0.0) {
    rtb_Filter_i_0 = 1;
  } else {
    rtb_Filter_i_0 = -1;
  }

  // End of Switch: '<S2>/Switch2'

  // Trigonometry: '<S2>/Acos'
  if (u0 > 1.0) {
    u0 = 1.0;
  } else if (u0 < -1.0) {
    u0 = -1.0;
  }

  // Product: '<S2>/Product2' incorporates:
  //   Trigonometry: '<S2>/Acos'

  rtb_Saturation = static_cast<real_T>(rtb_Filter_i_0) * std::acos(u0);

  // MagnitudeAngleToComplex: '<S2>/Magnitude-Angle to Complex'
  u0 = std::cos(rtb_Saturation);
  rtb_Saturation = std::sin(rtb_Saturation);

  // Product: '<S2>/Divide' incorporates:
  //   MagnitudeAngleToComplex: '<S2>/Magnitude-Angle to Complex'

  if (rtb_FilterCoefficient_i == 0.0) {
    if (rtb_Saturation == 0.0) {
      rtb_Filter_i = u0 / rtb_Integrator_b_tmp;
      rtb_Saturation = 0.0;
    } else if (u0 == 0.0) {
      rtb_Filter_i = 0.0;
      rtb_Saturation /= rtb_Integrator_b_tmp;
    } else {
      rtb_Filter_i = u0 / rtb_Integrator_b_tmp;
      rtb_Saturation /= rtb_Integrator_b_tmp;
    }
  } else if (rtb_Integrator_b_tmp == 0.0) {
    if (u0 == 0.0) {
      rtb_Filter_i = rtb_Saturation / rtb_FilterCoefficient_i;
      rtb_Saturation = 0.0;
    } else if (rtb_Saturation == 0.0) {
      rtb_Filter_i = 0.0;
      rtb_Saturation = -(u0 / rtb_FilterCoefficient_i);
    } else {
      rtb_Filter_i = rtb_Saturation / rtb_FilterCoefficient_i;
      rtb_Saturation = -(u0 / rtb_FilterCoefficient_i);
    }
  } else {
    real_T brm;
    brm = std::abs(rtb_Integrator_b_tmp);
    rtb_Filter_i = std::abs(rtb_FilterCoefficient_i);
    if (brm > rtb_Filter_i) {
      brm = rtb_FilterCoefficient_i / rtb_Integrator_b_tmp;
      rtb_FilterCoefficient_i = brm * rtb_FilterCoefficient_i +
        rtb_Integrator_b_tmp;
      rtb_Filter_i = (brm * rtb_Saturation + u0) / rtb_FilterCoefficient_i;
      rtb_Saturation = (rtb_Saturation - brm * u0) / rtb_FilterCoefficient_i;
    } else if (rtb_Filter_i == brm) {
      rtb_Integrator_b_tmp = rtb_Integrator_b_tmp > 0.0 ? 0.5 : -0.5;
      rtb_FilterCoefficient_i = rtb_FilterCoefficient_i > 0.0 ? 0.5 : -0.5;
      rtb_Filter_i = (u0 * rtb_Integrator_b_tmp + rtb_Saturation *
                      rtb_FilterCoefficient_i) / brm;
      rtb_Saturation = (rtb_Saturation * rtb_Integrator_b_tmp - u0 *
                        rtb_FilterCoefficient_i) / brm;
    } else {
      brm = rtb_Integrator_b_tmp / rtb_FilterCoefficient_i;
      rtb_FilterCoefficient_i += brm * rtb_Integrator_b_tmp;
      rtb_Filter_i = (brm * u0 + rtb_Saturation) / rtb_FilterCoefficient_i;
      rtb_Saturation = (brm * rtb_Saturation - u0) / rtb_FilterCoefficient_i;
    }
  }

  // ComplexToMagnitudeAngle: '<S2>/Complex to Magnitude-Angle' incorporates:
  //   Product: '<S2>/Divide'

  rtb_Saturation = rt_atan2d_snf(rtb_Saturation, rtb_Filter_i);

  // Gain: '<S88>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S80>/Filter'
  //   Gain: '<S79>/Derivative Gain'
  //   Sum: '<S80>/SumD'

  rtb_FilterCoefficient_i = (0 * rtb_Saturation -
    AGV_DW.Filter_DSTATE_f) * 21.355990965824;  //0.192641194615576

  // Sum: '<S94>/Sum' incorporates:
  //   DiscreteIntegrator: '<S85>/Integrator'
  //   Gain: '<S90>/Proportional Gain'

  u0 = ( 40* rtb_Saturation + AGV_DW.Integrator_DSTATE_n) +
    rtb_FilterCoefficient_i;///6.38447152637392

  // Saturate: '<S92>/Saturation'
  if (u0 > 3.1415926) {
    u0 = 3.1415926;
  } else if (u0 < -3.1415926) {
    u0 = -3.1415926;
  }

  // End of Saturate: '<S92>/Saturation'

  // Outport: '<Root>/Rotate_velocity' incorporates:
  //   Inport: '<Root>/Vehicle_angular_velocity'
  //   Sum: '<S2>/Sum1'

  AGV_Y.Rotate_velocity = u0 ;  //- AGV_U.Vehicle_angular_velocity

  // Update for DiscreteIntegrator: '<S37>/Integrator' incorporates:
  //   Gain: '<S34>/Integral Gain'

  AGV_DW.Integrator_DSTATE += 0.175451588372658 * rtb_Integrator_g * 0.02;

  // Update for DiscreteIntegrator: '<S32>/Filter'
  AGV_DW.Filter_DSTATE += 0.02 * rtb_FilterCoefficient;

  // Update for DiscreteIntegrator: '<S85>/Integrator' incorporates:
  //   Gain: '<S82>/Integral Gain'

  AGV_DW.Integrator_DSTATE_n += 0* rtb_Saturation * 0.02;//10.84639384459 

  // Update for DiscreteIntegrator: '<S80>/Filter'
  AGV_DW.Filter_DSTATE_f += 0.02 * rtb_FilterCoefficient_i;
}

// Model initialize function
void AGVModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
}

// Model terminate function
void AGVModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
AGVModelClass::AGVModelClass() :
  AGV_U(),
  AGV_Y(),
  AGV_DW(),
  AGV_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
AGVModelClass::~AGVModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
AGVModelClass::RT_MODEL_AGV_T * AGVModelClass::getRTM()
{
  return (&AGV_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
