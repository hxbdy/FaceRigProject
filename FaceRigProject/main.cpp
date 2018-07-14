//éƒ–èä»‰Ã‚Ìƒ‚ƒfƒ‹‚É‚¨‚¢‚ÄƒOƒŠ[ƒ“ƒoƒbƒN‚ðíœ‚µ‚Ä”’‚É‚¨‚«‚©‚¦‚é
//ƒAƒ‹ƒtƒ@’l‚ð‚Ç‚¤‚É‚©‚µ‚Ä”wŒi‚ð“§‰ß‚µ‚½‚¢

#include "opencv2\opencv.hpp"

float max(int a, int b) {
	return float(a > b ? a : b);
}

float min(int a, int b) {
	return float(a > b ? b : a);
}

//”wŒi“§‰ß
//RGB(0,255,0)‚ð“§‰ß
cv::Mat trans2bg(cv::Mat source) {
	cv::Mat alpha_image = cv::Mat(source.size(), CV_8UC3);
	cv::cvtColor(source, alpha_image, CV_RGB2RGBA);
	for (int y = 0; y < alpha_image.rows; ++y) {
		for (int x = 0; x < alpha_image.cols; ++x) {
			cv::Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			if (px[1] == 255) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}
	}
	return alpha_image;
}

//”wŒi”»’è
//bool isBG(cv::Mat* source,int x,int y){}

int main() {
	cv::Mat frame;
	cv::Mat dst;
	cv::VideoCapture cap;
	int blue, green, red;
	float m;
	cap.open(2);
	if (!cap.isOpened()) {
		std::cout << "ERROR:Camera cannot be enable" << std::endl;
		exit(-1);
	}
	else {
		std::cout << "SUCCESS:Camera can be enable" << std::endl;
	}
	cap >> frame;
	dst=frame.clone();
	cv::imshow("dst", trans2bg(dst));
	//cv::imwrite("dst.png", trans2bg(dst));
	cv::waitKey(0);
	std::cout << "cols=" << frame.cols << " rows=" << frame.rows << std::endl;
	std::cout << "channels=" << frame.channels() << std::endl;
	while (true) {
		cap >> frame;
		dst = frame.clone();
		for (int y = 0; y < dst.rows; y++) {
			for (int x = 0; x < dst.cols; x++) {
				blue  = int(dst.data[y * dst.step + x * dst.elemSize() + 0]);
				green = int(dst.data[y * dst.step + x * dst.elemSize() + 1]);
				red   = int(dst.data[y * dst.step + x * dst.elemSize() + 2]);
				m = max(max(blue, green), red);
				if (m == 0) m = 1.0;
				if(red/m<0.80){
					dst.data[y * dst.step + x * dst.elemSize() + 0] = 255;
					dst.data[y * dst.step + x * dst.elemSize() + 1] = 255;
					dst.data[y * dst.step + x * dst.elemSize() + 2] = 255;
				}
			}
		}
		cv::imshow("frame", frame);
		cv::imshow("dst", dst);
		if (cv::waitKey(1)==113) {
			break;
		}
	}
	cv::destroyAllWindows();

	return 0;
}