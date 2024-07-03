#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>
#include <stdbool.h>
#define BITS_PER_WORD 32
#define BITMAP_SHIFT 5
#define BITMAP_MASK 31
#define BITMAP_SIZE(bits) ((bits + BITS_PER_WORD - 1) >> BITMAP_SHIFT)


typedef uint32_t word;

typedef struct {
    word* array;
    size_t    bits;
} BitMap;

BitMap* bitmap_create(size_t bits);

void bitmap_destroy(BitMap* bm);

void bitmap_set(BitMap* bm, size_t n);

void bitmap_unset(BitMap* bm, size_t n);

bool bitmap_isset(BitMap* bm, size_t n);

void bitmap_clear(BitMap* bm);