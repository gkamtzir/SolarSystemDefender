#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Bullet.h"

const int WIDTH = 1200;
const int HEIGHT = 800;

Bullet::Bullet(){

	bulletSpeed = 10;
}



void Bullet::GetCooBullet(Player Zentes){
	bulletx = Zentes.GetX();
	bullety = Zentes.GetY() + 53;
}

void Bullet::UpdateBullet(){

	
	bulletx += bulletSpeed;

	
}

void Bullet::DrawBullet(ALLEGRO_BITMAP *Bullets){

	al_draw_bitmap(Bullets, bulletx, bullety, 0);
}


bool Bullet::AliveBullet(){

	if (bulletx > WIDTH){
		return false;
	}
	else{
		return true;
	}
}


bool Bullet::CheckForCollisionComet(Comets comet){


	if (bulletx + 30 > comet.GetCometX() +30 - comet.GetCometBX() &&
		bulletx + 30 < comet.GetCometX() +30 + comet.GetCometBX() &&
		bullety +15 > comet.GetCometY() +30 - comet.GetCometBY() &&
		bullety + 15 < comet.GetCometY() +30 + comet.GetCometBY())
	{
		return true;

	}
	else {
		return false;
	}

}

void Bullet::CheckForDrawingExplosionComet(Comets comet, ALLEGRO_BITMAP *Explosion){
	if (bulletx +30> comet.GetCometX()+30 - comet.GetCometBX() &&
		bulletx +30< comet.GetCometX()+30 + comet.GetCometBX() &&
		bullety +15> comet.GetCometY()+30 - comet.GetCometBY() &&
		bullety +15 < comet.GetCometY()+30 + comet.GetCometBY())
	{
	
		al_draw_bitmap(Explosion, comet.GetCometX() - 40, comet.GetCometY() - 40, 0);
		
	}
}

