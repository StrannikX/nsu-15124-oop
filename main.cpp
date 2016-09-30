# include <iostream>
# include "String.h"

int main(int argc, char** argv) {
    String str("Hello world!");
    String str2;
    str2 = "ab";
    std::cout << str << std::endl;
    std::cout << str + str2 << std::endl;
    str2 += "c";
    str2 += str;
    str2[4] = 'f';
    std::cout << str + str2 << std::endl;
    std::cout << str2.length() << std::endl;
    String str3;
    str2 += str3;
    std::cout << str + str3 + str2 << std::endl;
    return 0;
}
