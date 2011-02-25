/*
 * Copyright (C) 2011 <fwhacking|gmail:com>
 *
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 */

#ifndef _MPIMG_H_
#define _MPIMG_H_

typedef struct _MP_PART
{
	char magic;
	char padding[3];
	char length[4];
} MP_PART;

typedef struct _MP_HEADER
{
	char magic[8];
	uint32_t crc32;
	uint8_t minver;
	uint8_t majver;
	char padding[2];
	char name[32];
} MP_HEADER;

#endif // _MPIMG_H_
