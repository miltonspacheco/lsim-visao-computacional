
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp> //include cvtColor 
#include <iostream>

using namespace cv;
using namespace std;

const int alpha_slider_max = 4;
int alpha_slider;
Mat src1, dst;

int main(void)
{
	src1 = imread(samples::findFile("apple2.png"));
	dst = imread(samples::findFile("apple2.png"));
	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }
	if (dst.empty()) { cout << "Error loading dst \n"; return -1; }

	///*
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			//get pixel
			Vec3b& color = src1.at<Vec3b>(y, x);

			//change color

			int GrayScale = (0.299 * color[2]) + (0.587 * color[1]) + (0.114 * color[0]);

			color[0] = GrayScale;
			color[1] = GrayScale;
			color[2] = GrayScale;

			//set pixel back
			src1.at<Vec3b>(Point(x, y)) = color;
		}
	}
	//*/
	//cvtColor(src1, dst, COLOR_BGR2GRAY);

	imshow("Grayscale", src1);
	imshow("Grayscale1", dst);

	waitKey(0);

	return 0;
}