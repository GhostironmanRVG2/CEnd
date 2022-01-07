#include <gtk/gtk.h>
#include <string.h>
/**FUNCAO INPUT*/
FilterW(int argc, char** argv){
/**FUNCAO PARA VERIFICAR MATRICULA**/

/**FUNCAO PARA CRIAR ICON**/

GdkPixbuf *create_pixbuf(const gchar * filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {

      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}

/**INICIALIZAR WINDOW E OUTROS COMPONENTES*/
GtkWidget *windowInput;
GtkWidget *err;
GdkPixbuf *icon;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *hbox_input;
GdkColor color;
GtkWidget *title;
GtkWidget *button;
GtkWidget *input_widget;
GtkWidget *hbox_button;
char* m;
char matricula[20];
int i;
/**DIALOG WINDOW**/
void show_error() {

  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(windowInput),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Introduza uma matricula valida!");
  gtk_window_set_title(GTK_WINDOW(dialog), "Warning!");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}
/**FUNCAO PARA O BOTAO**/
void button_clicked(GtkWidget *widget, gpointer data) {
/**COLOCAR O INPUT DENTRO DA VARIAVEL MATRICULA**/

/**IR PARA OUTRA WINDOW && ENVIAR O INPUT DA MATRICULA COM O GTK_ENTRY_GET_TEXT**/
if(gtk_entry_get_text_length(input_widget)==8){
/**COLOCAR O INPUT DENTRO DE UM ARRAY DE CARACTERES**/
m=gtk_entry_get_text(input_widget);
strcpy(matricula,gtk_entry_get_text(input_widget));
/**FAZER VERIFICACAO DE MATRICULA**/
int isit=verifymatric(matricula);
if(isit){
/**CASO DE CERTO**/
gtk_widget_destroy(windowInput);
strcpy(m,matricula);
//CODIGO DE OK
i=1;
}else{
//CASO DE ERRO ENVIAR MATRICULA COM ERRO
show_error();
}
}else if(gtk_entry_get_text_length(input_widget)==0){

gtk_widget_destroy(windowInput);

}else{
//CASO DE ERRO ENVIAR MATRICULA COM ERRO
show_error();
}

}
GtkCssProvider *cssProvider = gtk_css_provider_new();
/**INICIALIZAR O PROGRAMA*/
gtk_init(&argc, &argv);
i=0;
/**LOAD DO CSS*/
gtk_css_provider_load_from_path(cssProvider, "common.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
/**CRIAR UMA WINDOW*/
windowInput = gtk_window_new(GTK_WINDOW_TOPLEVEL);
/**DIZER-LHE PARA FICAR NO MEIO*/
gtk_window_set_position(GTK_WINDOW(windowInput), GTK_WIN_POS_CENTER);
/**TAMANHO DA WINDOW*/
gtk_window_set_default_size(GTK_WINDOW(windowInput), 350, 350);
/**TITULO*/
gtk_window_set_title(GTK_WINDOW(windowInput), "KARGA");
/**ICON*/
icon = create_pixbuf("car.png");
gtk_window_set_icon(GTK_WINDOW(windowInput), icon);
/**BACKGROUND*/
color.red = 0xffff;
color.green = 0xFFA500;
color.blue = 0;
gtk_widget_modify_bg(windowInput, GTK_STATE_NORMAL, &color);
/**IMPEDIR USAR A MINIMIZACAO E MAXIMIZACAO**/
gtk_window_set_type_hint(windowInput,GDK_WINDOW_TYPE_HINT_MENU);
/**CRIAR UM VBOX**/
vbox= gtk_vbox_new(TRUE,0);
gtk_container_add(GTK_CONTAINER(windowInput), vbox);
/**CRIAR UMA HBOX**/
hbox=gtk_hbox_new(TRUE,1);
/**INSERIR A HBOX NO VBOX**/
gtk_box_pack_start(GTK_BOX(vbox),hbox, TRUE, TRUE, 0);
/**CRIAR LABEL PARA O TITULO**/
title=gtk_label_new("INTRODUZA A MATRICULA");
gtk_widget_set_name(title,"title");
gtk_box_pack_start(GTK_BOX(hbox),title,TRUE,TRUE,0);




/**CRIAR UMA HBOX PARA LABEL E INPUT**/
hbox_input= gtk_hbox_new(TRUE,1);
/**INSERIR A HBOXINPUT NO VBOX**/
gtk_box_pack_start(GTK_BOX(vbox),hbox_input,FALSE,FALSE,0);
/**CRIAR INPUT**/
input_widget=gtk_entry_new();
/**COLOCA-LO NA SEGUNDA BOX**/
gtk_box_pack_start(GTK_BOX(hbox_input),input_widget,FALSE,FALSE,0);






/**CRIAR UMA HBOX PARA O BOTAO**/
hbox_button=gtk_hbox_new(TRUE,0);
/**INSERIR A HBOX NO VBOX**/
gtk_box_pack_start(GTK_BOX(vbox),hbox_button,FALSE,FALSE,0);
/**CRIAR BUTTON**/
button=gtk_button_new_with_label("PROCURAR");
/**COLOCA-LO NA TERCEIRA BOX**/
gtk_box_pack_start(GTK_BOX(hbox_button),button,FALSE,FALSE,0);
/**ADICIONAR UM EVENTO ASSOCIADO AO BOTAO**/
g_signal_connect(G_OBJECT(button), "clicked",
      G_CALLBACK(button_clicked), NULL);

//CASO SEJA DESTRUIDA
g_signal_connect(windowInput, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);




/**MOSTRAR A WINDOW*/
gtk_widget_show_all(windowInput);
/**FECHAR O PROGRAMA*/
gtk_main();

}
