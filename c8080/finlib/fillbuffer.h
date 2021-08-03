#pragma once

#include <vector>
#include "string.h"
#include "fillbuffer.h"

// _Ptr: https://stackoverflow.com/questions/43684906/cant-access-std-vector-iterator-ptr-on-mac

class FillBuffer {
public:
  std::vector<char> buf;

  FillBuffer& str(const void* data, int len) { int o = buf.size(); buf.resize(o+len); memcpy(&buf[0]+o, data, len); return *this; }
  //FillBuffer& str(FillBuffer& buf) { str(buf.buf.begin()._Ptr, buf.buf.size()); return *this; }
  FillBuffer& str(const char_t* text) { str(text, strlen(text)*sizeof(char_t)); return *this; }
  FillBuffer& str(const string& text) { str(text.c_str(), strlen(text.c_str())*sizeof(char_t)); return *this; }
  FillBuffer& i2s(int i) { char buf[256]; sprintf(buf, "%i", i); str(buf); return *this; }
};
