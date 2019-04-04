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

void loadData();
void processData(vector<int>& labels, Mat& imageClassifications);
void setupSVM(vector<int>& labels, Mat& imageClassifications);

image_prefs i_pref;
vector <pair<string, string> > images;   
int main() {
	vector<int> labels;
	Mat imageClassifications;
	loadData();
	cout << "Loaded dataset" <<endl;
	processData(labels, imageClassifications);
	setupSVM(labels, imageClassifications);
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

void processData(vector<int>& labels, Mat& imageClassifications) {
	int count = 0;
	for(int i = 0; i < images.size(); i++) {
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		vector<vector<Point> > validContours;
		vector<Rect> validRects;
		Mat image = imread(images[i].first);
		Mat preprocessedImg = preprocessImage(image);
		validContours = getValidContours(contours, hierarchy, preprocessedImg);
		validRects = getValidRects(validContours);
		if(validContours.size() != 1) continue;

		Mat character = preprocessedImg(validRects[0]);
		Mat resized;
		resize(character, resized, Size(20, 20));

		labels.push_back((int)images[i].second[0]);

		Mat matFloat;
		resized.convertTo(matFloat, CV_32FC1);      
		Mat matFlat = matFloat.reshape(1, 1);     
		imageClassifications.push_back(matFlat);
		count++;
	}
	cout << images.size() << " " << count << endl;
}

void setupSVM(vector<int>& labels, Mat& imageClassifications) {
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