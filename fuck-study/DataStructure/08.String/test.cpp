#include "String.hpp"

#include <string>

int main(void)
{
    String s1 = "bcd";
    String s2 = "bcde";
    String s3 = "bc";
    String s4 = "ac";
    String s5 = "abc";
    String s6 = "ccd";
    String s7 = "bcd";

    std::cout << (s1 <= s2) << std::endl;
    std::cout << (s1 <= s3) << std::endl;
    std::cout << (s1 <= s4) << std::endl;
    std::cout << (s1 <= s5) << std::endl;
    std::cout << (s1 <= s6) << std::endl;
    std::cout << (s1 <= s7) << std::endl;

    std::cout << std::endl;

    std::string s11 = "bcd";
    std::string s12 = "bcde";
    std::string s13 = "bc";
    std::string s14 = "ac";
    std::string s15 = "abc";
    std::string s16 = "ccd";
    std::string s17 = "bcd";
    
    std::cout << (s11 <= s12) << std::endl;
    std::cout << (s11 <= s13) << std::endl;
    std::cout << (s11 <= s14) << std::endl;
    std::cout << (s11 <= s15) << std::endl;
    std::cout << (s11 <= s16) << std::endl;
    std::cout << (s11 <= s17) << std::endl;

    String ss1 = "hello";
    String ss2 = "world";
    String ss3 = "123";
    String ss4 = "444";
    std::cout << ss1 + ss2 << (ss1+ss2).size() <<  std::endl;
    std::cout << ss3 + "hello" << (ss3 + "hello").size() << std::endl;
    std::cout << "world" + ss4 << ("world" + ss4).size() << std::endl;

    String sss1;
    String sss2;

    std::cin >> sss1 >> sss2;
    std::cout << sss1 << " " << sss1.size() << std::endl;
    std::cout << sss2 << " " << sss2.size() << std::endl;

    return 0;
}