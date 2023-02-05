#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

void main()
{
	std::string path = "Resources/test.png";
	cv::Mat img = cv::imread(path);  // Reading image.

	cv::Mat img_grey, blur_img, canny_img, dialated_img, eroded_img;

	// Converting image colour.
	cv::cvtColor(img, img_grey, cv::COLOR_BGR2GRAY);  // cvtColor -> converts image colour. Args-> (Image to convert, Obj to store coloured image, Colour to convert to).

	// Blur image.
	cv::GaussianBlur(img, blur_img, cv::Size(9, 9), 200, 200);

	// Before using edge detection always use blur.
	cv::Canny(blur_img, canny_img, 50, 80);  // Detects edge of image.

	cv::Mat Kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::dilate(canny_img, dialated_img, Kernel);  // Re-define egdes by increasing (dialating) the size of lines.
	cv::erode(dialated_img, eroded_img, Kernel);  // Re-define edges of dialted image by decreasing (eroding) the size of lines.

	//cv::imshow("Image Gery", img_grey);
	cv::imshow("Image", img);
	//cv::imshow("Iamge Blur", blur_img);
	//cv::imshow("Canny Image", canny_img);
	cv::imshow("Dialated Image", dialated_img);
	cv::imshow("Eroded Image", eroded_img);

	cv::waitKey(0);
}