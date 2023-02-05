#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>



int main()
{
	cv::VideoCapture cap(0);
	cv::Mat image;

	// Define min and max values of HSV parameters.

	int hmin = 0, smin = 0, vmin = 0;  // Minimum values of HSV.
	int hmax = 255, smax = 255, vmax = 255; // Maximum values of HSV.

	cv::namedWindow("HSV", (640, 200));
	cv::createTrackbar("Hue Min", "HSV", &hmin, 179);
	cv::createTrackbar("Hue Max", "HSV", &hmax, 179);
	cv::createTrackbar("Sat Min", "HSV", &smin, 255);
	cv::createTrackbar("Hue Max", "HSV", &smax, 255);
	cv::createTrackbar("Val Min", "HSV", &vmin, 255);
	cv::createTrackbar("Hue Max", "HSV", &vmax, 255);

	cv::Mat imgHSV, imgMask;

	while (true)
	{
		cap.read(image);  // Read captured image.

		cv::cvtColor(image, imgHSV, cv::COLOR_BGR2HSV);  // Convert BGR colour space to HSV colour space.

		cv::Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);  // Define range in scalar.
		cv::inRange(imgHSV, lower, upper, imgMask);  // Define range.

		cv::imshow("Imag", image);  // Show actual image.
		cv::imshow("Mask", imgMask);  // Show mask.
		cv::waitKey(1);
	}

	return 0;
}