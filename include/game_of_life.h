#pragma once

#include <stdlib.h>
#include <stdbool.h>

static const int WORLD_SIZE = 100;

void generateWorld(bool[WORLD_SIZE][WORLD_SIZE]);
void drawWorld(bool[WORLD_SIZE][WORLD_SIZE]);
int toUint(bool[WORLD_SIZE][WORLD_SIZE], int const, int const);
void updateCell(bool const, bool*, int const);
void updateWorld(bool[WORLD_SIZE][WORLD_SIZE], bool[WORLD_SIZE][WORLD_SIZE]);
void app();
void drawWorld(bool[WORLD_SIZE][WORLD_SIZE]);
