// CONFIELD ELECTRONICS
// JACK RAIZMAN 
//=======================================================================
// !!!  limitation -- short requests, mod 256 REGs!!!

#include "parserMODICON.h"

// INTERFACE:
# ifdef __DATA_SOURCE_FILE

// --------------------------------------------------
// �� ���� - � ���筨�� ������  __DATA_SOURCE_FILE
// ������ �����⥭�஢����� ���᭮� ����࠭�⢮ [extIN_MODICON + extOUT_MODICON]
// --------------------------------------------------

# include "include\CROSS_CPU\C.h"
# include "include\CROSS\typeS.h"
# include "include\partitions.DEF"

# define  _size_of_segment_MODICON ((U16) 256)  /* REGs */

TVar( U16 )  segment_MODICON[ _size_of_segment_MODICON ];
TConst( TPartitionD16s16 )  MODICON_DB  =  { segment_MODICON,  _size_of_segment_MODICON};

# else
//=======================================================================

//---------------------------------------------------
// Atomic functions: copy extern MODICON-database 
// (to/from atomic CONFIELD extDB) by request
//---------------------------------------------------
// U16 REGISTERs -->

extern TConst( TPartitionU16s16 )  MODICON_DB;

//----------------------------------------------------
U8 parserMODICON( TVar( TPartitionDs8 ) * mailRAC )  {

  TVar( U16 ) * modiconDB;
  TVar( U8 ) *  message;
  U16 N, i;
  U16 REG;    

  message = mailRAC->ADR;	// ???

  ++message;	// skip SLAVE_ADDRESS

  i = *message++;  // FUNCTION

  _wrBYofW( 0, REG ) = message[1];	// REG_ADDRESS_LOW
  _wrBYofW( 1, REG ) = message[0];

  _wrBYofW( 0, N ) = message[3];	// NUM_OF_REG_LOW
  _wrBYofW( 1, N ) = message[2];

  if ( ( REG + N ) > MODICON_DB.Size )  return 1; 	// SPACEOUT

//------------------------------------
  switch ( i /* _M_ REG */ )  {

    case  0x03:
    case  0x04:	// READ

      modiconDB = & MODICON_DB.ADR[ REG ];  
      *message++ = N << 1;	// SIZE IN BYTES
      
      for ( i=0; i < N; ++i ) {
        *message++ = _rdBYofW( 1, *modiconDB );
        *message++ = _rdBYofW( 0, *modiconDB );
        ++modiconDB;
        }
      mailRAC->Size = (N << 1) + 3;
      break;

//------------------------------------
    case 0x10:	// WRITE
      
      message += 4;	// skip all this address numbers: 
                        // must be at the same positions in response

      modiconDB = & MODICON_DB.ADR[ REG ];  
      message += 1;	// SKIP SIZE IN BYTES	
      
      for ( i = 0; i < N; ++i ) {
        _wrBYofW( 1, *modiconDB ) = *message++;
        _wrBYofW( 0, *modiconDB ) = *message++;
        ++modiconDB;
        }

      mailRAC->Size = 2 + 4;
      break;
      
      
     default:   // error handler
         
        break;

    }

  return 0;

  }      

# endif
