// stdafx.cpp : source file that includes just the standard includes
// IP2ComServer.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#define H2I(x) (isdigit((x))?(x)-'0':(toupper((x))-'A')+10)

int Pack(UCHAR* destination,UCHAR* source,int len) 
{
	int j = 0;
	int i = 0;
	while (i < len) {
		if ( !isdigit(*(source + i)) ) {
			if ( *(source + i) < 'A' || *(source + i) > 'F' ) 
				return -1;
		}
		destination[j] = HexToInt((char*)source + i);
		i += 2;
		j++;
	}
	return j;
}

int UnPack(UCHAR* destination,UCHAR* source,int len) 
{
	UCHAR temp[3];
	int i = len;
	while (i > 0) {
		i--;
		sprintf((char*)temp, "%02X", source[i]);
		memcpy(destination + (i * 2), temp, 2);
	}
	return len * 2;
}
int HexToInt(char *s)
{
	int l,h;
	h=H2I(s[0]);
	l=H2I(s[1]);
	return (h*16+l);
}


