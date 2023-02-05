// TO DO:
// Detect colours in  hsv space.
// Pass the hsv image in contour method to find the contours.
// Get x and y position of contours.
// Create a circle at those points.

#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

// Declaring globally (not recommended).
cv::Mat image;
cv::Point myPoint(0, 0);
std::vector<std::vector<int>> newPoints;

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

cv::Point getContours(cv::Mat imgMask)
{
	std::vector<std::vector<cv::Point>> contours;  // Define vector to store the contour values.
	std::vector<cv::Vec4i> hierarchy; // Define storage for number of sucessive contours.

	cv::findContours(imgMask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  // RETE_EXT -> Gets only outermost contour of the object.
	
	std::vector<std::vector<cv::Point>> contourPoly(contours.size());  // Store points of polygon formed around the target.
	std::vector<cv::Rect> contourBox(contours.size());  // Store rectangular coordinates of the polygon.

	// Loop to get points.
	for (int i = 0; i < contours.size(); i++)
	{
		int area = cv::contourArea(contours[i]); // Get area of each contour.
		//std::cout << area << std::endl;  // 

		// Filter only detectable contours.
		if (area > 1000)
		{
			float peri = cv::arcLength(contours[i], true);  // Get perimeter.
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);  // Approximate polygon surrounding the contour.
			contourBox[i] = cv::boundingRect(contourPoly[i]);  // Create a bounding rectangle.
			myPoint.x = (contourBox[i].x + contourBox[i].width) / 2;  // Store bounding rectangle points.
			myPoint.y = contourBox[i].y;

			cv::drawContours(image, contourPoly, i, cv::Scalar(255, 0, 255), 2);  // Draw bounding rectangle.
			cv::rectangle(image, contourBox[i].tl(), contourBox[i].br(), cv::Scalar(0, 255, 0), 1);
		}
	}
	return myPoint;
}

void drawOnCanvas(std::vector<std::vector<int>> newPoints, std::vector<cv::Scalar> myColourValues)
// Function to draw on canvas with the specified colours.
{
	for (int i = 0; i < newPoints.size(); i++)
	{
		cv::circle(image, cv::Point(newPoints[i][0], newPoints[i][1]), 10, myColourValues[newPoints[i][2]], cv::FILLED);
	}
}

std::vector<std::vector<int>> findColor(cv::Mat img)
// Function to find the speceified colours.
{
	cv::Mat imgHSV;

	cv::cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);

	// Loop to detect all the colours in the vector.
	for (int i = 0; i < myColours.size(); i++)
	{
		cv::Scalar lower(myColours[i][0], myColours[i][1], myColours[i][2]), upper(myColours[i][3], myColours[i][4], myColours[i][5]);

		cv::Mat imgMask;  // New mask for each colour.

		cv::inRange(imgHSV, lower, upper, imgMask);
		
		// Get contours of the masks:
		cv::Point myPoints = getContours(imgMask);
		if (myPoints.x != 0 && myPoints.y != 0)
		{
			newPoints.push_back({ myPoints.x, myPoints.y, i });
		}
	}

	return newPoints;
}

int main()
{
	cv::VideoCapture capture(0);
	
	while (true)
	{
		capture.read(image);

		newPoints = findColor(image);
		drawOnCanvas(newPoints, myColourValues);

		cv::imshow("Camera Image", image);
		cv::waitKey(1);
	}
	return 0;
}