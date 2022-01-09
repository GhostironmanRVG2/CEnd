#include <gtk/gtk.h>
#include <string.h>

void InfoWindow(int argc, char** argv,char matricula[],int dia,int mes,int ano,int horas,int min,int sec){


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


    //INICIALIZAR WINDOW E OUTROS COMPONENTES
    GtkWidget *windowInfo;
    GtkWidget *fixedInfo;
    GtkWidget *matricula_t;
    GtkWidget *matricula_c;
    GtkWidget *tipo_t;
    GtkWidget *tipo_c;
    GtkWidget *data_t;
    GtkWidget *data_c;
    GtkWidget *titulo;
    GtkWidget *voltar_i;
    GdkColor color;
    GdkPixbuf *icon;
    /**FUNCAO PARA O BOTAO VOLTAR**/
    void voltar(){ gtk_widget_destroy(windowInfo); }

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    /**INICIALIZAR O PROGRAMA*/
    gtk_init(&argc, &argv);


    /**LOAD DO CSS*/
    gtk_css_provider_load_from_path(cssProvider, "info.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);

    //CRIAR UMA WINDOW
    windowInfo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //DIZER-LHE PARA FICAR NO MEIO
    gtk_window_set_position(GTK_WINDOW(windowInfo), GTK_WIN_POS_CENTER);
    //TAMANHO DA WINDOW
    gtk_window_set_default_size(GTK_WINDOW(windowInfo), 400, 300);
    //TITULO DA JANELA
    gtk_window_set_title(GTK_WINDOW(windowInfo), "KARGA");
    //ICON
    icon = create_pixbuf("car.png");
    gtk_window_set_icon(GTK_WINDOW(windowInfo), icon);


    //BACKGROUND
    color.red = 0xffff;
    color.green = 0xFFA500;
    color.blue = 0;
    gtk_widget_modify_bg(windowInfo, GTK_STATE_NORMAL, &color);


    //IMPEDIR USAR A MINIMIZACAO E MAXIMIZACAO
    gtk_window_set_type_hint(windowInfo,GDK_WINDOW_TYPE_HINT_MENU);


    //PONTO FIXO DAS COISAS
    fixedInfo = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(windowInfo), fixedInfo);


    //LABLEL TITULO
    titulo = gtk_label_new("INFORMACAO");
    gtk_widget_set_name(titulo, "titulo");
    gtk_fixed_put(GTK_FIXED(fixedInfo), titulo, 125, 17);
    gtk_widget_set_size_request(titulo, 80, 30);


    //LABLEL MATRICULA
    matricula_t = gtk_label_new("MATRICULA");
    gtk_widget_set_name(matricula_t, "matricula_t");
    gtk_fixed_put(GTK_FIXED(fixedInfo), matricula_t, 145, 60);
    gtk_widget_set_size_request(matricula_t, 80, 30);


    //LABLEL MATRICULA DO CARRO
    char result[7];
    snprintf(result,9,"%s",matricula);
    matricula_c = gtk_label_new(result);
    gtk_widget_set_name(matricula_c, "matricula_c");
    gtk_fixed_put(GTK_FIXED(fixedInfo), matricula_c, 150, 80);
    gtk_widget_set_size_request(matricula_c, 80, 30);


    //LABLEL TIPO
    tipo_t = gtk_label_new("TIPO DE CARRO");
    gtk_widget_set_name(tipo_t, "tipo_t");
    gtk_fixed_put(GTK_FIXED(fixedInfo), tipo_t, 125, 120);
    gtk_widget_set_size_request(tipo_t, 80, 30);


    //LABLEL TIPO DO CARRO
    tipo_c = gtk_label_new("CARRO");
    gtk_widget_set_name(tipo_c, "tipo_c");
    gtk_fixed_put(GTK_FIXED(fixedInfo), tipo_c, 150, 140);
    gtk_widget_set_size_request(tipo_c, 80, 30);


    //LABLEL DATA ENTRADA
    data_t = gtk_label_new("DATA DE ENTRADA");
    gtk_widget_set_name(data_t, "data_t");
    gtk_fixed_put(GTK_FIXED(fixedInfo), data_t, 115, 180);
    gtk_widget_set_size_request(data_t, 80, 30);


    //LABLEL DATA DE ENTRADA DO CARRO
    char date_entr[30];
    snprintf(date_entr,30,"%d/%d/%d %d:%d:%d",dia,mes,ano,horas,min,sec);
    data_c = gtk_label_new(date_entr);
    gtk_widget_set_name(data_c, "data_c");
    gtk_fixed_put(GTK_FIXED(fixedInfo), data_c, 108, 200);
    gtk_widget_set_size_request(data_c, 80, 30);


    //BOTAO DE VOLTAR
    voltar_i = gtk_button_new_with_label("VOLTAR");
    gtk_widget_set_name(voltar_i, "voltar_i");
    gtk_fixed_put(GTK_FIXED(fixedInfo), voltar_i, 135, 250);
    gtk_widget_set_size_request(voltar_i, 80, 30);
    //GUARDAR OS VALORES REGISTADOS
    g_signal_connect(G_OBJECT(voltar_i), "clicked",
            G_CALLBACK(voltar), (gpointer) windowInfo);


    //SHOW ALL WINDOWS
    gtk_widget_show_all(windowInfo);

    //CASO SEJA DESTRUIDA
    g_signal_connect(windowInfo, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);


    //MAIN
    gtk_main();
}
