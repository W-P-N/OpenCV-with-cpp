#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>


// Defining HSV colour codes to detect those colours in the image.
std::vector<std::vector<int>> myColours = {
	{124, 48, 117, 143, 170, 255},  // Purple.
	{68, 72, 156, 102, 126, 255}  // Green.
};

// Colours to display when above colours are detected.
std::vector<cv::Scalar> myColourValues = {
	{255, 0, 255},  // Purple.
	{0, 255, 0}  // Green.
};

void findColor(cv::Mat img)
{
	cv::Mat imgHSV;

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	// Loop to detect all the colours in the vector.
	for (int i = 0; i < myColours.size(); i++)
	{
		cv::Scalar lower(myColours[i][0], myColours[i][1], myColours[i][2]), upper(myColours[i][3], myColours[i][4], myColours[i][5]);
	
		cv::Mat imgMask;  // New mask for each colour.
		
		cv::inRange(imgHSV, lower, upper, imgMask);

		cv::imshow(std::to_string(i), imgMask);
	}

}

int main()
{
	cv::VideoCapture cap(0);
	cv::Mat img, imgHSV, imgMask;


	while (true)
	{
		cap.read(img);

		findColor(img);

		cv::imshow("Imag", img); 
		
		cv::waitKey(1);
	}
	return 0;
}