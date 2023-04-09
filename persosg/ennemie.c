#include "perso.h"
void initennemi(enemie*e)
{
    e->spritesheet=IMG_Load("ennemi_spr.png");  // Chargement de la sprite sheet de l'ennemi
if ((e->spritesheet)==NULL)
printf("erreur d ennemi %s",SDL_GetError());
    e->curframe=0;            // Initialisation de la frame à 0
    e->direction=0;        // Initialisation de la direction à droite
    e->pos.x=550;         // Initialisation de la position x de l'ennemi
    e->pos.y=550;          // Initialisation de la position y de l'ennemi
    e->frame.x=0;       // Initialisation de la frame x de l'ennemi
    e->frame.y=0;       // Initialisation de la frame y de l'ennemi
    e->frame.h=100;     // Initialisation de la hauteur de la frame de l'ennemi
    e->frame.w=100;     // Initialisation de la largeur de la frame de l'ennemi
    e->posmax.x=500;      // Initialisation de la position maximale x de l'ennemi
    e->posmin.x=0;      // Initialisation de la position minimale x de l'ennemi

}


void afficherennemi(enemie *e, SDL_Surface * screen)
{
    
	SDL_BlitSurface(e->spritesheet,&(e->frame),screen,&(e->pos));  // Affichage de l'ennemi sur l'écran

}

void animerennemi( enemie * e)
{

	if(e->direction==0)
	{
		e->frame.y=0;
		e->curframe++;
	if(e->curframe>=4)
	{
		e->curframe=0;
	}
		e->frame.x=e->curframe * 100;  

	}	
	else
		if(e->direction==1)
		{ 
			e->frame.y=100;
			e->curframe++;
		if(e->curframe>=4)
		{
			e->curframe=0;
		}
		e->frame.x=e->curframe * 100;  
  
		}
		else 
		if(e->direction==2) 
		{
			e->frame.x=0;

		}
	

}


void deplacer( enemie * e)
{
	switch (e->direction)
	{
	case 0 : 
		e->pos.x+=5;
		if (e->pos.x > e->posmax.x)
		e->direction=1;
		break;
	case 1 :
	e->pos.x-=5;
	if (e->pos.x < e->posmin.x)
		e->direction=0;	
	break;			
	}
}
/*int collision(SDL_Rect E, SDL_Rect p)
{
    int collision,px,py;
    px=p.x; // on calcule la position x du personnage + la largeur de son sprite
    py=p.y; // on calcule la position y du personnage + la hauteur de son sprite
    if (((px + p.w) < ) || (px > (E.x + E.w)) || ((py + p.h) < E.y) || (py > (E.y + E.h)))   // si le personnage ne touche pas l'ennemi
    {
        collision = 0;
    }
    else
    {
        collision = 1; // si le personnage touche l'ennemi
    }

    return collision;
}*/
int collisionbb(SDL_Rect E, SDL_Rect p)
{
    if (E.x < (p.x + p.w) && (E.x + E.w) > p.x && E.y < (p.y + p.h) && (E.y + E.h) > p.y) {
        // Les deux boîtes englobantes se chevauchent, il y a collision
        return 1;
    } else {
        // Pas de collision détectée
        return 0;
    }
}


void deplacerIA_2players(enemie *E, SDL_Rect posPerso1, SDL_Rect posPerso2)
{
    int range = posPerso1.w , range1=posPerso1.w; // set the range within which the enemy will start following the player
    int distanceToPlayer1 = abs(E->pos.x - posPerso1.x);
    int distanceToPlayer2 = abs(E->pos.x - posPerso2.x);
    if (E->pos.x > posPerso1.x + range1 && E->pos.x > posPerso2.x + range1) { // if the enemy is to the right of both players and out of range
        E->direction = 1; // set direction to right
        E->pos.x -= 5; // move the enemy left
    }
    else if (E->pos.x < posPerso1.x + range && E->pos.x < posPerso2.x + range) { // if the enemy is to the left of both players and out of range
        E->direction = 0; // set direction to left
        E->pos.x += 5; // move the enemy right
    }
    if ((E->pos.x > posPerso1.x + range1 && E->pos.x < posPerso2.x + range1)||(E->pos.x < posPerso1.x + range1 && E->pos.x > posPerso2.x + range1))//if the enemy is between both players
    {
        if (distanceToPlayer1<distanceToPlayer2)
        {
                if (E->pos.x > posPerso1.x + range1) { // if the enemy is to the right of the player and out of range
        E->direction = 1; // set direction to right
        E->pos.x -= 5; // move the enemy left
    }
    else if (E->pos.x < posPerso1.x + range) { // if the enemy is to the left of the player and out of range
        E->direction = 0; // set direction to left
        E->pos.x += 5; // move the enemy right
    }
        }
        else{
                if (E->pos.x > posPerso2.x + range1) { // if the enemy is to the right of the player and out of range
        E->direction = 1; // set direction to right
        E->pos.x -= 5; // move the enemy left
    }
    else if (E->pos.x < posPerso2.x + range) { // if the enemy is to the left of the player and out of range
        E->direction = 0; // set direction to left
        E->pos.x += 5; // move the enemy right
    }
        }
    }
}
void deplacerIA(enemie *E, SDL_Rect posPerso1)
{
    int range = posPerso1.w; // set the range within which the enemy will start following the player
    int distanceToPlayer1 = abs(E->pos.x - posPerso1.x);
    if (E->pos.x > posPerso1.x + range) { // if the enemy is to the right of the player and out of range
        E->direction = 1; // set direction to right
        E->pos.x -= 1; // move the enemy left
    }
    else if (E->pos.x < posPerso1.x) { // if the enemy is to the left of the player and out of range
        E->direction = 0; // set direction to left
        E->pos.x += 1; // move the enemy right
    }
}
