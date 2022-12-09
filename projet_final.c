/**
* @file projet_final.c
* SAE 1.01 Gestion d’une formation
* @author DURRMEYER Sarah et NJIKAM Iris du groupe 109
* @version 1.0 07/11/2022
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#pragma warning (disable:4996)

enum {
	NB_SEMESTRES = 2,
	MIN_UE = 3,
	MAX_UE = 6,
	MAX_MATIERES = 10,
	MAX_EPREUVES = 5,
	MAX_ETUDIANTS = 100,
	MAX_CHAR = 30
};
const float MIN_NOTE = 0.f, MAX_NOTE = 20.f;

typedef char CH30[31];

typedef struct {
	CH30 nom;
	float coef[MAX_UE];
} Epreuve;

typedef struct {
	CH30 nom;
	unsigned int nbEpreuves;
	Epreuve epreuves[MAX_EPREUVES];
} Matiere;

typedef struct {
	unsigned int nbMatieres;
	Matiere matieres[MAX_MATIERES];
} Semestre;

typedef struct {
	unsigned int nbUE;
	Semestre semestres[NB_SEMESTRES];
} Formation;

/* 
 * Le type structuré Etudiant définit un étudiant par son nom, ses notes ainsi que par
 * la somme des coefficients par UE et la somme des moyennes par UE.
 */
typedef struct {
	CH30 nom;
	float notes[NB_SEMESTRES][MAX_MATIERES][MAX_EPREUVES];
	float coefs[NB_SEMESTRES][MAX_UE];
	float moyennes[NB_SEMESTRES][MAX_UE];
} Etudiant;

/* Le type structuré Promo représente les étudiants qui participent à la formation. */
typedef struct {
	unsigned int nbEtudiants;
	Etudiant etudiants[MAX_ETUDIANTS];
} Promo;


/*
 * Si le numéro de semestre est valide, alors retourne le numéro de semestre décrémenté de 1.
 * Sinon, retourne -1.
 * [in-out] s le numéro de semestre
 */
int verif_semestre(const int s) {
	if (!((s == 1) || (s == 2))) {
		printf("Le numero de semestre est incorrect\n");
		return -1;
	}
	return (s - 1);
}

/* 
 * Si le nombre d'UE n'est pas défini, alors retourne -1.
 * Sinon, retourne 0.
 * [in] ue le nombre d'UE
 */
int verif_ue(const unsigned int ue) {
	if (ue == 0) {
		printf("Le nombre d'UE n'est pas defini\n");
		return -1;
	}
	return 0;
}

/* 
 * Initialise les attributs d'une variable de type Matiere. 
 * [in] x le pointeur d'une variable de type Matiere
 * [in] x_nom le nom de la matière
 */
void init_matiere(Matiere* x, CH30 x_nom){
	strcpy(x->nom, x_nom);
	x->nbEpreuves = 1;
}

/* 
 * Initialise les attributs d'une variable de type Epreuve. 
 * [in] y le pointeur d'une variable de type Epreuve
 * [in] y_nom le nom de l'épreuve
 * [in] y_coefs le tableau des coefficients par UE 
 * [in] y_nbUE le nombre d'UE
 */
void init_epreuve(Epreuve* y, CH30 y_nom, float y_coefs[MAX_UE], unsigned int y_nbUE){
	strcpy(y->nom, y_nom);
	for (unsigned int i = 0; i < y_nbUE; ++i) {
		y->coef[i] = y_coefs[i];
	}
}

/* Affiche un nombre avec l'arrondi au dixième inférieur. */
void affichage(const float nb) {
	if (nb*10 >= 100) {
		printf("%.1f ", ((float)((int)(nb * 10)) / 10));
	}
	else {
		printf(" %.1f ", ((float)((int)(nb * 10)) / 10));
	}
}

/* 
 * Retourne la longueur de la matière contenant le plus de caractères. 
 * [in] p le pointeur d'une variable de type Formation
 * [in] s le numéro de semestre
 */
int alignement(const Formation* p, const unsigned int s) {
	int longueur_max = 0;
	int tmp;
	for (unsigned int i = 0; i < p->semestres[s].nbMatieres; ++i) {
		tmp = strlen(p->semestres[s].matieres[i].nom);
		if (tmp > longueur_max) {
			longueur_max = tmp;
		}
	}
	return longueur_max;
}


// C2
void formation(Formation* p) {
	/* [in] p le pointeur d'une variable de type Formation */
	unsigned int ueActuelle = p->nbUE;
	unsigned int tmp;
	scanf("%u", &tmp);
	if (ueActuelle != 0) {
		printf("Le nombre d'UE est deja defini\n");
	}
	else if (tmp >= MIN_UE && tmp <= MAX_UE) {
		p->nbUE = tmp;
		printf("Le nombre d'UE est defini\n");
	}
	else {
		printf("Le nombre d'UE est incorrect\n");
	}
}

// C3
void epreuve(Formation* p) {
	/* [in] p le pointeur d'une variable de type Formation */
	int semestre;
	CH30 matiere;
	CH30 epreuve;
	float coefs[MAX_UE];
	int verif_matiere = 0;
	int verif_epreuve = 0;
	int verif_coef = 0;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	unsigned int i_matiere;

	scanf("%d", &semestre);
	scanf("%s", matiere);
	scanf("%s", epreuve);

	for (unsigned int i = 0; i < (p->nbUE); ++i) {
		scanf("%f", &coefs[i]);
	}

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	semestre = verif_semestre(semestre);
	if (semestre == -1) {
		return;
	}
	
	// Vérifie s'il existe déjà une matière et une épreuve du même nom.
	nb_matiere = p->semestres[semestre].nbMatieres;
	for (unsigned int i = 0; i < nb_matiere; ++i) {
		if (strcmp(p->semestres[semestre].matieres[i].nom, matiere) == 0) {
			verif_matiere = 1;
			i_matiere = i;
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				if (strcmp(p->semestres[semestre].matieres[i].epreuves[j].nom, epreuve) == 0) {
					verif_epreuve = 1;
				}
			}
		}
	}
	if ((verif_matiere == 1) && (verif_epreuve == 1)) {
		printf("Une meme epreuve existe deja\n");
		return;
	}

	// Vérifie si les coefficients sont corrects. 
	for (unsigned int i = 0; i < p->nbUE; ++i) {
		if (coefs[i] < 0) {
			printf("Au moins un des coefficients est incorrect\n");
			return;
		}
		if (coefs[i] > 0) {
			verif_coef = 1;
		}
	}
	if (verif_coef == 0) {
		printf("Au moins un des coefficients est incorrect\n");
		return;
	}
	
	// S'il n'existe aucune matière, alors initialise une première matière et une première épreuve.
	if (nb_matiere == 0) {
		Matiere m;
		init_matiere(&m,matiere);
		Epreuve e;
		init_epreuve(&e,epreuve,coefs,p->nbUE);
		p->semestres[semestre].matieres[0] = m;
		p->semestres[semestre].matieres[0].epreuves[0] = e;
		p->semestres[semestre].nbMatieres = 1; 
		printf("Matiere ajoutee a la formation\n");
		printf("Epreuve ajoutee a la formation\n");
		return;
	}
	else {
		// Si la matière existe déjà, alors initialise une nouvelle épreuve.
		if (verif_matiere == 1) {
			Epreuve e;
			init_epreuve(&e,epreuve,coefs,p->nbUE);
			nb_epreuve = p->semestres[semestre].matieres[i_matiere].nbEpreuves;
			p->semestres[semestre].matieres[i_matiere].epreuves[nb_epreuve] = e;
			p->semestres[semestre].matieres[i_matiere].nbEpreuves += 1;
			printf("Epreuve ajoutee a la formation\n");
			return;
		}
		// Si la matière n'existe pas, alors initialise une nouvelle matière et une nouvelle épreuve.
		else {
			Matiere m;
			init_matiere(&m,matiere);
			Epreuve e;
			init_epreuve(&e,epreuve,coefs,p->nbUE);
			p->semestres[semestre].matieres[nb_matiere] = m;
			p->semestres[semestre].matieres[nb_matiere].epreuves[0] = e;
			p->semestres[semestre].nbMatieres += 1;
			printf("Matiere ajoutee a la formation\n");
			printf("Epreuve ajoutee a la formation\n");
			return;
		}
	}
}

// C4
void coefficients(const Formation* p) {
	/* [in] p le pointeur d'une variable de type Formation */
	int semestre;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	
	scanf("%d", &semestre);

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	semestre = verif_semestre(semestre);
	if (semestre == -1) {
		return;
	}

	if (p->semestres[semestre].nbMatieres == 0) {
		printf("Le semestre ne contient aucune epreuve\n");
		return;
	}
	// Fait la somme des coefficients par UE pour vérifier s'ils sont corrects.
	float coef_tmp;
	nb_matiere = p->semestres[semestre].nbMatieres;
	for (unsigned int k = 0; k < p->nbUE; ++k) {
		coef_tmp = 0;
		for (unsigned int i = 0; i < nb_matiere; ++i) {
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				coef_tmp += p->semestres[semestre].matieres[i].epreuves[j].coef[k];
			}
		}
		if (coef_tmp == 0) {
			printf("Les coefficients d'au moins une UE de ce semestre sont tous nuls\n");
			return;
		}
	}
	printf("Coefficients corrects\n");
	return;
}

// C5
void note(Promo* q, const Formation* p) {
	/* 
	 * [in] q le pointeur d'une variable de type Promo 
	 * [in] p le pointeur d'une variable de type Formation 
	 */
	int semestre;
	CH30 nom_etu;
	CH30 matiere;
	CH30 epreuve;
	float note;
	int verif_etudiant = 0;
	int verif_matiere = 0;
	int verif_epreuve = 0;
	unsigned int i_etudiant;
	unsigned int i_matiere;
	unsigned int i_epreuve;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	unsigned int nb_etudiant = 0;

	scanf("%d", &semestre);
	scanf("%s", nom_etu);
	scanf("%s", matiere);
	scanf("%s", epreuve);
	scanf("%f", &note);

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	semestre = verif_semestre(semestre);
	if (semestre == -1) {
		return;
	}

	// Vérifie si la matière et l'épreuve existent.
	nb_matiere = p->semestres[semestre].nbMatieres;
	for (unsigned int i = 0; i < nb_matiere; ++i) {
		if (strcmp(p->semestres[semestre].matieres[i].nom, matiere) == 0) {
			verif_matiere = 1;
			i_matiere = i;
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				if (strcmp(p->semestres[semestre].matieres[i].epreuves[j].nom, epreuve) == 0) {
					verif_epreuve = 1;
					i_epreuve = j;
				}
			}
		}
	}
	if (verif_matiere == 0) {
		printf("Matiere inconnue\n");
		return;
	}
	else if (verif_epreuve == 0) {
		printf("Epreuve inconnue\n");
		return;
	}

	else if (note < 0 || note>20) {
		printf("Note incorrecte\n");
		return;
	}

	// Détermine l'indice de l'étudiant dans le tableau de Promo.
	nb_etudiant = q->nbEtudiants;
	for (unsigned int k = 0; k < nb_etudiant; ++k) {
		if (strcmp(q->etudiants[k].nom, nom_etu) == 0) {
			verif_etudiant = 1;
			i_etudiant = k;
		}
	}

	// Si l'étudiant existe, alors ajoute la note si celle-ci n'est pas déjà définie.
	if (verif_etudiant == 1) {
		if (q->etudiants[i_etudiant].notes[semestre][i_matiere][i_epreuve] < 0) {
			q->etudiants[i_etudiant].notes[semestre][i_matiere][i_epreuve] = note;
			printf("Note ajoutee a l'etudiant\n");
			return;
		}
		else {
			printf("Une note est deja definie pour cet etudiant\n");
			return;
		}
	}
	// Si l'étudiant n'existe pas, alors initialise un étudiant et lui ajoute la note.
	else {
		Etudiant e;
		strcpy(e.nom, nom_etu);
		for (int i = 0; i < NB_SEMESTRES; ++i) {
			for (unsigned int j = 0; j < MAX_MATIERES; ++j) {
				for (unsigned int k = 0; k < MAX_EPREUVES; ++k) {
					e.notes[i][j][k] = -1;
				}
			}
		}
		for (int i = 0; i < NB_SEMESTRES; ++i) {
			for (unsigned int j = 0; j < p->nbUE; ++j) {
				e.coefs[i][j] = 0;
			}
		}
		for (int i = 0; i < NB_SEMESTRES; ++i) {
			for (unsigned int j = 0; j < p->nbUE; ++j) {
				e.moyennes[i][j] = 0;
			}
		}

		if (nb_etudiant == 0) {
			q->etudiants[0] = e;
			q->etudiants[0].notes[semestre][i_matiere][i_epreuve] = note;
		}

		else {
			q->etudiants[nb_etudiant] = e;
			q->etudiants[nb_etudiant].notes[semestre][i_matiere][i_epreuve] = note;
		}
		q->nbEtudiants += 1;
		printf("Etudiant ajoute a la formation\n");
		printf("Note ajoutee a l'etudiant\n");
		return;
	}
}

// C6
void notes(const Promo* q, const Formation* p) {
	/* 
	 * [in] q le pointeur d'une variable de type Promo 
	 * [in] p le pointeur d'une variable de type Formation 
	 */
	int semestre;
	CH30 nom_etu;
	int verif_etudiant = 0;
	unsigned int i_etudiant;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	unsigned int nb_etudiant = 0;

	scanf("%d", &semestre);
	scanf("%s", nom_etu);

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	semestre = verif_semestre(semestre);
	if (semestre == -1) {
		return;
	}

	// Détermine l'indice de l'étudiant dans le tableau de Promo.
	nb_etudiant = q->nbEtudiants;
	for (unsigned int k = 0; k < nb_etudiant; ++k) {
		if (strcmp(q->etudiants[k].nom, nom_etu) == 0) {
			verif_etudiant = 1;
			i_etudiant = k;
		}
	}
	if (verif_etudiant == 0) {
		printf("Etudiant inconnu\n");
		return;
	}

	// Vérifie que l'étudiant a bien toutes ses notes. 
	nb_matiere = p->semestres[semestre].nbMatieres;
	for (unsigned int i = 0; i < nb_matiere; ++i) {
		nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
		for (unsigned int j = 0; j < nb_epreuve; ++j) {
			if (q->etudiants[i_etudiant].notes[semestre][i][j] < 0) {
				printf("Il manque au moins une note pour cet etudiant\n");
				return;
			}
		}
	}
	printf("Notes correctes\n");
	return;
}

// C7
void releve(Promo* q, const Formation* p) {
	/* 
	 * [in] q le un pointeur d'une variable de type Promo 
	 * [in] p le un pointeur d'une variable de type Formation 
	 */
	int semestre;
	CH30 nom_etu;
	float coef_tmp;
	int verif_etudiant = 0;
	unsigned int i_etudiant;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	unsigned int nb_etudiant = 0;
	float note_tmp;
	float moyenne_tmp = 0;
	float somme_coef_tmp = 0;
	int espace_tmp = 0;


	scanf("%d", &semestre);
	scanf("%s", nom_etu);

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	semestre = verif_semestre(semestre);
	if (semestre == -1) {
		return;
	}

	// Détermine l'indice de l'étudiant dans le tableau de Promo.
	nb_etudiant = q->nbEtudiants;
	for (unsigned int k = 0; k < nb_etudiant; ++k) {
		if (strcmp(q->etudiants[k].nom, nom_etu) == 0) {
			verif_etudiant = 1;
			i_etudiant = k;
		}
	}
	if (verif_etudiant == 0) {
		printf("Etudiant inconnu\n");
		return;

	}
	
	// Fait la somme des coefficients par UE pour vérifier s'ils sont corrects.
	nb_matiere = p->semestres[semestre].nbMatieres;
	for (unsigned int k = 0; k < p->nbUE; ++k) {
		coef_tmp = 0;
		for (unsigned int i = 0; i < nb_matiere; ++i) {
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				coef_tmp += p->semestres[semestre].matieres[i].epreuves[j].coef[k];
			}
		}
		if (coef_tmp == 0) {
			printf("Les coefficients de ce semestre sont incorrects\n");
			return;
		}
	}

	// Vérifie que l'étudiant a bien toutes ses notes. 
	for (unsigned int i = 0; i < nb_matiere; ++i) {
		nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
		for (unsigned int j = 0; j < nb_epreuve; ++j) {
			if (q->etudiants[i_etudiant].notes[semestre][i][j] < 0) {
				printf("Il manque au moins une note pour cet etudiant\n");
				return;
			}
		}
	}

	// Initialise les coefficients et les moyennes de l'étudiant.
	for (unsigned int k = 0; k < p->nbUE; ++k) {
		for (unsigned int i = 0; i < nb_matiere; ++i) {
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				q->etudiants[i_etudiant].coefs[semestre][k] = 0;
				q->etudiants[i_etudiant].moyennes[semestre][k] = 0;
			}
		}
	}

	int espace = alignement(p, semestre);

	for (int k = 0; k < espace + 1; ++k) {
		printf(" ");
	}

	for (unsigned int n = 0; n < p->nbUE; ++n) {
		printf(" UE%d ", n + 1);
	}

	// Affichage du relevé avec calcul des moyennes.
	for (unsigned int i = 0; i < nb_matiere; ++i) {
		printf("\n%s ", p->semestres[semestre].matieres[i].nom);
		espace_tmp = espace - (strlen(p->semestres[semestre].matieres[i].nom));
		for (int k = 0; k < espace_tmp; ++k) {
			printf(" ");
		}
		for (unsigned int n = 0; n < p->nbUE; ++n) {
			nb_epreuve = p->semestres[semestre].matieres[i].nbEpreuves;
			for (unsigned int j = 0; j < nb_epreuve; ++j) {
				note_tmp = (q->etudiants[i_etudiant].notes[semestre][i][j]) * (p->semestres[semestre].matieres[i].epreuves[j].coef[n]);
				moyenne_tmp += note_tmp;
				q->etudiants[i_etudiant].moyennes[semestre][n] += note_tmp;
				somme_coef_tmp += p->semestres[semestre].matieres[i].epreuves[j].coef[n];
			}
			if (somme_coef_tmp == 0) {
				printf("  ND ");
			}
			else {
				moyenne_tmp = moyenne_tmp / somme_coef_tmp;
				q->etudiants[i_etudiant].coefs[semestre][n] += somme_coef_tmp;
				affichage(moyenne_tmp);
				moyenne_tmp = 0;
				somme_coef_tmp = 0;
			}

		}
	}
	CH30 mot = "Moyennes";
	printf("\n--\n%s ", mot);
	espace_tmp = espace - (strlen(mot));
	for (int k = 0; k < espace_tmp; ++k) {
		printf(" ");
	}
	moyenne_tmp = 0;
	for (unsigned int n = 0; n < p->nbUE; ++n) {
		moyenne_tmp = q->etudiants[i_etudiant].moyennes[semestre][n] / q->etudiants[i_etudiant].coefs[semestre][n];
		affichage(moyenne_tmp);
		if (n == p->nbUE - 1) {
			printf("\n");
		}
	}
	return;
}

// C8
void decision(Promo* q, const Formation* p) {
	/* 
	 * [in] q le pointeur d'une variable de type Promo 
	 * [in] p le pointeur d'une variable de type Formation 
	 */
	CH30 nom_etu;
	float coef_tmp;
	int verif_etudiant = 0;
	unsigned int i_etudiant;
	unsigned int nb_matiere = 0;
	unsigned int nb_epreuve = 0;
	unsigned int nb_etudiant = 0;
	float note_tmp;
	float moyenne_tmp = 0;
	float somme_coef_tmp = 0;

	scanf("%s", nom_etu);

	if (verif_ue(p->nbUE) == -1) {
		return;
	}

	// Détermine l'indice de l'étudiant dans le tableau de Promo.
	nb_etudiant = q->nbEtudiants;
	for (unsigned int k = 0; k < nb_etudiant; ++k) {
		if (strcmp(q->etudiants[k].nom, nom_etu) == 0) {
			verif_etudiant = 1;
			i_etudiant = k;
		}
	}
	
	// Vérifie que l'étudiant a bien toutes ses notes.
	if (verif_etudiant == 1) {
		for (int s = 0; s < NB_SEMESTRES; ++s) {
			nb_matiere = p->semestres[s].nbMatieres;
			for (unsigned int i = 0; i < nb_matiere; ++i) {
				nb_epreuve = p->semestres[s].matieres[i].nbEpreuves;
				for (unsigned int j = 0; j < nb_epreuve; ++j) {
					if (q->etudiants[i_etudiant].notes[s][i][j] < 0) {
						printf("Il manque au moins une note pour cet etudiant\n");
						return;

					}
				}
			}
		}
	}
	else {
		printf("Etudiant inconnu\n");
		return;
	}

	// Fait la somme des coefficients par UE pour vérifier s'ils sont corrects.
	for (unsigned int k = 0; k < p->nbUE; ++k) {
		coef_tmp = 0;
		for (int s = 0; s < NB_SEMESTRES; ++s) {
			nb_matiere = p->semestres[s].nbMatieres;
			for (unsigned int i = 0; i < nb_matiere; ++i) {
				nb_epreuve = p->semestres[s].matieres[i].nbEpreuves;
				for (unsigned int j = 0; j < nb_epreuve; ++j) {
					coef_tmp += p->semestres[s].matieres[i].epreuves[j].coef[k];
				}
			}
			if (coef_tmp == 0) {
				printf("Les coefficients d'au moins un semestre sont incorrects\n");
				return;
			}
		}
	}

	// Initialise les coefficients et les moyennes de l'étudiant.
	for (int s = 0; s < NB_SEMESTRES; ++s) {
		for (unsigned int k = 0; k < p->nbUE; ++k) {
			nb_matiere = p->semestres[s].nbMatieres;
			for (unsigned int i = 0; i < nb_matiere; ++i) {
				nb_epreuve = p->semestres[s].matieres[i].nbEpreuves;
				for (unsigned int j = 0; j < nb_epreuve; ++j) {
					q->etudiants[i_etudiant].coefs[s][k] = 0;
					q->etudiants[i_etudiant].moyennes[s][k] = 0;
				}
			}
		}
	}

	// Affichage de la décision avec calcul des moyennes.
	printf("                   ");
	for (unsigned int n = 0; n < p->nbUE; ++n) {
		printf(" UE%u ", n + 1);
	}
	for (int s = 0; s < NB_SEMESTRES; ++s) {
		nb_matiere = p->semestres[s].nbMatieres;
		for (unsigned int i = 0; i < nb_matiere; ++i) {
			for (unsigned int n = 0; n < p->nbUE; ++n) {
				nb_epreuve = p->semestres[s].matieres[i].nbEpreuves;
				for (unsigned int j = 0; j < nb_epreuve; ++j) {
					note_tmp = (q->etudiants[i_etudiant].notes[s][i][j]) * (p->semestres[s].matieres[i].epreuves[j].coef[n]);
					moyenne_tmp += note_tmp;
					q->etudiants[i_etudiant].moyennes[s][n] += note_tmp;
					somme_coef_tmp += p->semestres[s].matieres[i].epreuves[j].coef[n];
				}
				if (somme_coef_tmp != 0) {
					moyenne_tmp = moyenne_tmp / somme_coef_tmp;
					q->etudiants[i_etudiant].coefs[s][n] += somme_coef_tmp;
					moyenne_tmp = 0;
					somme_coef_tmp = 0;
				}
			}
		}
	}
	for (int s = 0; s < NB_SEMESTRES; ++s) {
		printf("\nS%d                 ", s + 1);
		for (unsigned int n = 0; n < p->nbUE; ++n) {
			q->etudiants[i_etudiant].moyennes[s][n] = q->etudiants[i_etudiant].moyennes[s][n] / q->etudiants[i_etudiant].coefs[s][n];
			affichage(q->etudiants[i_etudiant].moyennes[s][n]);
		}
	}
	printf("\n--\nMoyennes annuelles ");
	float moyenne_annuelle_tmp = 0;
	unsigned int ue_valide[MAX_UE];
	for (unsigned int n = 0; n < MAX_UE; ++n) {
		ue_valide[n] = 0;
	}
	for (unsigned int n = 0; n < p->nbUE; ++n) {
		moyenne_annuelle_tmp = (q->etudiants[i_etudiant].moyennes[0][n] + q->etudiants[i_etudiant].moyennes[1][n]) / 2;
		affichage(moyenne_annuelle_tmp);
		if (moyenne_annuelle_tmp >= 10) {
			ue_valide[n] = 1;
		}
	}
	printf("\nAcquisition        ");
	unsigned int nb_ue_valide = 0;
	for (unsigned int n = 0; n < MAX_UE; ++n) {
		if (ue_valide[n] == 1) {
			if (nb_ue_valide == 0) {
				printf("UE%u", n + 1);
			}
			else {
				printf(", UE%u", n + 1);
			}
			nb_ue_valide += 1;
		}
	}
	if (nb_ue_valide == 0) {
		printf("Aucune");
	}
	printf("\nDevenir            ");
	if (nb_ue_valide > ((p->nbUE) / 2)) {
		printf("Passage\n");
	}
	else {
		printf("Redoublement\n");
	}
	
	return;
}

int main() {
	char cde[31] = "";
	Formation f;
	f.nbUE = 0;
	Formation* pf;
	pf = &f;

	Promo p;
	p.nbEtudiants = 0;
	Promo* pp;
	pp = &p;

	for (int i = 0; i < NB_SEMESTRES; ++i) {
		f.semestres[i].nbMatieres = 0;
	}

	do {
		scanf("%s", cde);
		if (strcmp(cde, "formation") == 0) { // C2
			formation(pf);
		}
		else if (strcmp(cde, "epreuve") == 0) { // C3
			epreuve(pf);
		}
		else if (strcmp(cde, "coefficients") == 0) { // C4
			coefficients(pf);
		}
		else if (strcmp(cde, "note") == 0) { // C5
			note(pp, pf);
		}
		else if (strcmp(cde, "notes") == 0) { // C6
			notes(pp, pf);
		}
		else if (strcmp(cde, "releve") == 0) { // C7
			releve(pp, pf);
		}
		else if (strcmp(cde, "decision") == 0) { // C8
			decision(pp, pf);
		}
	} while (strcmp(cde, "exit") != 0); // C1
}

