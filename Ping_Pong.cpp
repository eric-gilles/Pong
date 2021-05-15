#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>				
#include <math.h>
#include <Windows.h>

#include "SDL.h"				
#include "SDL_ttf.h"			

#include "Entete_Ping_Pong.h"


SDL_Surface * Init_Fenetre(int,int,int,char *);
void Blitter_Surface(SDL_Surface *, SDL_Surface *, int, int);
void balle_mouvement(int *,int * , SDL_Surface *,int *,int *,int ,int,int *,int *,bool * );
void debut(int *,int*,bool,bool*,int*);
void deplacement_raquette(int *, int *, bool , bool , bool , bool );

int main(int argc, char *argv[]){
	
	bool begin = false;
	bool pause = false;
	bool up=false, down=false, d=false, c=false;
	bool Point = false;
	bool *pt_Point = &Point;
	bool win_R =false,win_B=false;

	int continuer = 0;
	int sens_X,sens_Y;
	int *pt_sens_X = &sens_X,*pt_sens_Y = &sens_Y;
	int X = D_B_X ,Y = D_B_Y;
	int *pt_X = &X,*pt_Y = &Y;

	int Sens_X_D;
	int *pt_Sens_X_D = &Sens_X_D;

	int X_R = X_RR ,Y_R = 287;
	int X_B = X_RB ,Y_B = 287;
	int * pt_Y_R = &Y_R;
	int * pt_Y_B = &Y_B;

	int Score_R = 0,Score_B = 0;
	int *pt_Score_R = &Score_R, *pt_Score_B = &Score_B;

	char score_r[2],score_b[2];
	

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface * screen = Init_Fenetre(LARGEUR_ECRAN,HAUTEUR_ECRAN,MY_BITMAP,NOM_FENETRE);
	SDL_Event event;
	
	SDL_Surface *balle=NULL;
	balle =SDL_LoadBMP("Bitmap/balle.bmp");

	SDL_Surface *Raquette_B=NULL;
	Raquette_B =SDL_LoadBMP("Bitmap/Raquette_B.bmp");

	SDL_Surface *Raquette_R=NULL;
	Raquette_R =SDL_LoadBMP("Bitmap/Raquette_R.bmp");

	SDL_Surface *fond = NULL;
	fond=SDL_LoadBMP("Bitmap/fond.bmp");

	SDL_Surface *aide = NULL;
	aide = SDL_LoadBMP("Bitmap/help.bmp");
	//service
	SDL_Surface *Service_R = NULL;
	Service_R = SDL_LoadBMP("Bitmap/Service_R.bmp");

	SDL_Surface *Service_B = NULL;
	Service_B = SDL_LoadBMP("Bitmap/Service_B.bmp");
	//win
	SDL_Surface *Ecran_R = NULL;
	Ecran_R = SDL_LoadBMP("Bitmap/rouge_Win.bmp");

	SDL_Surface *Ecran_B = NULL;
	Ecran_B = SDL_LoadBMP("Bitmap/Bleu_Win.bmp");
	//TTF
	TTF_Init();
	SDL_Color couleur_texte_noire = {0, 0, 0};
	TTF_Font *police = TTF_OpenFont("arial.ttf",90);
	SDL_Surface *image = TTF_RenderText_Blended(police,"0", couleur_texte_noire);
	SDL_Surface *image2 = TTF_RenderText_Blended(police,"0", couleur_texte_noire);





	while (continuer != 1 ) {
		while (SDL_PollEvent (&event)){
			if ( event.type == SDL_QUIT){
			continuer = 1;
			break;
			}

			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_a:{
						continuer = 1;
						break;}
					case SDLK_SPACE:{
						if(begin == false){ 
							debut(pt_sens_X,pt_sens_Y,begin,pt_Point,pt_Sens_X_D);
						}
						if (Point == true){
							debut(pt_sens_X,pt_sens_Y,begin,pt_Point,pt_Sens_X_D);
						}
						begin = true;
						Point = false;
						break;
					}
					case SDLK_d:{
						d = true;
						break;
					}
					case SDLK_c:{
						c = true;
						break;
					}
					case SDLK_UP:{
						up = true;
						break;
					}
					case SDLK_DOWN:{
						down = true;
						break;
					}
					case SDLK_ESCAPE:{
						pause = false;
						break;
					}
					case SDLK_h:{
						pause = true;
						break;
					}
					case SDLK_KP_ENTER:{
						if ((win_R == true) || (win_B ==true)){
						X = D_B_X;
						Y = D_B_Y;
						Score_R = 0;
						Score_B = 0;
						begin = false;
						pause = false;}
					}

				}
			}
			if (event.type == SDL_KEYUP){
				switch(event.key.keysym.sym){
					case SDLK_d:{
						d = false;
						break;
					}
					case SDLK_c:{
						c = false;
						break;
					}
					case SDLK_UP:{
						up = false;
						break;
					}
					case SDLK_DOWN:{
						down = false;
						break;
					}
				
				}
			}
		}


		if ((pause == false) &&(Point == false)){
		balle_mouvement(pt_X,pt_Y,balle,pt_sens_X,pt_sens_Y,Y_R,Y_B,pt_Score_R,pt_Score_B,pt_Point);
		}
		deplacement_raquette(pt_Y_R,pt_Y_B,down,up,d,c);

		if (pause == true){
			Blitter_Surface(aide, screen, 0, 0);			
		}
		else{
		Blitter_Surface(fond, screen, 0,0);
		Blitter_Surface(balle, screen, X,Y);
		Blitter_Surface(Raquette_B, screen, X_B,Y_B);
		Blitter_Surface(Raquette_R, screen, X_R,Y_R);
		if (Sens_X_D == 0){
			Blitter_Surface(Service_R, screen, S_R,S_Y);
		}
		else{
			Blitter_Surface(Service_B, screen, S_B,S_Y);
		}
		itoa (Score_R, score_r, 10 );
		itoa (Score_B, score_b, 10 );
		image = TTF_RenderText_Blended(police,score_r, couleur_texte_noire);
		image2 = TTF_RenderText_Blended(police,score_b, couleur_texte_noire);
		Blitter_Surface(image, screen, 120,650);
		Blitter_Surface(image2, screen, 920,650);
		if (Score_B ==5){
			Blitter_Surface(Ecran_B, screen, 0,0);
			win_B = true;
		}
		if (Score_R ==5){
			Blitter_Surface(Ecran_R, screen, 0,0);
			win_R = true;
		}

		}
		SDL_Flip(screen);

	}
	//free surfaces
	SDL_FreeSurface(balle);
	SDL_FreeSurface(fond);
	SDL_FreeSurface(Raquette_B);
	SDL_FreeSurface(Raquette_R);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(aide);
	SDL_FreeSurface(Service_B);
	SDL_FreeSurface(Service_R);
	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(Ecran_R);
	SDL_FreeSurface(Ecran_B);
	TTF_CloseFont(police);
	TTF_Quit;
	SDL_Quit();
	

		

	 return 0;
	}
	


	
	


   



SDL_Surface * Init_Fenetre(int largeur, int hauteur, int nb_bits, char * nom_fenetre)
{
    SDL_Surface * screen = NULL;

  
    //atexit(SDL_Quit);

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) return NULL;

    SDL_WM_SetCaption(nom_fenetre , NULL); 

    screen = SDL_SetVideoMode( largeur , hauteur , nb_bits , SDL_DOUBLEBUF|SDL_ANYFORMAT|SDL_HWSURFACE);

    return screen;
}


void Blitter_Surface(SDL_Surface * source, SDL_Surface * destination, int X_offset, int Y_offset)
{
    SDL_Rect offset;
    offset.x = X_offset;
    offset.y = Y_offset;

    SDL_BlitSurface(source, NULL, destination, &offset);

    return;
}

void balle_mouvement(int  *X,int *Y,SDL_Surface * balle,int *sens_X,int *sens_Y,int pt_Y_R,int pt_Y_B,int *Score_R,int *Score_B,bool *Point){

	// comptage point
	if (*X >= 1028){
		*Score_R = *Score_R + 1;
		*X = D_B_X;
		*Y = D_B_Y;
		*Point = true;
	}
	else if (*X <= 0){
		*Score_B = *Score_B + 1;
		*X = D_B_X;
		*Y = D_B_Y;
		*Point = true;
	}

	// Rebond sur le mur haut et bas 
	if (*Y >= 574){
		*sens_Y = 0;
	}

	else if (*Y <= 0){
		*sens_Y = 1;
	}


	//Rebond raquette
	if (((*X+taille_balle) > X_RR) && ((*X) < (X_RR + LARGEUR_RR)) && ((*Y+taille_balle)>pt_Y_R) && (*Y<(pt_Y_R + HAUTEUR_RR))){
		*sens_X =1;	
	}
	if (((*X+taille_balle) > X_RB) && ((*X+taille_balle) < (X_RB + LARGEUR_RB)) && ((*Y+taille_balle)>pt_Y_B) && (*Y<(pt_Y_B + HAUTEUR_RB))){
		*sens_X = 0;	
	}
	

	if (*sens_X == 1){
		*X+=DELTA_BALLE;	
		}
	else if (*sens_X == 0 ){
		*X-=DELTA_BALLE;
		}
	
	if (*sens_Y == 1){
		*Y+=DELTA_BALLE;	
		}
	else if (*sens_Y == 0 ){
		*Y-=DELTA_BALLE;
		}
	
}

void debut(int *sens_X,int *sens_Y,bool Start,bool *Point,int *sens_X_D){
	srand((time(NULL)));
	if (Start == false){
		*sens_X = rand()%2;
		*sens_X_D = *sens_X;
	}
	if (*Point == true){
		*sens_X = *sens_X_D + 1;
		if (*sens_X > 1) {
			*sens_X = 0;
		}
		*sens_X_D = *sens_X;	
	}
	
	*sens_Y = rand()%2;

}


void deplacement_raquette(int *pt_R, int *pt_B, bool down, bool up , bool d, bool c){

	if ((up == true) && (down == false)){
		*pt_B = *pt_B - DELTA_RAQUETTE;
		if(*pt_B <0)
		{
		*pt_B = 0;
		}

	}
	else if ((up == false) && (down == true) ){
		*pt_B = *pt_B + DELTA_RAQUETTE;
		if((*pt_B + HAUTEUR_RB)> HAUTEUR_TERRAIN)
		{
		*pt_B = HAUTEUR_TERRAIN - HAUTEUR_RB;
		}
	}


	if ((d == true) && (c == false)){
		*pt_R = *pt_R - DELTA_RAQUETTE;
		if(*pt_R <0)
		{
		*pt_R = 0;
		}
	}
	else if ((d == false) && (c == true) && (*pt_R < 505)){
		*pt_R = *pt_R + DELTA_RAQUETTE;

		if((*pt_R + HAUTEUR_RR)> HAUTEUR_TERRAIN)
		{
		*pt_R = HAUTEUR_TERRAIN - HAUTEUR_RR;
		}
	}

 return;	
}