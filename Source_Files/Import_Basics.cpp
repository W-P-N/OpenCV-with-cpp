#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>


// Importing images
//int main()
//{
//	std::string path = "Your image path";
//	cv::Mat image = cv::imread(path);  // Matrix dataype that handles all the images.
//	cv::imshow("Image", image);  // Show image.
//	cv::waitKey(0);  // Infinite delay.
//
//	return 0;
//}


// Importing video
//void main()
//{
//	// Video is a series of images -> use while loop to call image.
//		
//	std::string path = "Your image path";  // Path to video file.
//
//	cv::VideoCapture cap(path);  // Creating object to capture video.
//	cv::Mat image;  // Declaring object outside loop... obviously.
//
//	while (true)
//	{
//		cap.read(image);  // Reading each and every image.
//
//		cv::imshow("Image", image);
//		cv::waitKey(99);  // Delay of 99ms.
//	}
//}


// Web Camera.
void main()
{
	cv::VideoCapture cap(0);  // Argument -> Camera ID: 0 if only one or enter ID if any.
	cv::Mat image;  // Declaring object outside loop... obviously.

	while (true)
	{
		cap.read(image);  // Reading each and every image.

		cv::imshow("Image", image);
		cv::waitKey(99);  // Delay of 99ms.
	}
}
