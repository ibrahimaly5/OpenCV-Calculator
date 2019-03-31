#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "tinydir.h"
#include <utility>
#include <vector>
#include "consts_and_types.h"
using namespace std;

void loadData();
void processData();

image_prefs i_pref;
vector <pair<string, string> > images;   
int main() {
	loadData();
	cout << "loaded data" << endl;
	processData();
}


void loadData() {
	tinydir_dir dir;
	tinydir_open(&dir, "dataset");
	while (dir.has_next) {
		tinydir_file file;
		tinydir_readfile(&dir, &file);
		if(file.is_dir){
			string subDir = file.name;
			if(subDir != "." && subDir != ".."){
				string label = file.name;
				subDir.insert(0, "dataset/");
				tinydir_dir folderName;
				tinydir_open(&folderName, subDir.c_str() );
				while (folderName.has_next){
					tinydir_file picture;
					tinydir_readfile(&folderName, &picture);
					string pictureName = picture.name;
					if (pictureName != "." && pictureName != ".."){
						pictureName.insert(0, subDir + "/");
						pair<string, string> image_data (pictureName, label);
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

void processData() {
	Mat matClassifications;
	Mat imageClassifications;
	char last = NULL;
	int count = 0;
	for(int i = 0; i < images.size(); i++) {
		Mat image = imread(images[i].first);
		// cout << images[i].first << " ";
		resize(image, image, Size(i_pref.width, i_pref.height));
	  cvtColor(image, image, CV_BGR2GRAY);
	  GaussianBlur(image, image, cvSize(5, 5), 0);
	  adaptiveThreshold(image, image, 
	                    255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,
	                    11, 2);
	  vector<vector<Point> > contours;
	  vector<Vec4i> hierarchy;
	  Mat image_copy = image.clone();
	  findContours( image_copy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		for( int j = 0; j < contours.size(); j++ ) {
      if(contourArea(contours[j]) >= 100) {
				matClassifications.push_back((int)images[i].second[0]);
				
				if(images[i].second[0] != last) {
					cout << images[i].second[0] << " " << count << endl;
					last = images[i].second[0];
					count = 0;

				}
				else count++;
				Mat matFloat;
				image.convertTo(matFloat, CV_32FC1);      
				Mat matFlat = matFloat.reshape(1, 1);     
				imageClassifications.push_back(matFlat); 
      }
    }
	}

  FileStorage Classifications("classifications.xml", FileStorage::WRITE);

  if (Classifications.isOpened() == false) {         

  }

  Classifications << "classifications" << matClassifications;
  Classifications.release();

  FileStorage imageClass("images.xml", FileStorage::WRITE);

  if (imageClass.isOpened() == false) {                
      cout << "error, unable to open training images file, exiting program\n\n";
  }

  imageClass << "images" << imageClassifications;
  imageClass.release();
}
