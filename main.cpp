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

// Processes the image captured from the image stream.
// Uses functions in util.cpp
// Inputs: frame - the image captured from the videostream to be processed
//                 to find the resulting equation
void processImage(Mat& frame);

// Passes the predicted equation to be evaluated. Returns the resulting string
// Inputs: equation - the predicted equation
// Returns: the evaluated equation
string equate(string equation);


// Asks the user for confirmation if the predicted equation is correct
// Inputs: result - the predicted equation
//         original - the mat with bounding rects drawn on it
//         validRects - a vector with all the valid bounding rects
bool confirm(string result, Mat original, vector<Rect> &validRects);


// Global vars from consts.h
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

  // return 0 by convention
  return 0;
}

void handleVideo(VideoCapture& cap) {
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
        // Confirms image is good to use if user presses
        // Return
        if(c == 13 || c == RETURN){
          processImage(frame);
          break;
          // Exits if user presses ESC
        } else if(c == ESC) {
          break;
        }
      }
    }
  }
}

void processImage(Mat& frame) {
  // Declare needed vars
	Mat contourImg;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<vector<Point> > validContours;
	vector<Rect> validRects;


	Mat original = frame;
  // Preprocess the image. See util.cpp for details
	Mat preprocessedImg = preprocessImage(frame);

  // If debug is enabled, will show the image after preprocessing
  if(DEBUG) {
  	imshow("preprocessedImg", preprocessedImg);
  }

  // Finds the valid contours, see util.cpp for details
	validContours = getValidContours(contours, hierarchy, preprocessedImg);
  // Finds the valid rects, see util.cpp for details
	validRects = getValidRects(validContours);

  // If debug is enabled, draw out the found contours
  if(DEBUG) {
  	showContours(validContours, hierarchy, preprocessedImg);
  }

  // loads the SVM
	Ptr<SVM> svm = StatModel::load<SVM>("model4.yml");

  // declare an empty string for the predicted equation
  string equation;
  char lastChar = 'a';

  // Loop through all the valid rectangles
	for(int i = 0; i < validRects.size(); i++) {

    // Draws a rectangle around the found contour
		rectangle(original, validRects[i], Colours.green, 2);
    imshow("Results", original);

    // Gets the region of interest
    Mat character = preprocessedImg(validRects[i]);
		Mat resized;
    // Resizes the image
		resize(character, resized, Size(20, 20));

    // Needed conversion for SVM to predict
    // Converts to float
		Mat matFloat;
		resized.convertTo(matFloat, CV_32FC1); 
    // Flattens image     
		Mat matFlat = matFloat.reshape(1, 1);
    // Predicts the character
		char predicted = svm->predict(matFlat);
    // Checks for a commmon false positive
    if(predicted == '-' && validRects[i].width <= 3 * validRects[i].height) {
      predicted = 'X';
    }

    // 8's frequently predicted as X
    // if(predicted == 'X') {
    //   if(validRects[i].height >= 1.5 * validRects[i].width) {
    //     predicted = 8;
    //   }
    // }

    // For future updates
    lastChar = predicted;
    // Adds the predicted char into the equation string
    equation += predicted;
    // Prints the predicted string
		cout << predicted;
	}
	cout << endl;
  // Copies
  Mat confirmCopy = original.clone();

  // Checks for confirmation of user if the prediction was correct
  if(confirm(equation, confirmCopy, validRects)){
    // Equates the equation
    string result = equate(equation);
    // Adds "= " to beginning of the result string
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
  // Finds the size of the text to be displayed
  Size textSize1 = getTextSize(result, font.fontFace,
                1, 2, 0);

  // Finds the text placement below the equation
  Point textOrg1((original.cols - textSize1.width)/2,
                validRects[0].y + validRects[0].height + 30);

  // Puts text on to screen
  putText(original, result, textOrg1, 
  font.fontFace, font.fontSize, Colours.red, 2, CV_AA);
  
  // String to be displayed on to the screen
  string confirmationEq = "Is this the right equation? (Y/N) (RETURN/ESC)";
  
  // Finds the size of the text to be displayed
  Size textSize = getTextSize(confirmationEq, font.fontFace,
                    0.75, 2, 0);

  // Places the text on the top of the window
  Point textOrg((original.cols - textSize.width)/2,
                textSize.height + 20);
  // Puts text on to screen
  putText(original, confirmationEq, textOrg, 
  font.fontFace, 0.75, font.fontColour, 2, CV_AA);
  imshow("Results", original);


  char c;
  // Return true if user presses RETURN
  // Returns false if user presses ESC
  while(true) {
    c = (char)waitKey(25);
    if(c == 13 || c == RETURN){
      return true;
    } else if(c == ESC) {
      return false;
    }
  }
}