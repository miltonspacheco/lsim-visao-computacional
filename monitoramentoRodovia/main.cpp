#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{
    //system parameters
    unsigned int frame_size = 20; //creating frame_size (how many images to average background)
    unsigned int frame_sampling = 10; //frame_sampling (time interval do use a frame into bgs model)
    unsigned int bgs_thres = 40; //thresholding, for the binary image


    //open video 
    VideoCapture cap("videoBom.AVI");
   // VideoCapture cap("floripa.mp4");


    if (!cap.isOpened()) return -1;

    namedWindow("frame", WINDOW_KEEPRATIO);
    resizeWindow("frame", 640, 360);

    namedWindow("blur", WINDOW_KEEPRATIO);
    resizeWindow("blur", 640, 360);

    namedWindow("final", WINDOW_KEEPRATIO);
    resizeWindow("final", 640, 360);

    vector< Mat > bgsmodels;

    while (true)
    {
        //capturing camera
        Mat frame;
        cap >> frame;

        //pushing back bgs model buffer
        static unsigned int sampling = 0;
        if (sampling++ >= frame_sampling)
        {
            bgsmodels.push_back(frame);
            sampling = 0;
        }

        //buffer has to have at least one frame to start
        if (bgsmodels.size() == 0) continue;

        //buffer is full, we have to elliminate the oldest frame
        if (bgsmodels.size() > frame_size)
            bgsmodels.erase(bgsmodels.begin());

        //computing an averaged image from the buffer
        Mat avgbgs = frame.clone();
        for (unsigned int i = 0; i < frame.rows; i++)
        {
            for (unsigned int j = 0; j < frame.cols; j++)
            {
                float meanr, meang, meanb; meanr = meang = meanb = 0;
                for (unsigned int k = 0; k < bgsmodels.size(); k++)
                {
                    meanr += bgsmodels.at(k).at<Vec3b>(i, j)[2];
                    meang += bgsmodels.at(k).at<Vec3b>(i, j)[1];
                    meanb += bgsmodels.at(k).at<Vec3b>(i, j)[0];
                }
                meanr /= bgsmodels.size();
                meang /= bgsmodels.size();
                meanb /= bgsmodels.size();

                avgbgs.at<Vec3b>(i, j)[2] = meanr;
                avgbgs.at<Vec3b>(i, j)[1] = meang;
                avgbgs.at<Vec3b>(i, j)[0] = meanb;
            }
        }

        //here we do the subtraction between the current frame, and the BGS Model
        Mat subtraction = abs(frame - avgbgs);
        cvtColor(subtraction, subtraction, cv::COLOR_BGR2GRAY);
        threshold(subtraction, subtraction, bgs_thres, 255, 0);

            //Filters
            Mat blur_img;
            medianBlur(subtraction, blur_img, 21);
        /*

            //Filling Holes
            Mat final_0 = subtraction.clone();
            floodFill(final_0, cv::Point(0,0), cv::Scalar(255));

            Mat final_1;
            bitwise_not(final_0 ,final_1);

            Mat final_2 = (subtraction | final_1);
        */

        //Find contours
        vector<vector<Point>> contours_vector;

        findContours(blur_img, contours_vector, RETR_TREE, CHAIN_APPROX_NONE);

        Mat contourImage(blur_img.size(), CV_8UC1, Scalar(0));
        for (unsigned short contour_index = 0; contour_index < contours_vector.size(); contour_index++) {
            drawContours(contourImage, contours_vector, contour_index, Scalar(255), -1);
        }

        /*
        //Draw contours
        Mat frame_copy = frame.clone();
        drawContours(frame_copy, blur_img, -1, Scalar(0, 255, 0), 2);
        */
        
         
        //display results
        imshow("frame", frame);
        imshow("final", blur_img);
        imshow("blur", contourImage);

        if (waitKey(10) >= 0) break;
    }

    return 0;
}