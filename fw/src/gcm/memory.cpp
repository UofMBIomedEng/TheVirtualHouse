/*   SCE CONFIDENTIAL                                       */
/*   PLAYSTATION(R)3 Programmer Tool Runtime Library 192.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cell/gcm.h>

#include "gcmutil.h"

using namespace cell::Gcm;

#define dprintf(x)
//#define dprintf(x) printf x

static size_t sLocalBaseAddress = 0;
static size_t sLocalCurrentAddress = 0;
static size_t sLocalSize = 0;

void cellGcmUtilInitializeLocalMemory(const size_t base, const size_t size)
{
	dprintf(("initialize video memory: %x %x\n", base, size));
	sLocalCurrentAddress = sLocalBaseAddress = base;
	sLocalSize = size;
}

void *cellGcmUtilAllocateLocalMemory(const size_t size, const size_t alignment)
{
	dprintf(("size %x, alignment %x\n", size, alignment));

	void *p = (void*)((sLocalCurrentAddress + alignment - 1) & ~(alignment - 1));
	sLocalCurrentAddress = (size_t)p + size;

	dprintf(("video memory: %x %x\n", p, sLocalCurrentAddress));

	if (sLocalCurrentAddress > sLocalBaseAddress + sLocalSize) {
		printf("Out of Local Memory: %x\n", sLocalCurrentAddress);
		exit(1);
	}

	return p;
}

static size_t sMainBaseAddress = 0;
static size_t sMainCurrentAddress = 0;
static size_t sMainSize = 0;
static uint32_t sMainBaseOffset = 0;

uint32_t cellGcmUtilGetOffsetOfMainMemory(void* ea)
{
	assert((size_t)ea < sMainBaseAddress + sMainSize);
	return (size_t)ea - sMainBaseAddress + sMainBaseOffset;
}

void cellGcmUtilInitializeMainMemory(const size_t size)
{
	// allocate system memory
	sMainCurrentAddress = sMainBaseAddress = (size_t)(uint32_t *)memalign(0x100000, size);
	dprintf(("initialize system memory: %x %x\n", sMainBaseAddress, size));
	if (sMainBaseAddress == NULL) {
		printf("Out of Main Memory\n");
		exit(1);
	}
	sMainSize = size;
	// map system memory in RSX's address space
	cellGcmMapMainMemory((void*)sMainBaseAddress, size, &sMainBaseOffset);

	printf("offset of system memory: %x\n", sMainBaseOffset);
}

void *cellGcmUtilAllocateMainMemory(const size_t size, const size_t alignment)
{
	dprintf(("size %x, alignment %x\n", size, alignment));

	void *p = (void*)((sMainCurrentAddress + alignment - 1) & ~(alignment - 1));
	sMainCurrentAddress = (size_t)p + size;

	dprintf(("system memory: %x %x\n", p, sMainCurrentAddress));

	if (sMainCurrentAddress > sMainBaseAddress + sMainSize) {
		printf("Out of Main Memory: %x\n", sMainCurrentAddress);
		exit(1);
	}

	return p;
}
