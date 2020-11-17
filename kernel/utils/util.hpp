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

int atoi(const char* str);

int itoa(int num, char* buf, int bufSize);

#endif