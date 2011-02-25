/*
 * Copyright (C) 2011 <fwhacking|gmail:com>
 *
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "mpimg.h"

static void print_usage(const char *name)
{
	printf("Usage: %s firmware\n", name);
}

int main(int argc, char **argv)
{
	FILE *fd;
	MP_HEADER *hdr;
	MP_PART *part;
	unsigned char *fp;
	char magic[16];
	char name[32];
	long size;

	if (argc != 2)
	{
		print_usage(argv[0]);
		exit(1);
	}

	fd = fopen(argv[1], "rb");
	if (fd == NULL)
	{
		printf("Could not read the firmware file '%s'\n", argv[1]);
		print_usage(argv[0]);
		exit(1);
	}

	size = fseek(fd, 0L, SEEK_END);
	size = ftell(fd);
	printf("Firmware file size : %ld bytes\n\n", size);
	fseek(fd, 0L, SEEK_SET);

	fp = malloc(size);
	fread(fp, size, 1, fd);
	fclose(fd);

	hdr = (MP_HEADER *) fp;
	
	memcpy(magic, hdr->magic, 8);
	magic[8] = '\0';
	
	if (strncmp("adma1.01", magic, 9) != 0)
	{
		printf("Magic 'adma1.01' not found\n");
		free(fp);
		exit(1);
	}
	
	memcpy(name, hdr->name, 32);
	name[31] = '\0';

	printf("HEADER\n");
	printf("-------------------------------------\n");
	printf("MAGIC\t\t%s\n", magic);
	printf("CRC32\t\t0x%08X\n", hdr->crc32);
	printf("VERSION\t\t%d.%d\n", hdr->majver, hdr->minver);
	printf("NAME\t\t%s\n", name);
	printf("-------------------------------------\n\n");
	
	part = (MP_PART *) (fp + sizeof(MP_HEADER));
	
	printf("PART 1\n");
	printf("-------------------------------------\n");
	printf("MAGIC\t\t%x\n", part->magic);
	printf("LENGTH\t\t%d\n", part->length);
	printf("-------------------------------------\n\n");

	part = (MP_PART *) (fp + sizeof(MP_HEADER) + sizeof(MP_PART) + part->length);
	
	printf("PART 2\n");
	printf("-------------------------------------\n");
	printf("MAGIC\t\t%x\n", part->magic);
	printf("LENGTH\t\t%d\n", part->length);
	printf("-------------------------------------\n\n");

	free(fp);

	exit(0);
}
