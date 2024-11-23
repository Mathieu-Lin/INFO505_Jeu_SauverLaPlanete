/**
 * @file mainGTK.c
 * @author Mathieu LIN L3-INFO-G1
 * @brief Fichier qui contient une fonction principale pour l'interface GTK
 * @version 0.1
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <gtk/gtk.h>
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
//
// Symboles :
// JTT : Jeu Tour à Tour
// JFA : Jeu Full Automatique
// Strat1 : Mode normal
// Strat2 : Mode sauver la prochaine génération (x2 energie)
// ======================


/**
 * @brief Structure ActionData permet aux actions de manipuler l'état de la Planete
 */
typedef struct {
    /**
     * @brief Action associée au bouton
     */
    Element *action; 
    /**
     * @brief Planete associée pour l'état
     */
    Planete *planete; 
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_status;
    /**
     * @brief Label pour l'état de la planète
     */
    GtkWidget *label_state;  
} ActionData;

/**
 * @brief Structure TurnData permet de manipuler chaque tour
 */
typedef struct {
    /**
     * @brief Label pour l'état de la planète
     */
    Planete *planete; // Planète associée
    /**
     * @brief Comptage de tour
     */
    int compt;
    /**
     * @brief Nombre de tour maximal
     */
    int tour;
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_status; 
    /**
     * @brief Le Strategie de calcul à transporter vers la victoire ou la défaite
     */
    Strategie strategieFonct;
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_welcome;  // Label pour welcome
    /**
     * @brief Label pour l'état de la planète
     */
    GtkWidget *label_planet; 
    /**
     * @brief Fond d'image pour planete
     */
    GtkWidget *image; 
    /**
     * @brief Fenetre à transporter vers la victoire ou la défaite
     */
    GtkWidget *window;
} TurnData;

/**
 * @brief Structure DemandData permet de manipuler la demande de l'utilisateur
 */
typedef struct {
    /**
     * @brief Entrée du nom d'action
     */
    GtkWidget *entry_nomAction;
    /**
     * @brief Entrée du nom du pollution d'action
     */
    GtkWidget *entry_pollutionAction;
    /**
     * @brief Entrée du nom d'une ressource d'action
     */
    GtkWidget *entry_ressourceAction;
    /**
     * @brief Entrée du nom d'énergie d'action
     */
    GtkWidget *entry_energieAction;
    /**
     * @brief Entrée du nom d'événement
     */
    GtkWidget *entry_nomEvent;
    /**
     * @brief Entrée du nom du pollution d'événement
     */
    GtkWidget *entry_pollutionEvent;
    /**
     * @brief Entrée du nom d'une ressource d'événement
     */
    GtkWidget *entry_ressourceEvent;
    /**
     * @brief Entrée du nom d'énergie d'action
     */
    GtkWidget *entry_energieEvent;
    /**
     * @brief Label pour messages
     */
    GtkWidget *label_welcome;
    /**
     * @brief Label pour le hover du liste Element
     */
    GtkWidget *info_label;
    /**
     * @brief Container pour la liste Action
     */
    GtkWidget *hboxAction;
    /**
     * @brief Container pour la liste Event
     */
    GtkWidget *hboxEvent;
    /**
     * @brief Fenetre à transporter vers la victoire ou la défaite
     */
    GtkWidget *window;
    /**
     * @brief Planete qui se modifie son état
     */
    Planete *planete;
    /**
     * @brief Strategie à transporter vers la victoire ou la défaite
     */
    Strategie strategieFonct;
} DemandData;

/**
 * @brief Structure GameState permet de manipuler l'automatique
 */
typedef struct {
    /**
     * @brief Nombre de tour maximal
     */
    int tours;        
    /**
     * @brief Comptage de tour
     */
    int compt;        
    /**
     * @brief Planete qui se modifie son état
     */
    Planete *p;       
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_welcome;
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_state;
    /**
     * @brief Label pour afficher les messages
     */
    GtkWidget *label_status;
    /**
     * @brief Label pour hover de la liste Element
     */
    GtkWidget *info_label;
    /**
     * @brief Container de la liste Action
     */
    GtkWidget *hboxAction;
    /**
     * @brief Container de la liste Event
     */
    GtkWidget *hboxEvent;
    /**
     * @brief Image pour le fond.
     */
    GtkWidget *image;
    /**
     * @brief Fenetre à transporter vers la victoire ou la défaite
     */
    GtkWidget *window;
    /**
     * @brief Strategie à transporter vers la victoire ou la défaite
     */
    Strategie calc;
} GameState;




// Prototype des fonctions
// PARTIE JTT /////////////////////////////////////////////
void on_buttonJTT_clicked(GtkWidget *widget, gpointer data);
void on_buttonJTTStrat1_clicked(GtkWidget *widget, gpointer data);
void on_buttonJTTStrat2_clicked(GtkWidget *widget, gpointer data);
void on_action_button_clicked(GtkWidget *widget, gpointer user_data);
void on_end_turn_clicked(GtkWidget *widget, gpointer data);
void create_interfaceJTT(GtkWidget *window);
void create_interfaceJTTStrat(GtkWidget *window, Strategie calc);
void on_button_hover(GtkWidget *widget, GdkEventCrossing *event, gpointer data);

// PARTIE JFA /////////////////////////////////////////////
void on_buttonJFA_clicked(GtkWidget *widget, gpointer data);
void on_buttonJFAStrat1_clicked(GtkWidget *widget, gpointer data);
void on_buttonJFAStrat2_clicked(GtkWidget *widget, gpointer data);
void on_demand_button_clicked(GtkWidget *widget, gpointer demand_data);
void on_next_button_clicked(GtkWidget *widget, gpointer demand_data);
void create_interfaceJFA(GtkWidget *window);
void create_interfaceJFAStrat(GtkWidget *window, Strategie calc);
void create_interfaceJFAStrat2(GtkWidget *window, Strategie calc, Planete *p);

// Autres 
void show_defeat_screen(GtkWidget *window, Strategie strat, Planete *p);
void show_victory_screen(GtkWidget *window, Strategie strat, Planete *p);
void load_css(const char *css_file);
int is_valid_integer(const char *str);
gboolean jouer_tour(GameState *state);
gboolean auto_random_action(GameState *state);













/**
 * @brief Fonction principale pour exécuter l'interface graphique
 */
int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *fixed;
    GtkWidget *image;
    GtkWidget *button1;
    GtkWidget *button2;

    // Initialisation de GTK
    gtk_init(&argc, &argv);

    // Charger le style CSS (facultatif)
    load_css("style.css");

    // Création de la fenêtre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sauver la planète !");
    gtk_window_set_default_size(GTK_WINDOW(window), 750, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    // Gestion de la fermeture de la fenêtre
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Conteneur fixe pour positionner les widgets
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Ajouter l'image de fond
    image = gtk_image_new_from_file("./image/planet.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    // Ajouter le bouton 1 : Jeu tour à tour
    button1 = gtk_button_new_with_label("Jeu tour à tour");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_buttonJTT_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 550, 250); // Positionnement en pixels

    // Ajouter le bouton 2 : Jeu full automatique
    button2 = gtk_button_new_with_label("Jeu full automatique crée par vous");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 475, 300); // Positionnement en pixels

    // Afficher tous les widgets
    gtk_widget_show_all(window);

    // Boucle principale GTK
    gtk_main();

    return 0;
}






























////////////////
//// BUTTON ///
////////////////

// PARTIE JTT /////////////////////////////////////////////
// Fonction appelée lors du clic sur le bouton JTT
/**
 * @brief Si vous choisissez jeu tour à tour
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJTT_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    create_interfaceJTT(window);
}

/**
 * @brief Si vous choisissez jeu tour à tour avec Strategie normale
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJTTStrat1_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    Strategie calc= calculScoreV1;
    create_interfaceJTTStrat(window, calc);
}

/**
 * @brief Si vous choisissez jeu tour à tour avec Strategie sauver la prochaine génération
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJTTStrat2_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    Strategie calc= calculScoreV2;
    create_interfaceJTTStrat(window, calc);
}

/**
 * @brief Callback pour gérer le clic sur un bouton d'action
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_action_button_clicked(GtkWidget *widget, gpointer user_data) {
    (void)widget;
    // Récupérer les données associées
    gpointer *data = (gpointer *)user_data;
    Element *action = (Element *)data[0];    // Action sélectionnée
    Planete *p = (Planete *)data[1];         // Planète concernée
    GtkLabel *label_status = (GtkLabel *)data[2]; // Label pour afficher les messages
    GtkLabel *label_state = (GtkLabel *)data[3];  // Label pour afficher l'état de la planète

    if (action == NULL || p == NULL || label_status == NULL || label_state == NULL) {
        gtk_label_set_text(label_status, "Erreur : données invalides.");
        return;
    }

    // Vérifier si l'action existe dans la liste
    Element *actionChoisie = rechercherElementNom(p->actions, action->nom);
    if (actionChoisie == NULL) {
        gtk_label_set_text(label_status, "Action non trouvée. Veuillez essayer une autre action.");
        return;
    }

    // Vérifier si la planète a suffisamment d'énergie
    if (p->niveauEnergie < actionChoisie->energie) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "Pas assez d'énergie pour l'action %s.", actionChoisie->nom);
        gtk_label_set_text(label_status, buffer);
        return;
    }

    // Appliquer les effets de l'action
    p->niveauEnergie -= actionChoisie->energie;     // Réduire l'énergie
    p->niveauRessource += actionChoisie->ressource; // Modifier les ressources
    p->niveauPollution += actionChoisie->pollution; // Modifier la pollution

    // Afficher le résultat après application
    gtk_label_set_text(label_status, "Action effectuée avec succès !");
    char buffer_state[256];
    snprintf(buffer_state, sizeof(buffer_state),
             " État de la planète %s : Pollution %d, Ressource %d, Energie %d",
             p->nom,p->niveauPollution, p->niveauRessource, p->niveauEnergie);
    gtk_label_set_text(label_state, buffer_state);
}

/**
 * @brief Callback pour gérer le clic sur un bouton de fin tour
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_end_turn_clicked(GtkWidget *widget, gpointer turn_data) {
    (void)widget; // Éviter l'avertissement pour widget inutilisé

    // Récupérer les données associées
    TurnData *data = (TurnData *)turn_data;
    if (!data) {
        g_warning("Données de tour non valides !");
        return;
    }

    Planete *p = data->planete;
    if (!p) {
        g_warning("Planète invalide !");
        return;
    }

    int *compt = &data->compt; // Référence à compt pour incrémenter directement
    int tours = data->tour;
    GtkLabel *label_status = GTK_LABEL(data->label_status);
    GtkLabel *label_welcome = GTK_LABEL(data->label_welcome);
    Strategie calculFonct = data->strategieFonct;
    GtkWidget *window = data->window;
    GtkLabel *label_planet = GTK_LABEL(data->label_planet);
    GtkImage *image = GTK_IMAGE(data->image);
    // Vérification des widgets
    if (!GTK_IS_LABEL(label_status) || !GTK_IS_LABEL(label_welcome)) {
        g_warning("Les widgets `label_status` ou `label_welcome` ne sont pas des GtkLabel valides !");
        return;
    }
    if (!GTK_IS_WINDOW(window)) {
        g_warning("Le widget `window` n'est pas une GtkWindow valide !");
        return;
    }

    // Vérifier l'état de la planète
    if (verifierPlanete(p)) {
        show_defeat_screen(window, calculFonct, p);
    } else if (*compt == tours) { // Vérifier si on atteint le dernier tour
        show_victory_screen(window, calculFonct, p);
    } else {
        // Incrémenter le compteur de tours
        (*compt)++;
        p->niveauEnergie +=40;

        // Evénement ! ///////////////////////////////////////////////////////////////////////////////
        Element *event = selectionnerElementAleatoire(p->evenements);
        p->niveauPollution += event->pollution;
        p->niveauRessource +=  event->ressource ;
        p->niveauEnergie += event->energie;
        // Evénement ! ///////////////////////////////////////////////////////////////////////////////

        if (verifierPlanete(p)){
            if (p->niveauPollution >= 100 && p->niveauRessource <= 0){
                gtk_image_set_from_file(image, "./image/defeat.jpg");
            } else if (p->niveauRessource <= 0){
                gtk_image_set_from_file(image, "./image/ressource.jpg");
            } else {
                gtk_image_set_from_file(image, "./image/pollution.jpg");
            }
        } else {
            gtk_image_set_from_file(image, "./image/planet.png");
        }
        // Mettre à jour les informations de l'interface
        char *label_wel = g_strdup_printf(
            "Tour %d (+40 energie par tour) | Evenement : %s (Pollution %d, Ressource %d, Energie %d) | Alerte : %s",
            *compt,event->nom, event->pollution, event->ressource, event->energie,verifierPlanete(p) ? "ON" : "OFF");
        gtk_label_set_text(label_welcome, label_wel);
        g_free(label_wel);

        char *label_state = g_strdup_printf(
            "État de la planète %s : Pollution %d, Ressource %d, Energie %d",
            p->nom, p->niveauPollution, p->niveauRessource, p->niveauEnergie);
        gtk_label_set_text(label_planet, label_state);
        g_free(label_state);

        // Appliquer la stratégie de calcul de score
        if (calculFonct) {
            calculFonct(p);
        } else {
            g_warning("Fonction de stratégie invalide !");
        }

        // Optionnel : Ajouter un message dans `label_status`
        gtk_label_set_text(label_status, "Fin du tour activé !");
    }
}



// PARTIE JFA /////////////////////////////////////////////

/**
 * @brief Callback pour gérer le clic sur un bouton vers le jeu full auto
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJFA_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    create_interfaceJFA(window);
}

/**
 * @brief Callback pour gérer le clic sur un bouton vers le jeu full auto Strategie normale
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJFAStrat1_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    Strategie calc= calculScoreV1;
    create_interfaceJFAStrat(window, calc);
}

/**
 * @brief Callback pour gérer le clic sur un bouton vers le jeu full auto Strategie sauver la prochaine generation
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_buttonJFAStrat2_clicked(GtkWidget *widget, gpointer data) {
    (void)widget;
    GtkWidget *window = GTK_WIDGET(data);
    Strategie calc= calculScoreV2;
    create_interfaceJFAStrat(window, calc);
}

/**
 * @brief Callback pour gérer le clic sur un bouton de gestion de vos demandes de saisie
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_demand_button_clicked(GtkWidget *widget, gpointer demand_data) {
    (void)widget;
    // Récupérer les données associées
    DemandData *data = (DemandData *)demand_data;
    Planete *p = data->planete;
    GtkWidget *label_welcome = data->label_welcome;
    GtkWidget *info_label = data->info_label;
    GtkWidget *hboxAction = data->hboxAction;
    GtkWidget *hboxEvent = data->hboxEvent;

    const char *nomAction = gtk_entry_get_text(GTK_ENTRY(data->entry_nomAction));
    const char *pollution_textAction = gtk_entry_get_text(GTK_ENTRY(data->entry_pollutionAction));
    const char *ressource_textAction = gtk_entry_get_text(GTK_ENTRY(data->entry_ressourceAction));
    const char *energie_textAction = gtk_entry_get_text(GTK_ENTRY(data->entry_energieAction));

    const char *nomEvent = gtk_entry_get_text(GTK_ENTRY(data->entry_nomEvent));
    const char *pollution_textEvent = gtk_entry_get_text(GTK_ENTRY(data->entry_pollutionEvent));
    const char *ressource_textEvent = gtk_entry_get_text(GTK_ENTRY(data->entry_ressourceEvent));
    const char *energie_textEvent = gtk_entry_get_text(GTK_ENTRY(data->entry_energieEvent));

    if (strlen(nomAction) != 0 && strlen(pollution_textAction) != 0 && strlen(ressource_textAction) != 0 && strlen(energie_textAction) != 0 ){
        if (is_valid_integer(pollution_textAction) && is_valid_integer(ressource_textAction) && is_valid_integer(energie_textAction)){
            // Conversion des autres entrées en entiers pour pollution, ressource et énergie
            int pollutionAction = atoi(pollution_textAction);
            int ressourceAction = atoi(ressource_textAction);
            int energieAction = atoi(energie_textAction);
            if (rechercherElementNom(p->actions, nomAction) == NULL) {
                ajouterAction(p, g_strdup(nomAction), pollutionAction, ressourceAction, energieAction);
            } else {
                supprimerElement(&(p->actions), nomAction);
                ajouterAction(p, g_strdup(nomAction), pollutionAction, ressourceAction, energieAction);
            }
            // Suppression à l'intérieur du container
            if (GTK_IS_CONTAINER(hboxAction)) {
                GList *children = gtk_container_get_children(GTK_CONTAINER(hboxAction));
                for (GList *child = children; child != NULL; child = child->next) {
                    gtk_widget_destroy(GTK_WIDGET(child->data));
                }
                g_list_free(children);
            }
            // Créer un bouton pour chaque action
            Element *current = p->actions; // Liste des actions
            while (current != NULL) {
                GtkWidget *button = gtk_button_new_with_label(current->nom);

                // Associer l'action au bouton avec g_object_set_data
                g_object_set_data(G_OBJECT(button), "action_data", current);  // ici on associe l'action au bouton

                // Connecter les signaux pour survol et sortie de la souris
                g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), info_label);
                g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), info_label);

                // Ajouter le bouton au conteneur horizontal
                gtk_box_pack_start(GTK_BOX(hboxAction), button, TRUE, TRUE, 0);

                current = current->suivant; // Passer à l'action suivante
            }
            // Rafraîchir l'affichage de hboxAction
            gtk_widget_show_all(hboxAction);
        } else {
            gtk_label_set_text(GTK_LABEL(label_welcome), "Valeur de l'action saisie pour pollution, ressource, energie contient uniquement en entier relatif");
        }
    } 
    
    if (strlen(nomEvent) != 0 && strlen(pollution_textEvent) != 0 && strlen(ressource_textEvent) != 0 && strlen(energie_textEvent) != 0 ){
        if (is_valid_integer(pollution_textEvent) && is_valid_integer(ressource_textEvent) && is_valid_integer(energie_textEvent)){
            // Conversion des autres entrées en entiers pour pollution, ressource et énergie
            int pollutionEvent = atoi(pollution_textEvent);
            int ressourceEvent = atoi(ressource_textEvent);
            int energieEvent = atoi(energie_textEvent);
            if (rechercherElementNom(p->evenements, nomEvent) == NULL){
                ajouterEvenement(p,g_strdup(nomEvent) , pollutionEvent, ressourceEvent, energieEvent);
            } else {
                supprimerElement(&(p->evenements), nomEvent);
                ajouterEvenement(p,g_strdup(nomEvent) , pollutionEvent, ressourceEvent, energieEvent);
            }
            // Suppression à l'intérieur du container
            if (GTK_IS_CONTAINER(hboxEvent)) {
                GList *children = gtk_container_get_children(GTK_CONTAINER(hboxEvent));
                for (GList *child = children; child != NULL; child = child->next) {
                    gtk_widget_destroy(GTK_WIDGET(child->data));
                }
                g_list_free(children);
            }
            // Créer un bouton pour chaque événement
            Element *current = p->evenements; // Liste des événements
            while (current != NULL) {
                GtkWidget *button = gtk_button_new_with_label(current->nom);

                // Associer l'action au bouton avec g_object_set_data
                g_object_set_data(G_OBJECT(button), "event_data", current);  // ici on associe l'action au bouton

                // Connecter les signaux pour survol et sortie de la souris
                g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), info_label);
                g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), info_label);

                // Ajouter le bouton au conteneur horizontal
                gtk_box_pack_start(GTK_BOX(hboxEvent), button, TRUE, TRUE, 0);

                current = current->suivant; // Passer à l'action suivante
            }
            // Rafraîchir l'affichage de hboxAction
            gtk_widget_show_all(hboxEvent);
        } else {
            if (is_valid_integer(pollution_textAction) && is_valid_integer(ressource_textAction) && is_valid_integer(energie_textAction)){
                gtk_label_set_text(GTK_LABEL(label_welcome), "Pour pollution, ressource, energie, il faut saisir uniquement en entier relatif");
            } else {
                gtk_label_set_text(GTK_LABEL(label_welcome), "Valeur de l'évenment saisi pour pollution, ressource, energie contient uniquement en entier relatif");
            }
        }
    }

}

/**
 * @brief Callback pour gérer le clic sur un bouton de démarrage d'une partie full auto
 * 
 * @param widget pour relier du bouton
 * @param gpointer pour le donnée
 */
void on_next_button_clicked(GtkWidget *widget, gpointer demand_data) {
    (void)widget;
    // Récupérer les données associées
    DemandData *data = (DemandData *)demand_data;
    Planete *p = data->planete;
    Strategie calc = data->strategieFonct;
    GtkWidget *window = data->window;
    // Interface
    if (p->actions != NULL && p->evenements != NULL){
        create_interfaceJFAStrat2(window, calc,p);
    }
}























////////////////
//// INTERFACE ///
////////////////









// PARTIE JTT /////////////////////////////////////////////
/**
 * @brief Fonction pour créer l'Interface JTT dans la même fenêtre
 * 
 * @param window pour fenetre
 */
void create_interfaceJTT(GtkWidget *window) {
    GtkWidget *fixed;  // Pour superposer les widgets
    GtkWidget *image;    // Image de fond
    GtkWidget *label;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button_back;


    // Supprimer tous les widgets de la fenêtre
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for (GList *child = children; child != NULL; child = child->next) {
        gtk_widget_destroy(GTK_WIDGET(child->data));
    }
    g_list_free(children);

    // Conteneur fixe pour positionner les widgets
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Ajouter l'image de fond
    image = gtk_image_new_from_file("./image/planet.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    // Label
    label = gtk_label_new("Bienvenue sur le jeu tour à tour !\n Choisissez la stratégie pour le calcul du score :");
    gtk_fixed_put(GTK_FIXED(fixed), label, 425, 250); 

    // Bouton Strat1
    button1 = gtk_button_new_with_label("Normal");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_buttonJTTStrat1_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 400, 300); 

    // Bouton Strat2
    button2 = gtk_button_new_with_label("Sauver la prochaine génération");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_buttonJTTStrat2_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 550, 300); 

    // Bouton pour revenir à l'interface JFA
    button_back = gtk_button_new_with_label("Revenir vers le jeu full automatique crée par vous !");
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button_back, 410, 350); 

    // Afficher l'interface
    gtk_widget_show_all(window);
}

/**
 * @brief Fonction pour créer l'Interface JTT avec Strategie qui lance la partie
 * 
 * @param window pour fenetre
 * @param Strategie pour transfert
 */
void create_interfaceJTTStrat(GtkWidget *window, Strategie calc) {
    // Créer une planète avec des valeurs initiales
    Planete *p = creationPlanete("Terre", 0, 70, 60);

    // Ajouter des actions
    ajouterAction(p, "Loi du climat mondial", -40, 45, 100);
    ajouterAction(p, "Nourriture strict", -5, 2, 10);
    ajouterAction(p, "Planter arbre", 1, 16, 20);
    ajouterAction(p, "Réduire émissions CO2", -7, 0, 10);
    ajouterAction(p, "Gestion des déchets", 4, 3, 5);

    // Ajouter des événements
    ajouterEvenement(p, "Ouragan", 15, -8, -5);
    ajouterEvenement(p, "Incendie", 30, -15, -5);
    ajouterEvenement(p, "Gisement des pétroles", 50, -30, 30);
    ajouterEvenement(p, "Rien", 0, 0, 0);
    ajouterEvenement(p, "Apocalypse climatique", 65, -50, -25);
    ajouterEvenement(p, "Chance", -5, 5, 25);

    // Evénement ! ///////////////////////////////////////////////////////////////////////////////
    Element *event = selectionnerElementAleatoire(p->evenements);
    p->niveauPollution += event->pollution;
    p->niveauRessource +=  event->ressource ;
    p->niveauEnergie += event->energie;
    // Evénement ! ///////////////////////////////////////////////////////////////////////////////

    // Gestion des tours
    int tours = 10; // Nombre de tours à simuler
    int compt = 1;

    // Supprimer tous les widgets existants dans la fenêtre
    if (GTK_IS_CONTAINER(window)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(window));
        for (GList *child = children; child != NULL; child = child->next) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
        g_list_free(children);
    }
    
    GtkWidget *fixed = gtk_fixed_new();
    GtkWidget *image = gtk_image_new_from_file("./image/planet.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    // Conteneur vertical principal
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 50, 50);
    gtk_container_add(GTK_CONTAINER(window), fixed);
    char *label_wel;
    if (verifierPlanete(p)){
        // Utiliser g_strdup_printf pour formater la chaîne avant de la passer à gtk_label_new
        label_wel = g_strdup_printf("Tour %d (+40 energie par tour)| Evenement : %s (Pollution %d, Ressource %d, Energie %d) | Alerte : ON", 
                                    compt, event->nom, event->pollution, event->ressource, event->energie);
    }else{
        // Utiliser g_strdup_printf pour formater la chaîne avant de la passer à gtk_label_new
        label_wel = g_strdup_printf("Tour %d (+40 energie par tour)| Evenement : %s (Pollution %d, Ressource %d, Energie %d) | Alerte : OFF", 
                                    compt, event->nom, event->pollution, event->ressource, event->energie);
    }

    // Label de bienvenue
    
    GtkWidget *label_welcome = gtk_label_new(label_wel);
    gtk_box_pack_start(GTK_BOX(vbox), label_welcome, TRUE, TRUE, 0);
    // Libérer la mémoire allouée pour la chaîne formatée
    g_free(label_wel);

    // Label d'état
    GtkWidget *label_status = gtk_label_new("Bienvenue sur le jeu tour à tour !");
    gtk_box_pack_start(GTK_BOX(vbox), label_status, TRUE, TRUE, 0);

    // Utiliser g_strdup_printf pour formater la chaîne avant de la passer à gtk_label_new
    char *label_text = g_strdup_printf("État de la planète %s : Pollution %d, Ressource %d, Energie %d", 
                                    p->nom, p->niveauPollution, p->niveauRessource, p->niveauEnergie);
    // Label pour afficher l'état de la planete
    GtkWidget *label_state = gtk_label_new(label_text);
    gtk_box_pack_start(GTK_BOX(vbox), label_state, TRUE, TRUE, 0);
    // Libérer la mémoire allouée pour la chaîne formatée
    g_free(label_text);

    // Label pour afficher les informations
    GtkWidget *info_label = gtk_label_new("Passez la souris sur un bouton pour voir les détails.");
    gtk_fixed_put(GTK_FIXED(fixed), info_label, 410, 350); 

    // Conteneur horizontal pour les actions
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    // Créer un bouton pour chaque action
    Element *current = p->actions; // Liste des actions
    while (current != NULL) {
        GtkWidget *button = gtk_button_new_with_label(current->nom);

        // Préparer les données pour le callback
        ActionData *data = g_malloc(sizeof(ActionData));
    

        data->action = current;
        data->planete = p;
        data->label_status = label_status;
        data->label_state = label_state;


        // Connecter le bouton avec les données
        g_signal_connect_data(button, "clicked", G_CALLBACK(on_action_button_clicked), data,
                              NULL, 0);
         // Associer l'action au bouton avec g_object_set_data
        g_object_set_data(G_OBJECT(button), "action_data", current);  // ici on associe l'action au bouton

        // Connecter les signaux pour survol et sortie de la souris
        g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), info_label);
        g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), info_label);

        // Ajouter le bouton au conteneur horizontal
        gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);

        current = current->suivant; // Passer à l'action suivante
    }

    // Préparer les données pour le callback
    TurnData *dataTurn = g_malloc(sizeof(TurnData));
    dataTurn->planete = p;
    dataTurn->compt = compt;
    dataTurn->tour = tours;
    dataTurn->label_status = label_status;
    dataTurn->strategieFonct = calc;
    dataTurn->label_welcome = label_welcome;
    dataTurn->label_planet = label_state;
    dataTurn->image = image;
    dataTurn->window = window;
    // Bouton pour finir le tour
    GtkWidget *button_end_turn = gtk_button_new_with_label("Fin du tour !");
    g_signal_connect(button_end_turn, "clicked", G_CALLBACK(on_end_turn_clicked), dataTurn); 
    gtk_box_pack_start(GTK_BOX(vbox), button_end_turn, TRUE, TRUE, 0);

    // Bouton pour revenir à l'interface JTT
    GtkWidget *button_back = gtk_button_new_with_label("Revenir vers le jeu tour à tour !");
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_buttonJTT_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button_back, TRUE, TRUE, 0);

    // Bouton pour revenir à l'interface JFA
    GtkWidget *button_back2 = gtk_button_new_with_label("Revenir vers le jeu full automatique !");
    g_signal_connect(button_back2, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_box_pack_start(GTK_BOX(vbox), button_back2, TRUE, TRUE, 0);

    // Afficher l'interface
    gtk_widget_show_all(window);
}

















// PARTIE JFA /////////////////////////////////////////////

/**
 * @brief  Fonction pour créer l'Interface JFA dans la même fenêtre
 * 
 * @param window pour fenetre
 * 
 */
void create_interfaceJFA(GtkWidget *window) {
    GtkWidget *fixed;  // Pour superposer les widgets
    GtkWidget *image;    // Image de fond
    GtkWidget *label;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button_back;

    // Supprimer tous les widgets de la fenêtre
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for (GList *child = children; child != NULL; child = child->next) {
        gtk_widget_destroy(GTK_WIDGET(child->data));
    }
    g_list_free(children);


    // Conteneur fixe pour positionner les widgets
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Ajouter l'image de fond
    image = gtk_image_new_from_file("./image/planet.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);

    // Label
    label = gtk_label_new("Bienvenue sur le jeu full automatique crée par vous !\n Choisissez la stratégie pour le calcul du score :");
    gtk_fixed_put(GTK_FIXED(fixed), label, 425, 250); 

    // Bouton Strat1
    button1 = gtk_button_new_with_label("Normal");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_buttonJFAStrat1_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 400, 300); 

    // Bouton Strat2
    button2 = gtk_button_new_with_label("Sauver la prochaine génération");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_buttonJFAStrat2_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 550, 300); 

    // Bouton pour revenir à l'interface JTT
    button_back = gtk_button_new_with_label("Revenir vers le jeu tour à tour !");
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_buttonJTT_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button_back, 410, 350); 

    // Afficher l'interface
    gtk_widget_show_all(window);
}

/**
 * @brief Fonction pour créer l'Interface JFA avec Strategie qui saisie vos demandes
 * 
 * @param window pour fenetre
 * @param Strategie pour transfert
 */
void create_interfaceJFAStrat(GtkWidget *window, Strategie calc) {
    // Créer une planète avec des valeurs initiales
    Planete *p = creationPlanete("Terre", 0, 70, 60);

    // Supprimer tous les widgets existants dans la fenêtre
    if (GTK_IS_CONTAINER(window)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(window));
        for (GList *child = children; child != NULL; child = child->next) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
        g_list_free(children);
    }
    
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button_back;
    DemandData *dataDemand = (DemandData *)malloc(sizeof(DemandData));
    dataDemand->planete = p;
    dataDemand->strategieFonct = calc;
    dataDemand->window = window;

    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    GtkWidget *image = gtk_image_new_from_file("./image/planet.png");
    gtk_fixed_put(GTK_FIXED(fixed), image, 0, 0);


    // Label de bienvenue    
    GtkWidget *label_welcome = gtk_label_new("Saisir les informations ceux dessous");
    gtk_fixed_put(GTK_FIXED(fixed), label_welcome, 500, 15); 
    dataDemand->label_welcome = label_welcome;

    // Label pour afficher les informations
    GtkWidget *info_label = gtk_label_new("Passez la souris sur un bouton pour voir les détails.");
    gtk_fixed_put(GTK_FIXED(fixed), info_label, 420, 150); 
    dataDemand->info_label = info_label;

    // Utiliser g_strdup_printf pour formater la chaîne avant de la passer à gtk_label_new
    char *label_text = g_strdup_printf("État intial de la planète %s : Pollution %d, Ressource %d, Energie %d", 
                                    p->nom, p->niveauPollution, p->niveauRessource, p->niveauEnergie);
    // Label pour afficher l'état de la planete
    GtkWidget *label_state = gtk_label_new(label_text);
    gtk_fixed_put(GTK_FIXED(fixed), label_state, 400, 55); 
    // Libérer la mémoire allouée pour la chaîne formatée
    g_free(label_text);

    
    ////////////////// ACTION /////////////////

    // Créer les étiquettes
    GtkWidget *label_nomAction = gtk_label_new("Nom de l'action :");
    gtk_fixed_put(GTK_FIXED(fixed), label_nomAction, 10, 200);
    
    GtkWidget *label_pollutionAction = gtk_label_new("Pollution (nombre) :");
    gtk_fixed_put(GTK_FIXED(fixed), label_pollutionAction, 10, 240);
    
    GtkWidget *label_ressourceAction = gtk_label_new("Ressource (nombre) :");
    gtk_fixed_put(GTK_FIXED(fixed), label_ressourceAction, 10, 280);
    
    GtkWidget *label_energieAction = gtk_label_new("Energie (nombre):");
    gtk_fixed_put(GTK_FIXED(fixed), label_energieAction, 10, 320);
    
    // Créer les champs de texte (Entry)
    GtkWidget *entry_nomAction = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_nomAction , 200, 200);
    dataDemand->entry_nomAction = entry_nomAction;
    
    GtkWidget *entry_pollutionAction = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_pollutionAction, 200, 240);
    dataDemand->entry_pollutionAction = entry_pollutionAction;
    
    GtkWidget *entry_ressourceAction = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_ressourceAction, 200, 280);
    dataDemand->entry_ressourceAction = entry_ressourceAction;
    
    GtkWidget *entry_energieAction = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_energieAction, 200, 320);
    dataDemand->entry_energieAction = entry_energieAction;

    /////////////// ACTION //////////////////////////


    /////////////// EVENT //////////////////////////

    // Créer les étiquettes
    GtkWidget *label_nomEvent = gtk_label_new("Nom de l'événement :");
    gtk_fixed_put(GTK_FIXED(fixed), label_nomEvent, 810, 200);
    
    GtkWidget *label_pollutionEvent = gtk_label_new("Pollution (nombre) :");
    gtk_fixed_put(GTK_FIXED(fixed), label_pollutionEvent, 810, 240);
    
    GtkWidget *label_ressourceEvent = gtk_label_new("Ressource (nombre) :");
    gtk_fixed_put(GTK_FIXED(fixed), label_ressourceEvent, 810, 280);
    
    GtkWidget *label_energieEvent = gtk_label_new("Energie (nombre):");
    gtk_fixed_put(GTK_FIXED(fixed), label_energieEvent, 810, 320);
    
    // Créer les champs de texte (Entry)
    GtkWidget *entry_nomEvent = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_nomEvent , 1000, 200);
    dataDemand->entry_nomEvent = entry_nomEvent;
    
    GtkWidget *entry_pollutionEvent = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed),entry_pollutionEvent, 1000, 240);
    dataDemand->entry_pollutionEvent = entry_pollutionEvent;
    
    GtkWidget *entry_ressourceEvent = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_ressourceEvent, 1000, 280);
    dataDemand->entry_ressourceEvent = entry_ressourceEvent;
    
    GtkWidget *entry_energieEvent = gtk_entry_new();
    gtk_fixed_put(GTK_FIXED(fixed), entry_energieEvent, 1000, 320);
    dataDemand->entry_energieEvent = entry_energieEvent;

    /////////////// EVENT //////////////////////////

    // Label pour Conteneur horizontal pour les actions
    GtkWidget *label_listeAction = gtk_label_new("Liste des actions :");
    gtk_fixed_put(GTK_FIXED(fixed), label_listeAction, 10, 550);

    // Conteneur horizontal pour les actions
    GtkWidget *hboxAction = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), hboxAction, 10, 590);
    dataDemand->hboxAction = hboxAction;
    
    // Label pour Conteneur horizontal pour les événements
    GtkWidget *label_listeEvent = gtk_label_new("Liste des événements :");
    gtk_fixed_put(GTK_FIXED(fixed), label_listeEvent, 10, 640);

    // Conteneur horizontal pour les événements
    GtkWidget *hboxEvent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), hboxEvent, 10, 680);
    dataDemand->hboxEvent = hboxEvent;

    // Créer un bouton pour chaque action
    Element *current = p->actions; // Liste des actions
    while (current != NULL) {
        GtkWidget *button = gtk_button_new_with_label(current->nom);

         // Associer l'action au bouton avec g_object_set_data
        g_object_set_data(G_OBJECT(button), "action_data", current);  // ici on associe l'action au bouton

        // Connecter les signaux pour survol et sortie de la souris
        g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), info_label);
        g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), info_label);

        // Ajouter le bouton au conteneur horizontal
        gtk_box_pack_start(GTK_BOX(hboxAction), button, TRUE, TRUE, 0);

        current = current->suivant; // Passer à l'action suivante
    }

    // Créer un bouton pour chaque événements
    Element *current2 = p->evenements; // Liste des événements
    while (current2 != NULL) {
        GtkWidget *button = gtk_button_new_with_label(current2->nom);

        // Associer l'événement au bouton avec g_object_set_data
        g_object_set_data(G_OBJECT(button), "event_data", current2); // Associer les données de l'événement

        // Connecter les signaux pour survol et sortie de la souris
        g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), info_label);
        g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), info_label);

        // Ajouter le bouton au conteneur horizontal
        gtk_box_pack_start(GTK_BOX(hboxEvent), button, TRUE, TRUE, 0);

        current2 = current2->suivant; // Passer à l'événement suivant
    }

    // Bouton Confirmer
    button1 = gtk_button_new_with_label("Confirmer vos saisies !");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_demand_button_clicked), dataDemand);
    gtk_fixed_put(GTK_FIXED(fixed), button1, 400, 400); 

    // Bouton Suivant
    button2 = gtk_button_new_with_label("Démarrer la partie !");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_next_button_clicked ), dataDemand);
    gtk_fixed_put(GTK_FIXED(fixed), button2, 700, 400); 

    // Bouton pour revenir à l'interface JFA
    button_back = gtk_button_new_with_label("Revenir !");
    g_signal_connect(button_back, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_fixed_put(GTK_FIXED(fixed), button_back, 600, 450); 

    // Afficher l'interface
    gtk_widget_show_all(window);
}

/**
 * @brief Fonction pour créer l'Interface JTT avec Strategie pour joueur full auto
 * 
 * @param window pour fenetre
 * @param Strategie pour transfert
 * @param Planete pour état
 */
void create_interfaceJFAStrat2(GtkWidget *window, Strategie calc, Planete *p) {
    // Supprimer tous les widgets existants dans la fenêtre
    if (GTK_IS_CONTAINER(window)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(window));
        for (GList *child = children; child != NULL; child = child->next) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
        g_list_free(children);
    }

    // Initialiser l'état du jeu
    GameState *state = g_new(GameState, 1);
    state->tours = 10;
    state->compt = 1;
    state->p = p;
    state->calc = calc;
    state->window = window;
    // Créez les widgets
    state->label_welcome = gtk_label_new("");
    state->label_state = gtk_label_new("");
    state->label_status = gtk_label_new("");
    state->info_label = gtk_label_new("");
    state->hboxAction = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    state->hboxEvent = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    state->image = gtk_image_new_from_file("./image/planet.png");
    GtkWidget *label_listeAction = gtk_label_new("Liste des actions :");
    GtkWidget *label_listeEvent = gtk_label_new("Liste des événements :");
    // Ajouter à la fenêtre
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);
    gtk_fixed_put(GTK_FIXED(fixed), state->image, 0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), state->label_welcome, 250, 50);
    gtk_fixed_put(GTK_FIXED(fixed), state->label_state, 250, 100);
    gtk_fixed_put(GTK_FIXED(fixed), state->label_status, 250, 150);
    gtk_fixed_put(GTK_FIXED(fixed), state->info_label, 250, 200);
    gtk_fixed_put(GTK_FIXED(fixed), state->hboxAction, 10, 590);
    gtk_fixed_put(GTK_FIXED(fixed), label_listeAction, 10, 550);
    gtk_fixed_put(GTK_FIXED(fixed), state->hboxEvent, 10, 680);
    gtk_fixed_put(GTK_FIXED(fixed), label_listeEvent, 10, 640);
    gtk_widget_show_all(window);

    // Démarrer la simulation avec un délai de 3 secondes
    g_timeout_add_seconds(3, (GSourceFunc)jouer_tour, state);

    
}
































////////////////
/// HOVER //////
////////////////
/**
 * @brief Fonction pour surfer sur les listes Element
 * 
 * @param widget 
 * @param event pour l'événement listener
 * @param data pour le stock de données
 */
void on_button_hover(GtkWidget *widget, GdkEventCrossing *event, gpointer data) {
    GtkWidget *info_label = (GtkWidget *)data;

    if (!GTK_IS_LABEL(info_label)) {
        g_warning("info_label n'est pas un label valide !");
        return;
    }

    // Vérifier le type de l'événement de souris
    if (event->type == GDK_ENTER_NOTIFY) {
        // Vérifier si le widget est lié à une action ou un événement
        Element *action = (Element *)g_object_get_data(G_OBJECT(widget), "action_data");
        Element *event_data = (Element *)g_object_get_data(G_OBJECT(widget), "event_data");

        if (action != NULL) {
            // Afficher les informations de l'action
            char info[256];
            snprintf(info, sizeof(info), "Action : %s\nPollution : %d\nRessource : %d\nEnergie : %d",
                     action->nom, action->pollution, action->ressource, action->energie);
            gtk_label_set_text(GTK_LABEL(info_label), info);
        } else if (event_data != NULL) {
            // Afficher les informations de l'événement
            char info[256];
            snprintf(info, sizeof(info), "Événement : %s\nPollution : %d\nRessource : %d\nEnergie : %d",
                     event_data->nom, event_data->pollution, event_data->ressource, event_data->energie);
            gtk_label_set_text(GTK_LABEL(info_label), info);
        } else {
            g_warning("Aucune action ou événement associé à ce bouton !");
        }
    } else if (event->type == GDK_LEAVE_NOTIFY) {
        // Effacer les informations lorsque la souris quitte le bouton
        gtk_label_set_text(GTK_LABEL(info_label), "");
    }
}



////////////////
/// Interface Victoire/Défaite
////////////////
/**
 * @brief Fonction pour créer l'Interface Défaite
 * 
 * @param window pour fenetre
 * @param Strategie pour transfert
 * @param Planete pour état
 */
void show_defeat_screen(GtkWidget *window, Strategie strat, Planete *p) {
    GtkWidget *vbox, *hbox, *button1, *button2, *label, *label_state;

    // Supprimer tous les widgets de la fenêtre en vérifiant leur validité
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for (GList *child = children; child != NULL; child = child->next) {
        if (GTK_IS_WIDGET(child->data)) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
    }
    g_list_free(children);

    // Conteneur fixe pour placer les éléments
    GtkWidget *fixed = gtk_fixed_new();
    if (p->niveauPollution>=100 && p->niveauRessource<=0){
        GtkWidget *image2 = gtk_image_new_from_file("./image/defeat.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), image2, 0, 0);
    } else if (p->niveauRessource<= 0){
        GtkWidget *image2 = gtk_image_new_from_file("./image/ressource.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), image2, 0, 0);
    } else {
        GtkWidget *image2 = gtk_image_new_from_file("./image/pollution.jpg");
        gtk_fixed_put(GTK_FIXED(fixed), image2, 0, 0);
    }


    // Conteneur vertical pour le contenu principal
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 350, 300);
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Ajouter un GIF (vérification si le fichier existe)
    if (g_file_test("./image/skeleton-berserk.gif", G_FILE_TEST_EXISTS)) {
        GtkWidget *image = gtk_image_new_from_file("./image/skeleton-berserk.gif");
        gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);
    } else {
        g_warning("Fichier ./image/skeleton-berserk.gif introuvable !");
    }

    // Ajouter un label avec le score
    int score = strat(p);
    score -= 50;
    char *label_text = g_strdup_printf("Défaite ! Votre score est : %d", score);
    label = gtk_label_new(label_text);
    g_free(label_text); // Libération après utilisation
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Ajouter un label avec l'état de la planète
    char *label_text2 = g_strdup_printf(
        "État de la planète %s : Pollution %d, Ressource %d, Energie %d",
        p->nom, p->niveauPollution, p->niveauRessource, p->niveauEnergie
    );
    label_state = gtk_label_new(label_text2);
    g_free(label_text2); // Libération après utilisation
    gtk_box_pack_start(GTK_BOX(vbox), label_state, TRUE, TRUE, 0);

    // Conteneur horizontal pour les boutons
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    // Bouton "Jeu tour à tour"
    button1 = gtk_button_new_with_label("Jeu tour à tour !");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_buttonJTT_clicked), window);
    gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);

    // Bouton "Jeu full automatique"
    button2 = gtk_button_new_with_label("Jeu full automatique !");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);

    // Afficher tous les widgets
    gtk_widget_show_all(window);
}

/**
 * @brief Fonction pour créer l'Interface Victoire
 * 
 * @param window pour fenetre
 * @param Strategie pour transfert
 * @param Planete pour état
 */
void show_victory_screen(GtkWidget *window, Strategie strat, Planete *p) {
    
    GtkWidget *vbox;
    GtkWidget *hbox;
    GtkWidget *button1, *button2, *label, *label_state;

    // Supprimer tous les widgets de la fenêtre
    GList *children = gtk_container_get_children(GTK_CONTAINER(window));
    for (GList *child = children; child != NULL; child = child->next) {
        gtk_widget_destroy(GTK_WIDGET(child->data));
    }
    g_list_free(children);


    GtkWidget *fixed = gtk_fixed_new();
    GtkWidget *image2 = gtk_image_new_from_file("./image/victory.jpg");
    gtk_fixed_put(GTK_FIXED(fixed), image2, 0, 0);

    // Conteneur vertical
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_fixed_put(GTK_FIXED(fixed), vbox, 350, 300);
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Ajouter un GIF
    GtkWidget *image = gtk_image_new_from_file("./image/spy-family-anya.gif");
    gtk_box_pack_start(GTK_BOX(vbox), image, TRUE, TRUE, 0);

    // Ajouter un label avec le score
    int score = strat(p);
    score += 50;
    char *label_text = g_strdup_printf("Victoire ! Votre score est : %d", score);
    label = gtk_label_new(label_text);
    g_free(label_text);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);

    // Ajouter un label avec l'état de la planète
    char *label_text2 = g_strdup_printf("État de la planète %s : Pollution %d, Ressource %d, Energie %d",
                                         p->nom, p->niveauPollution, p->niveauRessource, p->niveauEnergie);
    label_state = gtk_label_new(label_text2);
    g_free(label_text2);
    gtk_box_pack_start(GTK_BOX(vbox), label_state, TRUE, TRUE, 0);

    // Conteneur horizontal pour les boutons
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);

    // Boutons
    button1 = gtk_button_new_with_label("Jeu tour à tour !");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_buttonJTT_clicked), window);
    gtk_box_pack_start(GTK_BOX(hbox), button1, TRUE, TRUE, 0);

    button2 = gtk_button_new_with_label("Jeu full automatique !");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_buttonJFA_clicked), window);
    gtk_box_pack_start(GTK_BOX(hbox), button2, TRUE, TRUE, 0);

    // Afficher l'interface
    gtk_widget_show_all(window);
}


// Fonction pour charger le CSS
/**
 * @brief Fonction pour charger le CSS
 * 
 * @param css_file la redirection vers le fichier .css
 */
void load_css(const char *css_file) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GError *error = NULL;
    gtk_css_provider_load_from_path(provider, css_file, &error);
    if (error) {
        g_warning("Erreur lors du chargement du fichier CSS : %s", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}


/**
 * @brief Fonction pour vérifier si une chaîne de caractères peut être convertie en entier valide
 * 
 * @param str une chaine de saisie
 */
int is_valid_integer(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return (*endptr == '\0'); // Retourne 1 si c'est un entier valide, sinon 0
}

/**
 * @brief Fonction pour appel à jouer un tour automatiquement
 * 
 * @param state pour données
 */
gboolean jouer_tour(GameState *state) {
    if (state->compt > state->tours) {
        // Fin du jeu
        show_victory_screen(state->window, state->calc, state->p); // Exemple
        return FALSE; // Arrêter les appels
    }

    if (verifierPlanete(state->p)) {
        show_defeat_screen(state->window, state->calc, state->p); // Exemple
        return FALSE; // Arrêter les appels
    }
    // Simuler un événement
    Element *event = selectionnerElementAleatoire(state->p->evenements);
    state->p->niveauPollution += event->pollution;
    state->p->niveauRessource += event->ressource;
    state->p->niveauEnergie += event->energie;


    
    if (verifierPlanete(state->p)){
        if (state->p->niveauPollution >= 100 && state->p->niveauRessource <= 0){
            gtk_image_set_from_file(GTK_IMAGE(state->image), "./image/defeat.jpg");
        } else if (state->p->niveauRessource <= 0){
            gtk_image_set_from_file(GTK_IMAGE(state->image), "./image/ressource.jpg");
        } else {
            gtk_image_set_from_file(GTK_IMAGE(state->image), "./image/pollution.jpg");
        }
    } else {
        gtk_image_set_from_file(GTK_IMAGE(state->image), "./image/planet.png");
    }

    state->p->niveauEnergie += 40;
    char *label_text = g_strdup_printf("Tour %d (+40 energie par tour): Événement %s (Pollution %d, Ressource %d, Énergie %d)",
                                       state->compt, event->nom, event->pollution, event->ressource, event->energie);
    gtk_label_set_text(GTK_LABEL(state->label_welcome), label_text);
    g_free(label_text);

    char *etat_planete = g_strdup_printf("Planète %s : Pollution %d, Ressource %d, Énergie %d",
                                         state->p->nom, state->p->niveauPollution, state->p->niveauRessource, state->p->niveauEnergie);
    gtk_label_set_text(GTK_LABEL(state->label_state), etat_planete);
    g_free(etat_planete);

    // Mise à jour des boutons d'actions et événements
    if (GTK_IS_CONTAINER(state->hboxAction)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(state->hboxAction));
        for (GList *child = children; child != NULL; child = child->next) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
        g_list_free(children);
    }
    if (GTK_IS_CONTAINER(state->hboxEvent)) {
        GList *children = gtk_container_get_children(GTK_CONTAINER(state->hboxEvent));
        for (GList *child = children; child != NULL; child = child->next) {
            gtk_widget_destroy(GTK_WIDGET(child->data));
        }
        g_list_free(children);
    }
    // Créer un bouton pour chaque action
    Element *current = state->p->actions; // Liste des actions
    while (current != NULL) {
        GtkWidget *button = gtk_button_new_with_label(current->nom);

         // Associer l'action au bouton avec g_object_set_data
        g_object_set_data(G_OBJECT(button), "action_data", current);  // ici on associe l'action au bouton

        // Connecter les signaux pour survol et sortie de la souris
        g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), state->info_label);
        g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), state->info_label);

        // Ajouter le bouton au conteneur horizontal
        gtk_box_pack_start(GTK_BOX(state->hboxAction), button, TRUE, TRUE, 0);

        current = current->suivant; // Passer à l'action suivante
    }

    // Créer un bouton pour chaque événements
    Element *current2 = state->p->evenements; // Liste des événements
    while (current2 != NULL) {
        GtkWidget *button = gtk_button_new_with_label(current2->nom);

        // Associer l'événement au bouton avec g_object_set_data
        g_object_set_data(G_OBJECT(button), "event_data", current2); // Associer les données de l'événement

        // Connecter les signaux pour survol et sortie de la souris
        g_signal_connect(button, "enter-notify-event", G_CALLBACK(on_button_hover), state->info_label);
        g_signal_connect(button, "leave-notify-event", G_CALLBACK(on_button_hover), state->info_label);

        // Ajouter le bouton au conteneur horizontal
        gtk_box_pack_start(GTK_BOX(state->hboxEvent), button, TRUE, TRUE, 0);

        current2 = current2->suivant; // Passer à l'événement suivant
    }

    gtk_widget_show_all(state->hboxAction);
    gtk_widget_show_all(state->hboxEvent);
    
    // Démarrer le second timer pour les actions automatiques
    g_timeout_add(500, (GSourceFunc)auto_random_action, state);
    state->compt++; // Passer au tour suivant

    return TRUE; // Continuer les appels
}

/**
 * @brief  Fonction de callback pour effectuer une action aléatoire 
 * 
 * @param state pour données
 */
gboolean auto_random_action(GameState *state) {

    char nomAction[50];
    strcpy(nomAction, selectionnerElementAleatoire(state->p->actions)->nom);
    // Vérifier si l'action existe dans la liste d'actions
    Element *actionChoisie = rechercherElementNom(state->p->actions, nomAction);
    if (actionChoisie) {
        // Vérifier si la planète a suffisamment d'énergie
        if (state->p->niveauEnergie < actionChoisie->energie) {
            return FALSE;
        } else {
            // Appliquer l'action à la planète
            state->p->niveauEnergie -= actionChoisie->energie; // Coût en énergie
            state->p->niveauRessource += actionChoisie->ressource; // Modifier selon l'action
            state->p->niveauPollution += actionChoisie->pollution; // Modifier selon l'action
            char *label_text2 = g_strdup_printf("Action %s effectuée! Énergie restante: %d",
                                            actionChoisie->nom, state->p->niveauEnergie);
            gtk_label_set_text(GTK_LABEL(state->label_status), label_text2);
            g_free(label_text2);
        }
    } 
    // Mettre à jour l'interface (par exemple, des labels GTK)
    char *label_text = g_strdup_printf("Planète %s : Pollution %d, Ressource %d, Énergie %d",
                                       state->p->nom, state->p->niveauPollution, state->p->niveauRessource, state->p->niveauEnergie);
    gtk_label_set_text(GTK_LABEL(state->label_state), label_text);
    g_free(label_text);

    return TRUE; // Continuer le timer pour la prochaine exécution
}