#include <gtk/gtk.h>
 
static void button_clicked(GtkWidget* widget, gpointer data)
{
        gtk_label_set_text(GTK_LABEL(data), "you clicked the button");
}
 
int main(int argc, char* argv[])
{
        gtk_init(&argc, &argv);
        GtkWidget *window, *label, *button, *vbox;
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
 
        label = gtk_label_new("Hello World");
        button = gtk_button_new_with_label("Click me");
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), (gpointer)label);
        vbox = gtk_vbox_new(0, 0);
        gtk_box_pack_start(GTK_BOX(vbox), label, 1, 1, 0);
        gtk_box_pack_start(GTK_BOX(vbox), button, 1, 1, 0);
        gtk_container_add(GTK_CONTAINER(window), vbox);
        gtk_widget_show_all(window);
        gtk_main();
        return 0;
}