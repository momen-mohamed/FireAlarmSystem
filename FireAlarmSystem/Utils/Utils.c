/*
 * Utils.c
 *
 * Created: 6/18/2023 2:13:44 AM
 *  Author: mo2a
 */ 

#include "StdTypes.h"

u8 strLen(c8* str){
	u8 i = 0;
	for (i =0;str[i];i++);
	return i;
}

Bool_t string_compare(c8 *str1, c8 *str2)
{

	u16 i;
	Bool_t equal = TRUE;

	for (i = 0; str1[i] != 0 || str2[i] != 0; i++)
	{
		if (str1[i] != str2[i])
		{
			equal = FLASE;
		}
	}

	return equal;
}