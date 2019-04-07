#include <vector>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "consts.h"
#include "util.h"
#include <complex>
#include <stack>
#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
using namespace std;
using namespace cv;
using namespace cv::ml;

#define DEBUG 0
#define ESC 27
#define SPACE 32
#define RETURN 10

// Main function that will handle the video
// Inputs: Cap - Instance of the VideoCapture object holding the webcam
void handleVideo(VideoCapture& cap);

void processImage(Mat& frame);

string equate(string equation);

bool confirm(string result, Mat original, vector<Rect> &validRects);

image_prefs i_pref;
text font;
colours Colours;
int main(){
  // Instantiates the VideoCapture object 
  VideoCapture cap(1); 
    
  // Check if the webcam was opened succesfully
  if(!cap.isOpened()){
    // Output an error message to the user
    cout << errorMessage << endl;
    return -1;
  }
  
  // Main function that will handle the webcam
  handleVideo(cap);
  
  // Releases the VideoCapture Object
  cap.release();
 
  // Closes all windows
  destroyAllWindows();
     
  return 0;
}

void handleVideo(VideoCapture& cap) {\
  while(true){
    // Instantiate a mat object
    Mat frame;
    // Grab a frame
    cap >> frame;
  
    // Check if frame actually contains a frame
    if (frame.empty()) {
      break;
    }
 
    // Dispplay the frame on a window called "OpenCV calculator"
    imshow("OpenCV Calculator", frame);
 
    // Check for user input
    char c = (char)waitKey(25);
    // Check for ESC
    if(c == ESC) {
      // Stops the program
      break;
    // Check for space (Takes a picture)
    } else if(c == SPACE) {
      Mat DisplayConfirmation = frame.clone();
      // Get Size of text
      Size textSize = getTextSize(confirmation, font.fontFace,
                          1, 2, 0);
      // Center find placement of text
      Point textOrg((frame.cols - textSize.width)/2,
            				  textSize.height + 20);
      // Puts text on to screen
      putText(DisplayConfirmation, confirmation, textOrg, 
      font.fontFace, font.fontSize, font.fontColour, 2, CV_AA);
      // Displays the text
      imshow("OpenCV Calculator", DisplayConfirmation);

      // Displays the current frame until user confirms to 
      // image is good to use
      while(true) {
        c = (char)waitKey(25);
        if(c == 13 || c == RETURN){
          processImage(frame);
          break;
        } else if(c == ESC) {
          break;
        }
      }
    }
  }
}

void processImage(Mat& frame) {
	Mat contourImg;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<vector<Point> > validContours;
	vector<Rect> validRects;


	Mat original = frame;
	Mat preprocessedImg = preprocessImage(frame);
  if(DEBUG) {
  	imshow("preprocessedImg", preprocessedImg);
  }

	validContours = getValidContours(contours, hierarchy, preprocessedImg);
	validRects = getValidRects(validContours);
  if(DEBUG) {
  	showContours(validContours, hierarchy, preprocessedImg);
  }


	Ptr<SVM> svm = StatModel::load<SVM>("model4.yml");

  string equation;
  char lastChar = 'a';
	for(int i = 0; i < validRects.size(); i++) {
		rectangle(original, validRects[i], Colours.green, 2);
    imshow("Results", original);

    Mat character = preprocessedImg(validRects[i]);
		Mat resized;
		resize(character, resized, Size(20, 20));

		Mat matFloat;
		resized.convertTo(matFloat, CV_32FC1);      
		Mat matFlat = matFloat.reshape(1, 1);
		char predicted = svm->predict(matFlat);
    if(predicted == '-' && validRects[i].width <= 3 * validRects[i].height) {
      predicted = 'X';
    }
    // if(lastChar == 'X' && predicted == 'X') {
    //   predicted = '8';
    // }
    if(predicted == 'X') {
      if(validRects[i].height >= 1.5 * validRects[i].width) {
        predicted = 8;
      }
    }
    lastChar = predicted;
    equation += predicted;
		cout << predicted;
	}
	cout << endl;
  Mat confirmCopy = original.clone();
  if(confirm(equation, confirmCopy, validRects)){
    string result = equate(equation);
    result.insert(0,"= ");
    Size textSize = getTextSize(result, font.fontFace,
                    1, 2, 0);
    // Center find placement of text
    Point textOrg((original.cols - textSize.width)/2,
                  validRects[0].y + validRects[0].height + 50);
    // Puts text on to screen
    putText(original, result, textOrg, 
    font.fontFace, font.fontSize, font.fontColour, 2, CV_AA);
    imshow("Results", original);
  }
}

string equate(string equation) {
  lexer Lexer;
  parser Parser;
  evaluator Evaluator;

  Lexer.LexInput(equation);
  Parser.get_tokens(Lexer.getTokens());
  Parser.parse_tokens();

  Evaluator.start_evaluator(Parser.get_postfix());
  Evaluator.EvaluateExpr();
  string result = Evaluator.send_result();
  Evaluator.print_output();
  return result;
}


bool confirm(string result, Mat original, vector<Rect> &validRects) {
  // for(int i = 0; i < validRects.size(); i++) {
  //   Size textSize = getTextSize(result, font.fontFace,
  //                 1, 2, 0);
  // // Center find placement of text
  //   Point textOrg(validRects[i].x + validRects[i].width + 80,
  //                 validRects[i].y + validRects[i].height + 30);
  //   // Puts text on to screen
  //   putText(original, result, textOrg, 
  //   font.fontFace, font.fontSize, Colours.red, 2, CV_AA);
  // }
  Size textSize1 = getTextSize(result, font.fontFace,
                1, 2, 0);
  // Center find placement of text
  Point textOrg1((original.cols - textSize1.width)/2,
                validRects[0].y + validRects[0].height + 30);
  // Puts text on to screen
  putText(original, result, textOrg1, 
  font.fontFace, font.fontSize, Colours.red, 2, CV_AA);
  string confirmationEq = "Is this the right equation? (Y/N) (RETURN/ESC)";
  Size textSize = getTextSize(confirmationEq, font.fontFace,
                    0.75, 2, 0);
  // Center find placement of text
  Point textOrg((original.cols - textSize.width)/2,
                textSize.height + 20);
  // Puts text on to screen
  putText(original, confirmationEq, textOrg, 
  font.fontFace, 0.75, font.fontColour, 2, CV_AA);
  imshow("Results", original);

  char c;
  while(true) {
    c = (char)waitKey(25);
    if(c == 13 || c == RETURN){
      return true;
    } else if(c == ESC) {
      return false;
    }
  }
}