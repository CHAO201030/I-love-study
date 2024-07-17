#include "My_SelectSort"

template <typename T>
struct Compare
{
    bool operator()(const T & lhs, const T & rhs)
    {
        return lhs < rhs;
    }
};

class Point
{
public:
    Point(int x = 0, int y = 0):_x(x), _y(y){};
    ~Point() = default;
    friend bool operator<(const Point & lhs, const Point & rhs);
    friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
    int _x;
    int _y;
};

bool operator<(const Point & lhs, const Point & rhs)
{
    return lhs._x < rhs._x;
}

std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
    os << "(" << rhs._x << ", " << rhs._y << ")";

    return os;
}

void test_int_up()
{
    std::cout << "==================== Test_int::up ====================" << std::endl;

    int arr[10] = {1, 5, 44, 21, 82 ,0 ,91, 32, 99, 101};

    Compare<int> cmp;
    SelectSort<int, Compare<int>> ms(arr, sizeof(arr)/sizeof(arr[0]), cmp);

    ms.sort();

    ms.printResult();
}

void test_int_down()
{
    std::cout << "==================== Test_std::down ====================" << std::endl;

    int arr[10] = {1, 5, 44, 21, 82 ,0 ,91, 32, 99, 101};

    SelectSort<int, std::greater<int>> ms(arr, sizeof(arr)/sizeof(arr[0]), std::greater<int>());

    ms.sort();

    ms.printResult();
}

void test_point_up()
{
    std::cout << "==================== Test_point::up ====================" << std::endl;

    Point arrP[10] = {{1, 3}, {2, 4}, {-1, 5}, {80, 10}, {99, 20},
                      {3, 1}, {4, 2}, {5, -1}, {10, 80}, {20, 99}};

    Compare<Point> cmpP;

    SelectSort<Point, Compare<Point>> mqP(arrP, sizeof(arrP)/sizeof(arrP[0]), cmpP);
    mqP.sort();

    mqP.printResult();
}

int main(void)
{
    test_int_up();
    test_int_down();
    test_point_up();
    
    return 0;
}