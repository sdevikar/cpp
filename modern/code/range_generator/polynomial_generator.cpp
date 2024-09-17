#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

struct Point
{
    double x;
    double y;
};

std::vector<Point> PopulatePolynomial(double start_x, double start_y, double step_x, double step_y, size_t count)
{
    std::vector<Point> polynomial(count);
    Point default_point{0.0, 0.0};
    std::fill(polynomial.begin(), polynomial.begin() + 10, default_point);
    std::generate_n(polynomial.begin(), count, [&default_point, step_x, step_y]()
                    {
        default_point.x += step_x;
        default_point.y -= step_y;
        return default_point; });

    return polynomial;
}

int main(void)
{
    double start_x = 0.0;
    double start_y = 0.0;
    double step_x = 1.0;
    double step_y = 2.0;
    size_t count = 10;
    std::vector<Point> polynomial = PopulatePolynomial(start_x, start_y, step_x, step_y, count);
    for (Point p : polynomial)
    {
        std::cout << p.x << "," << p.y << std::endl;
    }
    std::cout << "done!" << std::endl;
}
