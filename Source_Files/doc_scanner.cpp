#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<functional>
#include<algorithm>

/*
* GrayScale
* Blur
* Canny Edge detetor
* Extract four corners of paper
* Get top view
* Preprocessing -> Contours -> Wrap.
*/


cv::Mat preprocessing(cv::Mat imageOriginal)
{
	cv::Mat imgGray, imgBlur, imgCanny, imgDil;

	cv::cvtColor(imageOriginal, imgGray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
	cv::Canny(imgBlur, imgCanny, 25, 75);

	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgCanny, imgDil, kernel);

	return imgDil;
}

std::vector<cv::Point> getContours(cv::Mat imgDil)
{
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point>> contoursPolygon(contours.size());
	std::vector<cv::Rect> boundingRect(contours.size());
	int maxArea = 0;
	std::vector<cv::Point> largest;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]);
		std::string objectType;

		if (area > 1000)
		{
			float peri = cv::arcLength(contours[i], true);
			cv::approxPolyDP(contours[i], contoursPolygon[i], 0.02 * peri, true);

			if (area > maxArea && contoursPolygon[i].size() == 4)
			{
				cv::drawContours(imgDil, contoursPolygon, i, cv::Scalar(255, 0, 255), 2);
				largest = {
					contoursPolygon[i][0],
					contoursPolygon[i][1],
					contoursPolygon[i][2],
					contoursPolygon[i][3]
				};
				maxArea = area;
			}

		}
	}

	return largest;
}

void drawPoints(std::vector<cv::Point>& points, cv::Scalar color, cv::Mat imgOriginal)
{
	for (int i = 0; i < points.size(); i++)
	{
		cv::circle(imgOriginal, points[i], 10, color, cv::FILLED);
		cv::putText(imgOriginal, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 5, color, 7);
	}
}

std::vector<cv::Point> reorder(const std::vector<cv::Point>& iniPoints)
{
	std::vector<cv::Point> newPoints;
	std::vector<int> sumPoints, subPoints;

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(iniPoints[i].x + iniPoints[i].y);
		subPoints.push_back(iniPoints[i].x - iniPoints[i].y);
	}
	newPoints.push_back(iniPoints[std::min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);
	newPoints.push_back(iniPoints[std::min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(iniPoints[std::max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);
	newPoints.push_back(iniPoints[std::max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);

	return newPoints;
}

cv::Mat getWarp(cv::Mat& imOriginal, std::vector<cv::Point>& docPts, float& w, float& h)
{
	cv::Point2f src[4] = { docPts[0], docPts[1], docPts[2], docPts[3]};
	cv::Point2f des[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };

	cv::Mat matrix = cv::getPerspectiveTransform(src, des), imgWarp;
	cv::warpPerspective(imOriginal, imgWarp, matrix, cv::Point(w, h));

	return imgWarp;
}

int main()
{ 
	float w = 420, h = 596;
	std::string path = "Your image path";
	cv::Mat imageOriginal = cv::imread(path), imgWarp, imgCrop;

	cv::resize(imageOriginal, imageOriginal, cv::Size(), 0.5, 0.5);
	
	auto output_func = std::bind(preprocessing, imageOriginal);
	std::vector<cv::Point> intitialPoints = getContours(output_func());

	std::vector<cv::Point> docPoints;

	docPoints = reorder(intitialPoints);
	drawPoints(docPoints, cv::Scalar(0, 0, 255), imageOriginal);

	imgWarp = getWarp(imageOriginal, docPoints, w, h);

	cv::Rect roi(5, 5, w-(2*5), h-(2*5));
	imgCrop = imgWarp(roi);

	cv::imshow("O_Image", imageOriginal);
	cv::imshow("C_Image", imgCrop);
	cv::waitKey(0);

	return 0;
}
