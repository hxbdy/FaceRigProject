//城ヶ崎莉嘉のモデルにおいてグリーンバックを削除して白におきかえる
//アルファ値をどうにかして背景を透過したい

#include "opencv2\opencv.hpp"

float max(int a, int b) {
	return float(a > b ? a : b);
}

float min(int a, int b) {
	return float(a > b ? b : a);
}

int main() {
	cv::Mat frame;
	cv::Mat dst;
	cv::VideoCapture cap;
	int blue, green, red;
	float m;
	cap.open(0);
	if (!cap.isOpened()) {
		std::cout << "ERROR:Camera cannot be enable" << std::endl;
		exit(-1);
	}
	else {
		std::cout << "SUCCESS:Camera can be enable" << std::endl;
	}
	cap >> frame;
	dst=frame.clone();
	cv::imshow("dst", dst);
	cv::waitKey(1);
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