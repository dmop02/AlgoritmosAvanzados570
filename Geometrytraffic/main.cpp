#include <iostream>
#include <vector>

struct Point {
    double x, y;
};

bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    double o1 = (q1.y - p1.y) * (p2.x - p1.x) - (q1.x - p1.x) * (p2.y - p1.y);
    double o2 = (q1.y - p1.y) * (q2.x - p1.x) - (q1.x - p1.x) * (q2.y - p1.y);
    double o3 = (q2.y - p2.y) * (p1.x - p2.x) - (q2.x - p2.x) * (p1.y - p2.y);
    double o4 = (q2.y - p2.y) * (q1.x - p2.x) - (q2.x - p2.x) * (q1.y - p2.y);

    if (o1 * o2 < 0 && o3 * o4 < 0) {
        return true;
    }

    return false;
}

int main() {
    int n;
    std::cout << "Enter the number of test cases: ";
    std::cin >> n;

    std::vector<bool> results;

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4;

        std::cout << "Enter x1 y1 x2 y2 x3 y3 x4 y4 for test case " << i+1 << ": ";
        std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        Point p1 = {x1, y1};
        Point q1 = {x2, y2};
        Point p2 = {x3, y3};
        Point q2 = {x4, y4};

        bool intersect = doIntersect(p1, q1, p2, q2);
        results.push_back(intersect);
    }

    for (bool intersect : results) {
        std::cout << (intersect ? "true" : "false") << std::endl;
    }

    return 0;
}