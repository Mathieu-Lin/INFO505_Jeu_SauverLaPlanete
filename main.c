/**
 * @file main.c
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier qui contient une fonction principale sans interface graphique pour l'éxecution ainsi que les autres fonctions tests 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "element.h"
#include "planete.h"
#include "jeu.h"

// Mathieu LIN
// TP INFO505 (3 séances)
// ======================
// Outils (à ignorer) :
// 
// GCC :
// gcc -o main main.c element.c
// gcc -o main main.c
// 
// Faire un bibiliothèque statique
// gcc -c element.c -o element.o    # Compiler le fichier source en objet
// ar rcs libElement.a element.o  # Créer la bibliothèque statique
// gcc -c planete.c -o planete.o    # Compiler le fichier source en objet
// ar rcs libElement.a planete.o element.o    # Compiler le fichier source en objet
// nano Makefile
//
// Création un makefile
// make
// make clean
// ======================


/**
 * @brief Fonction testElement() permet de tester la manipulation des listes chainées 
 * 
 */
void testElement() {
    Element *liste = NULL;

    // Ajout d'éléments
    ajouterElement(&liste, "Incendie", 5, -5,0);
    ajouterElement(&liste, "Sécheresse", 0, -10,0);
    ajouterElementTail(&liste, "Rien", 0, 0,0);
    ajouterElementTail(&liste, "Seisme", 0, -5,0);
    ajouterElementTail(&liste, "Tornade", 0, -3,0);
    ajouterElementTail(&liste, "Pluie abondance", -8, 8,0);
    ajouterElementTail(&liste, "Oula", 100, -100,0);
    
    printf("Liste après ajout d'elements :\n");
    afficherElement(liste);

    // Suppression d'un élément
    supprimerElement(&liste, "Oula");
    printf("\nListe après suppression d'un élément :\n");
    afficherElement(liste);

    // Recherche d'un élément
    Element *found = rechercherElementNom(liste, "Tornade");
    if (found) {
        printf("\nelement trouvé : %s, Pollution : %d, Ressource : %d, Energie : %d\n", found->nom, found->pollution, found->ressource, found->energie);
    } else {
        printf("\nelement non trouvé.\n");
    }

    // Tirage aléatoire d'un élément
    Element *randomElement = tirageAleatoireElement(liste);
    if (randomElement) {
        printf("element aléatoire : %s, Pollution : %d, Ressource : %d, Energie : %d\n", randomElement->nom, randomElement->pollution,randomElement->ressource, randomElement->energie);
    }

    // Libération de la mémoire
    libererListeElement(liste);
}

/**
 * @brief Fonction testPlanete() permet de tester la manipulation de la planète
 * 
 */
void testPlanete(){
    // ////////////////////////////////////////////////////////
    printf("\n//////////////////////////////////////////////////////////\n");

    Planete *terre = creationPlanete("Terre", 100, 200, 10);

    ajouterAction(terre, "Planter des arbres",-10,10,10);
    ajouterEvenement(terre, "Tempête",5,-2,0);

    afficherPlanete(terre);
    verifierPlanete(terre);

    modifierPlanete(terre, 80, 150, 50);
    afficherPlanete(terre);

    free(terre);  // Libération de la mémoire allouée
}


/**
 * @brief Fonction main() permet d'executer comme fonction principale
 * 
 * @return int 
 */
int main() {
    ///////////////////////
    // TESTS
    //////////////////////

    testElement();
    testPlanete();

    ///////////////////////
    // JOUER 
    //////////////////////
    int choix;
    printf("Choisissez une mode d'une partie du jeu :\n");
    printf("1. Partie 1 (Jeu tour à tour)\n");
    printf("2. Partie 2 (Jeu full automatique crée par vous)\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    getchar(); // Pour consommer le retour de ligne laissé par scanf

    if (choix == 2) {
        jeuComplet();
    } else {
        jeuChoix();
    }

    ///////////////////////
    // FIN
    //////////////////////

    return 0;
}

