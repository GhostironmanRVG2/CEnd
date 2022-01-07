#include <gtk/gtk.h>

enum {

  LIST_ITEM = 0,
  N_COLUMNS
};

void init_list(GtkWidget *list) {

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("List Items",
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list),
      GTK_TREE_MODEL(store));

  g_object_unref(store);
}

void add_to_list(GtkWidget *list, const gchar *str) {

  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

void on_changed(GtkWidget *widget, gpointer label) {

  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *value;

  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    gtk_label_set_text(GTK_LABEL(label), value);
    g_free(value);
  }
}

int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget **hbox_array;
  GtkWidget *vbox;
  GtkWidget *button;


 void button_clicked(GtkWidget *widget, gpointer data) {
  gtk_widget_destroy(hbox_array[0]);
  g_print("%d",sizeof(hbox_array));
}
  gtk_init(&argc, &argv);

     /**ARRAY DINAMICO DE HBOX**/
    hbox_array = (GtkWidget **) malloc(sizeof(GtkWidget*) * 6);

  hbox_array[0]=gtk_button_new_with_label("hello");
  hbox_array[1]=gtk_button_new_with_label("hello");
  hbox_array[2]=gtk_button_new_with_label("hello");
  hbox_array[3]=gtk_button_new_with_label("hello");
  hbox_array[4]=gtk_button_new_with_label("hello");


  vbox= gtk_vbox_new(FALSE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox_array[0],TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox_array[1],TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox_array[2],TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox_array[3],TRUE,TRUE,1);
  gtk_box_pack_start(GTK_BOX(vbox),hbox_array[4],TRUE,TRUE,1);
  button= gtk_button_new_with_label("AQUI SOME");
  gtk_box_pack_start(GTK_BOX(vbox),button,TRUE,TRUE,1);

  g_signal_connect(G_OBJECT(button), "clicked",
      G_CALLBACK(button_clicked), NULL);



  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_add(GTK_CONTAINER(window),vbox);

  gtk_window_set_title(GTK_WINDOW(window), "List view");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
