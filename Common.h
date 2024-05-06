/*
  Common.h - Declarations for functions imported from Common.dll.

  Jason Hood, 30 December, 2010.
*/

#ifndef _COMMON_H
#define _COMMON_H

#pragma comment( lib, "Common.lib" )

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define EXTERN __declspec(dllimport)


class EXTERN CEquipTraverser
{
public:
  CEquipTraverser();

private:
  int  mask;
  bool all;		// includes destroyed equipment
  int  state;
  int  iter;		// actually a pointer, of course
};


struct Archetype
{
  BYTE	dontcare[0x20];
  float mass;
};


class CEquip
{
public:
  BYTE	     dontcare1[12];
  Archetype* archetype;
  UINT	     dontcare2;
  UINT	     type;
  BYTE	     dontcare3[0x10];
  UINT	     count;		// CECargo only
};


class EXTERN CEquipManager
{
public:
  CEquip* Traverse( CEquipTraverser& );
};


#endif
