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
void opencv_avi::background_segmentation()//�I���۴�
{
	Mat test;
	//(a-b)+(b-a)
	subtract(default_image, continuous_image, sub_image_l);
	subtract(continuous_image, default_image, sub_image_r);
	add(sub_image_l, sub_image_r, result);
	//absdiff(im0, im1, result);

	//�N���G�ন�Ƕ�
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//�G�Ȥ�
	threshold(gray, bin, 30, 255, THRESH_BINARY);
	dilate(bin, bin, Mat());//����
	//�]�m��P�¥ճq�D�Ƥ��P�A�ҥH�ݦA��^�m��A��X���G�~�|���T
	cvtColor(bin, color, COLOR_GRAY2BGR);
	bitwise_and(continuous_image, color, and_pic);
}
void opencv_avi::adjacent_segmentation()//�۾F�۴�
{
	//(a-b)+(b-a)
	subtract(image, continuous_image, sub_image_l);
	subtract(continuous_image, image, sub_image_r);
	add(sub_image_l, sub_image_r, result);
	//absdiff(image, im1, result);

	//�N���G�ন�Ƕ�
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//�G�Ȥ�
	threshold(gray, bin, 30, 255, THRESH_BINARY);
	dilate(bin, bin, Mat());//����
	//�]�m��P�¥ճq�D�Ƥ��P�A�ҥH�ݦA��^�m��A��X���G�~�|���T
	cvtColor(bin, color, COLOR_GRAY2BGR);
	bitwise_and(continuous_image, color, and_pic);
}
void opencv_avi::light_flow_segmentation()//���y�k
{
	//(a-b)+(b-a)
	subtract(image, continuous_image, sub_image_l);
	subtract(continuous_image, image, sub_image_r);
	add(sub_image_l, sub_image_r, result);

	//�N���G�ন�Ƕ�
	cvtColor(result, gray, COLOR_BGR2GRAY);

	//�G�Ȥ�
	//threshold(gray, bin, 30, 255, THRESH_BINARY);
	//dilate(bin, bin, Mat());//����
	//�]�m��P�¥ճq�D�Ƥ��P�A�ҥH�ݦA��^�m��A��X���G�~�|���T
	cvtColor(gray, color, COLOR_GRAY2BGR);

	//���N�v����Ƕ��A��K����B��
	//cvtColor(image, gray, CV_BGR2GRAY);

	//�N��v���ƻs��color(output)����X
	image.copyTo(color);
	//color.setTo(Scalar::all(0));

	//�K�[�S�x�I
	if (addPoint())
	{
		//�S�x�I����
		goodFeaturesToTrack(gray, feat, maxcount, qlevel, mindist);
		points[0].insert(points[0].end(), feat.begin(), feat.end());
		init.insert(init.end(), feat.begin(), feat.end());
	}
	//�]���@�}�l�e�����šA�]�����N�U�@�i���ƻs��Ĥ@�i�A�~���|�o�Ϳ��~
	if (gray_pre.empty())
	{
		gray.copyTo(gray_pre);
	}

	//L-K���y�k(���r��)�B�ʤ�V���p
	calcOpticalFlowPyrLK(gray_pre, gray, points[0], points[1], status, err);

	//�h�����n���S�x�I
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

	// ��ܯS�x�I�P�B�ʭy��
	/*for (int i = 0; i<points[1].size(); i++)
	{
		line(color, init[i], points[1][i], Scalar(255, 255, 255), 2);
		circle(color, points[1][i], 2, Scalar(203, 112, 255), -1);//-1=��߶�
	}*/

	// ���e���ܵ��G�����U�@��Ѧ�
	swap(points[1], points[0]);
	swap(gray_pre, gray);
}
bool opencv_avi::addPoint()
{
	return points[0].size() <= 10;//�S�x�I�p�󵥩�10
}
bool opencv_avi::TrackedPoint(int i)
{
	//abs=�����m
	return status[i] &&
		(abs(points[0][i].x - points[1][i].x) +
			abs(points[0][i].y - points[1][i].y) > 1.5);
}