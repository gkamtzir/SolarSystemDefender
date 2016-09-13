# SolarSystemDefender
My first completed game. I built it using C++ and Allegro. The actul game has been uploaded on gamejolt.com.

------ MinGW/gcc compiler + allegro 5.0.10 ------
g++ -c Background.cpp Bullet.cpp Comets.cpp Player.cpp main.cpp

g++ Background.o Bullet.o Comets.o main.o Player.o -o game -lallegro-5.0.10-mt -lallegro_primitives-5.0.10-mt -lallegro_font-5.0.10-mt -lallegro_image-5.0.10-mt -lallegro_acodec-5.0.10-mt -lallegro_audio-5.0.10-mt -lallegro_ttf-5.0.10-mt
