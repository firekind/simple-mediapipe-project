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
)

cc_binary(
    name = "simpletest",
    srcs = ["main.cc"],
    deps = [
        ":rgb_to_grayscale_calculator",
        "@mediapipe//mediapipe/calculators/core:pass_through_calculator",
        "@mediapipe//mediapipe/framework:calculator_framework",
        "@mediapipe//mediapipe/framework/port:logging",
        "@mediapipe//mediapipe/framework/port:parse_text_proto",
        "@mediapipe//mediapipe/framework/port:status",
    ],
)
