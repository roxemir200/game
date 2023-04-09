#include "perso.h"

void initPerso(Personne *p){

int vi,sc;
vi=initTextvie(&p->vie);
sc=initTextscore(&p->score);

(*p).image=IMG_Load("perso1.png");  

p->position.x=0;
p->position.y=450;
p->position.w=100;
p->position.h=100;

p->frame.w=180; 
p->frame.h=218;
p->frame.x=0;
p->frame.y=0;

p->curframe=3;

p->direction=0;
p->v_x = 5;
p->v_grav = 0.3;
p->v_saut = -6.5;
p->v_y = p->v_saut;

p->acceleration=5;
p->vitesse=0;

}


/*void afficherPerso (Personne p,SDL_Surface *screen){

	displayvie(p.vie,screen);
	displayscore(p.score,screen);
	SDL_BlitSurface(p.image,&(p.frame),screen,&(p.position));  
}
*/
void afficherPerso (Personne p,SDL_Surface *screen,SDL_Rect camera_rect){
    SDL_Rect drawingRect= {p.position.x-camera_rect.x,p.position.y-camera_rect.y,p.position.w,p.position.h};
    displayvie(p.vie,screen);
    displayscore(p.score,screen);
    SDL_BlitSurface(p.image,&(p.frame),screen,&(drawingRect));
}



void deplacerPerso(Personne *p ,SDL_Surface *screen,int dt){ 
	
	
	
	if (dt==0){
		while(p->position.y<450) 
   		{ 
     			p->position.y+=3;
    		}
    		p->direction=dt;
    		animerPerso(p);
	
	}
	
	if (dt==1){
		p->position.x+=p->vitesse; 
		p->direction=dt; 
		animerPerso(p);
	
	}
   	
 	if (dt==2){
   		p->position.x-=p->vitesse;
   		p->direction=dt;
   		animerPerso(p);
	
	}
	
	if (dt==3){
		 
		p->position.y-=2; 
	 
	}
	
}


void animerPerso(Personne *p){
	if(p->direction==1)
	{
		p->frame.y=0;
		p->curframe++;
	if(p->curframe>=7)
	{
		p->curframe=3;
	}
		p->frame.x=p->curframe * 180;  

	}	
	else
		if(p->direction==2)
		{ 
			p->frame.y=218;
			p->curframe++;
		if(p->curframe>=7)
		{
			p->curframe=3;
		}
		p->frame.x=p->curframe * 180;  
  
		}
	else 
		if(p->direction==0) 
		{
			p->frame.x=0;

		}

}


void saut(Personne *p){
	
	if(p->position.y<450){
   	p->position.x += p->v_x;
   	p->position.y+= p->v_y;
   	p->v_y += p->v_grav;
   }
  	if (p->position.y> 450)
    	p->v_y = p->v_saut;
}

void sautgauche(Personne *p){
	if(p->position.y<450){
   	p->position.x -= p->v_x;
   	p->position.y+= p->v_y;
   	p->v_y += p->v_grav;
   }
  	if (p->position.y> 450)
    	p->v_y = p->v_saut;


}
void vitesseUP(Personne *p){
	 
       
         p->vitesse+=p->acceleration;
         p->position.x+=p->vitesse; 
         p->direction=1;
         if(p->vitesse>=30)
         {
          p->vitesse=30;
         }
}
void vitesseDOWN(Personne *p){
 	p->vitesse=0; 

}
void scrolling(SDL_Rect *b, int direction, int pas) {
    if (direction == 0) {
        b->x += pas;
    }
    else if (direction == 1) {
        b->x -= pas;
    }
}
SDL_Color getpixel(SDL_Surface *pSurface,int x,int y)//lezem n3dilha el masque 5tr hia fih elloun ak7el //mini
{
	SDL_Color color;
	Uint32 col=0;
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color);
}
int  collisionparfaite(SDL_Surface *psurface,Personne p)
{
	int tabx[7],taby[7],i;//7atit les position de x fi tableau mta3 x o hatit les position mat3 y fi tableau mta3 y o 3mlt coleur chntstih bih
	SDL_Color color1,color;//color lil test
	color1.r = 0;
	color1.g = 0;
	color1.b = 0;
	tabx[0]=p.position.x;
	tabx[1]=(p.position.x)+((p.position.w)/2);
	tabx[2]=(p.position.x+p.position.w);
	tabx[3]=p.position.x;
	tabx[4]=p.position.x;
	tabx[5]=(p.position.x)+((p.position.w)/2);
	tabx[6]=(p.position.x+p.position.w);
	tabx[7]=(p.position.x+p.position.w);
	taby[0]=p.position.y;
	taby[1]=p.position.y;
	taby[2]=p.position.y;
	taby[3]=(p.position.y)+((p.position.h)/2);
	taby[4]=(p.position.y+p.position.h);
	taby[5]=(p.position.y+p.position.h);
	taby[6]=(p.position.y+p.position.h);
	taby[7]=(p.position.y)+((p.position.h)/2);

	for(i=0;i<8;i++)
	{
	color=getpixel(psurface,tabx[i],taby[i]);//trj3lik el coleur ili inty fih
	if(color.r==color1.r && color.b==color1.b && color.g==color1.g)
	{
		return i;//trj3li indice win saret collision

	}
	}
	return 10;//maasartch collision kain raja3li 1

}

void collision(SDL_Surface *psurface,Personne *p)//il suffit saret collision scrolling leze nwkfo wktli collisionparfaite traja3 10 ya3ni mfmfch collision
{	int i;
	i=collisionparfaite(psurface,*p);

	switch (i)//wkt tsir collisision el perso idizo chwya
	{
		case 0 :p->position.y=p->position.y+20;
			break;
		case 1 :p->position.y=p->position.y+20;
			 break;
		case 2 :p->position.y=p->position.y+20;
			break;
		case 3 :p->position.x=p->position.x+20;
			break;
	        case 4 :p->position.y=p->position.y-20;
			break;
		case 5 :p->position.y=p->position.y-50;
			break;
		case 6 :p->position.y=p->position.y-30;
			break;
		case 7 :p->position.x=p->position.x-20;
			break;


	}
}
void Timer(int *tempsdebut)//t5rjli kdch 3ndi min seconde mili bdit nl3eb
{

   if( SDL_GetTicks() - *tempsdebut >= 1000 )//kain el wkt b3ed ili bdit fih -wakt bdit fih 3mlt seconde rw tempsdebut hot fih wakt el jdid
    {
        *tempsdebut = SDL_GetTicks() ;


    }

}

void inittemps(Time *t)
{   int test;
	t->tempsdebut=SDL_GetTicks();//thseblk kdch el wakt ili bdit fih execution
	t->mm=0;
	t->ss=0;
	test=initTexttime(&t->temps);
}
void inittempsenig(Time *t)
{   int test;
	t->tempsdebut=0;
	t->mm=0;
	t->ss=0;
	test=initTexttimeenig(&t->temps);
}
int initTexttime(Text* T)
{ int testload;
    T->couleurTxt.r = 0;
    T->couleurTxt.g = 0;
    T->couleurTxt.b = 0;

    strcpy(T->txt,"");
    T->positionText.x = 850;
    T->positionText.y = 50;
    testload=loadFonttime(T,"angelina.TTF");//fct 3mltha bich tlodili el font trj3li zero kain loadfont sar mrigl
    T->textSurface=NULL;
    return testload;
}
int initTexttimeenig(Text* T)
{ int testload;
    T->couleurTxt.r = 255;
    T->couleurTxt.g = 255;
    T->couleurTxt.b = 255;

    strcpy(T->txt, "");
    T->positionText.x = 0;
    T->positionText.y = 0;
    testload=loadFonttime(T,"angelina.TTF");
    T->textSurface=NULL;
    return testload;
}
int loadFonttime(Text* T, char* path)
{
    if(TTF_Init() == -1) {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    T->police= TTF_OpenFont(path,60);//pathn hoa esm l font o 60 l taile
    if (T->police == NULL) {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}

void update_time(Time* T)
{   int ts;
    Timer(&T->tempsdebut);//raj3tli kdch min milliseconde
    ts=T->tempsdebut/1000;//rdithom b seconde
    T->mm=ts/60;//kdch min min
    T->ss=ts % 60;//kdch min seconde ts mode 60
    if(T->mm<10&&T->ss<10)
       sprintf(T->temps.txt,"*** time :0%d:0%d  ***",T->mm,T->ss);
    else if(T->mm<10&&T->ss>10)
        sprintf(T->temps.txt,"*** time :0%d:%d  ***",T->mm,T->ss);
    else if(T->mm>10&&T->ss<10)
          sprintf(T->temps.txt,"*** time :%d:0%d  ***",T->mm,T->ss);//s y3ni chnktb fi variable chaine
    else
         sprintf(T->temps.txt,"*** time :%d:%d  ***",T->mm,T->ss);

    T->temps.textSurface=TTF_RenderText_Solid(T->temps.police,T->temps.txt,T->temps.couleurTxt);//ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
}
void update_timeenig(Time* T)
{   int ts;

    Timer(&T->tempsdebut);
    ts=T->tempsdebut/1000;
    T->mm=ts/ 60;
    T->ss=ts % 60;
    if(T->mm<10&&T->ss<10)//idhkain minute et seconde asgher min 10
       sprintf(T->temps.txt,"*** time :0%d:0%d  ***",T->mm,T->ss);
    else if(T->mm<10&&T->ss>10)
        sprintf(T->temps.txt,"*** time :0%d:%d  ***",T->mm,T->ss);
    else if(T->mm>10&&T->ss<10)
          sprintf(T->temps.txt,"*** time :%d:0%d  ***",T->mm,T->ss);
    else
         sprintf(T->temps.txt,"*** time :%d:%d  ***",T->mm,T->ss);
    T->temps.textSurface=TTF_RenderText_Solid(T->temps.police,T->temps.txt,T->temps.couleurTxt);//ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
}
void displaytime(Time T,SDL_Surface *screen)
{


     SDL_BlitSurface(T.temps.textSurface,NULL,screen,&(T.temps.positionText));

}

void freeTexttime(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}
void initialiser_map (map *m,SDL_Surface *screen)
{
	m->map=IMG_Load("ppppp.png");
	m->pos_map.x = 0;// equiv (*m).pos_map.x=1000;
	m->pos_map.y = 120;
	m->mini_perso=SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF,10,10,32,0,0,0,0);//hedhy taaml mouraba fil mini map ali houwa l perso mlwn mich bich nlskfih tswira o cht5dmli sur 32 bit 3al qualite ta image o sout
	SDL_FillRect(m->mini_perso,NULL,SDL_MapRGB(screen->format,0,255,0));// lel couleur
	m->perso_pos_map.x=0;
	m->perso_pos_map.y=0;

}


void perso_map(map *m,Personne *p)
{
	m->perso_pos_map.x=p->position.x/10+m->pos_map.x;//9otlo kif perso ikdem b 5otha el perso ta mini map lezem 1/10 5otwa ili 3mlha fil 7kika ikadem o m->pos_map.x bich ijibnifil minimap bidhbt
	m->perso_pos_map.y=p->position.y/10+10+m->pos_map.y;// besh l position ta" l mini perso iji kad kad maa l perso lekbir 3al axe y 5tr perso taille ta3o y akber dima ybda 3ndi probleme k3de nzid fi y wa7di bich tjini kadkad
}



void affiche_map(map m , SDL_Surface *screen)
{
	SDL_BlitSurface(m.map, NULL, screen,&m.pos_map);
	SDL_BlitSurface(m.mini_perso, NULL, screen,&m.perso_pos_map);
}




























