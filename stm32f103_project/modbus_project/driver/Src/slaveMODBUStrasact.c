
#include "slaveMODBUStrasact.h"

//----------------------------------------
// INTERFACE:

//extern  void UnSendMessage( void );
   extern    TConst( TPartitionDs8 ) UnRxTxBuf; // { & RxBuf2[0], sizeof( RxBuf2 ) };
   extern    TVar( U16 ) UnRxTxSize;

//--------------------------------------------------------------------
//--------------------------------------------------------------------

//--------------------------
TVar( U8 ) MyNode = 0x1A;
//---------------------------------------------------------

//extern U8 parserMODICON( TVar( TPartitionDs8 ) * mailRAC );

//---------------------------------------------------------------------------------------------
U8 MODBUStrasact( void )  {  

  TVar( TPartitionDs8 )  mailRAC; 	// mail of RAC - Remote Access Client
  TVar( TBLOCKo8s8    )  transBLOCK;      // operative buffer for all clients

  TVar( U8 ) * msg;
  U8 Err = 0;
  U16 Size = 0;
  U16 CRC;

  Size = UnRxTxSize;
  if ( Size < 8 )  return 1;	// Size == 0 or "no message"

  msg = UnRxTxBuf.ADR;

// CRC check ---------------------------------
  Size -= 2;
  _wrBYofW( 0, CRC ) = msg[ Size     ];
  _wrBYofW( 1, CRC ) = msg[ Size + 1 ];
  if ( CRC != CRC16ANSI( msg, Size ) )  return 2;
  transBLOCK.Size = Size + 1;	// "-1" -- __M__ ???
  
//-----------------------------------
  if ( *msg != MyNode )  {
    if ( *msg == (U8) 0xFF )  *msg = MyNode;
    else  return 3; 		// this message is to "other" client
    }
//-----------------------------------------------------
// Parsing with guaranteed answer: in any case -- will be some answer
//-----------------------------------------------------

  mailRAC.ADR = msg;			// address = mail of RAC
  mailRAC.Size = transBLOCK.Size - 1; 	// size without ???, but with address

  Err = parserMODICON( & mailRAC );	// ??????

  if ( Err )  {	// short answers for physicly right, but logically wrong requests 
        ++msg;		// skip address
//!!! ?????????????
        *msg++ |= 0x80;     // marker of error
        *msg++  = Err;      // nomber of error
// short answers writes without crc
        mailRAC.Size = 3;
//!!!----------------------------------------
        }
  else  {
    msg += mailRAC.Size; // shift for length of prepared answer for LRC
//  ++INmailBoxUPDATE2;
    }

// REMAKE !!!:
  if ( msg >= & (UnRxTxBuf.ADR)[ UnRxTxBuf.Size ] )  return 4; // no more place for CRC

//------------------------------------------------
// msg is already shifted for LRC/CRC

//------------------------------------------------
  CRC = CRC16ANSI( mailRAC.ADR, mailRAC.Size );
  *msg++ = _rdBYofW( 0, CRC );
  *msg   = _rdBYofW( 1, CRC );

  Size = mailRAC.Size + 2;

  UnRxTxSize = Size;
  //UnSendMessage();

  return 0;    // return 0; 
  }
						// ��� ������ ���������
