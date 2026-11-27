#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;
int hmin = 0,hmax = 179,smin = 0,smax = 255,vmin = 0,vmax = 255;
void Colartracker()
{
    namedWindow("tracker");
    createTrackbar("hmin", "tracker", &hmin, 179);
    createTrackbar("hmax", "tracker", &hmax, 179);
    createTrackbar("smin", "tracker", &smin, 255);
    createTrackbar("smax", "tracker", &smax, 255);
    createTrackbar("vmin", "tracker", &vmin, 255);
    createTrackbar("vmax", "tracker", &vmax, 255);

}
void Morphology(Mat& mask)              
{
    Mat k3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(mask, mask, MORPH_CLOSE, k3);

}
void getContours(Mat &mask, Mat &img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(auto box_ : contours)
    {
         Rect box = boundingRect(box_);
	    rectangle(img,box,Scalar(100,120,46),4);
    }

}
   
int main()
{
    Mat imgOri,hsv,mask;
    imgOri = imread("/home/liu_xian/sample/assets/images/3.jpg");
    Rect roi(0, 300,
                 static_cast<int>(imgOri.cols),
                 static_cast<int>(imgOri.rows * 1/3));
    roi &= Rect(0, 0, imgOri.cols, imgOri.rows);
    Mat img = imgOri(roi).clone();
    cvtColor(img, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(0, 0, 223), Scalar(80, 255, 255), mask);
    Morphology(mask);
    getContours(mask,img);
    // imshow("mask",mask);
    // imshow("imgOri",imgOri);
    imwrite("task2.jpg",img);
    waitKey(0);
    // Colartracker();
    // while(true)
    // {   
    //     Scalar lower(hmin, smin, vmin);
    //     Scalar upper(hmax, smax, vmax);
    //     inRange(hsv, lower, upper, mask);
    //     imshow("img",img);
    //     imshow("mask",mask);
    //     int key = waitKeyEx(1);
    //     if(key == 27)
    //     {
    //         break;
    //     }
        
        
    // }
    destroyAllWindows();

    







} 