#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Background.h"

const int WIDTH = 1200;
const int HEIGHT = 800;

Background::Background(ALLEGRO_BITMAP *image,int x, int y, int velX, int width, int height){

	this->image = image;
	this->x = x;
	this->y = y;
	this->velX = velX;
	this->width = width;
	this->height = height;
	dirX = -1;
}

void Background::DrawBackground(){

	al_draw_bitmap(image, x, y, 0);
	if (x + width < WIDTH){
		al_draw_bitmap(image, x + width, y, 0);
	}
}

void Background::UpdateBackground(){
	
	x += velX * dirX;
	if (x + width <= 0){
		x = 0;
	}

}