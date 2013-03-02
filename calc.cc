/*
 * calc.cc
 */

#include "cv-common.hpp"

int main() {
    Mat img = imread("homography.jpg", CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        cerr << "Could not open image.\n";
    }

    imshow("Homography", img);
    waitKey(0);
    return 0;
}
