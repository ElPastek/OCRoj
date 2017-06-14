# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL2/SDL_image.h>
# include <err.h>
# include "pixel_operations.h"
# include "segment.h"
# include "grey_level.h"
# include "black_and_white.h"
# include "open_image.h"


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
GtkWidget *button_commencer = NULL;
GtkWidget *button_recup = NULL;
GtkWidget *button_quit = NULL;

void fileselector_selection_changed()
{
  filepath = gtk_file_chooser_get_filename(file_selector);
  gtk_image_set_from_file(image, filepath);
}

void on_Commencer_clicked()
{
  if (filepath != NULL)
  {
    SDL_Surface *img = load_image(filepath);
    To_GreyLevel(img);
    To_Black_And_White(img);
    MakingBlocks(img);
    gtk_image_set_from_file(image, "segmented_image");
  }
  else
  {
    printf("filepath NULL");
  }
}

void on_quit_clicked()
{
  gtk_main_quit();
}

void on_Recup_clicked()
{

}

void callback_about(GtkMenuItem *menuitem,gpointer user_data);

int main(int argc, char *argv[])
{
  GtkWidget *fenetre_principale = NULL;
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
  fenetre_principale = GTK_WIDGET(gtk_builder_get_object (builder,"ocr"));

  //on lie l'image à notre widget sur glade
  image = GTK_IMAGE(gtk_builder_get_object(builder,"chosen_image"));

  //on lie ouvrir au bouton
  file_selector = GTK_FILE_CHOOSER(gtk_builder_get_object(builder, "button_ouvrir"));
  g_signal_connect(G_OBJECT(file_selector), "selection_changed", G_CALLBACK(fileselector_selection_changed), file_selector);

  button_commencer = GTK_WIDGET(gtk_builder_get_object(builder,"Commencer"));
  g_signal_connect(G_OBJECT(button_commencer), "clicked", G_CALLBACK(on_Commencer_clicked), button_commencer);

  button_recup = GTK_WIDGET(gtk_builder_get_object(builder,"button_get_text"));
  g_signal_connect(G_OBJECT(button_recup), "clicked", G_CALLBACK(on_Recup_clicked), button_recup);
  g_signal_connect(G_OBJECT(fenetre_principale), "destroy", G_CALLBACK(gtk_main_quit), gtk_main_quit);

  button_quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
  g_signal_connect(G_OBJECT(button_quit), "clicked", G_CALLBACK(on_quit_clicked), button_quit);

  g_object_unref(builder);
  gtk_widget_show_all(fenetre_principale);
  gtk_main();
  return 0;
}
