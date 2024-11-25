#include "Xstring.h"
using namespace std;

int main()
{
    using namespace base::XString;
    std::cout << "测试删除字符串左边指定字符：" << std::endl;
    char test1[] = "___The people's republic of China___";
    std::cout << "char* before: " << test1 << endl;
    LTrim(test1, '_');
    std::cout << "char* after: " << test1 << endl;

    std::string test2 = "___The people's republic of China___";
    std::cout << "str before: " << test2 << endl;
    LTrim(test2, '_');
    std::cout << "str after: " << test2 << endl;

    std::cout << "测试删除字符串右边指定字符:  " << std::endl;
    
    std::cout << "char* before: " << test1 << endl;
    RTrim(test1, '_');
    std::cout << "char* after: " << test1 << endl;

    std::cout << "str before: " << test2 << endl;
    std::cout << "str after: " << RTrim(test2, '_') << endl;

    std::cout << "测试大小写转换:" << std::endl;

    std::cout << "char* before: " << test1 << std::endl;
    std::cout << "char* after: " << ToUpper(test1) << std::endl;


    std::cout << "str before: " << test2 << std::endl;
    std::cout << "str after: " << ToUpper(test2) << std::endl;
    std::cout << "char* before: " << test1 << std::endl;
    std::cout << "char* after: " << ToLower(test1) << std::endl;

    std::cout << "str before: " << test2 << std::endl;
    std::cout << "str after: " << ToLower(test2) << std::endl;

    std::cout << "测试指定字符串替换:" << std::endl;
    std::cout << "char* before: " << test1 << std::endl;
    ReplaceStr(test1, "china", "CHINA!");
    std::cout << "char* after: " << test1 << std::endl;

    std::cout << "str before: " << test2 << std::endl;
    ReplaceStr(test2, "china", "CHINA!");
    std::cout << "str after: " << test2 << std::endl;

    std::cout<< "测试从字符串中提取数字等:" << std::endl;
    std::string test3 = "A gived number +3.1415926 and 1111";
    char* dest = (char*)malloc(test3.size());
    std::cout << "char* before: " << test3 << std::endl;
    PickNumber(test3, dest, true, true);
    std::cout << "char* after: " << dest << std::endl;

    std::string test4 = "A gived number +3.1415926 and 1111";
    std::cout << "str before: " << test4 << std::endl;
    std::cout << "str after: " << PickNumber(test4, true, true) << std::endl;
    free(dest);

    std::cout << "测试Split函数: " << std::endl;
    std::string test5 = "11;123;asdasd;asfasf;123123";
    std::string test6 = "123123123132";
    std::string test7 = "";
    std::string test8 = "qweqwe;;;qweqweqw;;;qweqweqw;;;;";
    std::vector<std::string> ans5;
    auto printfunc = [](std::string src, std::string delimiter){
        std::vector<std::string> temp;
        std::cout << "test: " << src << std::endl;
        Split(src, temp, delimiter);
        for (auto& str:temp)
            std::cout <<  "[" << str << "]" << " ";
        std::cout << endl;
    };

    printfunc(test5, ";");
    printfunc(test6, ";");
    printfunc(test7, ";");
    printfunc(test8, ";;");

    std::cout << "测试重载版本:" << std::endl;
    std::vector<std::string> ans9 = Split(test8, ";");
    std::cout << "test: " << test8 << std::endl;
    for (auto& str:ans9)
        std::cout <<  "[" << str << "]" << " ";
    std::cout << endl;

    return 0;
}