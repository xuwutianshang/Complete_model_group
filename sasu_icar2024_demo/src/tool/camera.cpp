#include "../include/common.hpp"
#include <atomic>             // 原子操作支持
#include <fstream>            // 文件操作类
#include <iostream>           // 输入输出类
#include <opencv2/opencv.hpp> // OpenCV终端部署
#include <thread>             // 多线程支持

using namespace std;
using namespace cv;

#define COLS_IMG 640 // 摄像头：图像的列数
#define ROWS_IMG 480 // 摄像头：图像的行数

// 全局变量，用于线程间通信
atomic<bool> running(true);
Mat frame;
Mat gridOverlay;

void captureThread(VideoCapture &capture) {
  while (running) {
    capture.read(frame);
    if (frame.empty()) {
      cout << "no video frame" << endl;
      continue;
    }
  }
}

void drawGrid(Mat &img) {
  uint16_t rows = ROWS_IMG / 30; // 8
  uint16_t cols = COLS_IMG / 32; // 10

  for (size_t i = 1; i < rows; i++) // 使用for循环绘制行线
  {
    line(img, Point(0, 30 * i), Point(img.cols - 1, 30 * i),
         Scalar(211, 211, 211), 1);
  }
  for (size_t i = 1; i < cols; i++) // 使用for循环绘制列线
  {
    if (i == (int)(cols / 2))
      line(img, Point(32 * i, 0), Point(32 * i, img.rows - 1),
           Scalar(0, 0, 255), 2);
    else
      line(img, Point(32 * i, 0), Point(32 * i, img.rows - 1),
           Scalar(211, 211, 211), 1);
  }
}

int main(int argc, char const *argv[]) {
  // 打开摄像头
  VideoCapture capture("/dev/video0", CAP_V4L2);
  if (!capture.isOpened()) {
    cout << "can not open video device " << endl;
    return 1;
  }

  capture.set(CAP_PROP_FRAME_WIDTH, COLS_IMG);  // 设置图像的列数
  capture.set(CAP_PROP_FRAME_HEIGHT, ROWS_IMG); // 设置图像的行数

  double rate = capture.get(CAP_PROP_FPS);            // 读取图像的帧率
  double width = capture.get(CAP_PROP_FRAME_WIDTH);   // 读取图像的宽度
  double height = capture.get(CAP_PROP_FRAME_HEIGHT); // 读取图像的高度
  cout << "Camera Param: frame rate = " << rate << " width = " << width
       << " height = " << height << endl;

  // 创建田字格图像
  gridOverlay = Mat::zeros(ROWS_IMG, COLS_IMG, CV_8UC3);
  drawGrid(gridOverlay);

  // 启动捕捉线程
  thread capThread(captureThread, ref(capture));

  while (running) {
    if (!frame.empty()) {
      Mat displayFrame = frame.clone();
      addWeighted(displayFrame, 1.0, gridOverlay, 1.0, 0.0, displayFrame);
      imshow("img", displayFrame);
      if (waitKey(1) == 27) // 按下ESC键退出
      {
        running = false;
        break;
      }
    }
  }

  capThread.join();
  capture.release();
  destroyAllWindows();

  return 0;
}
