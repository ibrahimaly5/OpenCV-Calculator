#ifndef _UTIL_H
#define _UTIL_H

Mat preprocessImage(Mat& image);

vector<vector<Point> > getValidContours(vector<vector<Point> >& contours,
																						vector<Vec4i>& hierarchy,
																						Mat preprocessedImg);

vector<Rect> getValidRects(vector<vector<Point> >& contours);

void showContours(vector<vector<Point> >& contours, vector<Vec4i>& hierarchy, Mat img);

#endif