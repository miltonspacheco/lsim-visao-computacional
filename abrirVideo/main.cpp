#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

int main( int argc, char ** argv ){
  cv::VideoCapture cap( "./sample.mp4" );
  cv::Mat img;

  while( true ){
    cap.read( img );
    cv::imshow("Minha Webcam", img);
    cv::waitKey( 20 );
  }

  return 0;
}
/

//g++ -I/usr/local/include/opencv4 -g main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio
