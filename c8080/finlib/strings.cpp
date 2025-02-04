// Открытая, бесплатная, ASIS версия библиотеки VinLib. В процессе написания
// (с) 5-12-2011 vinxru

#include <stdafx.h>
#include "finlib/strings.h"

// Подсчет кол-ва символов в строке
int charsCount(const char* ptr, char chr) {
  int c;
  for(c=0; ptr=strchr(ptr, chr); ptr++, c++);
  return c;
}

// Разделенеи строки на подстроки
void explodeText(std::vector<string>& out, const char* str) {
  // Подсчет строк  
  int lc = charsCount(str, '\n')+1;

  // Выделение памяти
  out.resize(lc);
  std::vector<string>::iterator outPtr = out.begin();
  std::vector<string>::iterator outEnd = out.end();

  // Деление строки
  const char* ptr = str;
  while(true) {
    const char* end = strchr(ptr, '\n');
    if(end==0) {
      outPtr->assign(ptr, strlen(ptr));
      break;
    }
    int l = end-ptr;
    if(end[-1]==13) l--;
    outPtr->assign(ptr, l);
    ptr=end+1;
    outPtr++;
    if(outPtr==outEnd) break; // anti bug    
  }  
}

// Таблица заглавных букв CP1251
const unsigned char upperCaseTbl[]={
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
  16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
  32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
  48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
  64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
  80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
  96,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
  80,81,82,83,84,85,86,87,88,89,90,123,124,125,126,127,
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
  176,177,178,179,180,181,182,183,168,185,186,187,188,189,190,191,
  192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
  208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
  192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
  208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223
};

// Привести строку к верхнему регистру
string upperCase(const char* in) {
  string out;
  out.resize(strlen(in));
  char* o = const_cast<char*>(out.c_str());
  while(*in)
    *o++=upperCaseTbl[(int)(unsigned char)*in++];
  return out;
}
/*
int strcmpi_rus(const char* a, const char* b) {
  int result;
  _asm {
    mov eax, a
    mov edx, b
    push ebx
    sub edx, eax
    xor ecx, ecx
_lp:  mov cl, [eax]
      mov bl, byte ptr upperCaseTbl[ecx]
      mov cl, [edx+eax]
      cmp bl, byte ptr upperCaseTbl[ecx]
      ja _a
      jb _b
      inc eax
      test bl, bl
    jnz _lp
    xor eax, eax
    pop ebx
    jmp _ret

_a: mov eax, 1
    pop ebx
    jmp _ret

_b: pop ebx
    mov eax, -1
    jmp _ret
_ret:
    mov result, eax;
  }
  return result;
}*/

void explode1(std::vector<std::string>& out, const char_t* sep, const char_t* str) {
  if(sep[0]==0) return;
  const char_t* ptr;
  int seplen=_tcslen(sep);

  // Подсчет строк
  int lc=1;
  ptr=str;
  while(true) {    
    ptr=_tcsstr(ptr, sep);
    if(ptr==0) break;
    ptr += seplen;
    lc++;
  }

  // Выделение памяти
  out.resize(lc);
  string* outPtr=&out[0];
//  assert(outPtr!=0);
  string* outEnd=outPtr + out.size();

  // Деление строки
  ptr=str;
  while(true) {
    const char_t* end=_tcsstr(ptr, sep);
    if(end==0) {
      outPtr->assign(ptr);
      break;
    }
    outPtr->assign(ptr, end-ptr);
    ptr=end+seplen;
    outPtr++;
    if(outPtr==outEnd) break; // anti bug    
  }  
}
