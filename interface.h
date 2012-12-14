#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include<stdlib.h>
#include<gtk/gtk.h>
#include <glib/gprintf.h>

GtkWidget *fenetre;

// Un timer
int timer;



//void menu(void);

GtkWidget * menu(void);
// Boîte de dialogue erreur
void message_erreur( GtkWindow *fparent, char *format, ... );


// boîte de base pour les autres boîtes de dialogue
void afficher_message( GtkWindow *fparent, GtkMessageType type, GtkButtonsType button, char *titre, const gchar *format, va_list va );

void OnQuitter(GtkWidget* widget, gpointer data);

// Fonction de destruction de la fenetre de demarrage
void Destruction_fenetre_demarrage( void );

//Fenetre qui affiche l'ecran de demarrage
void fenetre_ecran_demarrage( void );

void OnAbout(GtkWidget* widget, gpointer data);


void manipulation(void);

void test_motpasse(void);
// Fenetre d'authentification
int Fenetre_Authentification( void );
    // Boîte de dialogue information
void message_info( GtkWindow *fparent, char *format, ... );


        // Fenetre de confirmation d'une action
int fenetre_confirmation( char *message );


// Fenetre de changement de password
void Fenetre_Changer_Password( void );



//image de la fenetre principale
void f_image(void);


void ouvrir_fichier(GtkWidget *pWidget, gpointer data);

#endif
