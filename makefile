# Makefile for EquipMass.
# Jason Hood, 30 December, 2010.
# Updated 17 September, 2012.

CPPFLAGS = /nologo /W3 /GF /Ox /MD

EquipMass.dll: EquipMass.obj EquipMass.res Common.lib
	cl /nologo /LD EquipMass.obj EquipMass.res /link /base:0x6020000 /filealign:512

Common.lib: Common.def
	lib /nologo /machine:ix86 /def:Common.def
