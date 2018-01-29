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

#include "../../common.h"

extern Sprite *getSprite(char *name);
extern void nothing(void);
extern void addMIATeleportStars(float x, float y);
extern void addTeleportStars(Entity *e);
extern void setGameplayMessage(int type, char *format, ...);
extern void playSound(int snd, int ch);
extern void updateObjective(char *targetName);
extern void addRescuedMIA(char *name);

extern Entity *self;
extern World world;