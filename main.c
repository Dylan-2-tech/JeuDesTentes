#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction_tente.h"

#define LEN_GRILLE 6
#define LEN_LIGNE LEN_GRILLE+2 // 6 +2 (car '/0' et '\n')

/*
2 difficultées de jeu:
	- Facile: Impossible de placer une tente sur un mauvais emplacement
			  La partie s'arrête automatiquement lorsque la grille est complète
	
	- Difficile: Possibilité de placer une tente sur un mauvais emplacement
			  Le joueur décide lorsqu'il pense avoir fini la grille de jeu
*/


int main(void){

	// ############### Initialisation du jeu #################

	// Accueil
	printf("Bienvenue au jeu des tentes!\nLe jeu des tentes est un jeu de réfléxion dans lequel le joueur doit placer des tentes \ndans une grille contenant des arbre selon les règles suivantes:\n");
	printf(" - Une tente doit être placée sur un emplacement libre.\n");
	printf(" - Chaque tente doit être attaché à un arbre, \n  et donc placé sur une case adjacente (horizontalement ou verticalement).\n");
	printf(" - Deux tentes ne euvent se toucher, même en diagonale.\n");
	printf(" - Le nombre de tentes de chaque ligne et chaque colonne est indiqué à gauche et en haut.\n");

	printf("\nComment Jouer:\n");
	printf(" - Pour Placer une tente, entrez '+' puis ajouter ses coordonnés.\n   ex: + 4 5: la première valeur est le x et la deuxième est le y.\n");
	printf(" - Pour retirer une tente, entrez '_' puis ajouter ses coordonnés.\n   ex: _ 4 5: la première valeur est le x et la deuxième est le y.\n");
	printf(" - Pour retirer toutes les tentes, entrez 'c 0 0'.\n");
	printf(" - Pour résoudre la grille, entrez 'r 0 0'.\n");
	
	// Allocation de l'espace pour enregistrer le nom de la grille
	char *grille = malloc(15 * sizeof(char));

	// Pointeur d'un fichier
	FILE *fptr;
	do{
		// Demande quelle grille de jeu Jouer
		printf("\nQuelle grille de jeu souhaitez vous résoudre?: ");
		scanf("%s", grille);
	
		char path[40] = "grilleJeu/";
		strcat(path, grille);
		strcat(path, ".txt");

		// Ouverture du fichier en mode lecture
		fptr = fopen(path, "r");
		if (fptr == NULL)
			printf("Impossible d'ouvrir le fichier: Non trouvé.\n");

	}while (fptr == NULL);
	
	// Détermination de la grille de jeu
	GrilleJeu Jeu = get_grille_jeu(fptr);
 	// Fermeture du fichier
	fclose(fptr);
	
	// ################# cycle du jeu ###################

	int x, y, difficulte, fini;
	char action, temp;

	// Demande de la difficulté
	do{
		printf("Choisissez une difficulté de jeu:\n\t- 0: Facile\n\t- 1: Difficile\nChoix: ");
		scanf("%d", &difficulte);
		scanf("%c", &temp);
	}while (difficulte != 0 && difficulte != 1);

	// Explication en fonction de la difficulté
	if (difficulte) // Difficulte difficile
		printf("\n # INFO: Pour terminer la grille il suffit d'entrer 't 0 0'.");
	else
		printf("\n # INFO: Le jeu se terminera automatiquement lorsque vous aurez résolu la grille.");

	fini = 0;
	// Boucle de Jeu
	while (!fini){

		// Affichage de la grille de jeu
		affichageGrilleJeu(Jeu.grille, Jeu.tenteLigne, Jeu.tenteColonne);
		
		// Demande de l'action
		do{
			printf("Placer(+) ou retirer(_) la tente: ");
			scanf("%c", &action);
			scanf("%d", &x);
			scanf("%d", &y);
			scanf("%c", &temp);
			printf("Action joué: %c %d %d\n", action, x, y);

			if (x < 0 || x > 5)
				printf("X est trop grand: X => (0,5)\n");
			if (y < 0 || y > 5)
				printf("Y est trop grand: Y => (0,5)\n");

		}while (action != '+' && action != '_' && action != 't' && action != 'c' && action != 'r' || (x < 0 || x > 5) || (y < 0 || y > 5));
		
		// Si le joueur souhaite pense qu'il a résolu la grille
		if (difficulte && action == 't'){
			fini = est_resolu(Jeu.grille, Jeu.tenteLigne, Jeu.tenteColonne);
			if (!fini)
				printf("\nERROR: La grille de jeu n'est pas complète");
		}
		else if (action == '+')
			placer_tente(difficulte, Jeu.grille, x, y, Jeu.tenteLigne, Jeu.tenteColonne);
		else if (action == '_')
			retirer_tente(Jeu.grille, x, y);
		else if (action == 'c')
			clear_grille(Jeu.grille);
		else if (action == 'r'){
			if (!resoudre_grille(Jeu.grille, Jeu.tenteLigne, Jeu.tenteColonne))
				printf("ERROR: Grille Impossible à résoudre pour l'instant...");
		}
		// Si la difficulte est facile
		if (!difficulte)
			fini = est_resolu(Jeu.grille, Jeu.tenteLigne, Jeu.tenteColonne);
	}
	// Lorsque l'utilisateur a fini
	affichageGrilleJeu(Jeu.grille, Jeu.tenteLigne, Jeu.tenteColonne);
	printf("\nBravo puzzle résolu !\n");
	

	// Libération de tout l'espace alloué
	free(Jeu.tenteColonne);
	free(Jeu.tenteLigne);
	libererGrilleJeu(Jeu.grille,LEN_GRILLE);

	return 0;
}