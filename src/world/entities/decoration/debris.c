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

#include "debris.h"

static void tick(void);
static void action(void);
static void touch(Entity *other);

void initDebris(Entity *e)
{
	initEntity(e);
	
	e->effectType = rand() % 2;

	e->flags |= EF_BOUNCES | EF_IGNORE_BULLETS | EF_KILL_OFFSCREEN | EF_NO_TELEPORT;

	e->tick = tick;
	e->action = action;
	e->touch = touch;
}

static void tick(void)
{
	self->health--;
}

static void action(void)
{
	if (self->effectType == 0)
	{
		addFlameParticles(self->x + (rand() % self->w), self->y + (rand() % self->h));
	}
	else
	{
		addSmokeParticles(self->x + (rand() % self->w), self->y + (rand() % self->h));
	}

	self->thinkTime = 1;
}

static void touch(Entity *other)
{
	if (other == NULL)
	{
		self->dx *= 0.9;
	}
}
