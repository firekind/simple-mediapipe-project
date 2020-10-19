#include "simpleapp/include/rgb_to_grayscale_calculator.h"

#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"

namespace mediapipe {
    constexpr char kImageFrameTag[] = "IMAGE";

    ::mediapipe::Status GetContract(CalculatorContract* cc) {
        RET_CHECK(cc->Inputs().HasTag(kImageFrameTag));
        RET_CHECK(cc->Outputs().HasTag(kImageFrameTag));

        cc->Inputs().Tag(kImageFrameTag).Set<ImageFrame>();
        cc->Outputs().Tag(kImageFrameTag).Set<ImageFrame>();

        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status Open(CalculatorContext* cc) {
        // nothing much to do right now, so just return
        // ok status
        return ::mediapipe::OkStatus();
    }

    ::mediapipe::Status Process(CalculatorContext* cc) {
        RET_CHECK(cc->Inputs().Tag(kImageFrameTag).IsEmpty());

        // getting image frame from input
        const ImageFrame& frame = cc->Inputs().Tag(kImageFrameTag).Get<ImageFrame>();
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
        cc->Outputs().Tag(kImageFrameTag).Add(result.release(), cc->InputTimestamp());

        return ::mediapipe::OkStatus();
    }
}  // namespace mediapipe