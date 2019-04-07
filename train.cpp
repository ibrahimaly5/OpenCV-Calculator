#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "tinydir.h"
#include <utility>
#include <vector>
#include "consts.h"
#include "util.h"

using namespace cv;
using namespace cv::ml;
using namespace std;


// Uses tinydir to find the path of all image files for training
// The path and the associated label are then placed into a pair
// which are then place into a vector 
void loadData();

// Processes each image using function in util.cpp
void processData(vector<int>& labels, Mat& imageClassifications);

// Simply creates the SVM with the training data
void setupSVM(vector<int>& labels, Mat& imageClassifications);

// Global variable for image preferences
// Originates in consts.h
image_prefs i_pref;
// The vector containing each image path and its label
vector <pair<string, string> > images;   


int main() {
	// Holds all labels of the images
	vector<int> labels;
	Mat imageClassifications;
	// Calls loadDate
	loadData();
	// Displays the end of loading data
	cout << "Loaded dataset" <<endl;
	// Process all images
	processData(labels, imageClassifications);
	// Sets up the SVM
	setupSVM(labels, imageClassifications);
	// Return 0 by convention
	return 0;
}

// Finds path of each number in the dataset and pairs it with its label
void loadData() {
	// Instantiate tinydir_dir
	tinydir_dir dir;
	// Open the dataset folder
	tinydir_open(&dir, "dataset");
	// Loop through all folders
	while (dir.has_next) {
		// Instantiate tinydir_dir
		tinydir_file file;
		// Read the folder
		tinydir_readfile(&dir, &file);
		// Check if file is actually a folder
		if(file.is_dir){
			// Grab the Folder name
			string subDir = file.name;
			// Ignore hidden files
			if(subDir != "." && subDir != ".."){
				// Grab the label (Folder name)
				string label = file.name;
				// insert "dataset/" at beginning to compelete file path
				subDir.insert(0, "dataset/");
				// Instantiate tinydir_dir
				tinydir_dir folderName;
				// Open the folder
				tinydir_open(&folderName, subDir.c_str() );
				// Loop through all images
				while (folderName.has_next){
					// Instantiate tinydir_dir
					tinydir_file picture;
					// Read in the image
					tinydir_readfile(&folderName, &picture);
					string pictureName = picture.name;
					// Check for hiddent files
					if (pictureName != "." && pictureName != ".."){
						// Complete the file path
						pictureName.insert(0, subDir + "/");
						// Check for D (Placeholder for "/" as that cannot be a folder name)
						if(label == "D") label = "/";
						// Make a pair of the image path and the label
						pair<string, string> image_data (pictureName, label);
						// Push into the vector
						images.push_back(image_data);
					}
					tinydir_next(&folderName);
				}
				tinydir_close(&folderName); 	
			}
		}
		tinydir_next(&dir);
	}
	tinydir_close(&dir);	
}

void processData(vector<int>& labels, Mat& imageClassifications) {
	int count = 0;
	for(int i = 0; i < images.size(); i++) {
		// Instantiate vector needed for proccesing
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		vector<vector<Point> > validContours;
		vector<Rect> validRects;

		// Load the image
		Mat image = imread(images[i].first);
		// Call function to preprocess the image
		Mat preprocessedImg = preprocessImage(image);
		// Get the valid contour from the picture
		validContours = getValidContours(contours, hierarchy, preprocessedImg);
		// Grab the valid bounding rectangles
		validRects = getValidRects(validContours);
		// Checks if there is no only 1 detected contour
		if(validContours.size() != 1) continue;

		// Get region of interest
		Mat character = preprocessedImg(validRects[0]);
		// Resize the ROI
		Mat resized;
		resize(character, resized, Size(20, 20));

		// Classify the character
		labels.push_back((int)images[i].second[0]);

		Mat matFloat;
		resized.convertTo(matFloat, CV_32FC1);  
		// Flatten image    
		Mat matFlat = matFloat.reshape(1, 1);
		// push back processed image  
		imageClassifications.push_back(matFlat);
		count++;
	}
	cout << images.size() << " " << count << endl;
}

void setupSVM(vector<int>& labels, Mat& imageClassifications) {
	// Create the SVM and save the yml
	Ptr<SVM> svm = SVM::create();
	svm->setType(SVM::C_SVC);
	svm->setKernel(SVM::LINEAR);
	svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
	svm->setGamma(3);
	svm->setDegree(3);
	Ptr<TrainData> td = TrainData::create(imageClassifications, ROW_SAMPLE, labels);
	svm->trainAuto(td);
	svm->save("model4.yml");
}