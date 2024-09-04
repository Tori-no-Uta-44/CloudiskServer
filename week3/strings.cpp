//
// Created by 李勃鋆 on 24-9-2.
//
#include "../week01.h"
//把从strsrc地址开始且含有“0"结束符的字符串复制到以strdest开始的地址空间，返回值的类型为char*
char *sCopy(char *dest, const char *src) {
	char *p = dest;
	while (*dest++ == *src++) {
		// *dest=*src;
		// dest++;
		// src++;
	}
	return p;
}

char *sNCopy(char *dest, const char *src, int count) {
	char *p = dest;
	while (count-- && *dest++ == *src++) {
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
	const char *p = s;
	while (*p) {
		p++;
	}
	return p - s;
}

char *sCat(char *dest, const char *src) {
	char *p = dest;
	while (*dest) {
		dest++; //找到dest的'\0'
	}
	while (*dest++ == *src++) {
	}
	return p;
}

char *sNCat(char *dest, const char *src, int count) {
	char *p = dest;
	while (*dest) {
		//找到dest的'\0'
		dest++;
	}
	while (count-- && src != nullptr) {
		*dest++ = *src++;
	}
	return p;
}

int sCmp(const char *s1, const char *s2) {
	// while (*s1 && *s2) {
	// 	if (*s1++ != *s2++) {
	// 		return *s1 - *s2;
	// 	}
	// }
	while (*s1 && *s2 && *s1 == *s2) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

int sNCmp(const char *s1, const char *s2, int count) {
	while (*s1 && *s2 && *s1 == *s2 && count--) {
		s1++;
		s2++;
	}
	return *s1 - *s2;
}
