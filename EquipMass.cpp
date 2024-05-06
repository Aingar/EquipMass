/*
  EquipMass.cpp - Include equipment and cargo in the ship's mass.

  Jason Hood, 31 December, 2010.

  When the mass of the ship is wanted, this plugin will include the mass of all
  the equipment and cargo, affecting the handling of the ship (NPCs included, so
  those trains with six-figure cargos are quite sluggish).  Note that vanilla
  gives most equipment a mass of 10, with goods having the default mass of 1.

  Copy EquipMass.dll to your EXE directory and add it to the [Libraries]
  sections of dacom.ini & dacomsrv.ini.  Requires version 1.1 of common.dll.

  v1.01, 17 September, 2012:
  - fixed mass increase after a jump (in SP).
*/

#include "common.h"
#include <map>

#define NAKED	__declspec( naked )
#define STDCALL __stdcall


#define ADDR_MASS ((PDWORD)(0x639c098)) // CShip::get_mass


DWORD dummy;
#define ProtectX( addr, size ) \
  VirtualProtect( addr, size, PAGE_EXECUTE_READWRITE, &dummy )

#define NEWABS( from, to, prev ) \
  prev = *(PDWORD)(from); \
  *(PDWORD)(from) = (DWORD)to


char* cobject;

float Get_Equip_Mass()
{
  CEquipManager* em = (CEquipManager*)(cobject+0xE4);
  CEquipTraverser et;
  CEquip* equip;
  float mass = 0;
  while ((equip = em->Traverse( et )) != 0)
  {
    if (equip->type != 0x10000)
      mass += equip->archetype->mass;
  }
  return mass;
}


DWORD Mass_Org;

NAKED
void Mass_Hook()
{
  __asm {
	mov	cobject, ecx
	call	Mass_Org
	cmp	dword ptr [esp], 0x54a9ed // is the call from Freelancer?
	je	done		// yes, need to keep the original mass
	cmp	word ptr [esp], 0xe898	 // likewise if from Server
	je	done
	push	edx		// that's lucky
	call	Get_Equip_Mass
	pop	edx
	fadd
	fld	st		// update the reciprocal in the physics data
	fld1			// fortunately, it looks like mass is always
	fdivr			//  used before the reciprocal
	fstp	[edx+0x40]
  done:
	ret
  }
}


void Patch()
{
  ProtectX( ADDR_MASS, 4 );
  NEWABS( ADDR_MASS, Mass_Hook, Mass_Org );
}


BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
  if (fdwReason == DLL_PROCESS_ATTACH)
    Patch();

  return TRUE;
}
