/**
 * @file planete.c
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier source qui contient plusieurs fonctions pour planete.h et qui fait la manipulation d'état de la Planete 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include "planete.h"
#include "element.h"
/**
 * @brief Fonction creationPlanete qui crée une planete avec les états initiaux 
 *
 * \param *nom de type const char
 * \param pollution de type int pour le niveau de pollution
 * \param ressource de type int pour le niveau de ressource
 * \param energie de tpe int pour le niveau initial d'énergie
 * \brief Fonction qui crée une planete 
 * \return type Planete (avec les données complétées)
 * 
 */
Planete* creationPlanete(const char *nom, int pollution, int ressource, int energie ) {
    Planete *p = (Planete*)malloc(sizeof(Planete));
    strncpy(p->nom, nom, sizeof(p->nom));
    p->niveauPollution = pollution;
    p->niveauRessource = ressource;
    p->niveauEnergie = energie;
    p->actions = NULL;
    p->evenements = NULL;
    return p;
}
/**
 * @brief Fonction ajouterAction qui ajoute une action à la liste de la structure Planete
 * 
 * @param *p de type Planete
 * @param *nomAction de type const char
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterAction(Planete *p, const char *nomAction, int pollution, int ressource, int energie ) {
    ajouterElement(&p->actions, nomAction, pollution, ressource, energie); 
}

/**
 * @brief Fonction ajouterEvenement qui ajoute un événement à la liste de la structure Planete
 * 
 * @param *p de type Planete
 * @param *nomEvenement de type const char
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterEvenement(Planete *p, const char *nomEvenement, int pollution, int ressource, int energie) {
    ajouterElement(&p->evenements, nomEvenement, pollution, ressource, energie); 
}

/**
 * @brief Fonction afficherPlanete permet d'afficher l'état de la planete et les actions/évévenements.
 *
 * \param *p de type const Planete 
 */
void afficherPlanete(const Planete *p) {
    printf("Planète : %s\n", p->nom);
    printf("Niveau Pollution : %d\n", p->niveauPollution);
    printf("Niveau Ressource : %d\n", p->niveauRessource);
    printf("Niveau Energie : %d\n", p->niveauEnergie);

    // Affichage des actions
    printf("Actions:\n");
    Element *current = p->actions;
    while (current != NULL) {
        printf("- %s\n", current->nom);
        current = current->suivant;
    }

    // Affichage des événements climatiques
    printf("Evenements Climatiques:\n");
    current = p->evenements;
    while (current != NULL) {
        printf("- %s\n", current->nom);
        current = current->suivant;
    }
}

/**
 * @brief Fonction verifierPlanete permet de vérifier si la planète est en état critique.
 * 
 * @param *p de type const Planete
 * @return true si il est et false sinon
 */
bool verifierPlanete(const Planete *p) {
    if (p->niveauRessource <= 0) {
        return true;
    }
    if (p->niveauPollution >= 100) {
        return true;
    }
    return false;
}

/**
 * @brief Fonction modifierPlanete permet de modifier l'état de la planète
 * 
 * @param p de type Planete
 * @param pollution de type int
 * @param ressources de type int
 * @param energie de type int
 */
void modifierPlanete(Planete *p, int pollution, int ressource, int energie) {
    p->niveauPollution = pollution;
    p->niveauRessource = ressource;
    p->niveauEnergie = energie;
}


/**
 * @brief Fonction libererPlanete permet de libérer la mémoire.
 * 
 * @param p de type Planete
 */
void libererPlanete(Planete *p) {
    // Libérer la liste des actions
    libererListeElement(p->actions);
    
    // Libérer la liste des événements
    libererListeElement(p->evenements);
    
    // Libérer le nom
    free(p->nom);
}