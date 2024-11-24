#include "Xstring.h"

namespace base{
    namespace XString{
        char* LTrim(char* str, const char cc )
        {
            if (str == nullptr || *str == '\0')  return nullptr;
            char* p = str;
            while (*p == cc)    //遍历字符串，p指向第一个不是cc的字符
                p++;
            // 函数签名
            // void* memmove(void* dest, const void* src, size_t count);
            // 用于在内存中安全的复制数据，即使原和目标区域折叠，也能正确处理，不会破坏数据
            memmove(str, p, strlen(str) - (p - str)+1);
            return str;
        }

        std::string& LTrim(std::string& str, const char cc )
        {
            auto pos = str.find_first_not_of(cc);   //从左往右找到第一个不是cc的字符的位置，没找到则是0
            if (pos != 0) str.replace(0, pos, "");
            return str;
        }

        char* RTrim(char* str, const char cc)
        {
            if (str == nullptr || *str == '\0') return nullptr;
            size_t len = strlen(str);
            while(len > 0 && str[len - 1] == cc)    //从右往左找到第一个不是cc的字符位置
            {
                --len;
            }
            str[len] = '\0';    //截断字符串
            return str;
        }

        std::string& RTrim(std::string& str, const char cc)
        {
            auto pos = str.find_last_not_of(cc);
            if (pos != std::string::npos)
                str.erase(pos + 1);
            return str;
        }

        char* ToUpper(char* str)
        {
            if (str == nullptr) return nullptr;

            char *p = str;
            while (*p != 0)
            {
                if ( (*p >= 'a') && (*p <= 'z') ) *p = *p - 32;
                p++;
            }
            return str;
        }

        std::string& ToUpper(std::string& str)
        {
            for (auto &cc:str)
            {
                if ( (cc >= 'a') && (cc <= 'z') ) cc = cc - 32;
            }
            return str;
        }

        char* ToLower(char* str)
        {
            if (str == nullptr) return nullptr;
            char *p = str;
            while (*p != 0)
            {
                if( (*p >= 'A') && (*p <= 'Z') ) *p = *p + 32;
                p++;
            }
            return str;
        }

        std::string& ToLower(std::string& str)
        {
            for (auto& cc:str)
            {
                if ( (cc >= 'A') && (cc <= 'Z') ) cc = cc + 32; 
            }
            return str;
        }

        bool ReplaceStr(std::string& str, const std::string& str1, const std::string& str2)
        {
            if ( (str.length() == 0) || (str1.length() == 0) )  return false;
            size_t pos = 0;
            while ((pos = str.find(str1, pos)) != std::string::npos)
            {
                str.replace(pos, str1.length(), str2);
                pos += str2.length();   //移动指针避免死循环(str2 中 包含str1就会死循环)
            }
            return true;
        }    

        bool ReplaceStr(char* str,  const std::string& str1, const std::string& str2)
        {
            if ( str == nullptr)    return false;
            std::string strtemp(str);
            // 复用C++风格的字符串替换函数
            if (ReplaceStr(strtemp, str1, str2))
            {
                strtemp.copy(str, strtemp.length());
                str[strtemp.length()] = '\0';           //需要记住把最后的终止符加上
                return true;   
            }
            else
            {
                return false;
            }
        }

        char* PickNumber(const std::string& src, char* dest, const bool bsigned, const bool bdot)
        {
            if (dest == nullptr)    return nullptr;
            std::string strtemp = PickNumber(src, bsigned, bdot);
            strtemp.copy(dest, strtemp.length());
            dest[strtemp.length()] = '\0';
            return dest;
        }
        std::string& PickNumber(const std::string& src, std::string& dest, const bool bsigned, const bool bdot)
        {
            std::string str;
            for (char cc:src)
            {
                if ( (bsigned) && ((cc == '+') || (cc == '-')))
                {
                    str.push_back(cc);
                    continue;
                }
                if ( (bdot) && (cc == '.'))
                {
                    str.push_back(cc);
                    continue;
                }
                if (isdigit(cc))
                    str.push_back(cc);
            }

            dest = str;
            return dest;
        }

        std::string PickNumber(const std::string& src, const bool bsigned, const bool bdot)
        {
            std::string dest;
            PickNumber(src, dest, bsigned, bdot);
            return dest;
        }

    }
}