// g++ -std=c++0x word-dir.cxx
#include <string>
#include <codecvt>
#include <locale>
#include <iostream>
#include <stdio.h>
#define WIDGTH 16
using namespace std;

// utf8转unicode
wstring utf8_to_wstring(const string &str)
{
  wstring_convert<codecvt_utf8<wchar_t>> utf8_cvt;
  return utf8_cvt.from_bytes(str);
}

// unicode转utf8
string wstring_to_utf8(const wstring &str)
{
  wstring_convert<codecvt_utf8<wchar_t>> utf8_cvt;
  return utf8_cvt.to_bytes(str);
}
static wstring wstart = utf8_to_wstring(u8"←");
static wstring LR = utf8_to_wstring(u8"\n");
static wstring brackets =
utf8_to_wstring("〈〉《》「」『』【】〔〕（）()");

int main(int argc, char **argv) 
{
  int nwords = 0;
  
  /* wcout.imbue(locale("zh_CN.GBK")); */
  int has_num = 0;
  wstring wline = wstart;
  
  auto add_num = [&](wstring& wsequence) 
    {
     if (has_num) 
     { 
      nwords += has_num, has_num = 0;
      wline = wsequence + wline, wsequence.clear();
     }
     
    };
  
  wstring wnum;
  wstring wrev;
  
  //string str = u8"3+5 = 8";
  string str = u8"如：（3+5，6+8）的值是14；";
  cout << "请输入：";
  while (cin >> str)
  {
    wstring w1 = utf8_to_wstring(str);    // (w1.crbegin(), w1.crend());
    for (auto ch : w1)
    {
      
      auto found = brackets.find(ch) != wstring::npos;
      if (found)
        ch ^= 1;
      
      if (iswalnum(ch)) 
      {
        wnum += ch, has_num = 1;
        //cout << has_num;
        continue; 
      }

      add_num(wnum);
    
      wline.insert(wline.begin(), ch); // reverse order
      nwords += 1;
      if (nwords >= WIDGTH)
      {
        wrev += wline + LR;
        wline = wstart;
        nwords = 0;
      }
    
    }
  }
  if (nwords || has_num) 
  {
    add_num(wnum);
    wrev += wline;
  }
  str = wstring_to_utf8(wrev);
  cout << str << endl;
  
  return 0; 
}

