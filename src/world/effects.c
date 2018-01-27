/*
Copyright (C) 2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "effects.h"

static int fleshChunk[3];
static int debris[3];

void initEffects(void)
{
	fleshChunk[0] = getSpriteIndex("FleshChunk1");
	fleshChunk[1] = getSpriteIndex("FleshChunk2");
	fleshChunk[2] = getSpriteIndex("FleshChunk3");

	debris[0] = getSpriteIndex("Debris1");
	debris[1] = getSpriteIndex("Debris2");
	debris[2] = getSpriteIndex("Debris3");
}

void addExplosionEffect(int x, int y, float dx, float dy)
{
}

void addSmallFleshChunk(double x, double y)
{
	Entity *chunk;
	
	chunk = malloc(sizeof(Entity));
	memset(chunk, 0, sizeof(Entity));
	world.entityTail->next = chunk;
	world.entityTail = chunk;
	
	chunk->x = x;
	chunk->y = y;
	chunk->dx = 0;
	chunk->dy = 0;
	chunk->health = FPS / 4;
	chunk->sprite[0] = chunk->sprite[1] = chunk->sprite[2] = fleshChunk[0];
}

void throwFleshChunks(double x, double y, int amount)
{
	int i;
	Entity *chunk;
	
	for (i = 0; i < amount; i++)
	{
		chunk = malloc(sizeof(Entity));
		memset(chunk, 0, sizeof(Entity));
		world.entityTail->next = chunk;
		world.entityTail = chunk;
		
		chunk->x = x;
		chunk->y = y;
		chunk->dx = rrnd(-2, 2);
		chunk->dy = -rrnd(10, 15);
		chunk->health = FPS * rrnd(3, 12);
		chunk->sprite[0] = chunk->sprite[1] = chunk->sprite[2] = fleshChunk[i % 3];
	}
}