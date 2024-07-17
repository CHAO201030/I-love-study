#include "My_Vector"

template <typename _Tp>
void printVector(const Vector<_Tp> & vec)
{
    for(auto i = vec.begin(); i != vec.end(); i++)
    {
        std::cout << *i << " ";
    }

    std::cout << std::endl;
}

void test_int()
{
    std::cout << "=========================== Test_Vector<int> ============================" << std::endl;

    Vector<int> v1;
    Vector<int> v2(3);
    Vector<int> v3(6, 6);

    std::cout << "v1 size = "     << v1.size()
              << ", v1 max_size = " << v1.max_size()
              << ", capacity = "  << v1.capacity() << std::endl
              << "content : ";
    printVector(v1);

    std::cout << "v2 size = "     << v2.size()
              << ", v2 max_size = " << v2.max_size()
              << ", capacity = "  << v2.capacity() << std::endl
              << "content : ";
    printVector(v2);

    std::cout << "v3 size = "     << v3.size()
              << ", v3 max_size = " << v3.max_size()
              << ", capacity = "  << v3.capacity() << std::endl
              << "content : ";
    printVector(v3);

}

void test_double()
{
    std::cout << "=========================== Test_Vector<double> ============================" << std::endl;

    Vector<double> v1;
    Vector<double> v2(3.14);
    Vector<double> v3(6, 1.1);

    std::cout << "v1 size = "     << v1.size()
              << ", v1 max_size = " << v1.max_size()
              << ", capacity = "  << v1.capacity() << std::endl
              << "content : ";
    printVector(v1);

    std::cout << "v2 size = "     << v2.size()
              << ", v2 max_size = " << v2.max_size()
              << ", capacity = "  << v2.capacity() << std::endl
              << "content : ";
    printVector(v2);

    std::cout << "v3 size = "     << v3.size()
              << ", v3 max_size = " << v3.max_size()
              << ", capacity = "  << v3.capacity() << std::endl
              << "content : ";
    printVector(v3);
}

void test_push_pop()
{
    std::cout << "===========================    Test_push_pop    ============================" << std::endl;

    Vector<int> v1;

    v1.push_back(1);
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.push_back(2);
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.push_back(3);
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.push_back(4);
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.push_back(5);
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    std::cout << "--------- pop_back() ---------" << std::endl;

    v1.pop_back();
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.pop_back();
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.pop_back();
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.pop_back();
    std::cout << v1.size() << " " << v1.capacity() << std::endl;

    v1.pop_back();
    std::cout << v1.size() << " " << v1.capacity() << std::endl;
}

int main()
{
    test_int();
    
    test_double();

    test_push_pop();

    Vector<std::string> vstr(3, "123");
    printVector(vstr);

    auto it = vstr.begin();
    std::cout << *it << std::endl;
    return 0;
}