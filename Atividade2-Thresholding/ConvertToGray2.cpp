
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using std::cout;

const int alpha_slider_max = 4;
int alpha_slider;
Mat src1, dst;


static void on_trackbar(int, void*)
{
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
	imshow("Grayscale", src1);
}

int main(void)
{
	src1 = imread(samples::findFile("apple2.png"));

	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }

	namedWindow("Grayscale", WINDOW_AUTOSIZE); // Create Window

	//create trackbars
	char TrackbarName[50];
	snprintf(TrackbarName, sizeof(TrackbarName), "X x %d", alpha_slider_max);
	createTrackbar(TrackbarName, "Grayscale", &alpha_slider, alpha_slider_max, on_trackbar);

	on_trackbar(alpha_slider, 0);

	waitKey(0);

	return 0;
}