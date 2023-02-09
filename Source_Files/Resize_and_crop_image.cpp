#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>

// RESIZE & CROP //

void  main()
{
	std::string path = "Your image path";
	cv::Mat img = cv::imread(path);

	cv::Mat img_resize, img_crop;

	std::cout << img.size()<<std::endl;  // Get the size of image.

	//cv::resize(img, img_resize, cv::Size(640, 480));  // Direct Dimensions.
	//cv::resize(img, img_resize, cv::Size(), 0.5, 0.5);  // Scaling.

	cv::Rect roi(100, 100, 300, 250);  // Defining Region Of Intrest.
	img_crop = img(roi);  // Gets submatrix of defined rectangle.

	cv::imshow("Image", img);
	//cv::imshow("Resized Image", img_resize);
	cv::imshow("Crop Image", img_crop);

	cv::waitKey(0);
}
