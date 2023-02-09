#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

// Colour Detection.

void main()
{
	std::string path = "Your image path";
	cv::Mat img = cv::imread(path), imgHSV, imgMask;

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);  // Converts image from one colour space to other. Here we are converting to HSV colour space.
	
	// Changing HSV values according to detect specific colour in the HSV space.
	int hmin = 0, smin = 110, vmin = 153;  // Minimum values of HSV.
	int hmax = 19, smax = 240, vmax = 255; // Maximum values of HSV.

	cv::namedWindow("HSV", (640, 200));
	cv::createTrackbar("Hue Min", "HSV", &hmin, 179);
	cv::createTrackbar("Hue Max", "HSV", &hmax, 179);
	cv::createTrackbar("Sat Min", "HSV", &smin, 255);
	cv::createTrackbar("Hue Max", "HSV", &smax, 255);
	cv::createTrackbar("Val Min", "HSV", &vmin, 255);
	cv::createTrackbar("Hue Max", "HSV", &vmax, 255);


	while (true)
	{
		cv::Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);  // Defining range.
		cv::inRange(imgHSV, lower, upper, imgMask);  // Checks if the input array lies within the given range of arrrays.

		cv::imshow("Laborgini", img);
		cv::imshow("Laborgini HSV", imgHSV);
		cv::imshow("Masked Image", imgMask);
		cv::waitKey(1);
	}
}
