#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#define MAX_CAPACITY_BITS 4096


/*
	BitMap(λͼ): �� 1bit λ����ʾһ�����Ĵ������uint_32t���ͱ�����ʹ��λͼ���Դ洢32������
	uint32_t arr[4096] ռ�� 16KB �ռ�
	uint32_t arr[128]  ռ�� 512B �ռ�
	16KB/512B = 32 ��
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