#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool compareX(Point p1, Point p2) {
    return p1.x < p2.x;
}

bool compareY(Point p1, Point p2) {
    return p1.y < p2.y;
}

double closestPairDistance(vector<Point>& points, int left, int right) {
    if (right - left <= 3) {
        double minDist = numeric_limits<double>::max();
        for (int i = left; i <= right; i++) {
            for (int j = i + 1; j <= right; j++) {
                minDist = min(minDist, distance(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    double dl = closestPairDistance(points, left, mid);
    double dr = closestPairDistance(points, mid + 1, right);
    double d = min(dl, dr);

    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    double minStripDist = d;
    int stripSize = strip.size();
    for (int i = 0; i < stripSize; i++) {
        for (int j = i + 1; j < stripSize && (strip[j].y - strip[i].y) < minStripDist; j++) {
            minStripDist = min(minStripDist, distance(strip[i], strip[j]));
        }
    }

    return min(d, minStripDist);
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        char comma;
        cin >> points[i].x >> comma >> points[i].y;
    }

    sort(points.begin(), points.end(), compareX);

    double closestDistance = closestPairDistance(points, 0, n - 1);

    cout << "La distancia mas corta es: " << closestDistance << endl;

    return 0;
}