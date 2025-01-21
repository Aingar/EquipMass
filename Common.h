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
  BYTE	dontcare[0x4];
  UINT archId;
  BYTE dontcare2[0x18];
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


class IMPORT INI_Reader
{
public:
	INI_Reader(class INI_Reader const&);
	INI_Reader(void);
	~INI_Reader(void);
	class INI_Reader& operator=(class INI_Reader const&);
	void close(void);
	bool find_header(char const*);
	bool get_bool(unsigned int);
	char const* get_file_name(void)const;
	char const* get_header_ptr(void);
	char const* get_indexed_value(unsigned int);
	int get_line_num(void)const;
	char const* get_line_ptr(void);
	char const* get_name(void)const;
	char const* get_name_ptr(void);
	unsigned int get_num_parameters(void)const;
	void get_state(struct State&)const;
	bool get_value_bool(unsigned int);
	float get_value_float(unsigned int);
	int get_value_int(unsigned int);
	char const* get_value_ptr(void);
	char const* get_value_string(unsigned int);
	char const* get_value_string(void);
	unsigned short const* get_value_wstring(void);
	class Vector  get_vector(void);
	bool is_end(void)const;
	bool is_header(char const*);
	bool is_number(char const*)const;
	bool is_value(char const*);
	bool is_value_empty(unsigned int);
	void log_link(char const*)const;
	bool open(char const*, bool);
	bool open_memory(char const*, unsigned int);
	bool read_header(void);
	bool read_value(void);
	void reset(void);
	void seek(unsigned int);
	void set_state(struct State const&);
	unsigned int tell(void)const;
	double value_num(unsigned int);

public:
	unsigned char data[5480];
};

#endif
