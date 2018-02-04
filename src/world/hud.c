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

#include "hud.h"

static int messageTime;
static char message[MAX_DESCRIPTION_LENGTH];
static int messageType;
static SDL_Color messageColor;

static char infoMessage[MAX_DESCRIPTION_LENGTH];

void initHud(void)
{
	messageTime = FPS * 2;
	messageType = MSG_STANDARD;
	strcpy(message, "");
	messageColor = colors.white;
}

void doHud(void)
{
	messageTime--;
	
	if (messageTime <= 0)
	{
		messageType = MSG_STANDARD;
		
		messageTime = 0;
	}
}

void drawHud(void)
{
	int x, y;
	
	if (messageTime > 0)
	{
		drawRect(0, SCREEN_HEIGHT - 32, SCREEN_WIDTH, 32, 0, 0, 0, 200);
		
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 26, 16, TA_CENTER, messageColor, message);
	}
	
	if (dev.debug)
	{
		x = -camera.x + world.bob->x + (world.bob->w / 2);
		y = -camera.y + world.bob->y - world.bob->h;
		
		drawText(x, y, 14, TA_CENTER, colors.white, "[%.0f, %.0f]", world.bob->x / MAP_TILE_SIZE, world.bob->y / MAP_TILE_SIZE);
	}
}

void setGameplayMessage(int newMessageType, const char *format, ...)
{
	int i;
	char newMessage[MAX_DESCRIPTION_LENGTH];
	va_list args;

	memset(&newMessage, '\0', sizeof(newMessage));

	va_start(args, format);
	vsprintf(newMessage, format, args);
	va_end(args);
	
	if (newMessageType >= messageType && newMessage != NULL)
	{
		STRNCPY(message, newMessage, MAX_DESCRIPTION_LENGTH);
		messageType = newMessageType;
		messageTime = FPS * 3;
		
		for (i = 0 ; i < strlen(message) ; i++)
		{
			message[i] = toupper(message[i]);
		}
		
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%s", message);
		
		switch (messageType)
		{
			case MSG_STANDARD:
			case MSG_GAMEPLAY:
				messageColor = colors.white;
				break;
			
			case MSG_PROGRESS:
				messageColor = colors.cyan;
				break;
			
			case MSG_OBJECTIVE:
				messageColor = colors.green;
				break;
		}
	}
}

void showInfoMessage(char *newInfoMessage)
{
	STRNCPY(infoMessage, newInfoMessage, MAX_DESCRIPTION_LENGTH);

	showWidgetGroup("ok");
}
