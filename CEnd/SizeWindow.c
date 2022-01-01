#include <gtk/gtk.h>
#include <string.h>

int * SizeWindow(int argc, char** argv, int* pp) {

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


    GtkWidget *windowSize;
    GtkWidget *botao_s;
    GtkWidget *fixed;
    GtkWidget *colunas;
    GtkWidget *pisos;
    GtkWidget *linhas;
    GtkWidget *titulo_s;
    GtkWidget *spin1;
    GtkWidget *spin2;
    GtkWidget *spin3;
    GtkAdjustment *adjustment1;
    GtkAdjustment *adjustment2;
    GtkAdjustment *adjustment3;
    GdkColor color;
    GdkPixbuf *icon;

    //FUNÇÃO PARA GUARDAR OS VALORES DO TAMANHO DO PARQUE
    void Button_Clicked (GtkWidget *widget, gpointer data){
        pp[0]=gtk_spin_button_get_value(spin1);
        pp[1]=gtk_spin_button_get_value(spin2);
        pp[2]=gtk_spin_button_get_value (spin3);

        gtk_widget_destroy(windowSize);
        return pp;

    }
/**COLOCAR O INPUT DENTRO DE UM ARRAY DE CARACTERES**/

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    //INICIALIZAR O PROGRAMA
    gtk_init(&argc, &argv);


    /**LOAD DO CSS*/
    gtk_css_provider_load_from_path(cssProvider, "size.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    //CRIAR UMA WINDOW
    windowSize = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //TITULO DA JANELA
    gtk_window_set_title(GTK_WINDOW(windowSize), "Tamanho do Paruqe");
    //TAMANHO DA JANELA
    gtk_window_set_default_size(GTK_WINDOW(windowSize), 350, 300);
    //DIZER PARA FICAR NO MEIO
    gtk_window_set_position(GTK_WINDOW(windowSize), GTK_WIN_POS_CENTER);
    //ICON
    icon = create_pixbuf("car.png");
    gtk_window_set_icon(GTK_WINDOW(windowSize), icon);


    //BACKGROUND
    color.red = 0xffff;
    color.green = 0xFFA500;
    color.blue = 0;
    gtk_widget_modify_bg(windowSize, GTK_STATE_NORMAL, &color);


    //IMPEDIR USAR A MINIMIZACAO E MAXIMIZACAO
    gtk_window_set_type_hint(windowSize,GDK_WINDOW_TYPE_HINT_MENU);


    //PONTO FIXO DAS COISAS
    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(windowSize), fixed);

    //BOTAO 1
    botao_s = gtk_button_new_with_label("CONFIRMAR");
    gtk_widget_set_name(botao_s, "botao_s");
    gtk_fixed_put(GTK_FIXED(fixed), botao_s, 110, 250);
    gtk_widget_set_size_request(botao_s, 80, 30);
    //GUARDAR OS VALORES REGISTADOS
    g_signal_connect(G_OBJECT(botao_s), "clicked",
            G_CALLBACK(Button_Clicked), (gpointer) windowSize);


    //LABLEL PISOS
    pisos = gtk_label_new("Introduza o n de pisos: ");
    gtk_widget_set_name(pisos, "pisos");
    gtk_fixed_put(GTK_FIXED(fixed), pisos, 20, 70);
    gtk_widget_set_size_request(pisos, 80, 30);


    //LABLEL LINHAS
    linhas = gtk_label_new("Introduza o n de linhas: ");
    gtk_widget_set_name(linhas, "linhas");
    gtk_fixed_put(GTK_FIXED(fixed), linhas, 20, 130);
    gtk_widget_set_size_request(linhas, 80, 30);


    //LABLEL COLUNAS
    colunas = gtk_label_new("Introduza o n de colunas: ");
    gtk_widget_set_name(colunas, "colunas");
    gtk_fixed_put(GTK_FIXED(fixed), colunas, 20, 190);
    gtk_widget_set_size_request(colunas, 80, 30);


    //LABLEL TITULO
    titulo_s = gtk_label_new("TAMANHO DO PARQUE");
    gtk_widget_set_name(titulo_s, "titulo_s");
    gtk_fixed_put(GTK_FIXED(fixed), titulo_s, 65, 17);
    gtk_widget_set_size_request(titulo_s, 80, 30);


    //SPIN NUMERO DE PISOS
    adjustment1 = gtk_adjustment_new (1.0, 2.0, 20.0, 1.0, 5.0, 0.0);
    spin1 = gtk_spin_button_new(adjustment1, 1.0, 0);
    gtk_fixed_put(GTK_FIXED(fixed), spin1, 190, 70);


    //SPIN NUMERO DE LINHAS
    adjustment2 = gtk_adjustment_new (1.0, 3.0, 7.0, 1.0, 5.0, 0.0);
    spin2 = gtk_spin_button_new(adjustment2, 1, 0);
    gtk_fixed_put(GTK_FIXED(fixed), spin2, 190, 130);


    //SPIN NUMERO DE COLUNAS
    adjustment3 = gtk_adjustment_new (1.0, 4.0, 7.0, 1.0, 5.0, 0.0);
    spin3 = gtk_spin_button_new(adjustment3, 1, 0);
    gtk_fixed_put(GTK_FIXED(fixed), spin3, 190, 190);


    //SHOW ALL WINDOWS
    gtk_widget_show_all(windowSize);


        //CASO SEJA DESTRUIDA
g_signal_connect(windowSize, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

    //MAIN
    gtk_main();
}
