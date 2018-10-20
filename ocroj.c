# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>
# include <glib.h>
# include <SDL/SDL.h>
//# include <SDL2/SDL_image.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "TDI/pixel_operations.h"
# include "TDI/segment.h"
# include "TDI/grey_level.h"
# include "TDI/black_and_white.h"
# include "TDI/open_image.h"
# include "TDI/intomatrices.h"
# include "RDN/Lecture/lecture.c"

typedef struct
{
  GtkBuilder *builder;
  gpointer user_data;
}

SGlobalData;

GtkFileChooser *file_selector = NULL;
GtkBuilder *builder = NULL;
gchar *filepath = NULL;
GtkImage *image = NULL;
GtkWidget *fenetre_principale = NULL;
GtkWidget *button_commencer = NULL;
GtkWidget *button_recup = NULL;
GtkWidget *button_quit = NULL;
GtkWidget *button_quit2 = NULL;
GtkLabel *percent_label = NULL;
GtkWidget *fenetre_secondaire = NULL;

void fileselector_selection_changed()
{
  filepath = gtk_file_chooser_get_filename(file_selector);
  gtk_image_set_from_file(image, filepath);
  gtk_label_set_label(percent_label, "0 %");
}


char* output_to_string()
{
  FILE *ins     = fopen("RDN/Creation/inputs_RDN.txt", "r");
  size_t t[1] = {0};
  fscanf(ins, "%zu", &t[0]);
  fclose(ins);
  FILE *fichier = fopen("RDN/Creation/outputs_RDN.txt", "r");
  char *str = malloc(sizeof(char) * t[0]);
  for (size_t i = 0 ; i < t[0] ; i++)
    str[i] = fgetc(fichier);
  return str;
}

void on_Commencer_clicked()
{
  if (filepath != NULL)
  {
    SDL_Surface *img = load_image(filepath);
    To_GreyLevel(img);
    gtk_label_set_label(percent_label, "20 %");
    To_Black_And_White(img);
    gtk_label_set_label(percent_label, "40 %");
    MakingBlocks(img);
    gtk_image_set_from_file(image, "segmented_image");
    gtk_label_set_label(percent_label, "50 %");
    intoMatrices(img);
    gtk_label_set_label(percent_label, "60 %");
    load_RDN_from_path("RDN/Creation/saved_RDN_LBIW.txt");
    gtk_label_set_label(percent_label, "70  %");
    read_RDN("ocr");
    //gtk_label_set_label(percent_label, "91 %");
    //gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(fenetre_secondaire), output_to_string());    
    gtk_label_set_label(percent_label, "100 %");
  }
  else
  {
    printf("Aucune image choisie");
  }
}


void on_open_output_clicked()
{
  GtkWidget *fenetre_secondaire = gtk_message_dialog_new(
    NULL,
    GTK_DIALOG_MODAL,
    GTK_MESSAGE_OTHER,
    GTK_BUTTONS_CLOSE,
    output_to_string());
  //gtk_widget_show_all(fenetre_secondaire);
  gtk_dialog_run(GTK_DIALOG(fenetre_secondaire)); 
  gtk_widget_destroy(fenetre_secondaire);
}


void on_quit_clicked()
{
  gtk_main_quit();
}


void on_quit_output_clicked()
{
    
}

void callback_about(GtkMenuItem *menuitem,gpointer user_data);

int main(int argc, char *argv[])
{
  //GtkWidget *fenetre_principale = NULL; 
  GError *error = NULL;
  gchar *filename = NULL;

  gtk_init(&argc, &argv);

  builder =  gtk_builder_new();

  filename = g_build_filename("ocr.glade",NULL);

  gtk_builder_add_from_file (builder, filename,&error);
  g_free (filename);
  if (error)
  {
    gint code = error->code;
    g_printerr("%s\n", error->message);
    g_error_free (error);
    return code;
  }
  fenetre_principale = GTK_WIDGET(gtk_builder_get_object(builder,"ocr"));
  //fenetre_secondaire = GTK_WIDGET(gtk_builder_get_object(builder,"output_screen"));
  //on lie l'image à notre widget sur glade
  image = GTK_IMAGE(gtk_builder_get_object(builder,"chosen_image"));

  //on lie ouvrir au bouton
  file_selector = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "button_ouvrir"));
  g_signal_connect(G_OBJECT(file_selector), "selection_changed", G_CALLBACK(fileselector_selection_changed), file_selector);

  button_commencer = GTK_WIDGET(gtk_builder_get_object(builder,"Commencer"));
  g_signal_connect(G_OBJECT(button_commencer), "clicked", G_CALLBACK(on_Commencer_clicked), button_commencer);
  
  percent_label = GTK_LABEL(gtk_builder_get_object(builder, "label_percent"));

  button_recup = GTK_WIDGET(gtk_builder_get_object(builder, "open_output"));
  g_signal_connect(G_OBJECT(button_recup), "clicked", G_CALLBACK(on_open_output_clicked), button_recup);  

  button_quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
  g_signal_connect(G_OBJECT(button_quit), "clicked", G_CALLBACK(on_quit_clicked), button_quit);

  button_quit2 = GTK_WIDGET(gtk_builder_get_object(builder, "quit_output"));
  g_signal_connect(G_OBJECT(button_quit2), "clicked", G_CALLBACK(on_quit_output_clicked), button_quit2);

  g_object_unref(builder);
  gtk_widget_show_all(fenetre_principale);
  gtk_main();
  return 0;
}
