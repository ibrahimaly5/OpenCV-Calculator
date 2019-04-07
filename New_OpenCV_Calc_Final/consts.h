#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// Messages to be displayed to the screen for the user
string errorMessage = "Error opening webcam. Please check the connection";
string confirmation = "Use this image? (Y/N)(Enter/ESC)";

// Struct that holds properties for text to be put on to the screen
struct text {
	// Font
	int fontFace = CV_FONT_HERSHEY_TRIPLEX;
	// Size
	int fontSize = 1;
	// Colour
	Scalar fontColour = cvScalar(0, 0, 0);
};


// Struct that holds RGB values for colours
struct colours {
	Scalar black = cvScalar(0, 0, 0);
	Scalar green = cvScalar(0, 255, 0);
	Scalar red = cvScalar(255, 0, 0);
	Scalar blue = cvScalar(0, 0, 255);
	Scalar white = cvScalar(255, 255, 255);

};

// Height and width of image
struct image_prefs {
	const int width = 20;
	const int height = 30;
};



#endif