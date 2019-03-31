#include <vector>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "consts_and_types.h"
// #include "preprocessor.h"

using namespace std;
using namespace cv;
using namespace cv::ml;

#define ESC 27
#define SPACE 32
#define RETURN 10


image_prefs i_pref;
display_messages Message;
text font;
colours Colours;
RNG rng(12345);
// Main function that will handle the video
// Inputs: Cap - Instance of the VideoCapture object holding the webcam
void handleVideo(VideoCapture& cap);

void processImage(Mat& frame);

 
int main(){
  // Instantiates the VideoCapture object 
  VideoCapture cap(0); 
    
  // Check if the webcam was opened succesfully
  if(!cap.isOpened()){
    // Output an error message to the user
    cout << Message.errorMessage << endl;
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
      Size textSize = getTextSize(Message.confirmation, font.fontFace,
                          1, 2, 0);
      // Center find placement of text
      Point textOrg((frame.cols - textSize.width)/2,
            				  textSize.height + 20);
      // Puts text on to screen
      putText(DisplayConfirmation, Message.confirmation, textOrg, 
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
  Mat MatClassifications;
  FileStorage Classifications("classifications.xml", FileStorage::READ);
  Classifications["classifications"] >> MatClassifications;
  Classifications.release();
  Mat imageClassifications;
  FileStorage imageClass("images.xml", FileStorage::READ);
  imageClass["images"] >> imageClassifications;
  imageClass.release();
  Ptr<KNearest>  kNearest(KNearest::create());
  kNearest->train(imageClassifications, ROW_SAMPLE, MatClassifications);
  Mat processed;
  Mat original = frame.clone();
  imshow("Processing", original);
  // Convert to Grayscale
  cvtColor(frame, processed, CV_BGR2GRAY);
  // Debug
  imshow("frameGrayscale", processed);
  // Apply blur
  GaussianBlur(processed, processed, cvSize(5, 5), 0);
  // Debug
  imshow("Blurred", processed);

  adaptiveThreshold(processed, processed, 
                    255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,
                    11, 2);
  // Debug
  imshow("Threshold", processed);

  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  Mat processedClone = processed.clone();
  findContours( processedClone, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  Mat drawing = Mat::zeros( processed.size(), CV_8UC3 );
  // Debug
  for( int i = 0; i< contours.size(); i++ ) {
      if(contourArea(contours[i]) >= 300) {
          Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
          drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
          Rect bound = boundingRect(contours[i]);
          rectangle(original, bound, Colours.green,2);
          imshow("Processing", original);
          Mat crop = processedClone(bound);
          imshow("Crop", crop);
          Mat matFloat;
          Mat resized;
          resize(crop, resized, Size(i_pref.width, i_pref.height));
          resized.convertTo(matFloat, CV_32FC1);      
          Mat matFlat = matFloat.reshape(1, 1);     
          Mat result(0, 0, CV_32F);
          kNearest->findNearest(matFlat, 1, result);
          float fltCurrentChar = (float)result.at<float>(0, 0);
          cout <<  (char)fltCurrentChar << " ";
          // kNearest
        }
     }
  imshow( "Contours", drawing );
  // Mat blob;
  // blobFromImage(processed, blob, 1.0, Size(inpWidth, inpHeight), Scalar(123.68, 116.78, 103.94), true, false);
  // imshow( "Blob", blob );

}