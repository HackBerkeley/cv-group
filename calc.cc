/*
 * calc.cc
 */

#include <Eigen/Dense>
using namespace Eigen;

#include "cv-common.hpp"

static points pts;

/* Bottom left. */
static float x1 = 0;
static float y1hack = 0;

/* Bottom right. */
static float x2 = 1;
static float y2 = 0;

/* Top left. */
static float x3 = 0;
static float y3 = 1;

/* Top right. */
static float x4 = 1;
static float y4 = 1;

static void compute_homography() {
    /* Compute the homography matrix. */
    MatrixXd A(8, 8);
    A << 
        x1, y1hack, 1, 0, 0, 0, -pts[0].x * x1, -pts[0].x * y1hack,
        0, 0, 0, x1, y1hack, 1, -pts[0].y * x1, -pts[0].y * y1hack,
        x2, y2, 1, 0, 0, 0, -pts[1].x * x2, -pts[1].x * y2,
        0, 0, 0, x2, y2, 1, -pts[1].y * x2, -pts[1].y * y2,
        x3, y3, 1, 0, 0, 0, -pts[2].x * x3, -pts[2].x * y3,
        0, 0, 0, x3, y3, 1, -pts[2].y * x3, -pts[2].y * y3,
        x4, y4, 1, 0, 0, 0, -pts[3].x * x4, -pts[3].x * y4,
        0, 0, 0, x4, y4, 1, -pts[3].y * x4, -pts[3].y * y4;
    cout << "A = \n" << A << endl;

    MatrixXd b(8, 1);
    b <<
        pts[0].x,
        pts[0].y,
        pts[1].x,
        pts[1].y,
        pts[2].x,
        pts[2].y,
        pts[3].x,
        pts[3].y;
    cout << "b = \n" << b << endl;

    MatrixXd x(8, 1);
    x = A.inverse() * b;
    cout << "x = \n" << x << endl;

    MatrixXd H(3, 3);
    H << x(0, 0), x(1, 0), x(2, 0),
         x(3, 0), x(4, 0), x(5, 0),
         x(6, 0), x(7, 0), 1;
    cout << "H = \n" << H << endl;

    MatrixXd Q = H.inverse();
    cout << "Q = \n" << Q << endl;

    Point c = pts[4];
    float cx = (Q(0, 0)*c.x + Q(0, 1)*c.y + Q(0, 2))
            / (Q(2, 0)*c.x + Q(2, 1)*c.y + Q(2, 2));
    float cy = (Q(1, 0)*c.x + Q(1, 1)*c.y + Q(1, 2))
            / (Q(2, 0)*c.x + Q(2, 1)*c.y + Q(2, 2));
    cout << "Guess for the center of the phone in 'real-world' coordinates;\n"
        "cx = " << cx << ", cy = " << cy << endl;
}

static void onMouse(int evt, int x, int y, int, void*) {
    if (evt != CV_EVENT_LBUTTONDOWN) {
        return;
    }
    pts.push_back(Point(x, y));
    cout << "Point #" << pts.size() << ": " << x << " " << y << ".\n";
    if (pts.size() == 5) {
        compute_homography();
    }
    return;
}

int main() {
    Mat img = imread("homography.jpg", CV_LOAD_IMAGE_COLOR);
    if (!img.data) {
        cerr << "Could not open image.\n";
        return 1;
    }
    imshow("Homography", img);

    cout << "Select the bottom-left, bottom-right, top-left, and top-right "
            "corners in that order. You get to pick what those orientations "
            "mean.\n";
    setMouseCallback("Homography", onMouse, 0);
    waitKey(0);
    return 0;
}
