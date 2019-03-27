#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>


#define errorMessage "Error opening webcam. Please check the connection"


using namespace std;
using namespace cv;

// Main function that will handle the video
// Inputs: Cap - Instance of the VideoCapture object holding the webcam
void handleVideo(VideoCapture& cap);
 
int main(){
  // Instantiates the VideoCapture object 
  VideoCapture cap(0); 
    
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
  String confirmation = "Use this image? (Y/N)(Enter/ESC)";
  int fontFace = CV_FONT_HERSHEY_TRIPLEX;
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
    if(c == 27) {
      // Stops the program
      break;
    // Check for space (Takes a picture)
    } else if(c == 32) {
      // Get Size of text
      Size textSize = getTextSize(confirmation, fontFace,
                          1, 2, 0);
      // Center find placement of text
      Point textOrg((frame.cols - textSize.width)/2,
              textSize.height + 20);
      // Puts text on to screen
      putText(frame, confirmation, textOrg, 
      fontFace, 1, cvScalar(0,0,0), 2, CV_AA);
      // Displays the text
      imshow("OpenCV Calculator", frame);

      // Displays the current frame until user confirms to 
      // image is good to use
      while(true) {
        c = (char)waitKey(25);
        if(c == 13 || c == 10){
          break;
        }
      }
    }
  }
}