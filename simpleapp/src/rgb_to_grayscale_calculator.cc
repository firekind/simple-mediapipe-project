#include "simpleapp/include/rgb_to_grayscale_calculator.h"

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace mediapipe {
    constexpr char kInputImageTag[] = "RGB";
    constexpr char kOutputTag[] = "GRAYSCALE";

    REGISTER_CALCULATOR(RGBToGrayScaleCalculator);

    ::mediapipe::Status RGBToGrayScaleCalculator::GetContract(CalculatorContract* cc) {
        RET_CHECK(cc->Inputs().HasTag(kInputImageTag));
        RET_CHECK(cc->Outputs().HasTag(kOutputTag));

        cc->Inputs().Tag(kInputImageTag).Set<ImageFrame>();
        cc->Outputs().Tag(kOutputTag).Set<ImageFrame>();

        LOG(INFO) << "Contract done.";

        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status RGBToGrayScaleCalculator::Open(CalculatorContext* cc) {
        // nothing much to do right now, so just return
        // ok status

        LOG(INFO) << "Calculator opened.";
        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status RGBToGrayScaleCalculator::Process(CalculatorContext* cc) {
        RET_CHECK(! cc->Inputs().Tag(kInputImageTag).IsEmpty());

        // getting image frame from input
        const ImageFrame& frame = cc->Inputs().Tag(kInputImageTag).Get<ImageFrame>();
        // converting image frame to opencv matrix
        cv::Mat mat = formats::MatView(&frame);

        // converting image to grayscale
        cv::Mat converted;
        cv::cvtColor(mat, converted, CV_BGR2GRAY);

        // converting opencv matrix to image frame:
        // creating empty image frame
        auto result = absl::make_unique<ImageFrame>(
            ImageFormat::GRAY8,
            converted.cols,
            converted.rows,
            ImageFrame::kDefaultAlignmentBoundary
        );
        // getting mutable opencv matrix from result
        cv::Mat result_mat = formats::MatView(result.get());
        // copying converted image to result_mat
        converted.copyTo(result_mat);

        // sending result to output
        cc->Outputs().Tag(kOutputTag).Add(result.release(), cc->InputTimestamp());

        return ::mediapipe::OkStatus();
    }
}  // namespace mediapipe