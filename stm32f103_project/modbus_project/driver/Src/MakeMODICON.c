
#include "MakeMODICON.h"

//---------------------------------------------------
// Atomic functions: copy extern MODICON-database 
// (to/from atomic CONFIELD extDB) by request
//---------------------------------------------------

 /* extern  */  TConst( TPartitionU16s16 )  MODICON_extIN;
 /* extern  */  TConst( TPartitionU16s16 )  MODICON_extOUT;

 /* extern  */  TConst( TPartitionDs16 )  Control_IN;
 /* extern  */  TConst( TPartitionDs16 )  Control_OUT;

//---------------------------------------------------
void OUTtoMODICON( void )  {

  TVar( U8 ) * src;	// CONFIELD
  TVar( U8 ) * dst;	// MODICON
  U16  Size;

  src = Control_OUT.ADR;
  dst = (TVar( U8 ) *) MODICON_extOUT.ADR;
  Size = MODICON_extOUT.Size << 1;	// byte-copy
  for ( ; Size != 0; --Size )   *dst++ = *src++;

  }


//---------------------------------------------------
void INtoMODICON( void )  {
  TVar( U8 ) * src;	// CONFIELD
  TVar( U8 ) * dst;	// MODICON
  U16  Size;

  src = Control_IN.ADR;
  dst = (TVar( U8 ) *) MODICON_extIN.ADR;
  Size = MODICON_extIN.Size << 1;	// byte-copy

  for ( ; Size != 0; --Size )   *dst++ = *src++;

  }

//---------------------------------------------------
void MODICONtoIN( void )  {

  TVar( U8 ) * src;	// MODICON
  TVar( U8 ) * dst;	// CONFIELD
  U16  Size;

  dst = Control_IN.ADR;
  src = (TVar( U8 ) *) MODICON_extIN.ADR;
  Size = Control_IN.Size;	// byte-copy

  for ( ; Size != 0; --Size )   *dst++ = *src++;

  }

