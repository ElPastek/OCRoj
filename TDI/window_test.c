# include <gtk/gtk.h>
# include <stdlib.h>
# include <stdio.h>
# include <window_test.h>
# include <SDL/SDL.h>
# include "segment.h"
# include "grey_level.h"
# include "black_and_white.h"
# include "open_image.h"
# include "pixel_operations.h"

typedef struct {
  GtkBuilder *builder;
  gpointer user_data;
}

SGlobalData;

GtkFileChooser *file_selector = NULL;
GtkBuilder *builder = NULL;
gchar *filepath = NULL;
GtkImage *image = NULL;
GtkWidget *Ouvrir = NULL;
GtkEntry *champ_name = NULL;


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
  image = GTK_IMAGE(gtk_builder_get_object(builder,"logo"));
  button_commencer = GTK_WIDGET(gtk_builder_get_object(builder,"Commencer"));
  g_signal_connect(G_OBJECT(button_commencer), "clicked",
                  G_CALLBACK(on_Commencer_clicked));
  button_recup = GTK_WIDGET(gtk_builder_get_object(builder,"Récupérer le texte"));
  g_signal_connect(G_OBJECT(button_recup), "clicked",
                  G_CALLBACK(on_Recup_clicked));
  g_signal_connect(G_OBJECT(fenetre_principale), "destroy",
                  (GCallback)gtk_main_quit,NULL);



}


void on_Commencer_clicked()
{
  if (filepath != NULL)
  {
    SDL_Surface *img = LoadIMG(filepath);
    grey_level(img);
    black_and_white(img);
    MakingBlocks(img);
    gtk_image_set_from_file(image, "NewImg.bmp");
    else
    {
      printf("filepath NULL");
    }
  }
}

void on_Recup_clicked()
{

}
