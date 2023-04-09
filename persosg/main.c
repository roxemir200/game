#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <time.h>
#include "perso.h"

int main()
{
	int hauteur_fenetre = 640,t,a=1,done=1,vi=1,sc=1,dt=0,
        	largeur_fenetre = 2000;
int continuer;
SDL_Rect b;
	enigme en;
SDL_Surface *backgm;
SDL_Rect backgm_pos;
Time temps;
	Time tempsenig;
	map m;

b.x=0;
b.y=0;
b.w=largeur_fenetre;
b.h=hauteur_fenetre;
backgm = IMG_Load("Background2.png");
	backgm_pos.x = 0;
	backgm_pos.y = 0;

int sautt;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

	SDL_Surface *screen;
 intro (&screen);
	 if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("unable to initialize SDL: %s\n",SDL_GetError());
        return 1;
    }
 	screen=SDL_SetVideoMode(largeur_fenetre,hauteur_fenetre,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen==NULL)
    {
        printf("unable to set video mode:%s\n",SDL_GetError());
        return 1;
    }
  
	SDL_WM_SetCaption("JEUX", NULL); 

 	SDL_Surface *backg;
	SDL_Rect backg_pos;
	backg = IMG_Load("Background2.png");
	backg_pos.x = 0;
	backg_pos.y = 0;
enemie e;
   




 
	Personne p;
initennemi(&e);
	
	
	initPerso(&p);
inittemps(&temps);
	inittempsenig(&tempsenig);
	initialiser_map (&m,screen) ;
	 while(done)
    {  
	
    	SDL_PollEvent(&event);

 
     switch(event.type)

     {  
     	case SDL_QUIT: 
		done=0;
		break;
	case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {  
		case SDLK_s: 
               	dt=0;
               	deplacerPerso(&p ,screen,dt);
		break;

		
		case SDLK_d: 
               	dt=1;
                sautt=1;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 0, 10);

		break;
			
		case SDLK_q: 
               	dt=2;
                sautt=2;
               	deplacerPerso(&p ,screen,dt);

		scrolling(&b, 1, 10);

		break;
		case SDLK_SPACE:
			dt=3;
               	deplacerPerso(&p ,screen,dt);

	
			
		break;
		
		case SDLK_UP:
			vitesseUP(&p);
		break;
		
		case SDLK_DOWN:
			vitesseDOWN(&p);
		break;
               
		case SDLK_ESCAPE: 
              		done=0;
		break; 
		
               

                
            }
      
     } 
int coll=collisionbb(e.pos,p.position);
b.x=p.position.x-320;
b.y=p.position.y-1000;
if(b.x < 0)
    b.x=0;
    if(b.y < 0)
    b.y=0; 
collision(backgm,&p);
		update_time(&temps); 
perso_map(&m,&p);
	SDL_BlitSurface(backg,&b,screen,&backg_pos);
displaytime(temps,screen);

		affiche_map(m,screen);
	
		afficherPerso (p,screen,b);
afficherennemi(&e, screen);
deplacerIA(&e, p.position);
 animerennemi(&e);

if(p.position.x>3630){
continuer=afficherenigme(en,screen);
if(continuer==0)
SDL_BlitSurface(backg,&b,screen,&backg_pos);
}
           if(sautt==1)
          {
		saut(&p);
          }
         else if(sautt==2)
               {
              sautgauche(&p);
              }
	/*if(p.position.x==100){
afficherenigme(e,screen);
}*/

/*while(done){
		update_timeenig(&tempsenig);
afficherenigme(e,screen);
		
		displaytime(tempsenig,screen);
		
		if(tempsenig.ss==temps.ss+15)
		{
                  done=0;
		}}

}*/

		
	
     	SDL_Flip(screen);
    }
	freeTexttime(temps.temps);	
	SDL_FreeSurface(backg);
	SDL_Quit();

    return 0;
}










