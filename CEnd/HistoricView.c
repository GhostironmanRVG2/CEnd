#include <stdio.h>
#include <gtk/gtk.h>
//REFERENCIAS DA LISTA
enum {
  LIST_ITEM = 0,
  N_COLUMNS
};

//INICIAR A LISTA
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


//ADICIONAR ITENS NA LISTA
void add_to_list(GtkWidget *list, const gchar *str) {

    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model
        (GTK_TREE_VIEW(list)));

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}


//IR BUSCAR O QUE FOI SELECIONADO
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


//FUNCAO HISTORICO
void historic(int argc, char *argv[],char matricula[]) {
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
    //DEFS
    GtkWidget *window;
    GtkWidget *list;
    GdkColor color;
    GtkWidget *vbox;
    GtkWidget *label;
    GtkTreeSelection *selection;
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    GdkPixbuf *icon_pix;
    GtkWidget *scrolled;
    GtkWidget *button;
    FILE *file;
    parking *historico;
    int rows_inserted=0;
    //INIT
    gtk_init(&argc, &argv);
    /**FUNCAO PARA O BOTAO VOLTAR**/
    void voltar(){ gtk_widget_destroy(window); }
    /**LOAD DO CSS*/
    gtk_css_provider_load_from_path(cssProvider, "common.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                               GTK_STYLE_PROVIDER(cssProvider),
                               GTK_STYLE_PROVIDER_PRIORITY_USER);
    //CRIACAO DA WINDOW
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //CRIACAO DA LIST
    list = gtk_tree_view_new();
    //DEFS DA WINDOW
    gtk_window_set_title(GTK_WINDOW(window), "KARGA");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    /**TAMANHO DA WINDOW*/
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    /**ICON*/
    icon_pix = create_pixbuf("car.png");
    gtk_window_set_icon(GTK_WINDOW(window), icon_pix);
    /**BACKGROUND*/
    color.red = 0xffff;
    color.green = 0xFFA500;
    color.blue = 0;
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);
    /**IMPEDIR USAR A MINIMIZACAO E MAXIMIZACAO**/
    gtk_window_set_type_hint(window,GDK_WINDOW_TYPE_HINT_MENU);
    //SETAR LISTA COMO VISIVEL
    gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);
    //CRIACAO DE UMA VBOX
    vbox = gtk_vbox_new(FALSE, 0);
    //INICIALIZAR SCROLLED WINDOW
    scrolled=gtk_scrolled_window_new(NULL,NULL);
    //EMPACOTAR
    gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 5);
    //ADD WIDGET
    gtk_container_add(GTK_CONTAINER(scrolled),list);
    //CRIACAO DO LABEL
    label = gtk_label_new("");
    gtk_widget_set_name(label,"label_rows");
    //EMPACOTAR
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
    //CRIAR BUTTON E EMPACOTAR
    button=gtk_button_new_with_label("FAZER OUTRA PESQUISA");
    gtk_widget_set_name(button,"button");
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,5);
    //ACAO DO BUTTON
    g_signal_connect(G_OBJECT(button), "clicked",
            G_CALLBACK(voltar), (gpointer) window);
    //ADD TO WINDOW A VBOX
    gtk_container_add(GTK_CONTAINER(window), vbox);
    //INICIAR A LISTA
    init_list(list);
    historico= (parking*)malloc(sizeof(parking)*size_historico);
    file=fopen("historic","rb");
    //LER
    for (int i = 0; i < size_historico; i++){
        char j[9];
        fscanf(file,
        "day_chegada:%dhours_chegada:%dminutes_chegada:%dmonth_chegada:%dsecounds_chegada:%dyear_chegada:%destado:%dday_saida:%dhours_saida:%dminutes_saida:%dmonth_saida:%dsecounds_saida:%dyear_saida:%dtipo:%dn_lavagens:%dpagamento:%ftipo_de_veiculo:%dm:%c%c%c%c%c%c%c%c\n",
        &historico[i].entrada.day_chegada,
        &historico[i].entrada.hours_chegada,
        &historico[i].entrada.minutes_chegada,
        &historico[i].entrada.month_chegada,
        &historico[i].entrada.secounds_chegada,
        &historico[i].entrada.year_chegada,

        &historico[i].estado,

        &historico[i].saida.day_saida,
        &historico[i].saida.hours_saida,
        &historico[i].saida.minutes_saida,
        &historico[i].saida.month_saida,
        &historico[i].saida.secounds_saida,
        &historico[i].saida.year_saida,

        &historico[i].tipo,

        &historico[i].veiculo.n_lavagens,
        &historico[i].veiculo.pagamento,
        &historico[i].veiculo.tipo_de_veiculo,
        &j[0],
        &j[1],
        &j[2],
        &j[3],
        &j[4],
        &j[5],
        &j[6],
        &j[7]);

        strcpy(historico[i].veiculo.matricula,j);
    }
    fclose(file);
    if(!strcmp(matricula,"NON")){
        //CASO NAO HAJA MATRICULA
        //COLOCAR NA LISTA
        for(int i=0;i<size_historico;i++){
            //CHAR PARA INSERIR NA LISTA
            char lista_insert[150];
            if(historico[i].estado==0){
                snprintf(lista_insert,150,"[VEICULO REMOVIDO] MATRICULA: %s CHEGADA: %d/%d/%d %d:%d:%d SAIDA: %d/%d/%d %d:%d:%d PAGAMENTO: %0.2f",
                historico[i].veiculo.matricula,
                historico[i].entrada.day_chegada,
                historico[i].entrada.month_chegada,
                historico[i].entrada.year_chegada,
                historico[i].entrada.hours_chegada,
                historico[i].entrada.minutes_chegada,
                historico[i].entrada.secounds_chegada,
                historico[i].saida.day_saida,
                historico[i].saida.month_saida,
                historico[i].saida.year_saida,
                historico[i].saida.hours_saida,
                historico[i].saida.minutes_saida,
                historico[i].saida.secounds_saida,
                historico[i].veiculo.pagamento);
            }else{
                snprintf(lista_insert,150,"[VEICULO ESTACIONADO] MATRICULA: %s CHEGADA: %d/%d/%d %d:%d:%d",
                historico[i].veiculo.matricula,
                historico[i].entrada.day_chegada,
                historico[i].entrada.month_chegada,
                historico[i].entrada.year_chegada,
                historico[i].entrada.hours_chegada,
                historico[i].entrada.minutes_chegada,
                historico[i].entrada.secounds_chegada,
                historico[i].saida.day_saida,
                historico[i].saida.month_saida,
                historico[i].saida.year_saida,
                historico[i].saida.hours_saida,
                historico[i].saida.minutes_saida,
                historico[i].saida.secounds_saida,
                historico[i].veiculo.pagamento);
            }
            add_to_list(list,lista_insert);
            rows_inserted+=1;
        }
    }else{
        //CASO HAJA UM FILTRO DE MATRICULA:
        //COLOCAR NA LISTA
        for(int i=0;i<size_historico;i++){
            //CHAR PARA INSERIR NA LISTA
            if(!strcmp(matricula,historico[i].veiculo.matricula)){
                char lista_insert[150];
                if(historico[i].estado==0){
                    snprintf(lista_insert,150,"[VEICULO REMOVIDO] MATRICULA: %s CHEGADA: %d/%d/%d %d:%d:%d SAIDA: %d/%d/%d %d:%d:%d PAGAMENTO: %f",
                    historico[i].veiculo.matricula,
                    historico[i].entrada.day_chegada,
                    historico[i].entrada.month_chegada,
                    historico[i].entrada.year_chegada,
                    historico[i].entrada.hours_chegada,
                    historico[i].entrada.minutes_chegada,
                    historico[i].entrada.secounds_chegada,
                    historico[i].saida.day_saida,
                    historico[i].saida.month_saida,
                    historico[i].saida.year_saida,
                    historico[i].saida.hours_saida,
                    historico[i].saida.minutes_saida,
                    historico[i].saida.secounds_saida,
                    historico[i].veiculo.pagamento);
                }else{
                    snprintf(lista_insert,150,"[VEICULO ESTACIONADO] MATRICULA: %s CHEGADA: %d/%d/%d %d:%d:%d",
                    historico[i].veiculo.matricula,
                    historico[i].entrada.day_chegada,
                    historico[i].entrada.month_chegada,
                    historico[i].entrada.year_chegada,
                    historico[i].entrada.hours_chegada,
                    historico[i].entrada.minutes_chegada,
                    historico[i].entrada.secounds_chegada,
                    historico[i].saida.day_saida,
                    historico[i].saida.month_saida,
                    historico[i].saida.year_saida,
                    historico[i].saida.hours_saida,
                    historico[i].saida.minutes_saida,
                    historico[i].saida.secounds_saida,
                    historico[i].veiculo.pagamento);
                }
                add_to_list(list,lista_insert);
                rows_inserted+=1;
            }
        }
    }

    if(rows_inserted==0){
        gtk_label_set_text(label,"NAO EXISTEM RESULTADOS PARA OS CAMPOS DE PESQUISA DADOS");
    }

    //SELECAO
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    //SELECAO
    g_signal_connect(selection, "changed",
        G_CALLBACK(on_changed), label);
    //DESTRUIR
    g_signal_connect(G_OBJECT (window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
    //MOSTRAR TUDO
    gtk_widget_show_all(window);
    //FINAL DISTO
    gtk_main();
    return 0;
}



