/**
 * @file planete.h
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier header qui met en structure d'état de la Planete et qui regroupe les fonctions du planete.c 
 * @version 0.1
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PLANETE_H
#define PLANETE_H

#include "element.h"

/**
 * @brief Structure Planete qui contient des descriptions nécessaires pour le déroulement de la partie 
 */
typedef struct Planete {
    /**
    * @brief le nom d'une planète dont Terre par exemple
    */
    char nom[50];
    /**
    * @brief niveauPollution qui peut être négatif ou positif dont à ne pas dépasser 100
    */
    int niveauPollution;
    /**
    * @brief niveauRessource qui peut être négatif ou positif dont à ne pas être inférieur à 0
    */
    int niveauRessource;
    /**
    * @brief niveauEnergie qui peut être négatif ou positif
    */
    int niveauEnergie;
    /**
    * @brief liste chainée des actions
    */
    struct Element *actions;
    /**
    * @brief liste chainée des événements
    */
    struct Element *evenements;
} Planete;

/* Fonctions importées pour Planete */

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
Planete* creationPlanete(const char *nom, int pollution, int ressource, int energie );

/**
 * @brief Fonction ajouterAction qui ajoute une action à la liste de la structure Planete
 * 
 * @param *p de type Planete
 * @param *nomAction de type const char
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterAction(Planete *p, const char *nomAction, int pollution, int ressource, int energie );

/**
 * @brief Fonction ajouterEvenement qui ajoute un événement à la liste de la structure Planete
 * 
 * @param *p de type Planete
 * @param *nomEvenement de type const char
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterEvenement(Planete *p, const char *nomEvenement, int pollution, int ressource, int energie);

/**
 * @brief Fonction afficherPlanete permet d'afficher l'état de la planete et les actions/évévenements.
 *
 * \param *p de type const Planete 
 */
void afficherPlanete(const Planete *p);

/**
 * @brief Fonction verifierPlanete permet de vérifier si la planète est en état critique.
 * 
 * @param *p de type const Planete
 * @return true si il est et false sinon
 */
bool verifierPlanete(const Planete *p);

/**
 * @brief Fonction modifierPlanete permet de modifier l'état de la planète
 * 
 * @param p de type Planete
 * @param pollution de type int
 * @param ressources de type int
 * @param energie de type int
 */
void modifierPlanete(Planete *p, int pollution, int ressource, int energie);

/**
 * @brief Fonction libererPlanete permet de libérer la mémoire.
 * 
 * @param p de type Planete
 */
void libererPlanete(Planete *p);


#endif