#include <gtk/gtk.h>
#include "select_day.h"
#include "postgres.h"


void add_page_todays_date(GtkNotebook *mainNb)
{
	GtkBox *pageBox = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
	GtkWidget *label;
	char ***data = get_data("_2019_7_9");

	int rows = get_rows(NULL, "_2019_7_9");

	for (int i = 0; i < rows; ++i){
		label = gtk_label_new(data[i][0]);
		gtk_box_pack_start(pageBox, label, FALSE, FALSE, 2);
	}

	gtk_notebook_append_page(mainNb, GTK_WIDGET(pageBox), gtk_label_new("_2019_7_9"));
}


GtkNotebook *create_notebook(GtkBuilder *builder)
{
	GtkNotebook *mainNb = GTK_NOTEBOOK(gtk_notebook_new());
	gtk_notebook_set_scrollable(mainNb, TRUE);
	
	GtkBox *mainBox = GTK_BOX(gtk_builder_get_object(builder, "main_box"));
	gtk_box_pack_start(mainBox, GTK_WIDGET(mainNb), FALSE, FALSE, 0);

	add_page_todays_date(mainNb);

	return mainNb;
}


GtkWindow *create_app(GtkWindow *window)
{
	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "src/glade/tiny-todo.glade", NULL);
	gtk_builder_connect_signals(builder, NULL);	

	window = GTK_WINDOW(gtk_builder_get_object(builder, "main_window"));
	gtk_window_set_title(window, "tiny-todo");

	create_notebook(builder);

	g_object_unref(builder);

	return window;
}


int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	GtkWindow *window = NULL;
	window = create_app(window);
	
	gtk_widget_show_all(GTK_WIDGET(window));                
	gtk_main();

	return 0;
}