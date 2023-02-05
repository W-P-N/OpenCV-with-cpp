#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

// Creating ouw own blank image.

void drawChakra(cv::Mat img, int num)
{
	if (num == 24)
	{
		return;
	}
	cv::line(img, cv::Point(300, 250), cv::Point(300, 200), cv::Scalar(255, 0, 0));

	return drawChakra(img, num + 1);

}

void main()
{
	cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));  // Type: 8 bits, U - unsigned, C3 - 3 colour channels. Colour is defined using Scalar(b,g,r) values.
	// 0,0,0 -> black, 255,255,255 -> white.

	//cv::circle(img, cv::Point(256, 256), 155, cv::Scalar(255, 255, 255), cv::FILLED);  // Making circle in the image.
	
	// National flag:
	cv::rectangle(img, cv::Point(100, 100), cv::Point(500, 200), 1);  // Border - Top Rect.
	cv::rectangle(img, cv::Point(100, 100), cv::Point(500, 200), cv::Scalar(0, 165,255), cv::FILLED);  // Colour - Top rect.
	cv::rectangle(img, cv::Point(100, 200), cv::Point(500, 300), 1);  // Border - Mid Rect.
	cv::rectangle(img, cv::Point(100, 300), cv::Point(500, 400), 1);  // Border - Low Rect.
	cv::rectangle(img, cv::Point(100, 300), cv::Point(500, 400), cv::Scalar(0, 255, 0), cv::FILLED);  // Colour - Low rect.
	cv::circle(img, cv::Point(300, 250), 50, cv::Scalar(0, 0, 0));  // Circle.
	cv::putText(img, "Indian National Flag", cv::Point(100, 50), 2, 1.2, cv::Scalar(0, 0, 0));
	

	cv::imshow("Image", img);

	cv::waitKey(0);
}