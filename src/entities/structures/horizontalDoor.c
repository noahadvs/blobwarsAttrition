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

#include "horizontalDoor.h"

Entity *initHorizontalDoor(void)
{
	Structure *s;
	
	s = (Structure*)initDoor();
	
	s->type = ET_DOOR;
	
	s->sprite[0] = s->sprite[1] = s->sprite[2] = getSprite("HorizonalDoor");
	
	return (Entity*)s;
}

Entity *initBronzeHorizontalDoor(void)
{
	Structure *s;
	
	s = (Structure*)initHorizontalDoor();
	
	STRNCPY(s->requiredItem, "Bronze Key", MAX_NAME_LENGTH);
	
	return (Entity*)s;
}

Entity *initSilverHorizontalDoor(void)
{
	Structure *s;
	
	s = (Structure*)initHorizontalDoor();
	
	STRNCPY(s->requiredItem, "Silver Key", MAX_NAME_LENGTH);
	
	return (Entity*)s;
}

Entity *initGoldHorizontalDoor(void)
{
	Structure *s;
	
	s = (Structure*)initHorizontalDoor();
	
	STRNCPY(s->requiredItem, "Gold Key", MAX_NAME_LENGTH);
	
	return (Entity*)s;
}
