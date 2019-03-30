#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <string>
#include "opencv2/opencv.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct display_messages {
	string errorMessage = "Error opening webcam. Please check the connection";
	string confirmation = "Use this image? (Y/N)(Enter/ESC)";
};

struct text {
	int fontFace = CV_FONT_HERSHEY_TRIPLEX;
	int fontSize = 1;
	Scalar fontColour = cvScalar(0, 0, 0);
};

struct colours {
	Scalar black = cvScalar(0, 0, 0);
	Scalar green = cvScalar(0, 255, 0);
	Scalar red = cvScalar(255, 0, 0);
	Scalar blue = cvScalar(0, 0, 255);
	Scalar white = cvScalar(255, 255, 255);

};

#endif
