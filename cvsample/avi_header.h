#pragma once
#include <atlstr.h>
#include<opencv2\opencv.hpp>
#include <Windows.h>
#include <iostream>
#include <stdio.h>

using namespace System;
using namespace System::Drawing;
using namespace System::Runtime::InteropServices;
using namespace cv;
using namespace std;


class opencv_avi {
public:
	opencv_avi();
	~opencv_avi();
	void OpenFile(char* filename);
	bool Play();
	System::Drawing::Bitmap ^ opencv_avi::Mattobmp(Mat &image);
	Mat getmatImg();//access Image(回傳連續畫面)
	Mat getResult();
	Mat getmatBg();//access Image(回傳第一張畫面)

	void background_segmentation();
	void adjacent_segmentation();
	void light_flow_segmentation();

	bool addPoint();
	bool TrackedPoint(int i);

	vector<Point2f> points[2];//前後兩幅特徵點
	vector<Point2f> init;//初始特徵
	vector<Point2f> feat;//檢測到的特徵
	vector<uchar> status;//特徵點被成功跟踪的標誌
	vector<float> err;//跟踪時的特徵點小區域誤差和

	int maxcount = 500;
	double qlevel = 0.01;
	double mindist = 10.0;

	void GetFrame(int i);
	LONG GetFrameNum();
	LONG GetCurrentFrameNum();

	Mat continuous_image, sub_image_l, sub_image_r, result, gray, bin, color;
	Mat and_pic, gray_pre;

private:
	VideoCapture cap;
	Mat image, default_image;
};