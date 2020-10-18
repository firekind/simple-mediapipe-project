#ifndef RGB_TO_GRAYSCALE_CALCULATOR_H
#define RGB_TO_GRAYSCALE_CALCULATOR_H

#include "mediapipe/framework/calculator_framework.h"

namespace mediapipe {
    class RGBToGrayScaleCalculator : public CalculatorBase {
       public:
        static ::mediapipe::Status GetContract(CalculatorContract* cc);
        ::mediapipe::Status Open(CalculatorContext* cc);
        ::mediapipe::Status Process(CalculatorContext* cc);
    };
}  // namespace mediapipe

#endif