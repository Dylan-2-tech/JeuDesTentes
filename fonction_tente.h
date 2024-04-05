
// Structure grille de jeu
typedef struct GrilleJeu{
	
	char *tenteLigne;
	char *tenteColonne;
	char ** grille;
	
}GrilleJeu;

// Fonction qui renvoie une structure grille de jeu qui représente la grille de jeu choisis par le joueur
GrilleJeu get_grille_jeu(FILE * fptr);

// Fonction qui renvoie vrai si la case choisis par le joueur est libre
int est_libre(char **grilleJeu, int x, int y);

// Fonction qui renvoie vrai si dans la case choisis par le joueur il y'a un arbre à 1 case autour faux sinon
int arbre_autour(char **grilleJeu, int x, int y);

// Fonction qui renvoie vrai si dans la case choisis par le joueur il y a au moins une autre tente à 1 case autour
int tente_autour(char **grilleJeu, int x, int y);

// Fonction qui renvoie le int d'un chiffre entre 0 et 5
int str_to_int(char string);

// Fonction qui renvoie vrai si dans la ligne ET la colonne on peut y placer une tente
int check_ligne_colonne(char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne);

// Fonction qui renvoie 1 si la tente est bien placer
int tente_correct(char **grilleJeu, int x, int y);

/*
Règles pour placer une tente:
	- Au moins un arbre dans 1 case autour horizontal et vertical
	- Aucune autre tente dans 1 case tout autour
	- Si l'ajout de cette tente ne dépasse pas le nombre de tentes soufaité sur la ligne ET la colonne
*/
// Fonction qui renvoie 1 si une tente peut être placé au coordonées et 0 sinon
int place_correct(char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne);

// Fonction qui place la tente dans la grille de jeu
void placer_tente(int difficulte, char **grilleJeu, int x, int y, char *tenteLigne, char *tenteColonne);


// Fonction qui retire de la grille de jeu la tente sélectionné
void retirer_tente(char **grilleJeu, int x, int y);

// Fonction qui renvoie vrai(1) si la grille de jeu est résolu et faux(0) sinon (Mode de jeu FACILE)
int est_resolu(char **grilleJeu, char *tenteLigne, char *tenteColonne);

// Fonction d'affichage d'un tableau 2d
void affichageGrilleJeu(char ** grille, char * tenteLigne, char * tenteColonne);

// Fonction qui libére l'espace alloué d'un tableau 2d
void libererGrilleJeu(char ** tab, int nbLigne);