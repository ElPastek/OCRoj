/* Headers */
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include <unistd.h>
# include <gtk/gtk.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "open_image.h"
# include "pixel_operations.h"
# include "grey_level.h"
# include "black_and_white.h"
# include "segment.h"
//


char* file_chooser_create()
{
		GtkBuilder *builder;
		GtkWidget *window;
		GtkWidget *dialog;
		builder = gtk_builder_new();
		window = GTK_WIDGET(gtk_builder_get_object(builder, "window_folder"));
		dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(window),
		GTK_FILE_CHOOSER_ACTION_OPEN,
		GTK_STOCK_OK, GTK_RESPONSE_OK,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
		gtk_widget_show_all(dialog);
		gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
		gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
    char *str = malloc(100*sizeof(char));
		if(resp == GTK_RESPONSE_OK)
    {
			strcpy(str, (const char*)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    }
    gtk_widget_destroy(dialog);
    return str;
}

void on_Commencer_clicked()
{
<<<<<<< HEAD
	if(argc < 2)
		errx(1, "Please enter an image path.");
  init_sdl();
  SDL_Surface *image = load_image(argv[1]);
  //display_image(image);
  To_GreyLevel(image);
  //display_image(image);
  To_Black_And_White(image);
  //To_Black_On_White(image);
  //display_image(image);
  MakingBlocks(image);
  //display_image(image);
	intoMatrices(image);
  //display_image(image);
  SDL_FreeSurface(image);
  return 0;
=======
  char *file = (char*)file_chooser_create();
  SDL_Surface *image = load_image(file);
  To_GreyLevel(image);
  To_Black_And_White(image);
  MakingBlocks(image);
	printf("yolo");
}

void on_RDN_clicked()
{
	char* arg[] = {"1"};
	assert(execv("/home/thomas/OCRoj/RDN/Creation/RDN_main_2", arg));
	assert(execv("/home/thomas/OCRoj/RDN/Creation/lecture", arg));
}

/*void on_FileName_activate_current_link()
{
  GtkWidget *filename_label;
  GtkBuilder *builder;
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "ocr.glade", NULL);
  gtk_builder_connect_signals(builder, NULL);
  filename_label = GTK_WIDGET(gtk_builder_get_object(builder, "FileName"));
  gtk_label_set_text(GTK_LABEL(filename_label), on_ouvrir_activate());
}*/

// called when window is closed
void on_ocr_destroy()
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "ocr.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "ocr"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window);
		gtk_main();

    return 0;
>>>>>>> 1a863c3cc9f221a1816b30444f70ae8382ac1a9d
}
