//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <boost/lexical_cast.hpp>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
//int main(int argc, char** argv)
//{
//	if (argc != 3)
//	{
//		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
//		return -1;
//	}
//
//	Mat image;
//	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
//	ifstream ifs(argv[2]);
//
//	if (!image.data)                              // Check for invalid input
//	{
//		cout << "Could not open or find the image" << endl;
//		return -1;
//	}
//
//	if (ifs.fail())
//	{
//		cout << "Could not open of find the text" << endl;
//		return -1;
//	}
//
//	vector<Point2f> point;
//	for (string line; getline(ifs, line);)
//	{
//		istringstream s(line);
//		Point2f pt;
//		s >> pt.x >> pt.y;
//		point.push_back(pt);
//	}
//
//	for (int i = 0; i < point.size(); i+=4)
//	{
//		line(image, point[i], point[i + 1], Scalar(255, 0, 0));
//		line(image, point[i + 1], point[i + 2], Scalar(0, 0, 255));
//		line(image, point[i + 2], point[i + 3], Scalar(255, 0, 0));
//		line(image, point[i + 3], point[i], Scalar(0, 0, 255));
//		
//	}
//
//	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
//	imshow("Display window", image);                   // Show our image inside it.
//
//	waitKey(0);                                          // Wait for a keystroke in the window
//	return 0;
//}

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <boost/lexical_cast.hpp>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
//typedef struct {
//	float x;
//	float y;
//	float z;
//	float rgb;
//	int index;
//} PCDFile;
//
//// Draw grasp rectangle
//void drawGraspRectangle(Mat& image, vector<Point2f>& point)
//{
//	for (int i = 0; i < point.size(); i+=4)
//	{
//		line(image, point[i], point[i + 1], Scalar(255, 0, 0));
//		line(image, point[i + 1], point[i + 2], Scalar(0, 0, 255));
//		line(image, point[i + 2], point[i + 3], Scalar(255, 0, 0));
//		line(image, point[i + 3], point[i], Scalar(0, 0, 255));
//	}
//
//}
//
//// MAIN FUNCTION
//int main(int argc, char** argv)
//{
//	if (argc != 2)
//	{
//		cout << "Usage: *.exe fileIndex" << endl;
//		return -1;
//	}
//
//	String fileIndex = argv[1];
//
//	// Read the point cloud data
//	String filename = "pcd0" + fileIndex + ".txt";
//	ifstream ifs(filename);
//	if (ifs.fail())
//	{
//		cout << "Could not open point cloud data" << endl;
//		return -1;
//	}
//
//	// Read the positive grasp rectangle data
//	filename = "pcd0" + fileIndex + "cpos.txt";
//	ifstream ifs2(filename);
//	if (ifs2.fail())
//	{
//		cout << "Could not open the positive grasp ractangle data" << endl;
//		return -1;
//	}
//
//	// Read the negative grasp rectangle data
//	filename = "pcd0" + fileIndex + "cneg.txt";
//	ifstream ifs3(filename);
//	if (ifs3.fail())
//	{
//		cout << "Could not open the negative grasp ractangle data" << endl;
//		return -1;
//	}
//
//	Mat depth32F_img = Mat(480, 640, CV_32FC1);
//	Mat depth_img = Mat(480, 640, CV_8UC1);
//	
//	// Read color image
//	filename = "pcd0" + fileIndex + "r.png";
//	Mat color_img = imread(filename);
//
//	// Make depth image from point cloud data
//	vector<PCDFile> pcd;
//	int i = 1;
//	int row, col;
//	for (string line; getline(ifs, line);)
//	{
//		if (i > 10) {
//			istringstream s(line);
//			PCDFile tmp;
//			s >> tmp.x >> tmp.y >> tmp.z >> tmp.rgb >> tmp.index;
//			row = floor(tmp.index / 640) + 1;
//			col = (tmp.index % 640) + 1;
//			
//			//depth32F_img.at<float>(row - 1, col - 1) = tmp.x + tmp.z;
//			depth32F_img.at<float>(row - 1, col - 1) = tmp.z;
//			//depth32F_img.at<float>(row - 1, col - 1) = tmp.x;
//			pcd.push_back(tmp);
//		}
//		i++;
//	}
//	cv::normalize(depth32F_img, depth_img, 0, 255, CV_MINMAX, CV_8UC1);
//
//	// Store the position of the positive grasp rectangle 
//	vector<Point2f> point;
//	for (string line; getline(ifs2, line);)
//	{
//		istringstream s(line);
//		Point2f pt;
//		s >> pt.x >> pt.y;
//		point.push_back(pt);
//	}
//
//	// Store the position of the negative grasp rectangle
//	vector<Point2f> negativePoint;
//	for (string line; getline(ifs3, line);)
//	{
//		istringstream s(line);
//		Point2f pt;
//		s >> pt.x >> pt.y;
//		negativePoint.push_back(pt);
//	}
//	
//	// Show raw images
//	namedWindow("Raw depth image", WINDOW_AUTOSIZE);
//	namedWindow("Raw color image", WINDOW_AUTOSIZE);
//	imshow("Raw depth image", depth_img);
//	imshow("Raw color image", color_img);
//
//	Mat neg_depth_img = depth_img.clone();
//	Mat neg_color_img = color_img.clone();
//
//	// Draw positive grasp rectangle on images
//	drawGraspRectangle(depth_img, point);
//	drawGraspRectangle(color_img, point);
//
//	// Show images with positive rectangles
//	namedWindow("Depth image with grasp rectangle", WINDOW_AUTOSIZE);
//	namedWindow("Color image with grasp rectangle", WINDOW_AUTOSIZE);
//	imshow("Depth image with grasp rectangle", depth_img);
//	imshow("Color image with grasp rectangle", color_img);
//
//	// Draw negative grasp rectangle on images
//	drawGraspRectangle(neg_depth_img, negativePoint);
//	drawGraspRectangle(neg_color_img, negativePoint);
//
//	// Show images with rectangles
//	namedWindow("Depth image with negative grasp rectangle", WINDOW_AUTOSIZE);
//	namedWindow("Color image with negative grasp rectangle", WINDOW_AUTOSIZE);
//	imshow("Depth image with negative grasp rectangle", neg_depth_img);
//	imshow("Color image with negative grasp rectangle", neg_color_img);
//	
//	waitKey(0);
//
//	return 0;
//}

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

typedef struct {
	float x;
	float y;
	float z;
	float rgb;
	int index;
} PCDFile;

cv::Point2f rotate2d(const cv::Point2f& inPoint, const double& angRad)
{
	cv::Point2f outPoint;
	//CW rotation
	outPoint.x = std::cos(angRad)*inPoint.x - std::sin(angRad)*inPoint.y;
	outPoint.y = std::sin(angRad)*inPoint.x + std::cos(angRad)*inPoint.y;
	return outPoint;
}

cv::Point2f rotatePoint(const cv::Point2f& inPoint, const cv::Point2f& center, const double& angRad)
{
	return rotate2d(inPoint - center, angRad) + center;
}

float angleBetween(const Point &v1, const Point &v2)
{
	float len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
	float len2 = sqrt(v2.x * v2.x + v2.y * v2.y);

	float dot = v1.x * v2.x + v1.y * v2.y;

	float a = dot / (len1 * len2);

	if (a >= 1.0)
		return 0.0;
	else if (a <= -1.0)
		return 3.1415;
	else
		return acos(a); // 0..PI
}

// Draw grasp rectangle
void drawGraspRectangle(Mat& image, vector<Point2f>& point)
{
	Mat save = image.clone();
	Mat original = image.clone();
	//cvtColor(image, image, CV_BGR2GRAY);
	Canny(image, image, 10, 90, 3);
	for (int i = 0; i < point.size(); i += 4)
	{
		Mat copy = original.clone();
		/*	line(image, point[i], point[i + 1], Scalar(255, 0, 0));
		line(image, point[i + 1], point[i + 2], Scalar(0, 0, 255));
		line(image, point[i + 2], point[i + 3], Scalar(255, 0, 0));
		line(image, point[i + 3], point[i], Scalar(0, 0, 255));*/
		//line(image, point[i], point[i + 1], Scalar(0, 0, 255));
		//line(image, point[i + 1], point[i + 2], Scalar(0, 0, 255));
		//line(image, point[i + 2], point[i + 3], Scalar(0, 0, 255));
		//line(image, point[i + 3], point[i], Scalar(0, 0, 255));

		vector<Point2f> src;
		src.push_back(point[i]);
		src.push_back(point[i + 1]);
		src.push_back(point[i + 2]);
		src.push_back(point[i + 3]);
		vector<Point2f> dst;
		dst.push_back(Point2f(0, 0));
		dst.push_back(Point2f(0, 300));
		dst.push_back(Point2f(300, 300));
		dst.push_back(Point2f(300, 0));

		Mat m = getPerspectiveTransform(src, dst);
		Mat oman;
		warpPerspective(image, oman, m, Size(300, 300));
		//cvtColor(oman, oman, CV_BGR2GRAY);
		//blur(oman, oman, Size(3, 3));
		//Canny(oman, oman, 0, 30, 3);
		String omanman = "oman" + to_string(i + 1);
		imshow(omanman, oman);

		//line(copy, point[i], point[i + 1], Scalar(255, 0, 0));
		//line(copy, point[i + 1], point[i + 2], Scalar(0, 0, 255));
		//line(copy, point[i + 2], point[i + 3], Scalar(255, 0, 0));
		//line(copy, point[i + 3], point[i], Scalar(0, 0, 255));
		////if (i == 1) {
		//	Vec2f v = Vec2f(point[i].x - point[i + 1].x, point[i].y - point[i + 1].y);
		//	float angle = angleBetween(Point(v[0], v[1]), Point(1, 0));
		//	angle = angle * 180.0f / 3.1415;
		//	if (angle >= 90)
		//		angle = 180.0f - angle;
		//	//RotatedRect rect = RotatedRect(point[i + 3], point[i + 2], point[i + 1]);
		//	//cout << rect.angle << endl;
		//	Mat affine_matrix = getRotationMatrix2D(point[i], angle, 1.0f);
		//	Mat rotated_img;
		//	Mat rotated_img2;
		//	warpAffine(copy, rotated_img, affine_matrix, image.size());
		//	warpAffine(save, rotated_img2, affine_matrix, image.size());
		//	//cvtColor(rotated_img2, rotated_img2, CV_BGR2GRAY);
		//	GaussianBlur(rotated_img2, rotated_img2,Size(9,7),8,6);
		//	equalizeHist(rotated_img2, rotated_img2);
		//	//threshold(rotated_img2, rotated_img2, 210, 255, CV_THRESH_BINARY);
		//	String window = "Rotated image" + to_string(i + 1) + ".jpg";
		//	//if(i == 0)
		//	Point2f rotated_pt = rotatePoint(point[i + 2], point[i], -angle * 3.1415 / 180.0f);
		//	Mat cut_img(rotated_img2, Rect(rotated_pt, point[i]));
		//	//equalizeHist(cut_img, cut_img);
		//	imwrite(window, cut_img);
		//	//imwrite(window, rotated_img2);
		//	//if(point[i].x < rotated_pt.x)
		//		//Point2f 
		//	window = "Rotated image" + to_string(i + 1);
		//	circle(rotated_img, rotated_pt,10,Scalar(255,255,0));
		//	circle(rotated_img, point[i],10,Scalar(255,255,0));
		//	//String window = "Rotated image" + to_string(i + 1);
		//	cout << window << endl;
		//	cout << angle << endl;
		//	imshow(window, rotated_img);
		//}
	}

}

// ---------------------------------------------------------------------------------
// MAIN FUNCTION
int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cout << "Usage example: extractor.exe 770" << endl;
		return -1;
	}

	String fileIndex = argv[1];
	// Read the point cloud data
	String filename = "pcd0" + fileIndex + ".txt";
	ifstream ifs(filename);
	if (ifs.fail())
	{
		cout << "Could not open point cloud data" << endl;
		return -1;
	}

	// Read the positive grasp rectangle data
	filename = "pcd0" + fileIndex + "cpos.txt";
	ifstream ifs2(filename);
	if (ifs2.fail())
	{
		cout << "Could not open the positive grasp ractangle data" << endl;
		return -1;
	}

	// Read the negative grasp rectangle data
	filename = "pcd0" + fileIndex + "cneg.txt";
	ifstream ifs3(filename);
	if (ifs3.fail())
	{
		cout << "Could not open the negative grasp ractangle data" << endl;
		return -1;
	}

	Mat depth32F_img = Mat(480, 640, CV_32FC1);
	Mat depth_img = Mat(480, 640, CV_8UC1);

	// Read color image
	filename = "pcd0" + fileIndex + "r.png";
	Mat color_img = imread(filename);

	// Make depth image from point cloud data
	vector<PCDFile> pcd;
	int i = 1;
	int row, col;
	for (string line; getline(ifs, line);)
	{
		if (i > 10) {
			istringstream s(line);
			PCDFile tmp;
			s >> tmp.x >> tmp.y >> tmp.z >> tmp.rgb >> tmp.index;
			row = floor(tmp.index / 640) + 1;
			col = (tmp.index % 640) + 1;

			//depth32F_img.at<float>(row - 1, col - 1) = tmp.x + tmp.z;
			depth32F_img.at<float>(row - 1, col - 1) = tmp.z;
			//depth32F_img.at<float>(row - 1, col - 1) = tmp.x;
			pcd.push_back(tmp);
		}
		i++;
	}
	cv::normalize(depth32F_img, depth_img, 0, 255, CV_MINMAX, CV_8UC1);

	// Store the position of the positive grasp rectangle 
	vector<Point2f> point;
	for (string line; getline(ifs2, line);)
	{
		istringstream s(line);
		Point2f pt;
		s >> pt.x >> pt.y;
		point.push_back(pt);
	}

	// Store the position of the negative grasp rectangle
	vector<Point2f> negativePoint;
	for (string line; getline(ifs3, line);)
	{
		istringstream s(line);
		Point2f pt;
		s >> pt.x >> pt.y;
		negativePoint.push_back(pt);
	}

	// Show raw images
	namedWindow("Raw depth image", WINDOW_AUTOSIZE);
	//namedWindow("Raw color image", WINDOW_AUTOSIZE);
	imshow("Raw depth image", depth_img);
	//imshow("Raw color image", color_img);

	Mat neg_depth_img = depth_img.clone();
	Mat neg_color_img = color_img.clone();

	// Draw positive grasp rectangle on images
	drawGraspRectangle(depth_img, point);
	//drawGraspRectangle(color_img, point);

	// Show images with positive rectangles
	namedWindow("Depth image with grasp rectangle", WINDOW_AUTOSIZE);
	//namedWindow("Color image with grasp rectangle", WINDOW_AUTOSIZE);
	imshow("Depth image with grasp rectangle", depth_img);
	//imshow("Color image with grasp rectangle", color_img);
	//imwrite("training.jpg", color_img);
	//// Draw negative grasp rectangle on images
	//drawGraspRectangle(neg_depth_img, negativePoint);
	//drawGraspRectangle(neg_color_img, negativePoint);

	//// Show images with rectangles
	//namedWindow("Depth image with negative grasp rectangle", WINDOW_AUTOSIZE);
	//namedWindow("Color image with negative grasp rectangle", WINDOW_AUTOSIZE);
	//imshow("Depth image with negative grasp rectangle", neg_depth_img);
	//imshow("Color image with negative grasp rectangle", neg_color_img);

	waitKey(0);

	return 0;
}


//#include <iostream>
//#include <pcl/io/pcd_io.h>
//#include <pcl/point_types.h>
//#include <pcl/visualization/cloud_viewer.h>
//
//int
//main(int argc, char** argv)
//{
//	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
//	pcl::visualization::CloudViewer viewer("Cloud Viewer");
//
//	if (pcl::io::loadPCDFile<pcl::PointXYZ>("0117.pcd", *cloud) == -1) //* load the file
//	{
//		PCL_ERROR("Couldn't read file test_pcd.pcd \n");
//		return (-1);
//	}
//	
//	for (size_t i = 0; i < cloud->points.size(); ++i)
//	{
//		cloud->points[i].x = 0.001 *cloud->points[i].x;
//		cloud->points[i].y = 0.001 *cloud->points[i].y;
//		cloud->points[i].z = 0.001 *cloud->points[i].z;
//	}
//
//	viewer.showCloud(cloud);
//	while (!viewer.wasStopped())
//	{
//		
//	}
//	return (0);
//}

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <boost/lexical_cast.hpp>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//using namespace cv;
//using namespace std;
//
//typedef struct {
//	float x;
//	float y;
//	float z;
//	float rgb;
//	int index;
//} PCDFile;
//
//cv::Point2f rotate2d(const cv::Point2f& inPoint, const double& angRad)
//{
//	cv::Point2f outPoint;
//	//CW rotation
//	outPoint.x = std::cos(angRad)*inPoint.x - std::sin(angRad)*inPoint.y;
//	outPoint.y = std::sin(angRad)*inPoint.x + std::cos(angRad)*inPoint.y;
//	return outPoint;
//}
//
//cv::Point2f rotatePoint(const cv::Point2f& inPoint, const cv::Point2f& center, const double& angRad)
//{
//	return rotate2d(inPoint - center, angRad) + center;
//}
//
//float angleBetween(const Point &v1, const Point &v2)
//{
//	float len1 = sqrt(v1.x * v1.x + v1.y * v1.y);
//	float len2 = sqrt(v2.x * v2.x + v2.y * v2.y);
//
//	float dot = v1.x * v2.x + v1.y * v2.y;
//
//	float a = dot / (len1 * len2);
//
//	if (a >= 1.0)
//		return 0.0;
//	else if (a <= -1.0)
//		return 3.1415;
//	else
//		return acos(a); // 0..PI
//}
//
//// Draw grasp rectangle
//void drawGraspRectangle(Mat& image, vector<Point2f>& point)
//{
//	Mat save = image.clone();
//	Mat original = image.clone();
//	for (int i = 0; i < point.size(); i += 4)
//	{
//		Mat copy = original.clone();
//		line(image, point[i], point[i + 1], Scalar(255, 0, 0));
//		line(image, point[i + 1], point[i + 2], Scalar(0, 0, 255));
//		line(image, point[i + 2], point[i + 3], Scalar(255, 0, 0));
//		line(image, point[i + 3], point[i], Scalar(0, 0, 255));
//		
//		line(copy, point[i], point[i + 1], Scalar(255, 0, 0));
//		line(copy, point[i + 1], point[i + 2], Scalar(0, 0, 255));
//		line(copy, point[i + 2], point[i + 3], Scalar(255, 0, 0));
//		line(copy, point[i + 3], point[i], Scalar(0, 0, 255));
//		//if (i == 1) {
//			Vec2f v = Vec2f(point[i].x - point[i + 1].x, point[i].y - point[i + 1].y);
//			float angle = angleBetween(Point(v[0], v[1]), Point(1, 0));
//			angle = angle * 180.0f / 3.1415;
//			if (angle >= 90)
//				angle = 180.0f - angle;
//			//RotatedRect rect = RotatedRect(point[i + 3], point[i + 2], point[i + 1]);
//			//cout << rect.angle << endl;
//			Mat affine_matrix = getRotationMatrix2D(point[i], angle, 1.0f);
//			Mat rotated_img;
//			Mat rotated_img2;
//			warpAffine(copy, rotated_img, affine_matrix, image.size());
//			warpAffine(save, rotated_img2, affine_matrix, image.size());
//			//cvtColor(rotated_img2, rotated_img2, CV_BGR2GRAY);
//			equalizeHist(rotated_img2, rotated_img2);
//			threshold(rotated_img2, rotated_img2, 210, 255, CV_THRESH_BINARY);
//			if(i == 0)
//			imwrite("test.jpg", rotated_img2);
//			Point2f rotated_pt = rotatePoint(point[i + 2], point[i], -angle * 3.1415 / 180.0f);
//			//if(point[i].x < rotated_pt.x)
//				//Point2f 
//			circle(rotated_img, rotated_pt,10,Scalar(255,255,0));
//			circle(rotated_img, point[i],10,Scalar(255,255,0));
//			String window = "Rotated image" + to_string(i + 1);
//			cout << window << endl;
//			cout << angle << endl;
//			imshow(window, rotated_img);
//		//}
//	}
//
//}
//
//// MAIN FUNCTION
//int main(int argc, char** argv)
//{
//	Mat result = imread("result3.jpg");
//
//	if (result.empty())
//		return -1;
//	rectangle(result, Point(331, 296), Point(355, 310),Scalar(0,0,255));
//	imshow("result1", result);
//	imwrite("test2.jpg", result);
//	waitKey(0);
//
//	return 0;
//}