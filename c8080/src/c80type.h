
#include <finlib/strings.h>
#include <string>

enum CBaseType { cbtError, cbtVoid, cbtChar, cbtShort, cbtLong, cbtUChar, cbtUShort, cbtULong, cbtStruct, 
  cbtFlags
};

class C80Type {
public:
  CBaseType baseType;
  int addr, i, arr, arr2, arr3;
  //Place place;
  std::string needInclude;

  bool operator == (C80Type a) const {
    return baseType==a.baseType && addr==a.addr && i==a.i 
      && arr==a.arr && arr2==a.arr2 && arr3==a.arr3;
  }

  inline C80Type() { arr=arr2=arr3=addr=0; }
  inline C80Type(CBaseType _baseType) { arr=arr2=arr3=addr=0; baseType=_baseType; }
  std::string descr();
  int size();
  int size1();
  int sizeElement();

  bool isVoid() { return baseType==cbtVoid && addr==0; }
  bool isStackType() { return baseType==cbtChar || baseType==cbtUChar || baseType==cbtUShort || baseType==cbtShort || addr!=0; }
  bool is16() { return baseType==cbtUShort || baseType==cbtShort || addr!=0; }
  bool is8() { return (baseType==cbtChar || baseType==cbtUChar) && addr==0; }

  int getSize() {
    if(is8()) return 8;
    if(is16()) return 16;
    return 0;
  }
};
