load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "rgb_to_grayscale_calculator",
    srcs = ["src/rgb_to_grayscale_calculator.cc"],
    hdrs = ["include/rgb_to_grayscale_calculator.h"],
    deps = [
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:opencv_imgproc",
    ],
    alwayslink = True
)

cc_binary(
    name = "simpleapp",
    srcs = ["main.cc"],
    deps = [
        ":rgb_to_grayscale_calculator",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/formats:image_frame",
        "@mediapipe//mediapipe/framework/formats:image_frame_opencv",
        "@mediapipe//mediapipe/framework/port:logging",
        "@mediapipe//mediapipe/framework/port:opencv_highgui",
        "@mediapipe//mediapipe/framework/port:opencv_video",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
    ],
)
