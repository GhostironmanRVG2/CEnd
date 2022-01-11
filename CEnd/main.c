#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "parking.c"
#include "InputWindow.c"
#include "Structed.c"
#include "InfoWindow.c"
#include "SizeWindow.c"
#include "FilterWindow.c"
#include "HistoricView.c"
#include "Receive.c"


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


int main( int argc, char *argv[]){
    /**DECLARATIONS*/
    GtkWindow *windowPrincipal;
    GtkWidget *vbox;
    GdkPixbuf *icon;
    GdkColor color;
    GtkWidget *button;
    GtkWidget *buttoned;
    GtkWidget *fixed;
    parking ***parque;
    parque_widgets **widgets_array;
    GtkWidget **hbox_array;
    GtkWidget *label_piso;
    GtkWidget *historico_button;
    int posi;
    size_historico=0;
    FILE *file;
    //LER DADOS RELATIVOS AO HISTORICO
    file=fopen("size_historic","rb");
    fscanf(file,"size_historico=%d\n",&size_historico);
    fclose(file);

    //LER DADOS RELATIVOS AO TAMANHO DO PARQUE
    file=fopen("size","rb");
    //LER
    fscanf(file,"piso=%d\n",&piso);
    fscanf(file,"linha=%d\n",&linha);
    fscanf(file,"coluna=%d\n",&coluna);
    fscanf(file,"size_historico=%d\n",&size_historico);
    fclose(file);

    //CASO ESTES VALORES SEJAM ZERO!!!
    if(piso==0|linha==0|coluna==0){
        /**SETAR TAMANHO DO NOSSO PARQUE**/
        int pp[3];
        SizeWindow(argc,argv,pp);
        inicializar(0,0,0,0,parque);
        setTamanho(pp[0],pp[1],pp[2]);

        //ARMAZENAR ESTES DADOS NUM TXT
        file=fopen("size","wb");
        if(file==NULL){
            printf("\nERROR");
            exit(1);
        }
        //ESCREVER OS DADOS NO FILE
        fprintf(file,"piso=%d\n",piso);
        fprintf(file,"linha=%d\n",linha);
        fprintf(file,"coluna=%d\n",coluna);
        printf("DADOS GUARDADOS!");
    }

    //CASO OS VALORES SEJAM INTRODUZIDOS
    if(piso!=0|linha!=0|coluna!=0){
        /**ARRAY DINAMICO DE HBOX**/
        hbox_array = (GtkWidget **) malloc(sizeof(GtkWidget*) * linha+1);
        /**ARRAY DINAMICO DE WIDGETS**/
        widgets_array = (parque_widgets **) malloc (sizeof(parque_widgets **)*linha);
        for (int l = 0; l < linha; l++) {
            widgets_array[l] = (parque_widgets *) malloc(sizeof(parque_widgets)*coluna);
        }

        /**INICIALIZACAO DO NOSSO PARQUE**/
        parque = (parking ***) malloc (sizeof(parking ***)*piso);
        for (int p = 0; p < piso; p++) {
            parque[p] = (parking **) malloc(sizeof(parking*)*linha);
            for (int l = 0; l < linha; l++) {
                parque[p][l] = (parking *) malloc(sizeof(parking)*coluna);
            }
        }


        /**DIALOG WINDOW**/
        void show_error_duplicated() {
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(windowPrincipal),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Essa matricula ja existe!");
            gtk_window_set_position(dialog,GTK_WIN_POS_CENTER_ALWAYS);
            gtk_window_set_title(GTK_WINDOW(dialog), "Warning!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }


        /**DIALOG WINDOW**/
        void show_sucess() {
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(windowPrincipal),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Foi estacionado com sucesso!");
            gtk_window_set_position(dialog,GTK_WIN_POS_CENTER_ALWAYS);
            gtk_window_set_title(GTK_WINDOW(dialog), "Warning!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }


        void button_estacionar(GtkWidget *widget, gpointer data){
            if(!(strcmp(gtk_button_get_label(widget),"ESTACIONAR"))){
                //matricula
                char matricula[7];
                //REGISTOS
                char registo_aqui[10];
                char registo_comparar[10];
                //ABRIR JANELA PARA TIRAR A MATRICULA
                gtk_widget_hide(windowPrincipal);
                //GUARDAR A MATRICULA
                strcpy(matricula,input(argc,argv));

                if(Find_car(matricula,parque)!=0){
                    //SE O GET DA MATRICULA NAO FOR ERROR ESTACIONAMOS
                    if(strcmp(matricula,"ERROR")){
                        /**ESTACIONAR EM SI**/
                        //REGISTO DO BOTAO QUE FOI CLICADO
                        snprintf(registo_aqui,10,"%x",widget);
                        //PROCURAR O WIDGET
                        int l=0;
                        for (l;l<linha;l++){
                            //LINHA
                            int c=0;
                            for (c;c<coluna;c++){
                                //PASSAR O VALOR DO REGISTO NESSA POSICAO PARA O COMPARAR
                                snprintf(registo_comparar,10,"%x",widgets_array[l][c].button);
                                //VERIFICAR SE O AQUI E O COMPARAR SAO IGUAIS..SE FOREM ACABA AQUI O LOOP E DEVOLVE Linha e Coluna
                                if(!(strcmp(registo_aqui,registo_comparar))){
                                    //ESTACIONAR
                                    char verificada[9];
                                    snprintf(verificada,9,"%s",matricula);
                                    Estacionar(posi,l,c,verificada,3,parque);
                                    //SETAR IMAGEM NESSA POSICAO
                                    gtk_image_set_from_file(widgets_array[l][c].imagem,"estacionado.png");
                                    //SETAR NOME DA IMAGEM PARA UM WIDGET ESTACIONADO
                                    gtk_widget_set_name(widgets_array[l][c].event_box,"e");
                                    //MUDAR O NOME DO BUTTON
                                    gtk_button_set_label(widgets_array[l][c].button,"INFO");
                                    //MUDAR O LABEL
                                    char str[30];
                                    snprintf(str,30,"[%d][%d][%d]MATRICULA: %s",posi,l,c,parque[posi][l][c].veiculo.matricula);
                                    gtk_frame_set_label(widgets_array[l][c].frame,str);
                                    //TORNAR A WINDOW VISIVEL
                                    gtk_widget_show(windowPrincipal);
                                    //MSG DE SUCESSO
                                    show_sucess();
                                    //FILE APPEND
                                    file=fopen("historic","a");
                                    if(file==NULL){
                                        printf("\nERROR");
                                    }
                                    //ESCREVER OS DADOS NO FILE
                                    fprintf(file,"day_chegada:%dhours_chegada:%dminutes_chegada:%dmonth_chegada:%dsecounds_chegada:%dyear_chegada:%destado:%dday_saida:%dhours_saida:%dminutes_saida:%dmonth_saida:%dsecounds_saida:%dyear_saida:%dtipo:%dn_lavagens:%dpagamento:%ftipo_de_veiculo:%dm:%c%c%c%c%c%c%c%c\n",
                                    parque[posi][l][c].entrada.day_chegada,
                                    parque[posi][l][c].entrada.hours_chegada,
                                    parque[posi][l][c].entrada.minutes_chegada,
                                    parque[posi][l][c].entrada.month_chegada,
                                    parque[posi][l][c].entrada.secounds_chegada,
                                    parque[posi][l][c].entrada.year_chegada,

                                    parque[posi][l][c].estado,

                                    parque[posi][l][c].saida.day_saida,
                                    parque[posi][l][c].saida.hours_saida,
                                    parque[posi][l][c].saida.minutes_saida,
                                    parque[posi][l][c].saida.month_saida,
                                    parque[posi][l][c].saida.secounds_saida,
                                    parque[posi][l][c].saida.year_saida,

                                    parque[posi][l][c].tipo,

                                    parque[posi][l][c].veiculo.n_lavagens,
                                    parque[posi][l][c].veiculo.pagamento,
                                    parque[posi][l][c].veiculo.tipo_de_veiculo,
                                    parque[posi][l][c].veiculo.matricula[0],
                                    parque[posi][l][c].veiculo.matricula[1],
                                    parque[posi][l][c].veiculo.matricula[2],
                                    parque[posi][l][c].veiculo.matricula[3],
                                    parque[posi][l][c].veiculo.matricula[4],
                                    parque[posi][l][c].veiculo.matricula[5],
                                    parque[posi][l][c].veiculo.matricula[6],
                                    parque[posi][l][c].veiculo.matricula[7]);

                                    fclose(file);


                                    //AUMENTAR TAMANHO DO HISTORICO
                                    size_historico+=1;
                                    break;
                                }
                            }
                        }
                    }else{
                        gtk_widget_show(windowPrincipal);
                    }
                }else{
                    //DIZER QUE JA EXISTE ESSA MATRICULA
                    gtk_widget_show(windowPrincipal);
                    show_error_duplicated();
                }
            }else{

                /**GET DATA**/
                //REGISTOS
                char matricula[5];
                char tipo[6];
                char registo_aqui[10];
                char registo_comparar[10];
                int dia;
                int mes;
                int ano;
                int horas;
                int min;
                int sec;
                //PROCURAR O WIDGET
                //REGISTO DO BOTAO QUE FOI CLICADO
                snprintf(registo_aqui,10,"%x",widget);
                int l=0;
                for (l;l<linha;l++){
                    //LINHA
                    int c=0;
                    for (c;c<coluna;c++){
                        //PASSAR O VALOR DO REGISTO NESSA POSICAO PARA O COMPARAR
                        snprintf(registo_comparar,10,"%x",widgets_array[l][c].button);
                        //VERIFICAR SE O AQUI E O COMPARAR SAO IGUAIS..SE FOREM ACABA AQUI O LOOP E DEVOLVE Linha e Coluna
                        if(!(strcmp(registo_aqui,registo_comparar))){
                            //HIDE DA JANELA
                            gtk_widget_hide(windowPrincipal);
                            //GET DOS DADOS
                            strcpy(matricula,parque[posi][l][c].veiculo.matricula);
                            //TIPO DE CARRO
                            strcpy(tipo,"CARRO");
                            //dia
                            dia=parque[posi][l][c].entrada.day_chegada;
                            //mes
                            mes=parque[posi][l][c].entrada.month_chegada;
                            //ano
                            ano=parque[posi][l][c].entrada.year_chegada;
                            //horas
                            horas=parque[posi][l][c].entrada.hours_chegada;
                            //minutos
                            min=parque[posi][l][c].entrada.minutes_chegada;
                            //sec
                            sec=parque[posi][l][c].entrada.secounds_chegada;
                            //OPEN INFOWINDOW
                            InfoWindow(argc,argv,matricula,dia,mes,ano,horas,min,sec);
                            gtk_widget_show(windowPrincipal);
                            break;
                        }
                    }
                }
            }
        }


        /**DIALOG WINDOW**/
        void show_error() {
            GtkWidget *dialog;
            dialog = gtk_message_dialog_new(GTK_WINDOW(windowPrincipal),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Clique em carros para destacionar!");
            gtk_window_set_position(dialog,GTK_WIN_POS_CENTER_ALWAYS);
            gtk_window_set_title(GTK_WINDOW(dialog), "Warning!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }


        /**FUNCAO DESTACIONAR**/
        //FUNCAO PARA CASO O BOTAO SEJA CLICAVEL
        void image_clicked(GtkWidget *widget, gpointer data) {
            char matricula[10];
            //VERIFICAR TYPES DAS IMAGENS PELO EVENT BOX
            if(!(strcmp(gtk_widget_get_name(widget),"e"))){
                //CASO ESTEJA ESTACIONADO EFETUAR DESTACIONAR
                //REGISTOS
                char registo_aqui[10];
                char registo_comparar[10];
                /**ESTACIONAR EM SI**/
                //REGISTO DO BOTAO QUE FOI CLICADO
                snprintf(registo_aqui,10,"%x",widget);
                //PROCURAR O WIDGET
                int l=0;
                for (l;l<linha;l++){
                    //LINHA
                    int c=0;
                    for (c;c<coluna;c++){
                        //PASSAR O VALOR DO REGISTO NESSA POSICAO PARA O COMPARAR
                        snprintf(registo_comparar,10,"%x",widgets_array[l][c].event_box);
                        //VERIFICAR SE O AQUI E O COMPARAR SAO IGUAIS..SE FOREM ACABA AQUI O LOOP E DEVOLVE Linha e Coluna
                        if(!(strcmp(registo_aqui,registo_comparar))){
                            char price[30];
                            //ESCREVER OS DADOS NO FILE
                            //FILE APPEND
                            file=fopen("historic","a");
                            if(file==NULL){
                                printf("\nERROR");
                            }
                            //GET DOS DADOS
                            strcpy(matricula,parque[posi][l][c].veiculo.matricula);
                            //AUMENTAR TAMANHO DO HISTORICO
                            size_historico+=1;
                            //DESTACIONAR E RECEBER PAGAMENTO
                            float pagamento=Destacionar(posi,l,c,0,parque);
                            //SETAR ESTADO ANTES DE COLOCAR OS DADOS DENTRO
                            fprintf(file,"day_chegada:%dhours_chegada:%dminutes_chegada:%dmonth_chegada:%dsecounds_chegada:%dyear_chegada:%destado:%dday_saida:%dhours_saida:%dminutes_saida:%dmonth_saida:%dsecounds_saida:%dyear_saida:%dtipo:%dn_lavagens:%dpagamento:%ftipo_de_veiculo:%dm:%c%c%c%c%c%c%c%c\n",
                            parque[posi][l][c].entrada.day_chegada,
                            parque[posi][l][c].entrada.hours_chegada,
                            parque[posi][l][c].entrada.minutes_chegada,
                            parque[posi][l][c].entrada.month_chegada,
                            parque[posi][l][c].entrada.secounds_chegada,
                            parque[posi][l][c].entrada.year_chegada,

                            parque[posi][l][c].estado,

                            parque[posi][l][c].saida.day_saida,
                            parque[posi][l][c].saida.hours_saida,
                            parque[posi][l][c].saida.minutes_saida,
                            parque[posi][l][c].saida.month_saida,
                            parque[posi][l][c].saida.secounds_saida,
                            parque[posi][l][c].saida.year_saida,

                            parque[posi][l][c].tipo,

                            parque[posi][l][c].veiculo.n_lavagens,
                            parque[posi][l][c].veiculo.pagamento,
                            parque[posi][l][c].veiculo.tipo_de_veiculo,
                            parque[posi][l][c].veiculo.matricula[0],
                            parque[posi][l][c].veiculo.matricula[1],
                            parque[posi][l][c].veiculo.matricula[2],
                            parque[posi][l][c].veiculo.matricula[3],
                            parque[posi][l][c].veiculo.matricula[4],
                            parque[posi][l][c].veiculo.matricula[5],
                            parque[posi][l][c].veiculo.matricula[6],
                            parque[posi][l][c].veiculo.matricula[7]);

                            fclose(file);
                            //SETTAR A STRING DA MATRICULA COMO NULL
                            parque[posi][l][c].veiculo.matricula[0]='\0';
                            //SETAR IMAGEM NESSA POSICAO
                            gtk_image_set_from_file(widgets_array[l][c].imagem,"parking-lot.png");
                            //MUDAR O NOME DO BUTTON
                            gtk_button_set_label(widgets_array[l][c].button,"ESTACIONAR");
                            //MUDAR O LABEL
                            char str[10];
                            snprintf(str,10,"[%d][%d][%d]",posi,l,c);
                            gtk_frame_set_label(widgets_array[l][c].frame,str);

                            char tipo[6];
                            int dia_e;
                            int mes_e;
                            int ano_e;
                            int horas_e;
                            int min_e;
                            int sec_e;
                            int dia_s;
                            int mes_s;
                            int ano_s;
                            int horas_s;
                            int min_s;
                            int sec_s;

                            //HIDE DA JANELA
                            gtk_widget_hide(windowPrincipal);
                            //TIPO DE CARRO
                            strcpy(tipo,"CARRO");
                            //dia entrada
                            dia_e=parque[posi][l][c].entrada.day_chegada;
                            //mes entrada
                            mes_e=parque[posi][l][c].entrada.month_chegada;
                            //ano entrada
                            ano_e=parque[posi][l][c].entrada.year_chegada;
                            //horas entrada
                            horas_e=parque[posi][l][c].entrada.hours_chegada;
                            //minutos entrada
                            min_e=parque[posi][l][c].entrada.minutes_chegada;
                            //sec entrada
                            sec_e=parque[posi][l][c].entrada.secounds_chegada;
                            //dia saida
                            dia_s=parque[posi][l][c].saida.day_saida;
                            //mes saida
                            mes_s=parque[posi][l][c].saida.month_saida;
                            //ano saida
                            ano_s=parque[posi][l][c].saida.year_saida;
                            //horas saida
                            horas_s=parque[posi][l][c].saida.hours_saida;
                            //minutos saida
                            min_s=parque[posi][l][c].saida.minutes_saida;
                            //sec saida
                            sec_s=parque[posi][l][c].saida.secounds_saida;

                            Receive(argc,argv,matricula,dia_e,mes_e,ano_e,horas_e,min_e,sec_e,pagamento,dia_s,mes_s,ano_s,horas_s,min_s,sec_s);
                            gtk_widget_show(windowPrincipal);
                            break;
                        }
                    }
                }
            }else{
                //invocar funcao show error
                show_error();
            }
        }


        /**FUNCAO AVANCAR**/
        void button_next(GtkWidget *widget, gpointer data) {
            //STR DO LABEL
            char str_label[20];
            //SETTAR A POSI
            posi+=1;
            //QUANDO VOLTA VOLTA AQUI MUDA O PISO
            int l=0;
            for (l;l<linha;l++){
                //LINHA
                int c=0;
                for (c;c<coluna;c++){
                    /**CRIAR LABEL PERSONALIZADO**/
                    char str[30];

                    //AVERIGUAR OS LUGARES CONSOANTE O AVANCO
                    if(!(strlen(parque[posi][l][c].veiculo.matricula)>7)){
                        //CONTINUACAO LABEL PERSONALIZADO
                        snprintf(str,10,"[%d][%d][%d]",posi,l,c);
                        gtk_frame_set_label(widgets_array[l][c].frame,str);
                        //CASO NAO HAJA MATRICULA NESSE DADO LUGAR
                        gtk_button_set_label(widgets_array[l][c].button,"ESTACIONAR");
                        gtk_image_set_from_file(widgets_array[l][c].imagem,"parking-lot.png");
                        gtk_widget_set_name(widgets_array[l][c].event_box,"p");
                    }else{
                        snprintf(str,30,"[%d][%d][%d]MATRICULA: %s",posi,l,c,parque[posi][l][c].veiculo.matricula);
                        gtk_frame_set_label(widgets_array[l][c].frame,str);
                        gtk_button_set_label(widgets_array[l][c].button,"INFO");
                        gtk_image_set_from_file(widgets_array[l][c].imagem,"estacionado.png");
                        gtk_widget_set_name(widgets_array[l][c].event_box,"e");
                    }
                }
            }
            //TORNAR O BOTAO PREV VISIVEL QUANDO ESTIVERMOS NA POSI 1
            if(posi==1){
                gtk_widget_show(button);
            }
            //TORNAR O BOTAO NEXT INVISIVEL QUANDO ESTIVER NO MAXIMO n-1
            if(posi==piso-1){
                gtk_widget_hide(buttoned);
            }
            //MUDAR LABEL DO PISO
            if(posi-10<0){
                snprintf(str_label,20,"PISO\n   %d",posi);
            }else{
                snprintf(str_label,20,"PISO\n  %d",posi);
            }
            gtk_label_set_text(label_piso,str_label);
        }

        /**FUNCAO RECUAR**/
        void button_prev(GtkWidget *widget, gpointer data){
        //CHAR DO LABEL
        char str_label[20];
        //SETTAR A POSI
        posi-=1;
        //QUANDO VOLTA VOLTA AQUI MUDA O PISO
        int l=0;
        for (l;l<linha;l++){
            //LINHA
            int c=0;
            for (c;c<coluna;c++){
                /**CRIAR LABEL PERSONALIZADO**/
                char str[30];

                //AVERIGUAR OS LUGARES CONSOANTE O RECUO
                if(!(strlen(parque[posi][l][c].veiculo.matricula)>7)){
                    //CONTINUACAO LABEL PERSONALIZADO
                    snprintf(str,10,"[%d][%d][%d]",posi,l,c);
                    gtk_frame_set_label(widgets_array[l][c].frame,str);
                    //CASO NAO HAJA MATRICULA NESSE DADO LUGAR
                    //MUDAR BUTTON E IMAGEM
                    gtk_button_set_label(widgets_array[l][c].button,"ESTACIONAR");
                    gtk_image_set_from_file(widgets_array[l][c].imagem,"parking-lot.png");
                    //DAR UM NOME NA IMAGEM
                    gtk_widget_set_name(widgets_array[l][c].event_box,"p");
                }else{
                    //CONTINUACAO LABEL PERSONALIZADO
                    snprintf(str,30,"[%d][%d][%d]MATRICULA: %s",posi,l,c,parque[posi][l][c].veiculo.matricula);
                    gtk_frame_set_label(widgets_array[l][c].frame,str);
                    //MUDAR BUTTON E IMAGEM
                    gtk_button_set_label(widgets_array[l][c].button,"INFO");
                    gtk_image_set_from_file(widgets_array[l][c].imagem,"estacionado.png");
                     //DAR UM NOME NA IMAGEM
                    gtk_widget_set_name(widgets_array[l][c].event_box,"e");
                }
            }
        }

        //TORNAR O BOTAO PREV INVISIVEL QUANDO ESTIVER NA POSICAO 0
        if(posi==0){
            gtk_widget_hide(button);
        }
        //TORNAR VISIVEL O BOTAO NEXT QUANDO ESTIVER NA POSICAO n-2
        if(posi==piso-2){
            gtk_widget_show(buttoned);
        }
            //ALTERAR O PISO
            snprintf(str_label,20,"PISO\n   %d",posi);
            gtk_label_set_text(label_piso,str_label);
        }


        /**FUNCAO AVANCAR**/
        void button_historic(GtkWidget *widget, gpointer data) {
            //POR A JANELA PRINCIPAL INVISIVEL
            gtk_widget_hide(windowPrincipal);
            //PROCEDER Á FUNCAO DA JANELA DO HISTORICO
            FilterW(argc,argv);
            //TORNAR O WIDGET VISIVEL
            gtk_widget_show(windowPrincipal);
        }

        /**CSS INIT**/
        GtkCssProvider *cssProvider = gtk_css_provider_new();
        /**INICIALIZAR O PROGRAMA*/
        gtk_init(&argc, &argv);
        /**POSICAO DO PROGRAMA AO ABRIR**/
        posi=0;
        /**LOAD DO CSS*/
        gtk_css_provider_load_from_path(cssProvider, "common.css", NULL);
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                        GTK_STYLE_PROVIDER(cssProvider),
                                        GTK_STYLE_PROVIDER_PRIORITY_USER);
        /**LOAD DOS DADOS**/
        file=fopen("car","r");
        for (int p = 0; p < piso; p++){
            for (int l = 0; l < linha; l++){
                for (int c = 0; c < coluna; c++){
                    char j[9];
                    fscanf(file,"day_chegada:%dhours_chegada:%dminutes_chegada:%dmonth_chegada:%dsecounds_chegada:%dyear_chegada:%destado:%dday_saida:%dhours_saida:%dminutes_saida:%dmonth_saida:%dsecounds_saida:%dyear_saida:%dtipo:%dn_lavagens:%dpagamento:%ftipo_de_veiculo:%dm:%c%c%c%c%c%c%c%c\n",
                    &parque[p][l][c].entrada.day_chegada,
                    &parque[p][l][c].entrada.hours_chegada,
                    &parque[p][l][c].entrada.minutes_chegada,
                    &parque[p][l][c].entrada.month_chegada,
                    &parque[p][l][c].entrada.secounds_chegada,
                    &parque[p][l][c].entrada.year_chegada,

                    &parque[p][l][c].estado,

                    &parque[p][l][c].saida.day_saida,
                    &parque[p][l][c].saida.hours_saida,
                    &parque[p][l][c].saida.minutes_saida,
                    &parque[p][l][c].saida.month_saida,
                    &parque[p][l][c].saida.secounds_saida,
                    &parque[p][l][c].saida.year_saida,

                    &parque[p][l][c].tipo,

                    &parque[p][l][c].veiculo.n_lavagens,
                    &parque[p][l][c].veiculo.pagamento,
                    &parque[p][l][c].veiculo.tipo_de_veiculo,
                    &j[0],
                    &j[1],
                    &j[2],
                    &j[3],
                    &j[4],
                    &j[5],
                    &j[6],
                    &j[7]
                    );

                    strcpy(parque[p][l][c].veiculo.matricula,j);
                }
            }
        }
        fclose(file);

        /**CRIAR UMA WINDOW*/
        windowPrincipal = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        /**DIZER-LHE PARA FICAR NO MEIO*/
        gtk_window_set_position(GTK_WINDOW(windowPrincipal), GTK_WIN_POS_CENTER);
        /**MAXIMIZAR A WINDOW**/
        gtk_window_maximize(windowPrincipal);
        /**TITULO*/
        gtk_window_set_title(GTK_WINDOW(windowPrincipal), "KARGA");
        /**ICON*/
        icon = create_pixbuf("car.png");
        gtk_window_set_icon(GTK_WINDOW(windowPrincipal), icon);
        /**BACKGROUND*/
        color.red = 0xffff;
        color.green = 0xFFA500;
        color.blue = 0;
        gtk_widget_modify_bg(windowPrincipal, GTK_STATE_NORMAL, &color);
        /**CRIAR UMA VBOX*/
        vbox=gtk_vbox_new(TRUE,1);
        gtk_container_add(GTK_CONTAINER(windowPrincipal),vbox);

        /**INICIALIZAR HBOXES**/
        for(int i=0;i<linha+1;i++){
            if(i==linha){
                /**HBOX**/
                hbox_array[i]=gtk_hbox_new(TRUE,0);
                /**EMPACOTAR**/
                gtk_box_pack_start(GTK_BOX(vbox),hbox_array[i],FALSE,FALSE,1);
                /**CRIAR BUTTON**/
                button=gtk_button_new_with_label("ANTERIOR");
                /**CRIAR OUTRO BUTTON**/
                buttoned=gtk_button_new_with_label("SEGUINTE");
                /**CRIAR BUTTON**/
                historico_button=gtk_button_new_with_label("HISTORICO");
                /**DAR-LHE UM NOME PARA O CSS**/
                gtk_widget_set_name(button,"button");
                /**DAR-LHE UM NOME PARA O CSS**/
                gtk_widget_set_name(buttoned,"button");
                /**DAR-LHE UM NOME PARA O CSS**/
                gtk_widget_set_name(historico_button,"button_h");
                /**FUNCOES DOS BOTOES**/
                g_signal_connect(G_OBJECT(button), "clicked",
                    G_CALLBACK(button_prev), NULL);
                g_signal_connect(G_OBJECT(buttoned), "clicked",
                    G_CALLBACK(button_next), NULL);
                g_signal_connect(G_OBJECT(historico_button), "clicked",
                    G_CALLBACK(button_historic), NULL);
                //label
                label_piso=gtk_label_new("PISO\n   0");
                gtk_widget_set_name(label_piso,"label_piso");

                /**EMPACOTAR**/
                gtk_box_pack_start(GTK_BOX(hbox_array[i]),button,FALSE,FALSE,1);
                gtk_box_pack_start(GTK_BOX(hbox_array[i]),label_piso,FALSE,FALSE,1);
                gtk_box_pack_start(GTK_BOX(hbox_array[i]),historico_button,FALSE,FALSE,1);
                gtk_box_pack_start(GTK_BOX(hbox_array[i]),buttoned,FALSE,FALSE,1);
            }else{
                /**HBOX**/
                hbox_array[i]=gtk_hbox_new(TRUE,1);
                /**EMPACOTAR**/
                gtk_box_pack_start(GTK_BOX(vbox),hbox_array[i],TRUE,TRUE,1);
            }
        }

        /**INICIALIZAR CONTEUDO DAS HBOXES**/
        //QUANDO VOLTA VOLTA AQUI MUDA O PISO
        int l=0;
        for (l;l<linha;l++){
            //LINHA
            int c=0;
            for (c;c<coluna;c++){
                /**CRIAR LABEL PERSONALIZADO**/
                char str[30];
                if(!(strlen(parque[0][l][c].veiculo.matricula)>7)){
                    snprintf(str,10,"[%d][%d][%d]",0,l,c);
                    /**FRAME**/
                    widgets_array[l][c].frame=gtk_frame_new(str);
                }else{
                    snprintf(str,30,"[%d][%d][%d]MATRICULA: %s",0,l,c,parque[0][l][c].veiculo.matricula);
                    /**FRAME**/
                    widgets_array[l][c].frame=gtk_frame_new(str);
                }
                gtk_widget_set_name( widgets_array[l][c].frame,"frame" );
                //ADICIONAR AO HBOX
                gtk_box_pack_start(GTK_BOX(hbox_array[l]),widgets_array[l][c].frame,TRUE,TRUE,0);
                /**VERTICAL**/
                widgets_array[l][c].vertical=gtk_vbox_new(TRUE,0);
                //ADICIONAR AO FRAME
                gtk_container_add(GTK_CONTAINER(widgets_array[l][c].frame),widgets_array[l][c].vertical);
                /**EVENT BOX**/
                widgets_array[l][c].event_box=gtk_event_box_new();
                //ADICIONAR AO VBOX
                gtk_box_pack_start(GTK_BOX(widgets_array[l][c].vertical),widgets_array[l][c].event_box,TRUE,TRUE,0);
                /**IMAGENS**/
                if(!(strlen(parque[0][l][c].veiculo.matricula)>7)){
                    //LIVRE
                    widgets_array[l][c].imagem=gtk_image_new_from_file ("parking-lot.png");
                    //DAR-LHE UM NOME
                    gtk_widget_set_name(widgets_array[l][c].event_box,"p");
                }else{
                    //OCUPADO
                    widgets_array[l][c].imagem=gtk_image_new_from_file("estacionado.png");
                    //DAR-LHE UM NOME
                    gtk_widget_set_name(widgets_array[l][c].event_box,"e");
                }
                //ADICIONAR NA EVENT BOX
                gtk_container_add(GTK_CONTAINER(widgets_array[l][c].event_box),widgets_array[l][c].imagem);
                //CRIAR EVENTO E ASSOCIAR A UMA FUNCAO
                g_signal_connect(G_OBJECT(widgets_array[l][c].event_box), "button_press_event",
                G_CALLBACK(image_clicked), NULL);
                /**BUTTONS**/
                //ESTACIONAR
                if(!(strlen(parque[0][l][c].veiculo.matricula)>7)){
                    widgets_array[l][c].button=gtk_button_new_with_label("ESTACIONAR");
                }else{
                    widgets_array[l][c].button=gtk_button_new_with_label("INFO");
                }
                g_signal_connect(G_OBJECT(widgets_array[l][c].button), "clicked",
                    G_CALLBACK(button_estacionar), NULL);
                gtk_box_pack_start(GTK_BOX(widgets_array[l][c].vertical),widgets_array[l][c].button,TRUE,TRUE,0);
            }
        }

        //CASO SEJA DESTRUIDA
        g_signal_connect(windowPrincipal, "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
        /**MOSTRAR A WINDOW*/
        gtk_widget_show_all(windowPrincipal);
        /**FUNCAO PARA DAR HIDE**/
        gtk_widget_hide(button);
        gtk_main();
    }

    file=fopen("car","wb");
    if(file==NULL){
        printf("\nERROR");
        exit(1);
    }

    for (int p = 0; p < piso; p++){
        for (int l = 0; l < linha; l++){
            for (int c = 0; c < coluna; c++){
                fprintf(file,"day_chegada:%dhours_chegada:%dminutes_chegada:%dmonth_chegada:%dsecounds_chegada:%dyear_chegada:%destado:%dday_saida:%dhours_saida:%dminutes_saida:%dmonth_saida:%dsecounds_saida:%dyear_saida:%dtipo:%dn_lavagens:%dpagamento:%ftipo_de_veiculo:%dm:%c%c%c%c%c%c%c%c\n",
                parque[p][l][c].entrada.day_chegada,
                parque[p][l][c].entrada.hours_chegada,
                parque[p][l][c].entrada.minutes_chegada,
                parque[p][l][c].entrada.month_chegada,
                parque[p][l][c].entrada.secounds_chegada,
                parque[p][l][c].entrada.year_chegada,

                parque[p][l][c].estado,

                parque[p][l][c].saida.day_saida,
                parque[p][l][c].saida.hours_saida,
                parque[p][l][c].saida.minutes_saida,
                parque[p][l][c].saida.month_saida,
                parque[p][l][c].saida.secounds_saida,
                parque[p][l][c].saida.year_saida,

                parque[p][l][c].tipo,

                parque[p][l][c].veiculo.n_lavagens,
                parque[p][l][c].veiculo.pagamento,
                parque[p][l][c].veiculo.tipo_de_veiculo,
                parque[p][l][c].veiculo.matricula[0],
                parque[p][l][c].veiculo.matricula[1],
                parque[p][l][c].veiculo.matricula[2],
                parque[p][l][c].veiculo.matricula[3],
                parque[p][l][c].veiculo.matricula[4],
                parque[p][l][c].veiculo.matricula[5],
                parque[p][l][c].veiculo.matricula[6],
                parque[p][l][c].veiculo.matricula[7]);
            }
        }
    }
    fclose(file);


   //ARMAZENAR ESTES DADOS NUM TXT
    file=fopen("size_historic","wb");
    if(file==NULL){
        printf("\nERROR");
        exit(1);
    }
    //ESCREVER OS DADOS NO FILE
    fprintf(file,"size_historico=%d\n",size_historico);

    fclose(file);
}

