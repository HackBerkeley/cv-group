/*
 * calc.cc
 */

#include "cv-common.hpp"

static points pts;

static void onMouse(int evt, int x, int y, int, void*) {
    if (evt != CV_EVENT_LBUTTONDOWN) {
        return;
    }
    pts.push_back(Point(x, y));
    cout << "Point #" << pts.size() << ": " << x << " " << y << "\n";
    return;
}

int main() {
    Mat img = imread("homography.jpg", CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        cerr << "Could not open image.\n";
    }

    imshow("Homography", img);
    setMouseCallback("Homography", onMouse, 0);
    waitKey(0);
    return 0;
}
