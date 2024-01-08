

#ifndef STDTYPES_H_
#define STDTYPES_H_


typedef unsigned char    u8;
typedef   signed char    s8;

typedef unsigned int     u16;
typedef   signed int     s16;

typedef unsigned long    u32;
typedef   signed long    s32;

#define NULL_PTR    ((void*)0)

typedef enum{
	OK,
	NOK,
	NULL,
	OUT_OF_RANGE
	}Error_type;

typedef enum{
	FALSE,
	TRUE
	}bool_type;
	
#define  MAX_U16  ((u16)65535)
#define  MAX_S16  ((s16)32767)
#define  MIN_S16  ((s16)-32768)
#define  MIN_U16  ((u16)0)

	
	
	
	
	

#endif /* STDTYPES_H_ */