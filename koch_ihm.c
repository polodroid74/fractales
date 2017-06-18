/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "koch_fonctions.h"
// TODO

void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
  if(argc == 6 || argc ==7){ //nombre d'argument correct, avec ou sans le paramètre all.

    parameters->segment_length=atoi(argv[1]);
    parameters->image_size=atoi(argv[1])*2;
    parameters->nb_iterations=atoi(argv[2]);
    parameters->fg_color=(uint32_t)strtol(argv[3],NULL,16); //convertion de la chaîne de caractères en hexadécimal (base 16).
    parameters->bg_color=(uint32_t)strtol(argv[4],NULL,16);
    parameters->outfile=argv[5];
  

    if (argc == 7 && strcmp(argv[6],"all")==0){  //test du paramètre all et configuration de parameters->all en conséquence.
      parameters->all_images=true;
    }else if(argc ==6){
      parameters->all_images=false;
    }else{
      printf("Erreur, paramètre all incorrect \n \n ");
    }
  }else{  // Cas où le nombre de paramètres est incorrect -> mode interactif

    printf(" Saisie incorrecte, mode interactif activé, veuillez saisir les différents paramètres: \n");

    char segment[50];
    char iterations[50];
    char fgcolor[50]; // déclaration des chaînes de caractères.
    char bgcolor[50];
    char all[4];

    char *ptr_fgcolor=fgcolor; //création de pointeurs pour la fonction strtol
    char *ptr_bgcolor=bgcolor;

    parameters->outfile=malloc(sizeof(char[50]));

    printf("Longeur du segment ? \n");
    fgets(segment,50,stdin);  
    printf("Nombre d'itérations ? \n");
    fgets(iterations,50,stdin);
    printf("Couleur du tracé ? \n");
    fgets(fgcolor,50,stdin); 
    printf("Couleur de l'arrière-plan ? \n");
    fgets(bgcolor,50,stdin);
    printf("Nom du fichier?\n");

    fgets(parameters->outfile,50,stdin); //retrait du retour à la ligne en fin de nom de fichier
    char *cour;
    cour=strchr(parameters->outfile,'\n');
    *cour='\0';
      
    printf("Voulez-vous conserver toutes les images ? (all/no)\n");
    fgets(all,4,stdin);
  
    parameters->segment_length=atoi(segment);  // configuration des paramètres en fonction des entrées.
    parameters->image_size=(parameters->segment_length)*2;
    parameters->nb_iterations=atoi(iterations);
    parameters->fg_color=(uint32_t)strtol(ptr_fgcolor,NULL,16);
    parameters->bg_color=(uint32_t)strtol(ptr_bgcolor,NULL,16);

    

    if (strcmp(all, "all")==0){ //test du paramètre all.
      parameters->all_images=true;
 
    }else{
      parameters->all_images=false;
    }
    
  }

  char *tmp=".ppm";  //rajout du .ppm au cas où il a été omis dans le nom du fichier.
  if (strstr(parameters->outfile,tmp)==NULL){
    strcat(parameters->outfile,tmp);
    }
  

}

void show_koch_list(struct list *koch)
{   
  struct list *cour=koch;

  while (cour-> next != koch){ //parcours de la liste chaînée
    printf("x=%i\n", cour->x);
    printf("y=%i\n", cour->y);
    cour=cour->next;
  }
  printf("x=%i\n", cour->x);
  printf("y=%i\n", cour->y);
}

void show_parameters(const struct parameters *parameters)
{
  printf("Longeur du segment:");  //affichage des paramètres
  printf(" %u \n",parameters->segment_length);
  printf("Taille de l'image:");
  printf(" %u \n",parameters->image_size);
  printf("Nombre d'itérations:");
  printf(" %u \n",parameters->nb_iterations);
  printf("Couleur du tracé:");
  printf(" %u \n", parameters->fg_color);
  printf("Couleur de l'arrière-plan:");
  printf(" %u \n", parameters->bg_color);
  printf("Nom du fichier:");
  printf(" %s \n",parameters->outfile);
  printf("Conservation des images:");
  
  if (parameters->all_images== true){ //cas du paramètre all
    printf(" %s \n"," oui");
  }else{
    printf(" %s \n"," non");
  }
}
