# include "C.h"
# include "typeS.h"
# include "partitions.DEF"

#ifndef MAKEMODICON_H
#define MAKEMODICON_H

#ifdef __cplusplus

#endif

void OUTtoMODICON( void );	// atomic read OUT
void INtoMODICON( void );	// atomic readIN
void MODICONtoIN( void );  	// atomic write IN


#endif