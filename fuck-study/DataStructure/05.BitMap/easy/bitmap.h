#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#define MAX_CAPACITY_BITS 4096


/*
	BitMap(位图): 用 1bit 位来表示一个数的存在与否，uint_32t类型变量，使用位图可以存储32个数字
	uint32_t arr[4096] 占用 16KB 空间
	uint32_t arr[128]  占用 512B 空间
	16KB/512B = 32 倍
*/

typedef struct bitmap {
	uint32_t* array;
	size_t bits;
}BitMap;

BitMap* bitmap_create(size_t bits);

void bitmap_destroy(BitMap* bm);

// n is a bit index
void bitmap_set(BitMap* bm, size_t n); 

void bitmap_unset(BitMap* bm, size_t n);

bool bitmap_isset(BitMap* bm, size_t n);

void bitmap_clear(BitMap* bm);