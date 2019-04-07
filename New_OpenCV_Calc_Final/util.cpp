#include <opencv2/opencv.hpp>
#include <string>
#include <algorithm>

// For opencv
using namespace cv;

using namespace std;

// Takes in an image and processes it for contour detection
// Inputs: Image - a raw image that is to be processed
// Outputs: Thresh - a fully preprocessed image of the original one
Mat preprocessImage(Mat& image) {
	// Declare Mats
	Mat gray, blur, thresh, contrast, topHat, blackHat, dilate;
	// Convert image to grayscale
	cvtColor(image, gray, CV_BGR2GRAY);
	// Get the structuring element for use in morphology
	Mat structuringElement = getStructuringElement(CV_SHAPE_RECT, Size(3, 3));
	// Get tophat and blackhat to increase contrast in the image
	morphologyEx(gray, topHat, CV_MOP_TOPHAT, structuringElement);
	morphologyEx(gray, blackHat, CV_MOP_BLACKHAT, structuringElement);
	contrast = gray + topHat - blackHat;
	// Apply a guassian blur
	GaussianBlur(contrast, blur, cvSize(25, 25), 0);
	// Apply an adaptive threshold to the image
	adaptiveThreshold(blur, thresh, 
	                255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,
	                11, 2);
	// Dilate the result image
	morphologyEx(thresh, thresh, MORPH_DILATE, structuringElement);
	// Return fully preprocces image
	return thresh;
}

// Finds all contours that are larger than 300 and returns the resulting vector
// Inputs: contours - an empty vector of type vector of point
//         hierarchy - a blank vector of typr Vec4i
//				 preprocessedImg - The image preprocessed by preprocessImage function
vector<vector<Point> > getValidContours(vector<vector<Point> >& contours,
																						vector<Vec4i>& hierarchy, Mat preprocessedImg) {
	// Find all the contours
	findContours( preprocessedImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	// Declare a vector to hold all the valid contours
	vector<vector<Point> > valid;
	// Loop through all the found contours
	for(int i = 0; i < contours.size(); i++) {
		// Check if the area is greater than 300
		if(contourArea(contours[i]) > 300) {
			// Insert the contour into the valid vector
			valid.push_back(contours[i]);
		}
	}
	// return the vector of valid contours
	return valid;
}

// Function to enable sorting of rectangles
static bool sortRects(const Rect& rect1, const Rect& rect2) {
	return(rect1.x < rect2.x);
}

// Finds the bounding rect for each contour and returns a sorted
// vector of rectangles
// Inputs: contours - a vector of valid contours
// Outputs: a vector a bounding rects of all valid contours
vector<Rect> getValidRects(vector<vector<Point> >& contours) {
	// Declare a vector for valid rectangles
	vector<Rect> validRects;
	// Loop through all contours
	for(int i = 0; i < contours.size(); i++) {
		// Find the bounding rect
		Rect bound = boundingRect(contours[i]);
		// Push rect into the vector
		validRects.push_back(bound);
	}
	// Sort the rects by x position
	sort(validRects.begin(), validRects.end(), sortRects);
	// Return the vector of Rects
	return validRects;
}

// Debug step draw the contours that were found. Taken from the openCV documentation
void showContours(vector<vector<Point> >& contours, vector<Vec4i>& hierarchy, Mat img) {
	RNG rng(12345);
	Mat drawing = Mat::zeros( img.size(), CV_8UC3 );
	for(int i = 0; i < contours.size(); i++) {
		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
	}
	imshow( "Contours", drawing );
}