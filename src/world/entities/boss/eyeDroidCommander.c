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

#include "eyeDroidCommander.h"

static void activate(int activate);
static void tick(void);
static void walk(void);
static void moveTowardsPlayer(void);
static void die1(void);
static void die2(void);
static void selectWeapon(void);
static void attackPistol(void);
static void attackPlasma(void);
static void attackMissile(void);
static void preFire(void);
static void attack(void);
static void applyDamage(int amount);
static int getCurrentSprite(void);

static int brakingTimer;
static int aimedSprite;
static int missileSprite[2];
static int plasmaSprite[2];

void initEyeDroidCommander(Entity *e)
{
	initBoss(e);
	
	STRNCPY(e->name, "EyeDroid Commander", MAX_NAME_LENGTH);

	e->sprite[FACING_LEFT] = getSpriteIndex("DroidCommanderLeft");
	e->sprite[FACING_RIGHT] = getSpriteIndex("DroidCommanderRight");
	e->sprite[FACING_DIE] = getSpriteIndex("DroidCommanderDie");
	
	e->flags |= EF_WEIGHTLESS | EF_EXPLODES;

	e->health = e->healthMax = 250;
	
	e->walk = walk;
	e->tick = tick;
	e->activate = activate;
	e->applyDamage = applyDamage;
	e->getCurrentSprite = getCurrentSprite;

	brakingTimer = 0;
	
	aimedSprite = getSpriteIndex("AimedShot");
	
	missileSprite[0] = getSpriteIndex("MissileRight");
	missileSprite[1] = getSpriteIndex("MissileLeft");
	
	plasmaSprite[0] = getSpriteIndex("PlasmaRight");
	plasmaSprite[1] = getSpriteIndex("PlasmaLeft");
}

static void activate(int activate)
{
	self->flags &= ~EF_GONE;

	world.isBossActive = 1;

	addTeleportStars(self);

	playMusic("", 1);
}

static void tick(void)
{
	if (self->health > 0)
	{
		self->facing = (world.bob->x < self->x) ? FACING_LEFT : FACING_RIGHT;

		self->reload = (int) limit(self->reload - 1, 0, FPS);

		brakingTimer = (int) limit(--brakingTimer, 0, FPS);

		if (brakingTimer > 0)
		{
			self->dx *= 0.95;
			self->dy *= 0.95;
		}
	}
	else
	{
		addSmokeParticles(self->x + (self->w / 2), self->y);
	}
}

static void lookForPlayer(void)
{
	self->thinkTime = rrnd(0, FPS / 2);

	if (rand() % 100 < 5)
	{
		brakingTimer = rrnd(60, 120);
	}

	if (getDistance(world.bob->x, world.bob->y, self->x, self->y) > 650)
	{
		moveTowardsPlayer();
		return;
	}

	if (enemyCanSeePlayer(self))
	{
		moveTowardsPlayer();
		return;
	}

	if (rand() % 100 < 15)
	{
		selectWeapon();
	}

	moveTowardsPlayer();
}

static void selectWeapon(void)
{
	if (world.bob->isOnGround || abs(self->y - world.bob->y) > 64)
	{
		self->weaponType = WPN_AIMED_PISTOL;
		self->shotsToFire = rrnd(1, 12);
		self->action = preFire;
	}
	else if (rand() % 4 == 0)
	{
		self->weaponType = WPN_MISSILE;
		self->shotsToFire = rrnd(1, 3);
		self->action = preFire;
	}
	else
	{
		self->weaponType = WPN_PLASMA;
		self->shotsToFire = rrnd(1, 12);
		self->action = preFire;
	}
}

static void walk(void)
{
	self->action = (self->health > 0) ? lookForPlayer : die1;
}

static void moveTowardsPlayer(void)
{
	if (brakingTimer == 0)
	{
		if (world.bob->x < self->x)
		{
			self->dx -= 0.5;
		}

		if (world.bob->x > self->x)
		{
			self->dx += 0.5;
		}

		if (world.bob->y < self->y)
		{
			self->dy -= 0.5;
		}

		if (world.bob->y > self->y)
		{
			self->dy += 0.5;
		}

		self->dx = limit(self->dx, -7.5, 7.5);
		self->dy = limit(self->dy, -7.5, 7.5);
	}
}

static void preFire(void)
{
	if (self->reload > 0)
	{
		return;
	}

	attack();

	self->shotsToFire--;

	if (self->shotsToFire == 0)
	{
		self->walk();
	}
}

static void attack(void)
{
	switch (self->weaponType)
	{
		case WPN_AIMED_PISTOL:
			attackPistol();
			break;
		case WPN_MISSILE:
			attackMissile();
			break;
		case WPN_PLASMA:
			attackPlasma();
			break;
		default:
			break;
	}
}

static void attackPistol(void)
{
	int bx, by;
	float dx, dy;
	Entity *bullet;
	
	bx = world.bob->x + rrnd(-8, 24);
	by = world.bob->y + rrnd(-8, 24);

	getSlope(bx, by, self->x, self->y, &dx, &dy);

	bullet = createBaseBullet(self);
	bullet->x = (self->x + self->w / 2);
	bullet->y = (self->y + self->h / 2) - 3;
	bullet->facing = self->facing;
	bullet->damage = 1;
	bullet->owner = self;
	bullet->health = FPS * 3;
	bullet->weaponType = WPN_AIMED_PISTOL;
	bullet->dx = dx * 12;
	bullet->dy = dy * 12;
	bullet->sprite[0] = bullet->sprite[1] = aimedSprite;

	self->reload = 4;

	playSound(SND_MACHINE_GUN, CH_WEAPON);
}

static void attackPlasma(void)
{
	Entity *bullet;
	
	bullet = createBaseBullet(self);
	bullet->x = (self->x + self->w / 2);
	bullet->y = (self->y + self->h / 2) - 3;
	bullet->facing = self->facing;
	bullet->damage = 2;
	bullet->owner = self;
	bullet->health = FPS * 3;
	bullet->weaponType = WPN_AIMED_PISTOL;
	bullet->dx = self->facing == FACING_RIGHT ? 15 : -15;
	bullet->dy = 0;
	bullet->sprite[0] = plasmaSprite[0];
	bullet->sprite[1] = plasmaSprite[1];

	self->reload = 4;

	playSound(SND_PLASMA, CH_WEAPON);
}

static void attackMissile(void)
{
	Entity *missile;
	
	missile = createBaseBullet(self);
	missile->x = self->x + self->w / 2;
	missile->y = self->y + self->h / 2;
	missile->facing = self->facing;
	missile->dx = self->facing == FACING_RIGHT ? 15 : -15;
	missile->owner = self;
	missile->health = FPS * 3;
	missile->sprite[0] = missileSprite[0];
	missile->sprite[1] = missileSprite[1];

	self->reload = 15;

	playSound(SND_MISSILE, CH_WEAPON);
}

static void applyDamage(int amount)
{
	self->health -= amount;

	if (self->health <= 0)
	{
		self->health = 0;
		addExplosion(self->x + self->w / 2, self->y + self->h / 2, 50, self);
	}
}

static void die1(void)
{
	self->dx = (randF() - randF()) * 3;

	self->spriteTime = 0;
	self->spriteFrame = 0;

	self->action = die2;
	self->thinkTime = 0;
	self->flags &= ~(EF_WEIGHTLESS | EF_HALT_AT_EDGE);

	self->dy = JUMP_POWER;

	if (rand() % 2)
	{
		playSound(SND_DROID_DIE_1, CH_DEATH);
	}
	else
	{
		playSound(SND_DROID_DIE_2, CH_DEATH);
	}
}

static void die2()
{
	if (self->isOnGround)
	{
		addTeleportStars(self);

		playSound(SND_APPEAR, CH_ANY);

		self->alive = ALIVE_DEAD;

		updateObjective(self->name);

		addDefeatedTarget(self->name);

		game.enemiesKilled++;
	}
}

static int getCurrentSprite(void)
{
	if (self->health <= 0)
	{
		return self->sprite[FACING_DIE];
	}

	return self->sprite[self->facing];
}
