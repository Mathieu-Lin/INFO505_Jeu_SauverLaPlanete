/**
 * @file element.c
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier source qui contient plusieurs fonctions pour element.h et qui fait la manipulation d'état de la Element
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "element.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
/////////////////
// INITIALISATION
/////////////////
/**
 * @brief Fonction initElement qui initialise un element avec les données 
 * 
 * @param *e de type Element
 * @param *nom_Element de type const char (const sert à montrer que ce paramètre ne soit pas modifié)
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void initElement(Element *e, const char *nom_Element, int pollution, int ressource, int energie) {
    strcpy(e->nom, nom_Element);
    e->pollution = pollution;
    e->ressource = ressource;
    e->energie = energie;
    e->suivant = NULL;  // Initialiser le pointeur "suivant" à NULL
}

/////////////////
// AJOUTER
/////////////////
/**
 * @brief Fonction ajouterElement qui ajoute un nouveau element au début de la liste
 * 
 * @param **e de type Element (double pointeur) 
 * @param *nom de type const char 
 * @param pollution de type int
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterElement(Element **e, const char *nom, int pollution, int ressource, int energie) {
    Element *nouveau = (Element *)malloc(sizeof(Element));
    if (!nouveau) {
        fprintf(stderr, "Erreur mémoire\n");
        return;
    }
    strcpy(nouveau->nom, nom);
    nouveau->pollution = pollution;
    nouveau->ressource = ressource;
    nouveau->energie = energie;
    nouveau->suivant = *e;  // Le nouveau élément pointe vers l'ancien premier élément
    *e = nouveau;           // Le nouveau devient le premier élément de la liste
}

/////////////////
// AJOUTER FIN
/////////////////
/**
 * @brief Fonction ajouterElementTail qui ajoute un element à la fin de la liste
 * 
 * @param **e de type Element (double pointeur) 
 * @param *nom de type const char 
 * @param pollution de type int 
 * @param ressource de type int
 * @param energie de type int
 */
void ajouterElementTail(Element **e, const char *nom, int pollution, int ressource, int energie) {
    Element *nouveau = (Element *)malloc(sizeof(Element));
    if (!nouveau) {
        fprintf(stderr, "Erreur mémoire\n");
        return;
    }
    strcpy(nouveau->nom, nom);
    nouveau->pollution = pollution;
    nouveau->ressource = ressource;
    nouveau->energie = energie;
    nouveau->suivant = NULL;

    if (*e == NULL) {
        *e = nouveau;  // Si la liste est vide, le nouveau devient le premier élément
    } else {
        Element *current = *e;  // Correction : utilisation de *e au lieu de *liste
        while (current->suivant != NULL) {
            current = current->suivant;
        }
        current->suivant = nouveau;  // Lier le dernier element au nouveau
    }
}

/////////////////
// SUPPRIMER
/////////////////
/**
 * @brief Fonction supprimerElement qui supprime un element en tête
 * 
 * @param **e de type Element (double pointeur)
 * @param *nom de type const char  
 * @return true si la suppression est réussie
 * @return false sinon
 */
bool supprimerElement(Element **e, const char *nom) {
    Element *current = *e;
    Element *precedent = NULL;

    while (current != NULL && strcmp(current->nom, nom) != 0) {
        precedent = current;
        current = current->suivant;
    }

    if (current == NULL) {
        return false;  // element non trouvé
    }

    if (precedent == NULL) {
        *e = current->suivant;  // Supprime le premier élément
    } else {
        precedent->suivant = current->suivant;  // Supprime un element au milieu ou à la fin
    }

    free(current);
    return true;  // Suppression réussie
}

/////////////////
// AFFICHAGE
/////////////////
/**
 * @brief Fonction afficherElement qui affiche les elements chainés
 * 
 * @param *e de type const Element  
 */
void afficherElement(const Element *e) {
    const Element *current = e;
    while (current != NULL) {
        printf("//////////////////////////////////////\n");
        printf("Element : %s\n", current->nom);
        printf("Pollution : %d\n", current->pollution);
        printf("Ressource : %d\n", current->ressource);
        printf("Energie : %d\n", current->energie);
        current = current->suivant;  // Passer au prochain element
    }
}


/////////////////
// LIBERER LA MEMOIRE
/////////////////
/**
 * @brief Fonction libererListeElement qui libère la mémoire allouée pour la liste
 * 
 * @param *e de type Element 
 */
void libererListeElement(Element *e) {
    Element *current = e;
    while (current != NULL) {
        Element *temp = current;
        current = current->suivant;
        free(temp);
    }
}

/////////////////
// RECHERCHER NOM
/////////////////
/**
 * @brief Fonction rechercherElementNom qui recherche un element par le nom du paramètre
 * 
 * @param *e de type Element 
 * @param *nom de type const char 
 * @return Element*  si trouvé et NULL sinon  
 */
Element* rechercherElementNom(Element *e, const char *nom) {
    Element *current = e;
    while (current != NULL) {
        if (strcmp(current->nom, nom) == 0) {
            return current;  // Retourner l'element trouvé
        }
        current = current->suivant;
    }
    return NULL;  // Retourner NULL si non trouvé
}


/////////////////
// RECHERCHER INDICE
/////////////////
/**
 * @brief Fonction rechercherElementIndice qui recherche un element par l'indice du paramètre
 * 
 * @param *e de type Element
 * @param indice de type int
 * @return Element* si trouvé et NULL (aussi en cas de dépassement de l'indice) sinon 
 */
Element* rechercherElementIndice(Element *e, int indice) {
    Element *current = e;
    int i = 0;
    while (current != NULL) {
        if (i == indice) {
            return current;  // Retourner l'element trouvé
        }
        current = current->suivant;
        i++;
    }
    return NULL;  // Retourner NULL si l'indice est hors limites
}


/////////////////
// TIRAGE ALEATOIRE 
/////////////////
/**
 * @brief  Fonction tirageAleatoireElement qui tire un element aléatoire
 * \param  *e  de type Element
 * \return Element* choisi par hasard
 */
Element* tirageAleatoireElement(Element *e) {
    int taille = 0;
    Element *current = e;
    while (current != NULL) {
        taille++;
        current = current->suivant;
    }

    if (taille == 0) {
        return NULL;
    }
    srand(time(NULL));  // Initialiser le générateur aléatoire
    int randomIndex = rand() % taille;

    return rechercherElementIndice(e, randomIndex);
}