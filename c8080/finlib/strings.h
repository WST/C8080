// Открытая, бесплатная, ASIS версия библиотеки VinLib. В процессе написания
// (с) 5-12-2011 vinxru

#ifndef VINLIB_STRINGS_H
#define VINLIB_STRINGS_H

//#include <stdlib.h>
#include <string>
#include <cstring>
#include <vector>

// Костыль
#define _tcslen strlen
#define _tcsstr strstr

// Для удобства
typedef char char_t;
typedef const std::string& cstring;
typedef std::string string;

// Подсчет кол-ва символов в строке
int charsCount(const char* ptr, char chr);

// Разделение строки на подстроки (и поддержка типа данных std::string)
void explodeText(std::vector<string>& out, const char* str);
inline void explodeText(std::vector<string>& text, cstring str) { explodeText(text, str.c_str()); }

// Строку в верхний регистр (и поддержка типа данных std::string)
extern const unsigned char upperCaseTbl[];
string upperCase(const char* in);
inline string upperCase(cstring str) { return upperCase(str.c_str()); }

// Строку в десятичное число
//inline std::string i2s(int d) { char buf[256]; sprintf_s(buf, sizeof(buf), "%i", d); return buf; }
inline std::string i2s(int d) { char buf[256]; sprintf(buf, "%i", d); return buf; }

// Строку в шестнадцатеричное число
//inline std::string hex(int d) { char buf[256]; sprintf_s(buf, sizeof(buf), "%X", d); return buf; }
inline std::string hex(int d) { char buf[256]; sprintf(buf, "%X", d); return buf; }

int strcmpi_rus(const char* a, const char* b);
void explode1(std::vector<std::string>& out, const char_t* sep, const char_t* str);

#endif
