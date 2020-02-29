/**
 * @file types.h
 * @author Marcus Kram (m.kram@live.at)
 * @brief This class represents all needed custom types which are not served by ANSI-C std
 * @version 0.1
 * @date 2020-02-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef __TYPES_H_
#define __TYPES_H_

/**
 * @brief Definition of BYTE
 */
#define BYTE unsigned char

/**
 * @brief Definition of DWORD
 */
#define DWORD unsigned long

/**
 * @brief Definition of VIDMEM
 */
#define VIDMEM ((BYTE*)0xb8000)
#endif