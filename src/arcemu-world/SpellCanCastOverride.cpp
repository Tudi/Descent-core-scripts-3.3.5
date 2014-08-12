#include "StdAfx.h"

#define REGISTER_HANDLER( spell ) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->CanCastHandler == 0 ); \
	sp->CanCastHandler = &CCH_##spell;
#define REGISTER_SAMEHANDLER(spell,copy_from) sp = dbcSpell.LookupEntryForced( spell ); \
	ASSERT( sp->CanCastHandler == 0 ); \
	sp->CanCastHandler = &CCH_##copy_from;

uint32 CCH_31884(Spell *sp)
{
	//forbearance is casted after shielding target, avanging wrath cannot be casted for a while after shielding
	//this is also handled client side...so relax...take a coke
	if( sp->u_caster && sp->u_caster->HasAura( 61987 ) )
		return SPELL_FAILED_BAD_TARGETS;
	return SPELL_FAILED_SUCCESS;
}

void RegisterCanCastOverrides()
{
	SpellEntry *sp;
	//Avenging Wrath
	REGISTER_HANDLER( 31884 );
}