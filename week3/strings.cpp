//
// Created by 李勃鋆 on 24-9-2.
//
#include "../week01.h"
//把从strsrc地址开始且含有“0"结束符的字符串复制到以strdest开始的地址空间，返回值的类型为char*
char *sCopy(char *dest, const char *src) {
	char *p = dest;
	while (src != nullptr) {
		*dest++ = *src++;
		// *dest=*src;
		// dest++;
		// src++;
	}
	return p;
}

char *sNCopy(char *dest, const char *src,const int count) {
	char *p =dest;
	int i=0;
	while(i<count) {
		*dest++=*src++;
		i++;
	}
	return p;
}

long sLen(const char *s) {
	// int len=0;
	// while ((s++)!=nullptr) {
	// 	len++;
	// 	// s++;
	// }
	// return len;
	const char *p=s;
	while (*p) {
		p++;
	}
	return p-s;
}

char *sCat(char *dest,const char *src) {
	char *p=dest;
	while (dest!=nullptr) {
		dest++;
	}
	while (src!=nullptr) {
		*dest++=*src++;
	}
	return p;
}