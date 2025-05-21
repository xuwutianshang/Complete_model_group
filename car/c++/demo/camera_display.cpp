

#include "core/uart_test.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <unistd.h>

std::shared_ptr<Driver> driver = nullptr;
void send_data(int a);


#define LEFTB1  10
#define RIGHB1  310
#define CENTER1 159   //中心点
#define WBVALUE 180   //对比度
#define JUMPDOT 6    //搜线跳点数 
void search_line(cv::Mat ccd_data);



bool flag_l1 = 0, flag_r1 = 0, loss_flag = 0, flag_l2 = 0, flag_r2 = 0;   //左右搜线标志位
int  leftp1 = 0, rightp1 = 319, leftp2 = 25, rightp2 = 100;         //左右搜线起始位    2022年5月6日15:20:51
int  searchr_up = 80, searchr_down = 239;                      //搜线半径         2022年5月6日15:20:42
int  roadwidth1, roadwidth2;                                 //赛道宽度
int CCD_location,temp;                                   //偏移量   

int Otsu(cv::Mat& src, cv::Mat& dst, int thresh) {
	const int Grayscale = 256;
	int graynum[Grayscale] = { 0 };
	int r = src.rows;
	int c = src.cols;
	for (int i = 0; i < r; ++i) {
		const uchar* ptr = src.ptr<uchar>(i);
		for (int j = 0; j < c; ++j) {        //直方图统计
			graynum[ptr[j]]++;
		}
	}

	double P[Grayscale] = { 0 };
	double PK[Grayscale] = { 0 };
	double MK[Grayscale] = { 0 };
	double srcpixnum = r * c, sumtmpPK = 0, sumtmpMK = 0;
	for (int i = 0; i < Grayscale; ++i) {
		P[i] = graynum[i] / srcpixnum;   //每个灰度级出现的概率
		PK[i] = sumtmpPK + P[i];         //概率累计和 
		sumtmpPK = PK[i];
		MK[i] = sumtmpMK + i * P[i];       //灰度级的累加均值                                                                                                                                                                                                                                                                                                                                                                                                        
		sumtmpMK = MK[i];
	}

	//计算类间方差
	double Var = 0;
	for (int k = 0; k < Grayscale; ++k) {
		if ((MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k])) > Var) {
			Var = (MK[Grayscale - 1] * PK[k] - MK[k]) * (MK[Grayscale - 1] * PK[k] - MK[k]) / (PK[k] * (1 - PK[k]));
			thresh = k;
		}
	}

	//阈值处理
	src.copyTo(dst);
	for (int i = 0; i < r; ++i) {
		uchar* ptr = dst.ptr<uchar>(i);
		for (int j = 0; j < c; ++j) {
			if (ptr[j] > thresh)
				ptr[j] = 255;
			else
				ptr[j] = 0;
		}
	}
	return thresh;
}


class VideoCaptureMT {
public:
	VideoCaptureMT(int index, int height = 240, int width = 320);
	VideoCaptureMT(std::string filePath, int height = 240, int width = 320);
	~VideoCaptureMT();

	bool isOpened() {
		return m_IsOpen;
	}
	void release() {
		m_IsOpen = false;
	}
	bool read(cv::Mat& frame);

private:
	void captureInit(int index, std::string filePath, int height, int width);
	void captureFrame();

	cv::VideoCapture* m_pCapture;
	cv::Mat* m_pFrame;
	std::mutex* m_pMutex;
	std::thread* m_pThread;
	std::atomic_bool m_IsOpen;
};

VideoCaptureMT::VideoCaptureMT(int index, int height, int width)
{
	captureInit(index, std::string(), height, width);
}

VideoCaptureMT::VideoCaptureMT(std::string filePath, int height, int width)
{
	captureInit(0, filePath, height, width);
}

VideoCaptureMT::~VideoCaptureMT()
{
	m_IsOpen = false;
	m_pThread->join();
	if (m_pCapture->isOpened()) {
		m_pCapture->release();
	}

	delete m_pThread;
	delete m_pMutex;
	delete m_pCapture;
	delete m_pFrame;
}

void VideoCaptureMT::captureInit(int index, std::string filePath, int height, int width)
{
	if (!filePath.empty()) {
		m_pCapture = new cv::VideoCapture(filePath);
	}
	else {
		m_pCapture = new cv::VideoCapture(index);
	}
	m_pCapture->set(cv::CAP_PROP_FRAME_WIDTH, width);
	m_pCapture->set(cv::CAP_PROP_FRAME_HEIGHT, height);
	m_pCapture->set(cv::CAP_PROP_FPS, 30);

	m_IsOpen = true;
	m_pFrame = new cv::Mat(height, width, CV_8UC3);
	m_pMutex = new std::mutex();
	m_pThread = new std::thread(&VideoCaptureMT::captureFrame, this);
}

void VideoCaptureMT::captureFrame()
{
	cv::Mat frameBuff;
	while (m_IsOpen) {
		(*m_pCapture) >> frameBuff;
		if (m_pMutex->try_lock()) {
			frameBuff.copyTo(*m_pFrame);
			m_pMutex->unlock();
		}
		cv::waitKey(5);
	}
}

bool VideoCaptureMT::read(cv::Mat& frame)
{
	if (m_pFrame->empty()) {
		m_IsOpen = false;
	}
	else {
		m_pMutex->lock();
		m_pFrame->copyTo(frame);
		m_pMutex->unlock();
	}
	return m_IsOpen;
}

int main(int argc, char* argv[])
{
	VideoCaptureMT capture(0);
	//send_data(00);
	cv::Mat frame, gray,edges;
	while (capture.isOpened()) {
		if (!capture.read(frame)) {
			break;
		}
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
		//send_data(33);
		/*cv::blur(gray, gray, cv::Size(3, 3));
		cv::Canny(gray, gray, 5, 38, 3);*/
		//cv::waitKey(100);
		int thresh = 0;
		double t2 = (double)cv::getTickCount();
		thresh = Otsu(gray, edges, thresh);
		//send_data(11);
		t2 = (double)cv::getTickCount() - t2;
		double  Otsu = 0;
		search_line(edges);
		//send_data(22);
		//cv::imshow("image", edges);
		cv::waitKey(1);


	}
	capture.release();
	return 0;
}


void search_line(cv::Mat ccd_data)
{
	uchar* curr_row = ccd_data.ptr<uchar>(190);
	int i, endp, t;
	int left_start, left_end;
	int right_start, right_end;

	//确定搜索区域

	left_start = leftp1 + searchr_up;
	if (left_start > RIGHB1) left_start = RIGHB1;
	left_end = leftp1 - searchr_up;
	if (left_end < LEFTB1) left_end = LEFTB1;

	right_start = rightp1 - searchr_up;
	if (right_start < LEFTB1) right_start = LEFTB1;
	right_end = rightp1 + searchr_up;
	if (right_end > RIGHB1) right_end = RIGHB1;


	//验证搜索区域合法性
	if (left_start > right_start)
	{
		t = (left_start + right_start) / 2;
		left_start = t - 1;
		right_start = t + 1;
	}

	//搜线 
	flag_l1 = 0;


	for (i = left_start;i >= left_end;i--)
	{
		endp = i - JUMPDOT;
		if (endp < LEFTB1)    endp = LEFTB1;   //边界保护 
		if (curr_row[i] > curr_row[endp] && ((curr_row[i] - curr_row[endp]) / (curr_row[i] + curr_row[endp])) * 200 > WBVALUE)
		{
			leftp1 = endp;
			flag_l1 = 1;
			break;
		}
	}

	flag_r1 = 0;
	for (i = right_start;i <= right_end;i++)
	{
		endp = i + JUMPDOT;
		if (endp > RIGHB1)    endp = RIGHB1;   //边界保护  
		if (curr_row[i] > curr_row[endp] && ((curr_row[i] - curr_row[endp]) / (curr_row[i] + curr_row[endp])) * 200 > WBVALUE)
		{
			flag_r1 = 1;
			rightp1 = endp;
			break;
		}

	}

	roadwidth1 = (rightp1 - leftp1);
	//计算坐标   
	if (flag_l1 || flag_r1)
	{
		CCD_location = ((rightp1 + leftp1) / 2 - CENTER1);
		if (CCD_location > 80)  CCD_location =80;
		if (CCD_location < -80)  CCD_location = -80;

          temp =    (CCD_location/2)+40;
          
		if (temp > 80)  temp =80;
		if (temp < 0)  temp = 0;
	}
	

	/*
	   if (flag_l1 == 0 && flag_r1 == 0)  //十字或者或者坡道
	   {
		   searchr_up = 35;
		   loss_flag = 1;
	   }
	   else searchr_up = 15;

	   if (loss_flag == 1 && flag_l1 == 1 && flag_r1 == 1)
	   {
		   loss_flag = 0;
	   }
	   //   if(CCD() && time1 <= 2 && start_car)  CCD_location = 0;
	  //   if( rightp1 >= 100 && leftp1 <= 25 && !loss_flag && time1 >=1 ) //time1
	  //      Hill_flag = 1;

   *///for(i=0;i<15;i++)
	    send_data(temp);
	  

}


void send_data(int a) {
    //预留串口的设备名为/dev/ttyPS1
    driver = std::make_shared<Driver>("/dev/ttyUSB0", BaudRate::BAUD_115200);
   
    //串口初始化，打开串口设备及配置串口数据格式
    int ret = driver->open();
   

    
            driver->senddata(a);
         


}
