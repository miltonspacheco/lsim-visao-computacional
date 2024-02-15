#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    string image_path = samples::findFile("matt.png");
    Mat img = imread(image_path, IMREAD_COLOR);
    
    for (int y = 0; y < img.rows; y++) 
    {
        for (int x = 0; x < img.cols; x++)
        {
            //get pixel
            Vec3b& color = img.at<Vec3b>(y, x);
            
            //change color
            if (color[0] > 150 && color[1] > 150 && color[2] > 150)
            {
                color[0] = 255;
                color[1] = 255;
                color[2] = 255;
            }
            else
            {
                color.val[0] = 0;
                color.val[1] = 0;
                color.val[2] = 0;
            }
            //set pixel back
            img.at<Vec3b>(Point(x,y)) = color;
        }
    }


    if (img.empty())
    {
        cout << "Could not read the image: " << image_path << endl;
        return 1;
    }
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    if (k == 's')
    {
        imwrite("matt.png", img);
    }
    return 0;
}


