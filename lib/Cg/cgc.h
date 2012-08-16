/* SCE CONFIDENTIAL
PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001
* Copyright (C) 2006 Sony Computer Entertainment Inc. 
* All Rights Reserved.
*/

#ifndef __LIB_CGC_H__
#define __LIB_CGC_H__

#ifdef __cplusplus
extern "C" {
#endif	

int compile_program_from_string( const char*, const char *, const char*, const char**, char** );
void free_compiled_program ( char* );

#ifdef __cplusplus
}
#endif

#endif /* __LIB_CGC_H_ */
