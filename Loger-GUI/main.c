//#include <gtk-3.0/gdk/gdk.h>
//#include <gtk-3.0/gtk/gtk.h> // biblioteca GIMPTOOLKIT#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

GtkBuilder      *builder; //Elemento de construção da janela
GtkWidget       *window;   // Elemento janela 
GtkWidget       *acess_button; // botão de login
GtkWidget       *user_login; // botão de login
GtkWidget       *password_login; // botão de login
GtkWidget       *erro_acess_notification; // botão de login


GError     *error = NULL; // Recolhe exceções de erro


// testando evento 
//void on_acess_login_clicked(GtkButton *b){
//    gkt_label_set_text(GTK_LABEL(erro_acess_notification), "erro");
//}

// fechar janela
void on_window_main_destroy()
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    

    gtk_init(&argc, &argv); // Inicializações do gtk

    builder = gtk_builder_new(); // Criando um objeto construtor
    if( ! gtk_builder_add_from_file( builder, "./frontend/login.glade", &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }// constroi GUI Base apartir de glade

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_login"));//recolhe o elemento window a partir da builder.
    gtk_builder_connect_signals(builder, NULL);//Sinais da glade (eventos)

    //Obtendo alguns objetos
    acess_button = GTK_WIDGET(gtk_builder_get_object(builder,"acess_login"));
    user_login = GTK_WIDGET(gtk_builder_get_object(builder,"user_login"));
    erro_acess_notification = GTK_WIDGET(gtk_builder_get_object(builder,"error_acesso_notification"));


    g_object_unref(G_OBJECT( builder ));

    gtk_widget_show(window);                // exibe a janela construida para o usuario
    gtk_main(); // loop para receber sinais(eventos).

    return 0;
}



