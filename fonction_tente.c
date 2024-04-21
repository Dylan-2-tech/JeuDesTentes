#include <stdio.h>
#include <stdlib.h>
#include "fonction_tente.h"

#define LEN_GRILLE 6
#define LEN_LIGNE LEN_GRILLE+2 // 6 +2 (car '/0' et '\n')
#define ARBRE '*'
#define TENTE 'T'


// Fonction qui renvoie une structure grille de jeu qui représente la grille de jeu choisis par le joueur
GrilleJeu get_grille_jeu(FILE * fptr){

	// Initialisation de la grille de jeu
	GrilleJeu gj;

	// Allocation du tableau du nombre de tente sur les lignes(horizontale)
	gj.tenteLigne = malloc(LEN_LIGNE * sizeof(char));
	// Allocation du tableau du nombre de tente sur les colonnes(verticale)
	gj.tenteColonne = malloc(LEN_LIGNE * sizeof(char));

	// Allocation du tableau 2D de la grille de jeu
	gj.grille = malloc(6 * sizeof(char *));
	for (int i = 0; i < 6; i++)
		*(gj.grille+i) = malloc(6 * sizeof(char));

	// Pour la lecture on utilise 'fgets' qui lis un fichier ligne par ligne

	// Lecture de la première ligne qui est le nombre de tentes horizontale
	fgets(gj.tenteLigne, LEN_LIGNE, fptr);
	// Lecture de la deuxième ligne qui est le nombre de tentes verticale
	fgets(gj.tenteColonne, LEN_LIGNE, fptr);
	// Lecture du reste du fichier qui est la grille de jeu
	for (int i = 0; i < LEN_GRILLE; i++)
		fgets(*(gj.grille+i), LEN_LIGNE, fptr);

	return gj;
}

// Fonction qui renvoie vrai si la case choisis par le joueur est libre
int est_libre(char **grilleJeu, int x, int y){
	return *(*(grilleJeu+y)+x) == ' ';}

// Fonction qui renvoie vrai si dans la case choisis par le joueur il y'a un arbre à 1 case autour faux sinon
int arbre_autour(char **grilleJeu, int x, int y){

	int arbreAutour = 0;

	// Vérification sur les cases au-dessus et en-dessous
	/*
		c
		T
		c
	*/

	// Case au-dessus
	if (!arbreAutour && y - 1 >= 0)
		arbreAutour = *(*(grilleJeu+y-1)+x) == ARBRE;
	// Case au-dessous
	if (!arbreAutour && y + 1 < LEN_GRILLE)
		arbreAutour = *(*(grilleJeu+y+1)+x) == ARBRE;

	// Vérification sur les cases de droite et gauche
	/*
		
	  c T c
		
	*/

	// Case à gauche
	if (!arbreAutour && x - 1 >= 0)
		arbreAutour = *(*(grilleJeu+y)+x-1) == ARBRE;
	// Case à droite
	if (!arbreAutour && x + 1 < LEN_GRILLE)
		arbreAutour = *(*(grilleJeu+y)+x+1) == ARBRE;

	return arbreAutour;}

// Fonction qui renvoie vrai si dans la case choisis par le joueur il y a au moins une autre tente à 1 case autour
int tente_autour(char **grilleJeu, int x, int y){
	

	// Vérification sur la colonne à droite et la colonne de gauche de la position
	/* 
		T   T
		T T T
		T 	T
	*/

	int tenteAutour = 0;
	int xColonneGauche = x - 1;
	int xColonneDroite = x + 1;

	// Si la colonne de gauche est accessible
	if (xColonneGauche >= 0){

		// On vérifie pour chaque y autour

		// au milieu à gauche
		tenteAutour = *(*(grilleJeu+y)+xColonneGauche) == TENTE;

		// en haut à gauche
		if (!tenteAutour && y - 1 >= 0)
			tenteAutour = *(*(grilleJeu+y-1)+xColonneGauche) == TENTE;
		
		// en bas à gauche
		if (!tenteAutour && y + 1 < LEN_GRILLE)
			tenteAutour = *(*(grilleJeu+y+1)+xColonneGauche) == TENTE;
		
	}

	// Si la colonne de droite est accessible et que ya pas d'arbre avant
	if (!tenteAutour && xColonneDroite < LEN_GRILLE){

		// On vérifie pour chaque y autour

		// au milieu à droite
		tenteAutour = *(*(grilleJeu+y)+xColonneDroite) == TENTE;
		
		// en haut à gauche
		if (!tenteAutour && y - 1 >= 0)
			tenteAutour = *(*(grilleJeu+y-1)+xColonneDroite) == TENTE;
		
		// en bas à gauche
		if (!tenteAutour && y + 1 < LEN_GRILLE)
			tenteAutour = *(*(grilleJeu+y+1)+xColonneDroite) == TENTE;
	}

	// Vérification sur les dernieres cases manquantes
	/*
		T
		T
		T
	*/

	// Case au-dessus
	if (!tenteAutour && y - 1 >= 0)
		tenteAutour = *(*(grilleJeu+y-1)+x) == TENTE;
	// Case au-dessous
	if (!tenteAutour && y + 1 < LEN_GRILLE)
		tenteAutour = *(*(grilleJeu+y+1)+x) == TENTE;

	return tenteAutour;}

// Fonction qui renvoie le int d'un chiffre entre 0 et 5
int str_to_int(char string){
	switch (string){
		case('1'):
			return 1;
			break;
		case('2'):
			return 2;
			break;
		case('3'):
			return 3;
			break;
		case('4'):
			return 4;
			break;
		case('5'):
			return 5;
			break;
		default: // Si == 0 ou autre
			return 0;
	}}

// Fonction qui renvoie vrai si dans la ligne ET la colonne on peut y placer une tente
int check_ligne_colonne(char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne){

	// Vérification de la ligne

	// Comptage de tentes dans la ligne (vertical)
	int nbrLigne = 0;
	for (int i = 0; i < LEN_GRILLE; i++){

		if (*(*(grilleJeu+i)+x) == 'T')
			nbrLigne++;
	}

	if (nbrLigne >= str_to_int(*(tenteLigne+x))) // atoi ne marche pas car *(tenteColonne+x) n'est pas de type 'const char *'
		return 0;
	
	// Vérification de la colonne

	// Comptage de tentes dans la colonne (Horizontal)
	int nbrColonne = 0;
	for (int i = 0; i < LEN_GRILLE; i++){
		
		if (*(*(grilleJeu+y)+i) == 'T')
			nbrColonne++;
	}

	if (nbrColonne >= str_to_int(*(tenteColonne+y)))
		return 0;

	return 1;}

// Fonction qui renvoie 1 si la tente est bien placer
int tente_correct(char **grilleJeu, int x, int y){
	return (
		arbre_autour(grilleJeu, x, y) &&
		!tente_autour(grilleJeu,x, y)
		);}

// Fonction qui renvoie 1 si une tente peut être placé au coordonées et 0 sinon
int place_correct(char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne){
	return (
		est_libre(grilleJeu, x, y) && 
		arbre_autour(grilleJeu, x, y) && 
		!tente_autour(grilleJeu, x, y) &&
		check_ligne_colonne(grilleJeu, x, y, tenteLigne, tenteColonne)
		);}

// Fonction qui place la tente dans la grille de jeu
void placer_tente(int diffculte, char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne){

	if (diffculte == 1){
		if (est_libre(grilleJeu, x, y))
			*(*(grilleJeu+y)+x) = TENTE;
		else
			printf("ERROR: Emplacement occupé par un arbre ou une tente...\n");
	}
	else if (place_correct(grilleJeu, x, y, tenteLigne, tenteColonne))
		*(*(grilleJeu+y)+x) = TENTE;
	else
		printf("ERROR: Emplacement incorrect...\n");}

// Fonction qui retire de la grille de jeu la tente sélectionné
void retirer_tente(char **grilleJeu, int x, int y){

	if (*(*(grilleJeu+y)+x) == 'T')
		*(*(grilleJeu+y)+x) = ' ';
	else
		printf("ERROR: Aucune tente à cette emplacement...\n");}


// Fonction qui retire toutes les tentes de la grille
void clear_grille(char **grilleJeu){

	for (int i = 0; i < LEN_GRILLE; i++){
		for (int j = 0; j < LEN_GRILLE; j++){
			if (*(*(grilleJeu+j)+i) == 'T')
				*(*(grilleJeu+j)+i) = ' ';
		}
	}
}

// Fonction qui résous le plus possible une grille
int resoudre_grille(char **grilleJeu, char * tenteLigne, char * tenteColonne){

	/*
	Objectif: Parcourir toute la grille (une ou plrs fois) afin de trouver les emplacement sûr et d'y placer les tentes
	
	Comment: Parcours de la grille en double boucle for avec i et j les coordonnées des emplacement
			 Sur chaque ligne, on compte le nombre d'emplacement valides:
			 	- Si le nombre d'emplacement valide correspond au nombre de tentes à placer => On place les tentes au emplacements trouvé
			 	- Si le nombre est supérieur, on passe à la ligne suivante
			 	=> Suppose qu'au moins une ligne sera toujours rempli à chaque tour de boucle cad une action est joué

	Le tour de boucle se fait tant que la grille n'est pas résolu ou alors qu'aucune action est faite
	*/

	// Variables
	int CompteurPlaceCorrect;
	int action = 1;

	while (!est_resolu(grilleJeu, tenteLigne, tenteColonne) && action){
			
		action = 0;

		for (int y = 0; y < LEN_GRILLE; y++){
			
			int CompteurPlaceCorrect = 0;

			for (int x = 0; x < LEN_GRILLE; x++){
				if (place_correct(grilleJeu, x, y, tenteLigne, tenteColonne))
					CompteurPlaceCorrect++;
			}

			if (CompteurPlaceCorrect == str_to_int(*(tenteColonne+y))){

				action = 1;
				
				for (int x = 0; x < LEN_GRILLE; x++){
					if (place_correct(grilleJeu, x, y, tenteLigne, tenteColonne))
						placer_tente(1, grilleJeu, x, y, tenteLigne, tenteColonne);
				}
			}
		}
	}
	return action;
}


// Fonction qui renvoie vrai(1) si la grille de jeu est résolu et faux(0) sinon (Mode de jeu FACILE)
int est_resolu(char **grilleJeu, char *tenteLigne, char *tenteColonne){
	
	// Besoin de vérifier uniquement le nombre de tentes correcte pour les ligne est les colonnes
	
	int nbrColonne;
	int nbrLigne;

	// Vérification du bon nombre de tente sur les colonnes et les lignes
	for (int i = 0; i < LEN_GRILLE; i++){
		
		nbrColonne = 0;
		nbrLigne = 0;

		for (int j = 0; j < LEN_GRILLE; j++){

			// +1 sur le nombre de tente si une tente est rencontrée
			if (*(*(grilleJeu+i)+j) == 'T'){

				// Si la tentes est correctement placé on continu le programme
				if (!tente_correct(grilleJeu, j, i))
					return 0;

				nbrLigne++;
			}

			// +1 sur le nombre de tente si une tente est rencontrée
			if (*(*(grilleJeu+j)+i) == 'T')
				nbrColonne++;
		}

		// Si le nombre de tentes sur la ligne OU sur la colonne n'est pas égale alors on retourne 0 sinon on continue le programme
		if (nbrColonne != str_to_int(*(tenteLigne+i)) ||
			nbrLigne != str_to_int(*(tenteColonne+i)))
			return 0;

	}
	return 1;}

// Fonction d'affichage d'un tableau 2d
void affichageGrilleJeu(char ** grille, char * tenteLigne, char * tenteColonne){
	
	int i;

	// Affichage des tentes horizontale
	printf("\n ");
	for (i = 0; i < LEN_GRILLE; i++){
		printf(" %c", *(tenteLigne+i));
	}
	printf("\n");

	// Affichage de la grille
	for (i = 0; i < LEN_GRILLE; i++){
		for (int j = 0; j < LEN_GRILLE; j++){
			if (j == 0)
				printf("%c",*(tenteColonne+i));
			printf("|%c", *(*(grille+i)+j));
		}
		printf("|\n");
	}}

// Fonction qui libére l'espace alloué d'un tableau 2d
void libererGrilleJeu(char ** tab, int nbLigne){
	for (int i = 0; i < nbLigne; i++) {
		free (tab[i]) ;
	}
	free (tab);}
