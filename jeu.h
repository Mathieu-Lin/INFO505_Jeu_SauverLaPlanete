/**
 * @file jeu.h
 * @author Mathieu LIN L3-INFO-G1 
 * @brief Fichier header qui regroupe les fonctions du jeu.c 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef JEU_H
#define JEU_H

#include "planete.h"
#include "element.h"

/**
 * @typedef Déclaration du type de fonction pour la stratégie de calcul de score
 * @brief Utilisé pour les stratégies des deux versions de calculs de score
 * 
 */
typedef int (*Strategie)(Planete *p);

/**
 * @brief Fonction selectionnerElementAleatoire qui sélectionne au hasard un élément de la liste chainée
 * 
 * @param *e  de type Element
 * @return Element* de type element
 */
Element* selectionnerElementAleatoire(Element *e);

/**
 * @brief Fonction caculScoreV1 permet de calculer un score en fonction de l'état de la planète
 * 
 * @param *p de type Planete dont on calcul en fonction de l'état de la planète (J'ai mis 100 pour éviter le négatif)
 * @return un score de type int
 */
int calculScoreV1(Planete *p);

/**
 * @brief Fonction caculScoreV2 permet de calculer un score mais favorise l'importance de l'énergie qui sert pour les générations futures
 * 
 * @param *p de type Planete dont on calcul en fonction de l'état de la planète mais favorisant l'énergie
 * @return un score de type int
 */
int calculScoreV2(Planete *p);

/**
 * @brief Fonction pour sélectionner la stratégie de score
 *  
 */ 
Strategie choisirStrategie();

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
void tourDeJeu(Planete *p, Element *evenements, Element *actions,Strategie scoreFonct, int *score, int nb_tour);

/**
 * @brief Fonction jeuChoix() permet de jouer et communiquer avec l'utilisateur 
 * 
 */
void jeuChoix();

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
void tourDeJeu2(Planete *p, Element *evenements, Element *actions,Strategie scoreFonct, int *score, int nb_tour);

/**
 * @brief Fonction jeuComplet() permet de jouer et l'automatiser
 * 
 */
void jeuComplet();

#endif


/**
 * @def Definition pour optimiser le code selon le mode de compilation (DEBUG/RELEASE), (je ne l'utilise pas ^^')
 */
#ifdef DEBUG
    #define LOG_DEBUG(msg) printf("DEBUG: %s\n", msg)
#else
    #define LOG_DEBUG(msg)
#endif
