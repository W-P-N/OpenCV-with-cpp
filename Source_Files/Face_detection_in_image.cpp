#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<opencv2/objdetect.hpp>

int main()
{
	std::string path = "Your image path";

	cv::Mat img = cv::imread(path);

	cv::CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");

	std::vector<cv::Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);

	// Iterating through all the faces detected and drawing them:
	for (int i = 0; i < faces.size(); i++)
	{
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 255));
	}

	cv::imshow("Image", img);
	cv::waitKey(0);
	return 0;
}
