#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

// Countors and boundary detection.

void get_contors(cv::Mat imgDil, cv::Mat imgDraw)
{
	std::vector<std::vector<cv::Point>> contours;  // Stores the vector of contour points.
	std::vector<cv::Vec4i> hierarchy; // Has 4 vector points.
	
	cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  // Get contours in hierarchical order. RETR_EXT -> Gets only external contours. CHAIN_APP_SIMPLE -> Stores the contour points.
	//cv::drawContours(imgDraw, contours, -1, cv::Scalar(255, 0, 255), 4);

	std::vector<std::vector<cv::Point>> contourPoly(contours.size());  // To store the approximate polygon coordinates.
	std::vector<cv::Rect> contourBox(contours.size());  // To store the bounding rectangle coorinates.

	std::string objType;

	for (int i = 0; i < contours.size(); i++)  // Looping through each contour and filtering according to area.
	{
		int area = cv::contourArea(contours[i]);
		std::cout << area << std::endl;

		// Remove Noise -> unwanted contours.
		if (area > 1000)
		{
			float peri = cv::arcLength(contours[i], true);  // gets arclength of each shape. true -> to get only enclosed bounds.
			cv::approxPolyDP(contours[i], contourPoly[i], 0.02 * peri, true);  // Approximates contours.
			cv::drawContours(imgDraw, contourPoly, i, cv::Scalar(255, 0, 255), 4);  // Draw contours.
		
			// To get the polygon enclosing shape.
			contourBox[i] = cv::boundingRect(contourPoly[i]);  // To get the bounding rectangle of polygon.
			cv::rectangle(imgDraw, contourBox[i].tl(), contourBox[i].br(), cv::Scalar(0, 255, 0), 1);  // Draws the bounding rectangle.

			// To identify the shape.
			int objCoordinates = (int)contourPoly[i].size(); // Get number of coordinates of polygon contours.

			if (objCoordinates == 3)
			{
				objType = "Triangle";
			}
			else if (objCoordinates == 4)
			{
				float aspratio = (float)contourBox[i].height / (float)contourBox[i].width;

				if (aspratio >= 0.95 && aspratio <= 1.05)
				{
					objType = "Square";
				}
				else
				{
					objType = "Rect";
				}
			}
			else if (objCoordinates > 4)
			{
				objType = "Circle";
			}

			cv::putText(imgDraw, objType, { contourBox[i].x, contourBox[i].y - 5 }, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 0));
		}
	}
}

int main()
{
	std::string path = "Your image path";
	cv::Mat img = cv::imread(path);

	// To detect the edges we first need to convert the image to dialated form to amplify the edges of the image - Preprocessing.

	cv::Mat imgGray, imgBlur, imgCanny, imgDil;

	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);  // Converting to gray image.
	cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);  // Blurring the image.
	cv::Canny(imgBlur, imgCanny, 25, 75);  // Detects edge.
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));  // Kernel to dialate image.
	cv::dilate(imgCanny, imgDil, kernel);  // Dialate image boundaries formed by Canny.

	get_contors(imgDil, img);


	cv::imshow("Image", img);
	//cv::imshow("Image Gray Bl/*ur", imgBlur);
	//cv::imshow("Dialated Image", imgDil);
	cv::waitKey(0);
	return 0;
}
