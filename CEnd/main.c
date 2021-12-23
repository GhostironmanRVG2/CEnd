#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "Structed.c"
#include "InputWindow.c"
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










int main( int argc, char *argv[])
{
    /**DECLARATIONS*/
    GtkWindow *windowPrincipal;
    GtkWidget *vbox;
    GdkPixbuf *icon;
    GdkColor color;
    GtkWidget *button;
    GtkWidget *buttoned;
    GtkWidget *fixed;
    int posi;
    char matricula[10];
    /**ARRAY DINAMICO DE HBOX**/
    GtkWidget *hbox_array[4];
    /**ARRAY DINAMICO DE WIDGETS**/
    parque_widgets widgets_array[4][4];
    /**FUNCAO PARA ESTACIONAR**/
    void button_estacionar(GtkWidget *widget, gpointer data){

    //ABRIR JANELA PARA TIRAR A MATRICULA
    gtk_widget_hide(windowPrincipal);
    //GUARDAR A MATRICULA
    strcpy(matricula,input(argc,argv));
    //VOLTAR A DEMONSTRAR A WINDOW
    gtk_widget_show(windowPrincipal);
    }

    /**FUNCAO AVANCAR**/
    void button_next(GtkWidget *widget, gpointer data) {
    //SETTAR A POSI
    posi+=1;
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    int l=0;
    for (l;l<4;l++)
    {
    //LINHA
    int c=0;
    for (c;c<4;c++)
    {
    /**CRIAR LABEL PERSONALIZADO**/
    char str[10];
    snprintf(str,10,"[%d][%d][%d]",posi,l,c);
    gtk_frame_set_label(widgets_array[l][c].frame,str);
    }
    }
    //TORNAR O BOTAO PREV VISIVEL QUANDO ESTIVERMOS NA POSI 1
    if(posi==1){
     gtk_widget_show(button);
    }
    //TORNAR O BOTAO NEXT INVISIVEL QUANDO ESTIVER NO MAXIMO n
    if(posi==9){
     gtk_widget_hide(buttoned);
    }

    }

    /**FUNCAO RECUAR**/
    void button_prev(GtkWidget *widget, gpointer data){

    //SETTAR A POSI
    posi-=1;
    //QUANDO VOLTA VOLTA AQUI MUDA O PISO
    int l=0;
    for (l;l<4;l++)
    {
    //LINHA
    int c=0;
    for (c;c<4;c++)
    {
    /**CRIAR LABEL PERSONALIZADO**/
    char str[10];
    snprintf(str,10,"[%d][%d][%d]",posi,l,c);
    gtk_frame_set_label(widgets_array[l][c].frame,str);
    }
    }
    //TORNAR O BOTAO PREV INVISIVEL QUANDO ESTIVER NA POSICAO 0
    if(posi==0){
     gtk_widget_hide(button);
    }
    //TORNAR VISIVEL O BOTAO NEXT QUANDO ESTIVER NA POSICAO n-1
    if(posi==8){
    gtk_widget_show(buttoned);
    }


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
for(int i=0;i<5;i++){
    if(i==4){
    /**HBOX**/
    hbox_array[i]=gtk_hbox_new(TRUE,0);
    /**EMPACOTAR**/
    gtk_box_pack_start(GTK_BOX(vbox),hbox_array[i],FALSE,FALSE,1);
    /**CRIAR BUTTON**/
    button=gtk_button_new_with_label("PREV");
    /**CRIAR OUTRO BUTTON**/
    buttoned=gtk_button_new_with_label("NEXT");
    /**DAR-LHE UM NOME PARA O CSS**/
    gtk_widget_set_name(button,"button");
    /**DAR-LHE UM NOME PARA O CSS**/
    gtk_widget_set_name(buttoned,"button");
    /**FUNCOES DOS BOTOES**/
    g_signal_connect(G_OBJECT(button), "clicked",
      G_CALLBACK(button_prev), NULL);
    g_signal_connect(G_OBJECT(buttoned), "clicked",
      G_CALLBACK(button_next), NULL);
    /**EMPACOTAR**/
    gtk_box_pack_start(GTK_BOX(hbox_array[i]),button,FALSE,FALSE,1);
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
    for (l;l<4;l++)
    {
    //LINHA
    int c=0;
    for (c;c<4;c++)
    {
    /**CRIAR LABEL PERSONALIZADO**/
    char str[10];
    snprintf(str,10,"[%d][%d][%d]",0,l,c);
    /**FRAME**/
    widgets_array[l][c].frame=gtk_frame_new(str);
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
    //LIVRE
    widgets_array[l][c].imagem=gtk_image_new_from_file ("parking-lot.png");
    //ADICIONAR NA EVENT BOX
    gtk_container_add(GTK_CONTAINER(widgets_array[l][c].event_box),widgets_array[l][c].imagem);
    /**BUTTONS**/
    //ESTACIONAR
    widgets_array[l][c].button=gtk_button_new_with_label("ESTACIONAR");
    g_signal_connect(G_OBJECT(widgets_array[l][c].button), "clicked",
      G_CALLBACK(button_estacionar), NULL);
    gtk_box_pack_start(GTK_BOX(widgets_array[l][c].vertical),widgets_array[l][c].button,TRUE,TRUE,0);


    }
    }
/**MOSTRAR A WINDOW*/
gtk_widget_show_all(windowPrincipal);
/**FUNCAO PARA DAR HIDE**/
gtk_widget_hide(button);
gtk_main();
}

