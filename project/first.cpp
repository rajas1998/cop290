#include <gtk/gtk.h>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
string filename;
static void menu_response(GtkWidget* menu_item, gpointer window)
{
        if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)), "New") == 0)       // equal
        {
                GtkWidget *dialog;
                dialog = gtk_file_chooser_dialog_new("Chosse a file", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
                gtk_widget_show_all(dialog);
        //      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),"/");
                gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());
                gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
                if(resp == GTK_RESPONSE_OK){
                        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
                        cout<<filename<<endl;
                }
                else
                        g_print("You pressed Cancel\n");
                gtk_widget_destroy(dialog);
        }
}
 
int main(int argc, char* argv[])
{
        gtk_init(&argc, &argv);
        GtkWidget *window, *menu_bar, *menu_item, *file_menu, *help_menu, *vbox, *button, *label, *label2, *notebook;
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
 
        // The menu bar is created 
        menu_bar = gtk_menu_bar_new();
 
        file_menu = gtk_menu_new();
 
        menu_item = gtk_menu_item_new_with_label("File");
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
 
        menu_item = gtk_menu_item_new_with_label("New");
        gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
        g_signal_connect(menu_item, "activate", G_CALLBACK(menu_response), NULL);
 

        // Notebook for 2D to 3D or 3D to 2D
        notebook = gtk_notebook_new();
        gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);


        // 3D to 2D tab
        GtkWidget *direction_label, *x_label, *y_label, *z_label, *hbox_for_x, *hbox_for_y, *hbox_for_z;
        GtkWidget *entry_for_x, *entry_for_y, *entry_for_z;
        label = gtk_label_new("3D to 2D");
        vbox = gtk_vbox_new(0,10);
        gtk_box_pack_start(GTK_BOX(vbox), menu_bar,0,0,0);

        // Heading for direction
        direction_label = gtk_label_new("Enter the viewing direction");
        gtk_box_pack_start(GTK_BOX(vbox), direction_label,0,0,0);

        // x part written
        x_label = gtk_label_new("Enter x-component");
        entry_for_x = gtk_entry_new();
        hbox_for_x = gtk_hbox_new(0,10);
        gtk_box_pack_start(GTK_BOX(hbox_for_x), x_label, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(hbox_for_x), entry_for_x, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_for_x,0,0,10);

        // y part written
        y_label = gtk_label_new("Enter y-component");
        entry_for_y = gtk_entry_new();
        hbox_for_y = gtk_hbox_new(0,10);
        gtk_box_pack_start(GTK_BOX(hbox_for_y), y_label, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(hbox_for_y), entry_for_y, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_for_y,0,0,10);

        // z part written
        z_label = gtk_label_new("Enter z-component");
        entry_for_z = gtk_entry_new();
        hbox_for_z = gtk_hbox_new(0,10);
        gtk_box_pack_start(GTK_BOX(hbox_for_z), z_label, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(hbox_for_z), entry_for_z, 0, 0, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_for_z,0,0,10);

        //sliders declared
        GtkWidget *slider_label_x, *slider_label_y, *slider_label_z;
        GtkWidget *scale_x, *scale_y, *scale_z, *hbox_slider_for_x, *hbox_slider_for_y, *hbox_slider_for_z;

        // x slider
        slider_label_x = gtk_label_new("Enter angle to be rotated by with x-axis");
        scale_x = gtk_hscale_new_with_range(0,180,5);
        gtk_scale_set_value_pos(GTK_SCALE(scale_x),GTK_POS_BOTTOM);
        hbox_slider_for_x = gtk_hbox_new(1,10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_x), slider_label_x, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_x), scale_x, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_slider_for_x,1,1,10);

        // y slider
        slider_label_y = gtk_label_new("Enter angle to be rotated by with y-axis");
        scale_y = gtk_hscale_new_with_range(0,180,5);
        gtk_scale_set_value_pos(GTK_SCALE(scale_y),GTK_POS_BOTTOM);
        hbox_slider_for_y = gtk_hbox_new(1,10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_y), slider_label_y, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_y), scale_y, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_slider_for_y,1,1,10);

        //z slider
        slider_label_z = gtk_label_new("Enter angle to be rotated by with x-axis");
        scale_z = gtk_hscale_new_with_range(0,180,5);
        gtk_scale_set_value_pos(GTK_SCALE(scale_z),GTK_POS_BOTTOM);
        hbox_slider_for_z = gtk_hbox_new(1,10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_z), slider_label_z, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(hbox_slider_for_z), scale_z, 1, 1, 10);
        gtk_box_pack_start(GTK_BOX(vbox), hbox_slider_for_z,1,1,10);

        //button = gtk_button_new_with_label("This is a Button dh28ec c8uehd2ujhdxionc juu");
        //gtk_box_pack_start(GTK_BOX(vbox), button,0,0,0);
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);
        button = gtk_button_new_with_label("This is a Button");
        label = gtk_label_new("Hi 2");
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), button, label);


        // Main container added to the window
        gtk_container_add(GTK_CONTAINER(window), notebook);

        // Setting the window title
        gtk_window_set_title(GTK_WINDOW(window),"ED Package");
        gtk_widget_show_all(window);
        gtk_main();
        return 0;
}