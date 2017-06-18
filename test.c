#include <stdlib.h>
#include <stdio.h>
#include "koch_fonctions.h"
#include "create_image.h"

int main(void) {
  uint32_t size=2000;
  uint32_t segment_length=1000;
  uint32_t iteration=6;

  struct list *koch1=NULL; 
  struct list **koch=&koch1;

  init_koch(koch, size,segment_length );/*test de init_koch*/
  struct list *cour=*koch;

  printf("test de init cour\n");

  for (int16_t i=1; i<=4; i++){
    printf("%i\n", cour->x);
    printf("%i\n", cour->y);  // affiche la liste de points.
    cour=cour->next;
    }
  /*-------------------------------------------------------------------------*/
  printf("test de generer_koch\n");
  /*test de generer_koch*/

  struct list *tmp;
  cour=*koch;

  while ( cour->next != *koch){
    tmp=cour -> next;
    generer_koch(cour,iteration);
    cour=tmp;
 
    
  }
  generer_koch(cour,iteration);
  cour=*koch;

  while (cour-> next != *koch){
    printf("x=%i\n", cour->x);  //affiche la liste de points.
    printf("y=%i\n", cour->y);
    cour=cour->next;
    }

  uint32_t *picture1=NULL;
  uint32_t **picture=&picture1;
  char *fractale="fractale.ppm";

  init_picture(picture,size,400);
  render_image_bresenham(*picture,*koch,size,0);
  create_image_ppm(*picture,size,size,fractale);
  free_koch(*koch);
  free(*picture);
  return EXIT_SUCCESS;
}
