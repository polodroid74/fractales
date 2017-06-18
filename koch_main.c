/*
 * Fichier : koch_main.c
 * Description : Trace de fractales geometriques - flocon de koch - programme principal
 */

#include <stdlib.h> 
#include "koch_fonctions.h"
#include "koch_ihm.h"
#include "create_image.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  struct parameters *parametres=malloc(sizeof(struct parameters));
  init_parameters(parametres,argc,argv); //recupération des paramètres
  show_parameters(parametres); //affichage des paramètres

  if (parametres->nb_iterations >= 4294967295 || parametres->segment_length >=4294967294/2){
    printf("\n Paramètres trop grands ! \n");  // évite des erreurs de segmentation en cas de paramètres négatifs.
    return 0;
  }



  struct list *koch1=NULL; 
  struct list **koch=&koch1; // koch est un pointeur de pointeur.

  init_koch(koch, parametres->image_size,parametres->segment_length );

  struct list *tmp; 
  struct list *cour=*koch; 

  uint32_t *picture1=NULL;
  uint32_t **picture=&picture1; //picture est un pointeur de pointeur

  char *fractale=NULL; //pointeur vers le nom du fichier initialisé

  if (parametres->all_images){  // distinction du cas où l'option est présente ou non.

    for(uint32_t i=1;i<=parametres->nb_iterations;i++){
      cour=*koch;
      while ( cour->next != *koch){
	tmp=cour -> next;
	generer_koch(cour,1); //on ne génere qu'une seule itération en plus à chaquetour de  boucle
	cour=tmp;
      }
      generer_koch(cour,1); //dernière itération entre la tête et la queue

      fractale=malloc(sizeof(char[50])); //pointeur vers le nom du fichier

      sprintf(fractale,"%i",i);
      strcat(fractale,"_");  // construction du nom de fichier
      strcat(fractale, parametres->outfile);
 
      init_picture(picture,parametres->image_size,parametres->bg_color);
      render_image_bresenham(*picture,*koch,parametres->image_size,parametres->fg_color);
      create_image_ppm(*picture,parametres->image_size,parametres->image_size,fractale);
      free(*picture);  //libération de *picture pour la rendre disponible au prochain tour de boucle
      free(fractale); //libération du pointeur vers le om de fichier
    }

  }else{ //cas sans l'option all

    while ( cour->next != *koch){
      tmp=cour -> next;
      generer_koch(cour,parametres->nb_iterations);
      cour=tmp;
    }
    generer_koch(cour,parametres->nb_iterations); //dernière itération entre la tête et la queue
 
  

    fractale=parametres->outfile; // récupération du nom du fichier

    init_picture(picture,parametres->image_size,parametres->bg_color);
    render_image_bresenham(*picture,*koch,parametres->image_size,parametres->fg_color);
    create_image_ppm(*picture,parametres->image_size,parametres->image_size,fractale);
    free(*picture);
  }
 if(argc != 6 && argc !=7){
   free(parametres->outfile); // Evite une fuite mémoire de "parameters->outfile=malloc(sizeof(char[50]));" du mode intéractif.
 } 
  free(parametres); // libération des différents pointeurs alloués
  free_koch(*koch);
  return EXIT_SUCCESS;
}
