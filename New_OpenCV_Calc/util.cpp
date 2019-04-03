#include <opencv2/opencv.hpp>
#include <string>
#include <algorithm>


using namespace cv;
using namespace std;

Mat preprocessImage(Mat& image) {
	Mat gray, blur, thresh, contrast, topHat, blackHat, dilate;
	cvtColor(image, gray, CV_BGR2GRAY);
	Mat structuringElement = getStructuringElement(CV_SHAPE_RECT, Size(3, 3));
	morphologyEx(gray, topHat, CV_MOP_TOPHAT, structuringElement);
	morphologyEx(gray, blackHat, CV_MOP_BLACKHAT, structuringElement);
	contrast = gray + topHat - blackHat;
	GaussianBlur(contrast, blur, cvSize(25, 25), 0);
	adaptiveThreshold(blur, thresh, 
	                255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,
	                11, 2);
	morphologyEx(thresh, thresh, MORPH_DILATE, structuringElement);
	return thresh;
}

vector<vector<Point> > getValidContours(vector<vector<Point> >& contours,
																						vector<Vec4i>& hierarchy, Mat preprocessedImg) {
	findContours( preprocessedImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	vector<vector<Point> > valid;
	for(int i = 0; i < contours.size(); i++) {
		if(contourArea(contours[i]) > 100) {
			valid.push_back(contours[i]);
		}
	}
	return valid;
}

static bool sortRects(const Rect& rect1, const Rect& rect2) {
	return(rect1.x < rect2.x);
}


vector<Rect> getValidRects(vector<vector<Point> >& contours) {
	vector<Rect> validRects;
	vector<vector<Point> > poly(contours.size());
	for(int i = 0; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), poly[i], 3, true);
		Rect bound = boundingRect(poly[i]);
		validRects.push_back(bound);
	}
	sort(validRects.begin(), validRects.end(), sortRects);
	return validRects;
}

void showContours(vector<vector<Point> >& contours, vector<Vec4i>& hierarchy, Mat img) {
	RNG rng(12345);
	Mat drawing = Mat::zeros( img.size(), CV_8UC3 );
	for(int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
	}
	imshow( "Contours", drawing );
}