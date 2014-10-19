/*
 * Port_droid.h
 *
 *  Created on: 2013-12-5
 *      Author: dell
 */

#ifndef PORT_DROID_H_
#define PORT_DROID_H_

#define TRUE 1
#define FALSE 0

typedef int BOOL;
typedef unsigned int DWORD;

typedef unsigned char BYTE;
typedef unsigned short WORD;

typedef unsigned int COLORREF;
typedef DWORD* LPCOLORREF;

#define GetRValue(rgb)   ((BYTE) (rgb))
#define GetGValue(rgb)   ((BYTE) (((WORD) (rgb)) >> 8))
#define GetBValue(rgb)   ((BYTE) ((rgb) >> 16))

#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

/**
#define GetBValue(rgb)   ((BYTE) (rgb))
#define GetGValue(rgb)   ((BYTE) (((WORD) (rgb)) >> 8))
#define GetRValue(rgb)   ((BYTE) ((rgb) >> 16))

#define RGB(r,g,b) ((COLORREF)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16) | (((BYTE)0xFF)<<24)))
*/

#endif /* PORT_DROID_H_ */
