#ifndef UTILITAIRE_H_INCLUDED
#define UTILITAIRE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>




typedef struct {

	SDL_Surface* textSurface;
	SDL_Rect positionText;
	char txt[20];
	SDL_Color couleurTxt;
	TTF_Font* police;
    
}text;






int initTextvie(text* T);

void displayvie(text T,SDL_Surface *screen);
void freeTextvie(text T);
int loadFontvie(text* T, char* path);
int initTextscore(text* T);
void displayscore(text T,SDL_Surface *screen);
void freeTextscore(text T);
int loadFontscore(text* T, char* path);


#endif
