
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using std::cout;

const int alpha_slider_max = 255;
int alpha_slider;
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
	
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			//get pixel
			Vec3b& color = src1.at<Vec3b>(y, x);
			Vec3b& color2 = dst.at<Vec3b>(y, x);

			color[0] = color2[0];
			color[1] = color2[1];
			color[2] = color2[2];

			//change color
			if (color[0] >= alpha_slider)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;
			}
			if (color[0] <= alpha_slider)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 0;
			}
			

			//set pixel back
			src1.at<Vec3b>(Point(x, y)) = color;
			dst.at<Vec3b>(Point(x, y)) = color2;
			
		}
	}
	imshow("Grayscale", src1);
}

int main(void)
{
	src1 = imread(samples::findFile("apple2.png"));
	dst = imread(samples::findFile("apple2.png"));

	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }
	if (dst.empty()) { cout << "Error loading dst \n"; return -1; }

	ConvertToGray();

	namedWindow("Grayscale", WINDOW_AUTOSIZE); // Create Window

	//create trackbars
	char TrackbarName[50];
	snprintf(TrackbarName, sizeof(TrackbarName), "X x %d", alpha_slider_max);
	createTrackbar(TrackbarName, "Grayscale", &alpha_slider, alpha_slider_max, on_trackbar);

	on_trackbar(0, 0);

	waitKey(0);

	return 0;
}