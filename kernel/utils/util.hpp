/**
 * @file util.h
 * @author Marcus Kram (m.kram@live.at)
 * @brief 
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __UTIL_H_
#define __UTIL_H_

#include "../types.h"

/**
 * @brief Return the lenght [int] of a given chararray
 * 
 * @param str 
 * @return int 
 */
int strlen(const char* str);
int strlen(const unsigned char* str);

int strcpy(const char* src, char* dst);
bool strcmp(const char* str0, const char* str1);

int atoi(const char* str);
int itoa(int num, char* buf, int bufSize);

void memcpy(const char* src, char* dst, int length);
void memfill(void* src, unsigned char toFill, unsigned int len);

#endif