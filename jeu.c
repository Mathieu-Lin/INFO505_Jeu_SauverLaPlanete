/**
 * @file jeu.c
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier source qui manipule les jeux
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "planete.h"
#include "element.h"
#include "jeu.h"

/**
 * @brief Fonction selectionnerElementAleatoire qui sélectionne au hasard un élément de la liste chainée
 * 
 * @param *e  de type Element
 * @return Element* de type element
 */
Element* selectionnerElementAleatoire(Element *e) {
    if (!e) {
        perror("Echec de la fonction : selectionnerElementAleatoire");
        return NULL;
    }
    return tirageAleatoireElement(e) ;
}

/**
 * @brief Fonction caculScoreV1 permet de calculer un score en fonction de l'état de la planète
 * 
 * @param *p de type Planete dont on calcul en fonction de l'état de la planète (J'ai mis 100 pour éviter le négatif)
 * @return un score de type int
 */
int calculScoreV1(Planete *p) {
    return 100 - p->niveauPollution + p->niveauRessource + p->niveauEnergie;
}

/**
 * @brief Fonction caculScoreV2 permet de calculer un score mais favorise l'importance de l'énergie qui sert pour les générations futures
 * 
 * @param *p de type Planete dont on calcul en fonction de l'état de la planète mais favorisant l'énergie
 * @return un score de type int
 */
int calculScoreV2(Planete *p) {
    return 100 - p->niveauPollution + p->niveauRessource + 2 * p->niveauEnergie;
}

/**
 * @brief Fonction pour sélectionner la stratégie de score
 *  
 */ 
Strategie choisirStrategie() {
    int choix;
    printf("Choisissez une stratégie de calcul de score :\n");
    printf("1. Stratégie 1 (normal)\n");
    printf("2. Stratégie 2 (mode sauvons notre futur génération)\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    getchar(); // Pour consommer le retour de ligne laissé par scanf

    if (choix == 2) {
        return calculScoreV2;
    } else {
        return calculScoreV1;
    }
}


/**
 * @brief Fonction tourDeJeu qui mis à jour l'état de la planète.
 * 
 * @param *p de type Planète
 * @param *evenements de type Element
 * @param *actions de type Element
 * @param scoreFonct de type Strategie 
 * @param *score de type int
 * @param nb_tour de type int
 */
void tourDeJeu(Planete *p, Element *evenements, Element *actions,Strategie scoreFonct, int *score, int nb_tour) {

// à changer pour qu'il affiche la planete après l'aléa
    // Chaque début de tour, la planète se régénère l'énergie    
    p->niveauEnergie += 40;
    // Sélectionner un événement aléatoirement
    Element *event = selectionnerElementAleatoire(evenements);
    // Mise à jour de l'état de la planète
    p->niveauPollution += event->pollution;
    p->niveauRessource +=  event->ressource ;
    p->niveauEnergie += event->energie;

    // Tableau pour stocker le nom de l'action saisie
    char nomAction[50];

    // Demande à l'utilisateur de choisir les actions possibles
    int choix = -1;
    while (choix<0){
        // Affichage des informations du tour
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("Tour %d (Chaque tour +40 energie) : \n", nb_tour);
        printf("Nouveau score : %d\n", *score);
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        afficherPlanete(p);
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        int ajout = -1;
        printf("/////////////////////\n");
        
        // Vérifie l'état de la planète et alerte au joueur si le seuil a été dépassé
        if (verifierPlanete(p)){
            printf("||||||||||||||||||||||||||\n");
            printf("!!!! ALERTE CRITIQUE !!!!\n ");
            printf("||||||||||||||||||||||||||\n");
        }; 

        // Affiche des informations au joueur
        printf("Evenement Tour %d : %s (Pollution : %d, Ressource : %d, Energie : %d) \n", nb_tour, event->nom,event->pollution, event->ressource, event->energie);
        printf("Choisissez parmi les actions : \n");
        afficherElement(actions);

        // Partie de saisie du choix de l'utilisateur et il s'arrête s'il saisie "fin"
        while(ajout<0){
            printf("Saissiez le nom de l'element (fin si vous voulez terminer) : ");
            fgets(nomAction, sizeof(nomAction), stdin);
            // Supprimer le caractère de nouvelle ligne '\n' de fgets
            nomAction[strcspn(nomAction, "\n")] = 0;
            // Terminer le tour
            if (strcmp(nomAction, "fin") == 0) {
                choix=0;
                break;
            }
            // Vérifier si l'action existe dans la liste d'actions
            Element *actionChoisie = rechercherElementNom(actions, nomAction);
            if (actionChoisie) {
                // Vérifier si la planète a suffisamment d'énergie
                if (p->niveauEnergie < actionChoisie->energie) {
                    printf("Pas assez d'énergie pour effectuer l'action %s. Essayez une autre action.\n", nomAction);
                } else {
                    // Ajouter l'action choisie à la liste des actions
                    ajout = 0; // Action ajoutée avec succès
                    // Appliquer l'action à la planète
                    p->niveauEnergie -= actionChoisie->energie; // Coût en énergie
                    p->niveauRessource += actionChoisie->ressource; // Modifier selon l'action
                    p->niveauPollution += actionChoisie->pollution; // Modifier selon l'action

                    // Afficher les résultats de l'action
                    printf("Action %s effectuée! Énergie restante: %d\n", actionChoisie->nom, p->niveauEnergie);
                }
            } else {
                // Afficher si l'action selectionée n'est pas dans la liste
                printf("Action non trouvée. Veuillez essayer une autre action.\n");
            }
        }
    }
    
    // Mise à jour du score
    *score = scoreFonct(p);

    // Affichage des informations du tour
    printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Fin du Tour %d \n", nb_tour);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
}

/**
 * @brief Fonction jeuChoix() permet de jouer et communiquer avec l'utilisateur 
 * 
 */
void jeuChoix() {

    // Créer une planète avec des valeurs initiales
    Planete *p = creationPlanete("Terre", 0, 70, 20);

    // En cas d'erreur,
    if (p == NULL) {
        perror("erreur dans jeuComplet : Création Planete");
        return;
    }

    // Ajouter des actions et événements (exemple simplifié)
    // Actions
    ajouterAction(p, "Loi du climat mondial", -40, 45, 100);
    ajouterAction(p, "Nourriture strict", -5, 2, 10);
    ajouterAction(p, "Planter arbre", 1, 16, 20);
    ajouterAction(p, "Réduire émissions CO2", -7, 0, 10);
    ajouterAction(p, "Gestion des déchets", 4, 3, 5);

    // Evenements
    ajouterEvenement(p, "Ouragan", 15, -8, -5);
    ajouterEvenement(p, "Incendie", 30, -15, -5);
    ajouterEvenement(p, "Gisement des pétroles", 50, -30, 30);
    ajouterEvenement(p, "Rien", 0, 0, 0);
    ajouterEvenement(p, "Apocalypse climatique", 65, -50, -25);
    ajouterEvenement(p, "Chance", -5, 5, 25);

    // Affichage des informations initiales de la planète
    afficherPlanete(p);

    // Demande la stratégie de calcul de score
    Strategie scoreFonct = choisirStrategie();

    // Boucle de jeu
    int tours = 10; // Nombre de tours à simuler
    int score = scoreFonct(p);
    int compt = 0;
    for (int i = 0; i < tours; i++) {
        tourDeJeu(p, p->evenements, p->actions, *scoreFonct,&score, i + 1);
        if (verifierPlanete(p)){
            printf("||||||||||||||||||||||||||\n");
            printf("!!!! DEFAITE (-50 au score) !!!!\n ");
            score = score - 50;
            printf("Nouveau score : %d\n", score);
            printf("||||||||||||||||||||||||||\n");
            break;
        }; 
        compt = i;
    }
    if (compt >= 9){
        printf("||||||||||||||||||||||||||\n");
        printf("!!!! VICTOIRE (+50 au score) !!!!\n ");
        score = score + 50;
        printf("Nouveau score : %d\n", score);
        printf("||||||||||||||||||||||||||\n");
    }

    // Afficher les résultats finaux
    printf("|||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Partie terminée ! État final de la planète :\n");
    afficherPlanete(p);
    printf("Score finale : %d\n", score);

    // Libérer la mémoire allouée
    libererPlanete(p);

}



/**
 * @brief Fonction tourDeJeu2 qui mis à jour l'état de la planète.
 * 
 * @param *p de type Planète
 * @param *evenements de type Element
 * @param *actions de type Element
 * @param scoreFonct de type Strategie 
 * @param *score de type int
 * @param nb_tour de type int
 */
void tourDeJeu2(Planete *p, Element *evenements, Element *actions,Strategie scoreFonct, int *score, int nb_tour) {

// à changer pour qu'il affiche la planete après l'aléa

    // Chaque début de tour, la planète se régénère l'énergie    
    p->niveauEnergie += 40;
    // Sélectionner un événement aléatoirement
    Element *event = selectionnerElementAleatoire(evenements);
    // Mise à jour de l'état de la planète
    p->niveauPollution += event->pollution;
    p->niveauRessource +=  event->ressource ;
    p->niveauEnergie += event->energie;

    // Tableau pour stocker le nom de l'action saisie
    char nomAction[50];

    // Demande à l'utilisateur de choisir les actions possibles
    int choix = -1;
    while (choix<0){
        sleep(3);
        // Affichage des informations du tour
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("Tour %d (Chaque tour +40 energie) : \n", nb_tour);
        printf("Nouveau score : %d\n", *score);
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        afficherPlanete(p);
        printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
        int ajout = -1;
        printf("/////////////////////\n");
        
        // Vérifie l'état de la planète et alerte au joueur si le seuil a été dépassé
        if (verifierPlanete(p)){
            printf("||||||||||||||||||||||||||\n");
            printf("!!!! ALERTE CRITIQUE !!!!\n ");
            printf("||||||||||||||||||||||||||\n");
        }; 

        // Affiche des informations au joueur
        printf("Evenement Tour %d : %s (Pollution : %d, Ressource : %d, Energie : %d) \n", nb_tour, event->nom,event->pollution, event->ressource, event->energie);
        printf("Choisissez parmi les actions : \n");
        afficherElement(actions);

        // Partie de saisie du choix de l'utilisateur et il s'arrête s'il saisie "fin"
        while(ajout<0){
            sleep(3);
            strcpy(nomAction, selectionnerElementAleatoire(actions)->nom);
            // Vérifier si l'action existe dans la liste d'actions
            Element *actionChoisie = rechercherElementNom(actions, nomAction);
            if (actionChoisie) {
                // Vérifier si la planète a suffisamment d'énergie
                if (p->niveauEnergie < actionChoisie->energie) {
                    choix = 0;
                    ajout = 0;
                } else {
                    // Ajouter l'action choisie à la liste des actions
                    ajout = 0; // Action ajoutée avec succès
                    // Appliquer l'action à la planète
                    p->niveauEnergie -= actionChoisie->energie; // Coût en énergie
                    p->niveauRessource += actionChoisie->ressource; // Modifier selon l'action
                    p->niveauPollution += actionChoisie->pollution; // Modifier selon l'action

                    // Afficher les résultats de l'action
                    printf("Action %s effectuée! Énergie restante: %d\n", actionChoisie->nom, p->niveauEnergie);
                }
            } else {
                // Afficher si l'action selectionée n'est pas dans la liste
                printf("Action non trouvée. Veuillez essayer une autre action.\n");
            }
        }
    }
    
    // Mise à jour du score
    *score = scoreFonct(p);

    // Affichage des informations du tour
    printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Fin du Tour %d \n", nb_tour);
    printf("|||||||||||||||||||||||||||||||||||||||||||||||\n");
    sleep(3);
}

/**
 * @brief Fonction jeuComplet() permet de jouer et l'automatiser
 * 
 */
void jeuComplet() {
    // Créer une planète avec des valeurs initiales
    Planete *p = creationPlanete("Terre", 0, 70, 20);

    // En cas d'erreur,
    if (p == NULL) {
        perror("erreur dans jeuComplet : Création Planete");
        return;
    }

    // Initialiser les listes d'actions et d'événements
    Element *actions = NULL;
    Element *evenements = NULL;

    // Ajouter des actions
    int nb_actions;
    printf("Entrez le nombre d'actions à ajouter : ");
    scanf("%d", &nb_actions);
    getchar(); // Nettoyer le caractère '\n' laissé par scanf

    for (int i = 0; i < nb_actions; i++) {
        char nom[50];
        int pollution, ressource, energie;

        printf("Nom de l'action %d : ", i + 1);
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = 0;

        printf("Pollution causée par l'action %s : ", nom);
        scanf("%d", &pollution);
        printf("Ressources générées par l'action %s : ", nom);
        scanf("%d", &ressource);
        printf("Énergie requise pour l'action %s : ", nom);
        scanf("%d", &energie);
        getchar(); // Nettoyer le '\n'

        ajouterElement(&actions, nom, pollution, ressource, energie);


    }

    // Ajouter des événements
    int nb_evenements;
    printf("Entrez le nombre d'événements à ajouter : ");
    scanf("%d", &nb_evenements);
    getchar(); // Nettoyer le '\n'

    for (int i = 0; i < nb_evenements; i++) {
        char nom[50];
        int pollution, ressource, energie;

        printf("Nom de l'événement %d : ", i + 1);
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = 0;

        printf("Pollution causée par l'événement %s : ", nom);
        scanf("%d", &pollution);
        printf("Ressources générées par l'événement %s : ", nom);
        scanf("%d", &ressource);
        printf("Énergie générée par l'événement %s : ", nom);
        scanf("%d", &energie);
        getchar(); // Nettoyer le '\n'

        ajouterElement(&evenements, nom, pollution, ressource, energie);
    }

    // Affichage des informations initiales de la planète
    afficherPlanete(p);

    // Demande la stratégie de calcul de score
    Strategie scoreFonct = choisirStrategie();

    // Boucle de jeu
    int tours = 10; // Nombre de tours à simuler
    int score = scoreFonct(p);
    int compt = 0;
    for (int i = 0; i < tours; i++) {
        tourDeJeu2(p, evenements, actions, *scoreFonct, &score, i + 1);
        if (verifierPlanete(p)) {
            sleep(3);
            printf("||||||||||||||||||||||||||\n");
            printf("!!!! DEFAITE (-50 au score) !!!!\n ");
            score = score - 50;
            printf("Nouveau score : %d\n", score);
            printf("||||||||||||||||||||||||||\n");
            break;
        }
        compt = i;
    }

    if (compt >= 9) {
        sleep(3);
        printf("||||||||||||||||||||||||||\n");
        printf("!!!! VICTOIRE !!!!\n ");
        score = score + 50;
        printf("Nouveau score : %d\n", score);
        printf("||||||||||||||||||||||||||\n");
    }

    sleep(3);
    // Afficher les résultats finaux
    printf("|||||||||||||||||||||||||||||||||||||||||||\n");
    printf("Partie terminée ! État final de la planète :\n");
    afficherPlanete(p);
    printf("Score final : %d\n", score);

    // Libérer la mémoire allouée
    libererPlanete(p);
    libererListeElement(actions);
    libererListeElement(evenements);
}
