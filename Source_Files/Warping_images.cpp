#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

// Warping Images.

cv::Mat matrix, imgWarp;
float h = 350, w = 250;

void main()
{
	std::string path = "Your image path";  // Go to paint and get the edge pixel points.

	cv::Mat img = cv::imread(path);

	cv::Point2f src[4] = { {529, 142}, {771, 190}, {405, 395}, {674, 457} };  // Source points declared as floating points.
	cv::Point2f des[4] = { {0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h} };  // Destination points.

	matrix = cv::getPerspectiveTransform(src, des);  // Storing transformation matrix using getPerspectiveTransform function taking source and destnation points.
	cv::warpPerspective(img, imgWarp, matrix, cv::Point(w, h));  // Warp the imag and store in imgWarp using transformation matrix and dimensions.

	cv::imshow("Warp", img);
	cv::imshow("Warp", imgWarp);
	cv::waitKey(0);
}
