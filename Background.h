#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>



class Background{

	int x;
	int y;
	int width;
	int height;
	int velX;
	int dirX;
	ALLEGRO_BITMAP *image;

public:
	Background(ALLEGRO_BITMAP *image, int x, int y, int velX, int width, int height);
	void DrawBackground();
	void UpdateBackground();


};