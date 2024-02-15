
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
using std::cout;

const int alpha_slider_max = 255;
int alpha_sliderB;
int alpha_sliderG;
int alpha_sliderR;
int b, g, r = 0;
Mat src1, src2;


static void on_trackbar(int, void*)
{
	
	for (int y = 0; y < src1.rows; y++)
	{
		for (int x = 0; x < src1.cols; x++)
		{
			//get pixel
			Vec3b& color = src1.at<Vec3b>(y, x);
			Vec3b& color2 = src2.at<Vec3b>(y, x);
			
			//change color
			
			color[0] = color2[0];
			color[1] = color2[1];
			color[2] = color2[2];

			if (alpha_sliderB > color[0]){
				color[0] = alpha_sliderB;
			}
			
			if (alpha_sliderG > color[1]){
				color[1] = alpha_sliderG;
			}
			
			if (alpha_sliderR > color[2]){
				color[2] = alpha_sliderR;
			}
			
			//set pixel back
			src1.at<Vec3b>(Point(x, y)) = color;
			src2.at<Vec3b>(Point(x, y)) = color2;

		}
	}
	imshow("RGB", src1);
}

int main(void)
{

	alpha_sliderB, alpha_sliderG, alpha_sliderR = 0;

	src1 = imread(samples::findFile("green.jpg"));
	src2 = src1.clone();

	if (src1.empty()) { cout << "Error loading src1 \n"; return -1; }
	if (src2.empty()) { cout << "Error loading src1 \n"; return -1; }

	namedWindow("RGB", WINDOW_AUTOSIZE); // Create Window

	//create trackbars
	char TrackbarName[50];
	snprintf(TrackbarName, sizeof(TrackbarName), "B x %d", alpha_slider_max);
	createTrackbar(TrackbarName, "RGB", &alpha_sliderB, alpha_slider_max, on_trackbar);

	char TrackbarName1[50];
	snprintf(TrackbarName1, sizeof(TrackbarName1), "G x %d", alpha_slider_max);
	createTrackbar(TrackbarName1, "RGB", &alpha_sliderG, alpha_slider_max, on_trackbar);

	char TrackbarName2[50];
	snprintf(TrackbarName2, sizeof(TrackbarName2), "R x %d", alpha_slider_max);
	createTrackbar(TrackbarName2, "RGB", &alpha_sliderR, alpha_slider_max, on_trackbar);

	on_trackbar(0, 0);

	waitKey(0);

	return 0;
}