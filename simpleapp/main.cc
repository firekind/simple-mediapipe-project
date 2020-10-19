#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/logging.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"

namespace mediapipe {
    constexpr char kInputStream[] = "in";
    constexpr char kOutputStream[] = "out";
    constexpr char kWindowName[] = "Simple App";

    ::mediapipe::Status run() {
        // Configures a simple graph, which has the rgb to gray scale calculator.
        CalculatorGraphConfig config = ParseTextProtoOrDie<CalculatorGraphConfig>(R"(
            input_stream: "in"
            output_stream: "out"
            node {
              calculator: "RGBToGrayScaleCalculator"
              input_stream: "RGB:in"
              output_stream: "GRAYSCALE:out"
            }
        )");

        LOG(INFO) << "Initializing graph";
        CalculatorGraph graph; // creating graph object
        MP_RETURN_IF_ERROR(graph.Initialize(config)); // initializing graph

        LOG(INFO) << "Initializing the camera";
        cv::VideoCapture capture; // creating camera object
        capture.open(0); // opening camera
        RET_CHECK(capture.isOpened()); // checking if camera is opened

        LOG(INFO) << "Starting the calculator graph";
        ASSIGN_OR_RETURN(
            ::mediapipe::OutputStreamPoller poller,
            graph.AddOutputStreamPoller(kOutputStream)
        ); // adding a poller to the output stream of the graph so we can get the outputs
        MP_RETURN_IF_ERROR(graph.StartRun({})); // starting graph

        LOG(INFO) << "Starting to grab and process frames";
        bool grab_frames = true;
        while (grab_frames) {
            // getting frame from camera
            cv::Mat raw;
            cv::Mat camera_frame;
            capture >> raw;
            cv::cvtColor(raw, camera_frame, cv::COLOR_BGR2RGB); // converting to RGB image

            // converting opencv mat to image frame
            auto image_frame = absl::make_unique<ImageFrame>(
                ImageFormat::SRGB,
                camera_frame.cols,
                camera_frame.rows,
                ImageFrame::kDefaultAlignmentBoundary
            );
            cv::Mat image_frame_mat = formats::MatView(image_frame.get());
            camera_frame.copyTo(image_frame_mat);

            // sending image frame into graph
            size_t frame_timestamp = (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
            MP_RETURN_IF_ERROR(
                graph.AddPacketToInputStream(
                    kInputStream,
                    ::mediapipe::Adopt(image_frame.release()).At(::mediapipe::Timestamp(frame_timestamp))
                )
            );

            // getting result from graph, or stopping if that fails
            ::mediapipe::Packet output_packet;
            if (!poller.Next(&output_packet))
                break;
            auto& output_frame = output_packet.Get<ImageFrame>();

            // converting to opencv and displaying
            cv::Mat output_frame_mat = formats::MatView(&output_frame);
            cv::imshow(kWindowName, output_frame_mat);
            
            // terminating if key is pressed
            const int key = cv::waitKey(5);
            if (key >= 0 && key != 255)
                grab_frames = false;
        }

        LOG(INFO) << "Shutting down";
        MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
        return graph.WaitUntilDone();
    }
}  // namespace mediapipe

int main(int argc, char** argv) {
    google::InitGoogleLogging(argv[0]);
    CHECK(mediapipe::run().ok());
    return 0;
}