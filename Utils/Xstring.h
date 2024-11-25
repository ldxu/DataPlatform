#ifndef __XSTRING_H__
#define __XSTRING_H__
/**
 * @describ:一些通用的字符串操作工具头文件声明
 */

#include"../stdafx.h"


namespace base
{
    namespace XString
    {
        /**
         * @brief:删除字符串左边的指定字符
         * @str:    c/c++风格字符串
         * @cc:     需要删除的字符，缺省删除空格
         */
        char* LTrim(char* str, const char cc = ' ' );
        std::string& LTrim(std::string& str, const char cc = ' ' );

        /**
         * @brief:删除字符串右边的指定字符
         * @str:    c/c++风格字符串
         * @cc:     需要删除的字符，缺省删除空格
         */
        char* RTrim(char* str, const char cc = ' ');
        std::string& RTrim(std::string& str, const char cc = ' ');

        /**
         * @brief:将字符串中的大写字符转换成小写，忽略不是字母的字符
         * @str:    待转换的字符串
         */
        char* ToLower(char* str);
        std::string& ToLower(std::string& str); 
           
        /**
         * @brief:将字符串中的小写字符转换成大写，忽略不是字母的字符
         * @str:    待转换的字符串
         */
        char* ToUpper(char* str);
        std::string& ToUpper(std::string& str); 

        /**
         * @brief:字符串替换函数，如果str中存在str1子串，那么将str1子串替换为str2
         * @str:    待处理的字符串
         * @str1:   被替换字符串
         * @str2:   替换后的字符串
         * 注意：
         * 1、如果str2比str1要长，替换后str会变长，所以必须保证str有足够的空间，否则内存会溢出（C++风格字符串不存在这个问题）。
         * 2、如果str2为空，表示删除str中str1的内容。       
         */
        bool ReplaceStr(char* str, const std::string& str1, const std::string& str2);
        bool ReplaceStr(std::string& str, const std::string& str1, const std::string& str2);  

        /**
         * @brief: 将字符串src中提取出数字、符号以及小数点，并存放到另一个字符串中
         * @src:    源字符串
         * @dest:   目标字符串
         * @bsigned:是否提取符号（+ 和 -） true-包括 false-不包括
         * @bdot:   是否提取小数点  
         */
        char* PickNumber(const std::string& src, char* dest, const bool bsigned = false, const bool bdot = false);
        std::string& PickNumber(const std::string& src, std::string* dest,  const bool bsigned = false, const bool bdot = false);
        std::string  PickNumber(const std::string &src,const bool bsigned=false,const bool bdot=false);

        /**
         * @str:        被分割字符串
         * @dest:       分割后保存的字符串容器
         * @delimiter:  分割的标志（字符）
         */
        std::vector<std::string>& Split(const std::string& str, std::vector<std::string>& dest, const std::string& delimiter);
        std::vector<std::string> Split(const std::string& str, const std::string& delimiter);

        /**
         * @brief: C++格式化输出函数模版 example：("这是第 %d 个程序，程序名是%s", num, str)
         */
        template< typename... Args >
        bool StrFormat(string &str,const char* fmt, Args... args ) 
        {
            int len = snprintf( nullptr, 0, fmt, args... );      // 得到格式化输出后字符串的总长度。
            if (len < 0) return false;                                  // 如果调用snprintf失败，返回-1。
            if (len == 0) { str.clear(); return true; }            // 如果调用snprintf返回0，表示格式化输出的内容为空。

            str.resize(len);                                                 // 为string分配内存。
            snprintf(&str[0], len + 1, fmt, args... );           // linux平台第二个参数是len+1，windows平台是len。
            return true;
        }
        template< typename... Args >
        string StrFormat(const char* fmt, Args... args ) 
        {
            string str;

            int len = snprintf( nullptr, 0, fmt, args... );      // 得到格式化后字符串的长度。
            if (len < 0) return str;              // 如果调用snprintf失败，返回-1。
            if (len == 0) return str;           // 如果调用snprintf返回0，表示格式化输出的内容为空。;

            str.resize(len);                                                // 为string分配内存。
            snprintf(&str[0], len + 1, fmt, args... );          // linux平台第二个参数是len+1，windows平台是len。
            return str;
        }    
    } 
}
#endif