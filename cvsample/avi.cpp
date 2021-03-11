#include "avi_header.h"

using namespace cv;

opencv_avi::opencv_avi() {}
opencv_avi::~opencv_avi() {}

void opencv_avi::OpenFile(char* filename) {
	cap.open(filename);
	cap >> default_image;
}

bool opencv_avi::Play() {
	cap >> image;
	cap >> continuous_image;
	if (continuous_image.empty()) {
		return false;
	}
	return true;
}

System::Drawing::Bitmap ^ opencv_avi::Mattobmp(Mat &image)
{
	return gcnew System::Drawing::Bitmap(
		image.cols,
		image.rows,
		image.step1(),
		System::Drawing::Imaging::PixelFormat::Format24bppRgb,
		(System::IntPtr)image.ptr());
}


Mat opencv_avi::getmatImg()
{
	return image;
}
Mat opencv_avi::getResult()
{
	return color;
}

Mat opencv_avi::getmatBg(){
	return default_image;
}
void opencv_avi::background_segmentation()//背景相減
{
	Mat test;
	//(a-b)+(b-a)
	subtract(default_image, continuous_image, sub_image_l);
	subtract(continuous_image, default_image, sub_image_r);
	add(sub_image_l, sub_image_r, result);
	//absdiff(im0, im1, result);

	//將結果轉成灰階
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//二值化
	threshold(gray, bin, 30, 255, THRESH_BINARY);
	dilate(bin, bin, Mat());//膨脹
	//因彩色與黑白通道數不同，所以需再轉回彩色，輸出結果才會正確
	cvtColor(bin, color, COLOR_GRAY2BGR);
	bitwise_and(continuous_image, color, and_pic);
}
void opencv_avi::adjacent_segmentation()//相鄰相減
{
	//(a-b)+(b-a)
	subtract(image, continuous_image, sub_image_l);
	subtract(continuous_image, image, sub_image_r);
	add(sub_image_l, sub_image_r, result);
	//absdiff(image, im1, result);

	//將結果轉成灰階
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//二值化
	threshold(gray, bin, 30, 255, THRESH_BINARY);
	dilate(bin, bin, Mat());//膨脹
	//因彩色與黑白通道數不同，所以需再轉回彩色，輸出結果才會正確
	cvtColor(bin, color, COLOR_GRAY2BGR);
	bitwise_and(continuous_image, color, and_pic);
}
void opencv_avi::light_flow_segmentation()//光流法
{
	//(a-b)+(b-a)
	subtract(image, continuous_image, sub_image_l);
	subtract(continuous_image, image, sub_image_r);
	add(sub_image_l, sub_image_r, result);

	//將結果轉成灰階
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//二值化
	//threshold(gray, bin, 30, 255, THRESH_BINARY);
	//dilate(bin, bin, Mat());//膨脹
	//因彩色與黑白通道數不同，所以需再轉回彩色，輸出結果才會正確
	cvtColor(gray, color, COLOR_GRAY2BGR);

	//先將影像轉灰階，方便後續運算
	//cvtColor(image, gray, CV_BGR2GRAY);

	//將原影像複製到color(output)做輸出
	image.copyTo(color);
	//color.setTo(Scalar::all(0));

	//添加特徵點
	if (addPoint())
	{
		//特徵點偵測
		goodFeaturesToTrack(gray, feat, maxcount, qlevel, mindist);
		points[0].insert(points[0].end(), feat.begin(), feat.end());
		init.insert(init.end(), feat.begin(), feat.end());
	}
	//因為一開始畫面為空，因此須將下一張先複製到第一張，才不會發生錯誤
	if (gray_pre.empty())
	{
		gray.copyTo(gray_pre);
	}

	//L-K光流法(金字塔)運動方向估計
	calcOpticalFlowPyrLK(gray_pre, gray, points[0], points[1], status, err);

	//去掉不好的特徵點
	int k = 0;
	for (int i = 0; i < points[1].size(); i++)
	{
		if (TrackedPoint(i))
		{
			init[k] = init[i];
			points[1][k++] = points[1][i];
			line(color, points[0][i], points[1][i], Scalar(255, 255, 255), 2);
		}
	}
	points[1].resize(k);
	init.resize(k);

	// 顯示特徵點與運動軌跡
	/*for (int i = 0; i<points[1].size(); i++)
	{
		line(color, init[i], points[1][i], Scalar(255, 255, 255), 2);
		circle(color, points[1][i], 2, Scalar(203, 112, 255), -1);//-1=實心圓
	}*/

	// 把當前跟蹤結果做為下一批參考
	swap(points[1], points[0]);
	swap(gray_pre, gray);
}
bool opencv_avi::addPoint()
{
	return points[0].size() <= 10;//特徵點小於等於10
}
bool opencv_avi::TrackedPoint(int i)
{
	//abs=絕對位置
	return status[i] &&
		(abs(points[0][i].x - points[1][i].x) +
			abs(points[0][i].y - points[1][i].y) > 1.5);
}