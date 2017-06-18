/*
 * Fichier : koch_fonctions.c
 * Description : Trace de fractales geometriques - flocon de koch - generation des points et rendu des lignes
 */

#include "koch_fonctions.h"
#include "create_image.h"
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
// TODO

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
void init_koch(struct list **koch, uint32_t size, uint32_t segment_length)
{
  *koch=malloc(sizeof(struct list)); 
  struct list *t=*koch;  //initialisation d'un ponteur courant
  

  t->x=size/4; //On place le segement initial au centre de l'image (image_size= 2*segment_size)
  t->y=size/4;
  t->next=malloc(sizeof (struct list));

  t=t->next;

  t->x=size/4 + segment_length/2;
  t->y=size/4 + (tan(60.0*3.1415/180.0))*segment_length/2;
  t->next=malloc(sizeof (struct list));
  

  t=t->next;

  t->x=size/4 + segment_length;
  t->y=size/4;
  
  t->next= *koch; //La liste créée est circulaire (la queue reboucle sur la cellule de te pointée pas *koch)
 
}

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */

void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color){
  
  *picture=malloc(sizeof(uint32_t)*size*size); //allocation de l'espace mémoire pour *picture

  for(uint32_t i=0; i<size*size;i++){
    (*picture)[i]=bg_color; // initilisation de l'image avec la couleur de fond.
  }

}

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
void generer_koch(struct list *koch, uint32_t nb_iterations){

  if (nb_iterations != 0){

    float x0=(float)koch->x;
    float x1=(float)koch->next->x;
    float y0=(float)koch->y;
    float y1=(float)koch->next->y;
    float cx;
    float cy;
   
    struct list *b=malloc(sizeof(struct list));
    struct list *c=malloc(sizeof(struct list));
    struct list *d=malloc(sizeof(struct list));

    b->x=(x1+2*x0)/3;
    b->y=(y1+2*y0)/3;
    

    d->x=(2*x1+x0)/3;
    d->y=(2*y1+y0)/3;
    

    cx=((float)b->x+(float)d->x)*cos(3.1415/3.0)-((float)d->y-(float)b->y)*sin(3.1415/3.0);  //on transforme les coordonnées en flottants pour éviter les erreurs d'arrondis
    cy=((float)b->y+(float)d->y)*cos(3.1415/3.0)+((float)d->x-(float)b->x)*sin(3.1415/3.0);
    
    c->x=(uint32_t)cx; // On converti le résultat en entier non signé
    c->y=(uint32_t)cy;
    
    c->next=d;
    b->next=c;  // création du chainage
    d->next=koch->next;
    koch->next=b;
    
    generer_koch(koch,nb_iterations-1);
    generer_koch(b,nb_iterations-1); // appel recursif sur tout les sous-segments avec une itération en moins.
    generer_koch(c,nb_iterations-1);
    generer_koch(d,nb_iterations-1);

  }
 


}

void tracer_ligne_bresenham(uint32_t *picture, struct list *koch,uint32_t fg_color,uint32_t size){

  int32_t dx=abs((koch->next->x) - (koch->x));  // type entier et non pas NON-signé pour eviter les erreurs en cas de résultat négatif.
  int32_t dy=abs((koch->next->y) - (koch->y));
  int32_t sx =-1;
  int32_t sy=-1;
  int32_t err= dx-dy;
  int32_t e2=0;
  uint32_t tmp;
  uint32_t x0=koch->x;
  uint32_t x1=koch->next->x;
  uint32_t y0=koch->y;
  uint32_t y1=koch->next->y;

  if(x0 < x1){
    sx=1;
  }  
  if(y0 < y1){
    sy=1;
  }
  do{
    tmp=size*y0+x0;
    picture[tmp]=fg_color;
    if(x0==x1 && y0==y1){
      break;
    }
    e2=2*err;
    if(e2>-dy){
      err=err-dy;
      x0=x0+sx;
    }
    if(e2<dx){
      err=err+dx;
      y0=y0+sy;
    }

  }while(1); // boucle tant que la condition de sortie n'est pas remplie




}
/*Rendu image via algorithme bresehem - version generalisee
  simplifiee */
void render_image_bresenham(uint32_t *picture, struct list *koch, uint32_t size, uint32_t fg_color)
{

  struct list *cour=koch;
  while((cour->next)!=koch){
    tracer_ligne_bresenham(picture,cour,fg_color,size);	 // On trace une droite entre chaque cellule de notre liste chainée.		   
    cour=(cour->next);
 
    }
  tracer_ligne_bresenham(picture, cour,fg_color,size); // On trace la dernière droite (entre la queue et la tête de la liste)
}

/* Liberation de la memoire allouee a la liste chainee */
void free_koch(struct list *koch)
{
  struct list *cour=koch;
  struct list *tmp=koch;
  while (cour->next != koch){
    tmp=(cour->next);
    free(cour);
    cour=tmp;
  }
  free(cour);
}
