// Открытая, бесплатная, ASIS версия библиотеки VinLib. В процессе написания
// (с) 5-12-2011 vinxru

#include <stdafx.h>
#include "finlib/file.h"
#include "finlib/types.h"
#include "finlib/winapi_exception.h"
#include "finlib/exception.h"

File::File() throw() {
  handle = INVALID_HANDLE_VALUE;
}

void File::raiseIfNotOpened() {
  if(handle==INVALID_HANDLE_VALUE) raise("Файл не открыт");
}

int File::size32() {
 int current_position = ftell(handle);
 fseek(handle, 0, SEEK_END);
 int size = ftell(f);
 fseek(handle, current_position, SEEK_SET);
 return size;
}

void File::open(const char* fileName, int access, int share, int distr) {
  close();
  /*handle=CreateFile(fileName, access, share, 0, distr, 0, 0);
  if(handle==INVALID_HANDLE_VALUE) raise_os((string)"Ошибка создания/открытия файла "+fileName+"\nCreateFile");*/
  handle = fopen(fileName, "w+"); // TODO mode
  if(handle == INVALID_HANDLE_VALUE) raise_os((string)"Ошибка создания/открытия файла " + fileName);
}

void File::openR(const char* fileName) {
  close();
  handle = fopen(fileName, "r");
  if(handle == INVALID_HANDLE_VALUE) raise_os((string)"Ошибка открытия файла " + fileName);
}

void File::openC(const char* fileName, FileCreateMode mode) {
  close();
  handle = fopen(fileName, "w+"); // TODO mode
  if(handle == INVALID_HANDLE_VALUE) raise_os((string)"Ошибка создания/открытия файла " + fileName);
}

void File::read(void* buf, int len0) {
  raiseIfNotOpened();
  if(len0==0) return;
  if(len0<0) raise_os("ReadFile");
  /*
  unsigned long len=len0; // С уветом верхней проверки ошибок нет, а компилятор счаслив
  unsigned long res;
  if(!ReadFile(handle, buf, len, &res, 0)) raise_os("ReadFile");
  if(res!=len) raise("Ошибка чтения файла");*/

  // size_t fread(void *buf, size_t size, size_t count, FILE *stream)
  fread(buf, (size_t) len0, 1, handle);
}

void File::write(const void* buf, int len0) {
  raiseIfNotOpened();
  if(len0==0) return;
  if(len0<0) raise_os("ReadFile"); 
  /*
  unsigned long len=len0; // С уветом верхней проверки ошибок нет, а компилятор счаслив
  unsigned long res;
  if(!WriteFile(handle, buf, len, &res, 0))
    raise_os("WriteFile");
  if(res!=len) raise("Ошибка записи в файл");
  */
  fwrite(buf, (size_t) len0, 1, handle);
}

void File::close() {
  if(handle == INVALID_HANDLE_VALUE) return;
  fclose(handle);
  handle = INVALID_HANDLE_VALUE;
}

File::~File() {  
  if(handle != INVALID_HANDLE_VALUE) {
    close();
  }
}

void saveFile(const char* fileName, FileCreateMode mode, const void* buf, int len) {
  File file;
  file.openC(fileName, mode);
  file.write(buf, len);
}

void loadFile(std::vector<byte_t>& out, cstring fileName) {
  File f;
  f.openR(fileName);
  int len = f.size32();
  out.resize(len);
  if(len>0) f.read(&out[0], len);
}

// Только 8-битные файлы
void loadStringFromFile(std::string& out, const string& fileName) {
  std::vector<byte_t> buf;
  loadFile(buf, fileName);
  if(buf.size()>0) out.assign(&buf[0], buf.size());
}
