#define _CRT_SECURE_NO_WARNINGS
#include"search.h"

//wstring=>string
std::string WString2String(const std::wstring& ws)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const wchar_t* wchSrc = ws.c_str();
    size_t nDestSize = wcstombs(NULL, wchSrc, 0) + 1;
    char* chDest = new char[nDestSize];
    memset(chDest, 0, nDestSize);
    wcstombs(chDest, wchSrc, nDestSize);
    std::string strResult = chDest;
    delete[]chDest;
    setlocale(LC_ALL, strLocale.c_str());
    return strResult;
}
// string => wstring
std::wstring String2WString(const std::string& s)
{
    std::string strLocale = setlocale(LC_ALL, "");
    const char* chSrc = s.c_str();
    size_t nDestSize = mbstowcs(NULL, chSrc, 0) + 1;
    wchar_t* wchDest = new wchar_t[nDestSize];
    wmemset(wchDest, 0, nDestSize);
    mbstowcs(wchDest, chSrc, nDestSize);
    std::wstring wstrResult = wchDest;
    delete[]wchDest;
    setlocale(LC_ALL, strLocale.c_str());
    return wstrResult;
}

bool is_include(string& s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '^' || s[i] == '$')
            return true;
    }
    return false;
}

bool is_name_match(string a,const string& b) {
    for (int i = 0; i < a.size(); i++)
        if (a[i] == '.') {
            a.insert(i, ".");
            i++;
        }
    //cout << a << endl;
    smatch sm;
    regex re(a);
    bool flag;
    //if (is_include(a))
        flag = regex_search(b, sm, re);
    //else
        //flag = regex_match(b, re);
    //flag ? cout << "yes" : cout << "no";
    return flag;
}

bool is_id_match(string a, const string& b) {
    smatch sm;
    regex re(a);
    bool flag;
    flag = regex_search(b, sm, re);
    //flag ? cout << "yes" : cout << "no";
    return flag;
}

vector<string> split(const string& src, string separate_character)
{
    vector<string> strs;
    int separate_characterLen = separate_character.size();//分割字符串的长度,这样就可以支持如“,,”多字符串的分隔符
    int lastPosition = 0, index = -1;
    while (-1 != (index = src.find(separate_character, lastPosition)))
    {
        strs.push_back(src.substr(lastPosition, index - lastPosition));
        lastPosition = index + separate_characterLen;
    }
    string lastString = src.substr(lastPosition);//截取最后一个分隔符后的内容
    if (!lastString.empty())
        strs.push_back(lastString);//如果最后一个分隔符后还有内容就入队
    return strs;
}

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}
