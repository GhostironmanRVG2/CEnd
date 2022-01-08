#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>

void Receive(int argc, char** argv,char matricula[],int dia_e,int mes_e,int ano_e,int horas_e,int min_e,int sec_e, char pagamento[],int dia_s,int mes_s,int ano_s,int horas_s,int min_s,int sec_s){

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
    GtkWidget *windowRecev;
    GtkWidget *fixedRecev;
    GtkWidget *voltar_i;
    GtkWidget *titulo;
    GtkWidget *logo;
    GtkWidget *barra_1;
    GtkWidget *data_ent_l;
    GtkWidget *data_said_l;
    GtkWidget *matri_l;
    GtkWidget *valor_l;
    GtkWidget *data_c;
    GtkWidget *data_s;
    GtkWidget *matri;
    GtkWidget *valor;
    GtkWidget *barra_2;
    GtkWidget *mensagem;
    GtkWidget *cod_barras;
    GdkColor color;
    GdkPixbuf *icon;
    /**FUNCAO PARA O BOTAO VOLTAR**/
    void voltar(){ gtk_widget_destroy(windowRecev); }


    GtkCssProvider *cssProvider = gtk_css_provider_new();
    /**INICIALIZAR O PROGRAMA*/
    gtk_init(&argc, &argv);


    /**LOAD DO CSS*/
    gtk_css_provider_load_from_path(cssProvider, "recev.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                   GTK_STYLE_PROVIDER(cssProvider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);


    //CRIAR UMA WINDOW
    windowRecev = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //DIZER-LHE PARA FICAR NO MEIO
    gtk_window_set_position(GTK_WINDOW(windowRecev), GTK_WIN_POS_CENTER);
    //TAMANHO DA WINDOW
    gtk_window_set_default_size(GTK_WINDOW(windowRecev), 300, 480);
    //TITULO DA JANELA
    gtk_window_set_title(GTK_WINDOW(windowRecev), "KARGA");
    //CARREGAR A IMAGEM PARA A ICON
    icon = create_pixbuf("car.png");
    //ADICIONAR O ICON A JANELA
    gtk_window_set_icon(GTK_WINDOW(windowRecev), icon);


    //BACKGROUND
    color.red = 0xffff;
    color.green = 0xFFA500;
    color.blue = 0;
    gtk_widget_modify_bg(windowRecev, GTK_STATE_NORMAL, &color);


    //IMPEDIR USAR A MINIMIZACAO E MAXIMIZACAO
    gtk_window_set_type_hint(windowRecev,GDK_WINDOW_TYPE_HINT_MENU);


    //PONTO FIXO DAS COISAS
    fixedRecev = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(windowRecev), fixedRecev);


    //LABLEL TITULO
    titulo = gtk_label_new("KARGA");
    gtk_widget_set_name(titulo, "titulo");
    gtk_fixed_put(GTK_FIXED(fixedRecev), titulo, 145, 25);
    gtk_widget_set_size_request(titulo, 80, 30);


    //LOGO
    logo = gtk_image_new_from_file("recibo.png");
    gtk_widget_set_name(logo, "logo");
    gtk_fixed_put(GTK_FIXED(fixedRecev), logo, 20, 10);


    //BARRA QUE SEPARA O TITULO E A INFORMAÇÃO
    barra_1 = gtk_label_new("###############################");
    gtk_widget_set_name(barra_1, "barra_1");
    gtk_fixed_put(GTK_FIXED(fixedRecev), barra_1, 6, 70);
    gtk_widget_set_size_request(barra_1, 80, 30);


    //LABLEL DATA DE ENTRADA
    data_ent_l = gtk_label_new("Data Entrada:");
    gtk_widget_set_name(data_ent_l, "data_ent_l");
    gtk_fixed_put(GTK_FIXED(fixedRecev), data_ent_l, 30, 110);
    gtk_widget_set_size_request(data_ent_l, 80, 30);


    //LABLEL DATA DE ENTRADA DO CARRO
    char date_entr[30];
    snprintf(date_entr,30,"%d/%d/%d %d:%d:%d",dia_e,mes_e,ano_e,horas_e,min_e,sec_e);
    data_c = gtk_label_new(date_entr);
    gtk_widget_set_name(data_c, "data_c");
    gtk_fixed_put(GTK_FIXED(fixedRecev), data_c, 140, 110);
    gtk_widget_set_size_request(data_c, 80, 30);


    //LABLEL DATA DE SAIDA
    data_said_l = gtk_label_new("Data Saida:");
    gtk_widget_set_name(data_said_l, "data_said_l");
    gtk_fixed_put(GTK_FIXED(fixedRecev), data_said_l, 30, 160);
    gtk_widget_set_size_request(data_said_l, 80, 30);


    //LABLEL DATA DE SAIDA DO CARRO
    char date_saida[30];
    snprintf(date_saida,30,"%d/%d/%d %d:%d:%d",dia_s,mes_s,ano_s,horas_s,min_s,sec_s);
    data_s = gtk_label_new(date_saida);
    gtk_widget_set_name(data_s, "data_s");
    gtk_fixed_put(GTK_FIXED(fixedRecev), data_s, 140, 160);
    gtk_widget_set_size_request(data_s, 80, 30);


    //LABLEL MATRICULA
    matri_l = gtk_label_new("Matricula:");
    gtk_widget_set_name(matri_l, "matri_l");
    gtk_fixed_put(GTK_FIXED(fixedRecev), matri_l, 28, 210);
    gtk_widget_set_size_request(matri_l, 80, 30);


    //LABLEL MATRICULA DO CARRO
    matri = gtk_label_new(matricula);
    gtk_widget_set_name(matri, "matri");
    gtk_fixed_put(GTK_FIXED(fixedRecev), matri, 130, 210);
    gtk_widget_set_size_request(matri, 80, 30);


    //LABLEL VALOR PAGAMENTO
    valor_l = gtk_label_new("VALOR:");
    gtk_widget_set_name(valor_l, "valor_l");
    gtk_fixed_put(GTK_FIXED(fixedRecev), valor_l, 60, 260);
    gtk_widget_set_size_request(valor_l, 80, 30);


    //LABLEL VALOR DO PAGAMENTO
    valor = gtk_label_new(pagamento);
    gtk_widget_set_name(valor, "valor");
    gtk_fixed_put(GTK_FIXED(fixedRecev), valor, 110, 260);
    gtk_widget_set_size_request(valor, 80, 30);


    //BARRA QUE SEPARA O TITULO E A INFORMAÇÃO
    barra_2 = gtk_label_new("###############################");
    gtk_widget_set_name(barra_2, "barra_2");
    gtk_fixed_put(GTK_FIXED(fixedRecev), barra_2, 6, 300);
    gtk_widget_set_size_request(barra_2, 80, 30);


    //LABLEL MENSAGEM
    mensagem = gtk_label_new("OBRIGADO E BOM DIA!!");
    gtk_widget_set_name(mensagem, "mensagem");
    gtk_fixed_put(GTK_FIXED(fixedRecev), mensagem, 55, 325);
    gtk_widget_set_size_request(mensagem, 80, 30);


    //LOGO
    cod_barras = gtk_image_new_from_file("barra.png");
    gtk_widget_set_name(cod_barras, "cod_barras");
    gtk_fixed_put(GTK_FIXED(fixedRecev), cod_barras, 50, 355);


    //BOTAO DE VOLTAR
    voltar_i = gtk_button_new_with_label("VOLTAR");
    gtk_widget_set_name(voltar_i, "voltar_i");
    gtk_fixed_put(GTK_FIXED(fixedRecev), voltar_i, 90, 450);
    gtk_widget_set_size_request(voltar_i, 80, 30);
    //GUARDAR OS VALORES REGISTADOS
    g_signal_connect(G_OBJECT(voltar_i), "clicked",
            G_CALLBACK(voltar), (gpointer) windowRecev);


    //SHOW ALL WINDOWS
    gtk_widget_show_all(windowRecev);

    //CASO SEJA DESTRUIDA
    g_signal_connect(windowRecev, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);


    //MAIN
    gtk_main();
}

