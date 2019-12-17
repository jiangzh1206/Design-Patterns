// DesignPatterns.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#ifdef BOOST_ALL_NO_LIB
#undef BOOST_ALL_NO_LIB
#endif

#include <iostream>
#include <fstream>
#include "../MaybeMonad/maybemonad.h"
#include "../Iterator/iterator_j.h"

void modify_file(const std::string& path)
{
    std::fstream fs(path, std::ios::binary | std::ios::out | std::ios::in);
    if (!fs.is_open()) {
        return;
    }
    
    std::string pre = "/CIP3TransferFilmCurveData";
    std::string line;
    size_t size = 0;
    while (std::getline(fs, line)) {
        if (line.find(pre) == std::string::npos) {
            size += (line.size() + 1);
        }
        else {
            fs.seekp(size, std::ios::beg);
            // 覆盖行的字节数应该和line的相等
            std::string write_line = "/CIP3TransferFilmCurveData  [0.0   0.0   0.0   0.0   0.35   0.5   0.5   0.65  0.0   0.0   1.0    1.0 ] def\r\n";
            fs.write(write_line.c_str(), write_line.size());
            break;
        }
    }

}


int main()
{
    //modify_file("E:\\test.ppf");

    //test();

    test_43534();

    int a;
    std::cin >> a;
}
