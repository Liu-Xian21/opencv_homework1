
#include <opencv2/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>
using namespace std;
using namespace cv;
void Morphology(Mat& mask)              
{
    Mat k5 = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(mask, mask, MORPH_CLOSE, k5);

}
void getContours_yellow(Mat &imgdil, Mat &img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgdil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(const auto &box_ : contours)
    {
        //  Rect box = boundingRect(box_);
	    // rectangle(img,box,Scalar(0, 255, 255),1);
        RotatedRect rect = minAreaRect(box_);
        Point2f boxPoints[4];
        rect.points(boxPoints);
        vector<Point>box;
        for(int i = 0;i<4;i++)
        {
            box.push_back(Point(static_cast<int>(boxPoints[i].x),static_cast<int>(boxPoints[i].y)));
            
        }
        polylines(img,box,true,Scalar(0, 255, 255),2);
    }
    
}
void getContours_green(Mat &imgdil, Mat &img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgdil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
     for(const auto &box_ : contours)
    {
        //  Rect box = boundingRect(box_);
	    // rectangle(img,box,Scalar(0, 255, 255),1);
        RotatedRect rect = minAreaRect(box_);
        Point2f boxPoints[4];
        rect.points(boxPoints);
        vector<Point>box;
        for(int i = 0;i<4;i++)
        {
            box.push_back(Point(static_cast<int>(boxPoints[i].x),static_cast<int>(boxPoints[i].y)));
            
        }
        polylines(img,box,true,Scalar(0, 255, 0),2);
    }
}
int main()
{
    Mat img,hsv,maskBlue,maskRed_1,maskRed_2,maskRed;
    img = imread("/home/liu_xian/sample/assets/images/2.png");
    cvtColor(img, hsv, COLOR_BGR2HSV);
    inRange(hsv, Scalar(100, 43, 46), Scalar(124, 255, 255), maskBlue);
    inRange(hsv, Scalar(0,   130, 120), Scalar(8,   255, 255), maskRed_1);
    inRange(hsv, Scalar(172, 130, 120), Scalar(180, 255, 255), maskRed_2);
    bitwise_or(maskRed_1, maskRed_2, maskRed);

    Morphology(maskBlue);
    Morphology(maskRed);
    getContours_yellow(maskBlue,img);
    getContours_green(maskRed, img);
    imwrite("task1.jpg",img);
    waitKey( 0);
    destroyAllWindows();

}
