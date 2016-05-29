#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Player.h"
#include "Comets.h"



class Bullet{

	int bulletx;
	int bullety;
	int boundx;
	int boundy;
	int bulletSpeed;

public:
	Bullet();
	void UpdateBullet();
	void DrawBullet(ALLEGRO_BITMAP *Bullets);
	void GetCooBullet(Player Zentes);
	bool AliveBullet();
	bool CheckForCollisionComet(Comets comet);
	void CheckForDrawingExplosionComet(Comets comet, ALLEGRO_BITMAP *Explosion);


};

