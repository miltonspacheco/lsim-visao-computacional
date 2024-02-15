
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using std::cout;

const int alpha_slider_max = 255;
const int type_max = 4;
int alpha_slider, type_value;
Mat src1, dst;


void ConvertToGray()
{
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			//get pixel
			Vec3b& color = src1.at<Vec3b>(y, x);
			Vec3b& color2 = dst.at<Vec3b>(y, x);

			//change color

			int GrayScale = (0.299 * color[2]) + (0.587 * color[1]) + (0.114 * color[0]);
			color[0] = GrayScale;
			color[1] = GrayScale;
			color[2] = GrayScale;
			color2[0] = GrayScale;
			color2[1] = GrayScale;
			color2[2] = GrayScale;

			//set pixel back
			src1.at<Vec3b>(Point(x, y)) = color;
			dst.at<Vec3b>(Point(x, y)) = color2;
		}
	}
}

static void on_trackbar(int, void*)
{
	if (type_value == 0) //Threshold Binary
	{
		for (int y = 0; y < src1.rows; y++)
		{
			for (int x = 0; x < src1.cols; x++)
			{
				//get pixel
				Vec3b& color = src1.at<Vec3b>(y, x);
				Vec3b& color2 = dst.at<Vec3b>(y, x);

				color2[0] = color[0];
				color2[1] = color[1];
				color2[2] = color[2];

				//change color
				if (color[0] >= alpha_slider)
				{
					color2[0] = 255;
					color2[1] = 255;
					color2[2] = 255;
				}
				if (color[0] <= alpha_slider)
				{
					color2[0] = 0;
					color2[1] = 0;
					color2[2] = 0;
				}

				//set pixel back
				src1.at<Vec3b>(Point(x, y)) = color;
				dst.at<Vec3b>(Point(x, y)) = color2;
			}
		}
		imshow("Thresholding multibanda", dst);
		//break;
	}
	if (type_value == 1) //Threshold Binary, Inverted
	{
		for (int y = 0; y < src1.rows; y++)
		{
			for (int x = 0; x < src1.cols; x++)
			{
				//get pixel
				Vec3b& color = src1.at<Vec3b>(y, x);
				Vec3b& color2 = dst.at<Vec3b>(y, x);

				color2[0] = color[0];
				color2[1] = color[1];
				color2[2] = color[2];

				//change color
				if (color[0] >= alpha_slider)
				{
					color2[0] = 0;
					color2[1] = 0;
					color2[2] = 0;
				}
				if (color[0] <= alpha_slider)
				{
					color2[0] = 255;
					color2[1] = 255;
					color2[2] = 255;
				}
				//set pixel back
				src1.at<Vec3b>(Point(x, y)) = color;
				dst.at<Vec3b>(Point(x, y)) = color2;
			}
		}
		imshow("Thresholding multibanda", dst);	
	}
	if (type_value == 2) //Truncate
	{
		for (int y = 0; y < src1.rows; y++)
		{
			for (int x = 0; x < src1.cols; x++)
			{
				//get pixel
				Vec3b& color = src1.at<Vec3b>(y, x);
				Vec3b& color2 = dst.at<Vec3b>(y, x);

				color2[0] = color[0];
				color2[1] = color[1];
				color2[2] = color[2];

				//change color
				if (color[0] > alpha_slider)
				{
					color2[0] = alpha_slider;
					color2[1] = alpha_slider;
					color2[2] = alpha_slider;
				}

				//set pixel back
				src1.at<Vec3b>(Point(x, y)) = color;
				dst.at<Vec3b>(Point(x, y)) = color2;
			}
		}
		imshow("Thresholding multibanda", dst);
	}
	if (type_value == 3) //Threshold to Zero
	{
		for (int y = 0; y < src1.rows; y++)
		{
			for (int x = 0; x < src1.cols; x++)
			{
				//get pixel
				Vec3b& color = src1.at<Vec3b>(y, x);
				Vec3b& color2 = dst.at<Vec3b>(y, x);

				color2[0] = color[0];
				color2[1] = color[1];
				color2[2] = color[2];

				//change color
				if (color[0] < alpha_slider)
				{
					color2[0] = 0;
					color2[1] = 0;
					color2[2] = 0;
				}

				//set pixel back
				src1.at<Vec3b>(Point(x, y)) = color;
				dst.at<Vec3b>(Point(x, y)) = color2;
			}
		}
		imshow("Thresholding multibanda", dst);
	}
	if (type_value == 4) //Threshold to Zero Inverted
	{
		for (int y = 0; y < src1.rows; y++)
		{
			for (int x = 0; x < src1.cols; x++)
			{
				//get pixel
				Vec3b& color = src1.at<Vec3b>(y, x);
				Vec3b& color2 = dst.at<Vec3b>(y, x);

				color2[0] = color[0];
				color2[1] = color[1];
				color2[2] = color[2];

				//change color
				if (color[0] > alpha_slider)
				{
					color2[0] = 0;
					color2[1] = 0;
					color2[2] = 0;
				}

				//set pixel back
				src1.at<Vec3b>(Point(x, y)) = color;
				dst.at<Vec3b>(Point(x, y)) = color2;
			}
		}
		imshow("Thresholding multibanda", dst);
	}
}

int main(void)
{
	src1 = imread(samples::findFile("apple2.png"));
	dst = imread(samples::findFile("apple2.png"));

	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }
	if (dst.empty()) { cout << "Error loading dst \n"; return -1; }

	ConvertToGray();

	namedWindow("Thresholding multibanda", WINDOW_AUTOSIZE); // Create Window

	//create trackbars
	char TrackbarName[50];
	snprintf(TrackbarName, sizeof(TrackbarName), "Value x %d", alpha_slider_max);
	createTrackbar(TrackbarName, "Thresholding multibanda", &alpha_slider, alpha_slider_max, on_trackbar);

	char TrackbarName1[50];
	snprintf(TrackbarName1, sizeof(TrackbarName1), "Type x %d", type_max);
	createTrackbar(TrackbarName1, "Thresholding multibanda", &type_value, type_max, on_trackbar);


	on_trackbar(0, 0);

	waitKey(0);

	return 0;
}