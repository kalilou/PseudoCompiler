#include "interface.h"
  GtkWidget *fenetre;



// Fonction de destruction de la fenetre de demarrage
void Destruction_fenetre_demarrage( void )
{
    if ( timer )
    g_source_remove ( timer );
	gtk_main_quit();
}

//Fenetre qui affiche l'ecran de demarrage
void fenetre_ecran_demarrage( void )
{
    // Déclaration des variable
    GtkWidget *f_demarrage;
	GtkWidget *v_box;
	GtkWidget *image;

    // Creation de la fenetre de demarrage
	f_demarrage = gtk_window_new( GTK_WINDOW_POPUP );
	gtk_window_set_position( GTK_WINDOW( f_demarrage ), GTK_WIN_POS_CENTER );
	gtk_window_set_default_size( GTK_WINDOW( f_demarrage ), 150,150 );
	gtk_window_set_title( GTK_WINDOW( f_demarrage ), "VOICE COMPILATION" );

    // Creation d'un conteneur
	v_box = gtk_vbox_new( FALSE, 0 );
	gtk_container_add( GTK_CONTAINER( f_demarrage ), v_box );

	// Chargement de l'image
	image = gtk_image_new_from_file( "a.png" );
	gtk_box_pack_start( GTK_BOX( v_box ), image, FALSE, FALSE, 5 );

    // Affichage de la fenetre
	gtk_widget_show_all( f_demarrage );

	// Initialisation du timer
    timer = g_timeout_add( 2500, ( GSourceFunc )Destruction_fenetre_demarrage, NULL );

    // Lancement de la boucle événementielle
	gtk_main();

	// Destruction de la fenetre
    gtk_widget_destroy( f_demarrage );

}



GtkWidget * menu(void)
{
    GtkWidget *pVBox;
    GtkWidget *pMenuBar;
    GtkWidget *pMenu;
    GtkWidget *pMenuItem;

    /* Creation de la GtkVBox */
    pVBox = gtk_vbox_new(FALSE, 0);
   // gtk_container_add(GTK_CONTAINER(fenetre), pVBox);


/**** Creation du menu ****/
/* ETAPE 1 */
pMenuBar = gtk_menu_bar_new();




/** Premier sous menu   fichier**/
pMenu = gtk_menu_new();
pMenuItem = gtk_menu_item_new_with_label("ouvrir");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL), NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("changer mot de passe" );
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL), fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("changer Identifiant" );
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL), fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Quitter");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter), (GtkWidget *)fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("fichier");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);
/* ETAPE 2 */

/** Deuxieme sous menu   employe**/
pMenu = gtk_menu_new();
/* ETAPE 3 */
pMenuItem = gtk_menu_item_new_with_label("Nouveau");
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
pMenuItem = gtk_menu_item_new_with_label("Afficher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Rechercher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Supprimer");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
//le menu employe qui va contenir les autres definis ci dessus
pMenuItem = gtk_menu_item_new_with_label("Employe");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu); //ajout a la barre de menu
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

/** Troixieme sous menu   Administrateur**/
pMenu = gtk_menu_new();

pMenuItem = gtk_menu_item_new_with_label("Nouveau");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Afficher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Rechercher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Supprimer");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Administration");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);


/** Quatrieme sous menu   seance**/
pMenu = gtk_menu_new();
pMenuItem = gtk_menu_item_new_with_label("Nouveau");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Afficher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL), fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Modifier");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL), fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Rechercher par jour");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Supprimer");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Seance");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

/** Cinquieme sous menu   Film**/
pMenu = gtk_menu_new();
pMenuItem = gtk_menu_item_new_with_label("Nouveau");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Afficher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Rechercher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Supprimer");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Film");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

/** Sixieme sous menu   salle**/
pMenu = gtk_menu_new();
pMenuItem = gtk_menu_item_new_with_label("Nouveau");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Afficher");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Supprimer");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),NULL);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("Salle");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

/** Septieme sous menu  a propos **/
pMenu = gtk_menu_new();
pMenuItem = gtk_menu_item_new_with_label("Auteur");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK( OnAbout),(GtkWidget *) fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("aide");
g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(NULL),(GtkWidget *) fenetre);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
pMenuItem = gtk_menu_item_new_with_label("A propos");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);


/* Ajout du menu a la fenetre */
gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
return pVBox;
}



void OnQuitter(GtkWidget* widget, gpointer data)
{

GtkWidget *pQuestion;
pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
GTK_DIALOG_MODAL,
GTK_MESSAGE_QUESTION,
GTK_BUTTONS_YES_NO,
"Voulez vous vraiment\n"
"quitter le programme?");
switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
{
case GTK_RESPONSE_YES:
gtk_main_quit();
break;
case GTK_RESPONSE_NONE:
case GTK_RESPONSE_NO:
gtk_widget_destroy(pQuestion);
break;
}
}


void OnAbout(GtkWidget* widget, gpointer data)
{
GtkWidget *pAbout;
pAbout = gtk_message_dialog_new (GTK_WINDOW(data),
GTK_DIALOG_MODAL,
GTK_MESSAGE_INFO,
GTK_BUTTONS_OK,
"Realiser par\n"
"Diaby Kalilou\n"
"Congo faical Yannick Palingwende\n");
gtk_dialog_run(GTK_DIALOG(pAbout));
gtk_widget_destroy(pAbout);
}




void manipulation(void)
{
    GtkWidget *icone = gtk_image_new_from_file( "a.png" );
    GtkWidget *table;
    GtkWidget *image;
    GtkWidget *image1;
      // Configuration aspect graphique de l'interface par un Gtkrc
        gtk_rc_parse("2.rc");

    //GtkWidget  *pImage;
    fenetre_ecran_demarrage();
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(fenetre), 0);
    gtk_window_set_title(GTK_WINDOW(fenetre),"VOICE COMPILATION");
    gtk_window_set_position(GTK_WINDOW(fenetre),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(fenetre),520,300);
    gtk_window_set_resizable(GTK_WINDOW(fenetre),TRUE);
    gtk_window_set_icon( GTK_WINDOW( fenetre ), gtk_image_get_pixbuf( GTK_IMAGE( icone ) ) );
    table = gtk_table_new(5,5,FALSE);
    image = gtk_image_new_from_file("1.png");
    image1 = gtk_image_new_from_file("0.png");
    gtk_table_attach(GTK_TABLE(table),menu(),0,2,0,2,GTK_FILL | GTK_SHRINK,GTK_FILL | GTK_SHRINK,0,0);
   gtk_table_attach(GTK_TABLE(table),image ,2,5,0,5,GTK_FILL | GTK_SHRINK,GTK_FILL | GTK_SHRINK,0,0);
   gtk_table_attach(GTK_TABLE(table),image1 ,0,2,2,5,GTK_FILL | GTK_SHRINK,GTK_FILL | GTK_SHRINK,0,0);
    gtk_container_add(GTK_CONTAINER(fenetre),table);
    gtk_widget_show_all(fenetre);

   //test_motpasse();
    gtk_main();
   // enregistrement_entiere();
}

