# Simple Mediapipe Project

This project is a simple mediapipe project that converts the RGB input from the webcam into grayscale and displays it. This project uses mediapipe as an external dependency.

## Requirements
- This project was developed to work on Manjaro. For other distros, edit the `srcs`, `hdrs` and `includes` in [`opencv_linux.BUILD`](./third_party/opencv_linux.BUILD) to point to the correct locations.

- bazel version: `3.6.0`

## Build and Run
To build the application, run

```
$ bazel build simpleapp:simpleapp
```

and to run the application,

```
$ ./bazel-bin/simpleapp/simpleapp
```

To build and run the application,
```
$ bazel run simpleapp:simpleapp
```