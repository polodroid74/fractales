/*
 * Fichier : create_image.c
 * Description : Creation d'un fichier ppm a partir d'une image sous la forme
 *               d'un tableau uint32_t *
 */
#include "create_image.h"
#include <stdlib.h>
#include <stdio.h>

void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename)
{

   FILE *fractale=fopen(filename, "wb");
  fprintf(fractale,"P6\n");
  fprintf(fractale,"%i %i \n",size_x, size_y);
  fprintf(fractale,"255\n");

  for(int32_t i=0; i<size_y*size_x; i++){
    fprintf(fractale,"%c",pic[i]>>16);  //décalage vers la gauche pour extraire les octets intéressants du fichier.
    fprintf(fractale,"%c",pic[i]>>8);
    fprintf(fractale,"%c",pic[i]);
    } 

  fclose(fractale);
 
  
}
