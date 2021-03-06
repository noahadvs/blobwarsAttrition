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
#include "../../json/cJSON.h"

extern void addTeleporterEffect(float x, float y);
extern Structure *createStructure(void);
extern Sprite *getSprite(char *name);
extern int isOnScreen(Entity *e);
extern void observeActivation(Entity *e);
extern void playBattleSound(int snd, int ch, int x, int y);
extern void setGameplayMessage(int type, char *format, ...);
extern void teleportEntity(Entity *e, float tx, float ty);

extern App app;
extern Entity *self;
