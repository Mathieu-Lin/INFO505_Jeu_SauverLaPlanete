/**
 * @file element.h
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier header qui met en structure d'état de la Element et qui regroupe les fonctions du element.c 
 * @version 0.1
 * @date 2024-11-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

/**
 * @brief struct Element qui est une liste chainée
*/
typedef struct Element {
    /**
     * @brief nom 
     */
    char nom[50];
    /**
     * @brief pollution qui peut être positif ou négatif pour perturber l'état de Planete
     */
    int pollution;
    /**
     * @brief ressource qui peut être positif ou négatif pour perturber l'état de Planete
     */
    int ressource;
    /**
     * @brief energie qui peut être positif ou négatif pour perturber l'utilisation d' Action
     */
    int energie;
    /**
     * @brief suivant qui est la suite du structure Element
     */
    struct Element *suivant; 
} Element;

/* Les fonctions importées */

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
void initElement(Element *e, const char *nom_Element, int pollution, int ressource, int energie);

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
void ajouterElement(Element **e, const char *nom, int pollution, int ressource, int energie);

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
void ajouterElementTail(Element **e, const char *nom, int pollution, int ressource, int energie);

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
bool supprimerElement(Element **e, const char *nom);

/////////////////
// AFFICHAGE
/////////////////
/**
 * @brief Fonction afficherElement qui affiche les elements chainés
 * 
 * @param *e de type const Element  
 */
void afficherElement(const Element *e);

/////////////////
// LIBERER LA MEMOIRE
/////////////////
/**
 * @brief Fonction libererListeElement qui libère la mémoire allouée pour la liste
 * 
 * @param *e de type Element 
 */
void libererListeElement(Element *e);

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
Element* rechercherElementNom(Element *e, const char *nom);

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
Element* rechercherElementIndice(Element *e, int indice);

/////////////////
// TIRAGE ALEATOIRE
/////////////////
/**
 * @brief  Fonction tirageAleatoireElement qui tire un element aléatoire
 * \param  *e  de type Element
 * \return Element* choisi par hasard
 */
Element* tirageAleatoireElement(Element *e);


#endif
