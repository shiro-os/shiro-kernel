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

#include "types.h"

/**
 * @brief Sets characters to stdio
 * 
 * @param x 
 * @param y 
 * @param c 
 */
void setchar(int x, int y, char c);

/**
 * @brief Set char color 
 * 
 * @param x 
 * @param y 
 * @param color 
 */
void setcharcolor(int x, int y, uint8_t color);

/**
 * @brief Return the lenght [int] of a given chararray
 * 
 * @param str 
 * @return int 
 */
int strlen(char * str);

/**
 * @brief Clear console screen
 */
void cls();

/**
 * @brief Set color for given object
 * 
 * @param color 
 */
void setColor(uint8_t color);

/**
 * @brief Print out data in stdio
 * 
 * @param msg 
 */
void puts(const char *msg);

#endif