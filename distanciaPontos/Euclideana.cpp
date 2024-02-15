
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp> //include cvtColor 
#include <iostream>

using namespace cv;
using namespace std;

const int alpha_slider_max = 4;
int alpha_slider, bPref, gPref, rPref;
Mat src1, dst;

int main(void)
{
	src1 = imread(samples::findFile("estrela.jpg"));
	dst = imread(samples::findFile("estrela.jpg"));
	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }
	if (dst.empty()) { cout << "Error loading dst \n"; return -1; }

	///*
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			//get pixel
			Vec3b& color = src1.at<Vec3b>(y, x);
			Vec3b& color2 = dst.at<Vec3b>(120, 240);

			//change color

			int d = sqrt(((color[2] - color2[2]) * (color[2] - color2[2])) + ((color[1] - color2[1]) * (color[1] - color2[1])) + ((color[0] - color2[0]) * (color[0] - color2[0])));

			color[0] = d;
			color[1] = d;
			color[2] = d;

			//set pixel back
			src1.at<Vec3b>(Point(x, y)) = color;
		}
	}
	imshow("Euclidiana", src1);
	imshow("EuclidianaOriginal", dst);

	waitKey(0);

	return 0;
}