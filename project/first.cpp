#include <gtk/gtk.h>
#include <cstring>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <armadillo>
#include "threedtotwod.cpp"
#include "show_canvas.cpp"
#include <math.h>
#define PI 3.14159265
using namespace std;
string filename = "";
GtkWidget *entry_for_x, *entry_for_y, *entry_for_z, *scale_x, *scale_y, *scale_z;
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
                        cout<<"Input file selected is "<<filename<<endl;
                }
                else
                        g_print("You pressed Cancel\n");
                gtk_widget_destroy(dialog);
        }
}

static void button_clicked(GtkWidget *widget, gpointer data){
        double xdir = atof(gtk_entry_get_text(GTK_ENTRY(entry_for_x)));
        double ydir = atof(gtk_entry_get_text(GTK_ENTRY(entry_for_y)));
        double zdir = atof(gtk_entry_get_text(GTK_ENTRY(entry_for_z)));
        Triplet dir = {xdir, ydir, zdir};
        if (filename.compare("")!=0){
                Threedtotwod T;
                T.G = T.toGraph(filename);
                float x_angle = gtk_range_get_value(GTK_RANGE(scale_x));
                float y_angle = gtk_range_get_value(GTK_RANGE(scale_y));
                float z_angle = gtk_range_get_value(GTK_RANGE(scale_z));
                float sin_x = sin((x_angle*PI)/180);
                float cos_x = cos((x_angle*PI)/180);
                float sin_y = sin((y_angle*PI)/180);
                float cos_y = cos((y_angle*PI)/180);
                float sin_z = sin((z_angle*PI)/180);
                float cos_z = cos((z_angle*PI)/180);
                mat rot_x<<1<<0<<0<<endr<<0<<cos_x<<(-sin_x)<<endr<<0<<sin_x<<cos_x<<endr;
                mat rot_y<<cos_y<<0<<sin_y<<endr<<0<<1<<0<<endr<<(-sin_y)<<0<<cos_y<<endr;
                mat rot_z<<cos_z<<(-sin_z)<<0<<endr<<sin_z<<cos_z<<0<<endr<<0<<0<<1<<endr;
                mat final_rot = rot_z * rot_y * rot_x;
                std::vector<Triplet> rotated_vertices;
                for (int i = 0; i < T.G.vertices.size(); ++i)
                {
                        mat coordinates;
                        coordinates<<vertices[i].one<<endr<<vertices[i].two<<endr<<vertices[i].three<<endr;
                        mat rotated_y_x = final_rot * coordinates;
                        Triplet temp = {rotated_y_x(0,0), rotated_y_x(1,0), rotated_y_x(2,0)};
                        rotated_vertices.push_back(temp);
                }
                T.G.vertices = rotated_vertices;
                show_qt_projections(T, dir);

        }
        else {
                cout<<"Please select a file"<<endl;
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
        GtkWidget *hbox_slider_for_x, *hbox_slider_for_y, *hbox_slider_for_z;

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

        //button to submit these changes
        button = gtk_button_new_with_label("Make Projections");
        gtk_box_pack_start(GTK_BOX(vbox), button,1,1,10);
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);
        
        //signal for button select
        g_signal_connect(button, "clicked", G_CALLBACK(button_clicked), NULL);
        g_signal_connect(entry_for_z, "activate", G_CALLBACK(button_clicked), NULL);

        // 2d to 3d
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