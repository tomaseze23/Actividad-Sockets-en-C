#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

#define MAX 80

void menuInicial();

int leerLinea(char *cad, int n);

char linea[MAX];

int myAtoi(char* str);

int main(int argc, char* argv[]){
    WSADATA wsa;
    SOCKET skt;
    int puerto=0, recv_size;
    char mensaje[2000];
    char fecha[MAX];
    struct sockaddr_in server;
    /*====================INICIALIZACIÓN WINSOCK====================*/
    printf("Inicializando Winsock...\n");
    if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("Error al inicializar el winsock\n");
        exit(-1);
    }
    printf("\nWinsock inicializado.\n");

    /*====================CREACIÓN SOCKET====================*/
    printf("\nCreando socket...\n");
    if((skt = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
        printf("Error creando socket\n");
        exit(-1);
    }

    /*====================CONFIGURACION SOCKADDR_IN====================*/
    server.sin_family = AF_INET;
    printf("ingrese puerto: ");
    fflush(stdin);
    scanf("%d", &puerto);
    server.sin_port = htons(puerto);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(skt, (struct sockaddr *)&server, sizeof(server)) < 0){
        printf("Error de conexion\n");
        exit(-1);
    }
    printf("Conexion exitosa.\n");
    printf("\nSocket creado.\n");
    int opcion=-1;
    do{
        //ingreso al sistema
        if((recv_size = recv(skt, mensaje, 2000, 0)) == SOCKET_ERROR){
            printf("Recepcion fallida\n");
        }
        mensaje[recv_size] = '\0';
        printf("\nServer - %s",mensaje);
        fflush(stdin);
        gets(mensaje);
        opcion = myAtoi(mensaje);
        //envio al servidor del dato para permitir acceso al sistema
        if(send(skt, mensaje, strlen(mensaje), 0) < 0){
            printf("Error al enviar mensaje\n");
            exit(-1);
        }
        if(opcion!=0)
            menuInicial();
    }while(opcion!=0);

    printf("\n\nElegiste salir! Adios!");


    system("pause");

    closesocket(skt);
    WSACleanup();

    return 0;
}

void menuInicial(){
    char repite = 1;
    int opcion=-1;
    do{
        system("cls");
        printf("\n\t\t\tMENU\n");
        printf("\t\t\t============\n");
		printf("\n\t\t[1]. Generar Usuario\n");
		printf("\t\t[2]. Generar contrase%ca\n", 164);
		printf("\t\t[0]. Salir\n");
		printf("\n\t\tIngrese su opcion: [ ]\b\b");
		leerLinea(linea, MAX);
		sscanf(linea, "%d", &opcion);

		switch(opcion) {
            case 1:
                    generarUsuario();
                    break;
            case 2: generarContrasenia();
                    break;
            case 0: //exit(1);
                    repite = 0;
                    break;
		}
    } while(repite == 1);
}

int leerLinea(char *cad, int n) {
    int i, c;
    //primero comprobamos datos iniciales en el buffer
    c=getchar();

    if(c == EOF) {
        cad[0] = '\0';
        return 0;
    }

    if(c == '\n') {
        i = 0;
    } else{
        cad[0] = c;
        i = 1;
    }

    //lectura de la cadena
    for(; i < n-1 && (c = getchar())!= EOF && c != '\n'; i++) {
       cad[i] = c;
    }
    cad[i] = '\0';

    //limpieza del buffer
    if(c != '\n' && c != EOF){
        while((c = getchar()) != '\n' && c != EOF);
    }
    return 1;
}

void usuarioAleatorio(int tamanio){
    int i = 0;
    int aleatorio = 0, aux = -1;
    // hace que el generador de numeros aleatorios se sincronize con la hora actual para que los numeros sean diferentes cada vez
    srand((unsigned int) (time (NULL)));

    //array de minusculas
    char vocales[] = "aeiouAEIOU";
    char consonantes[] = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

    char usuario[tamanio];

    //para seleccionar la aleatoriedad dentro del for
    for (i = 0; i < tamanio; i++){
        aleatorio = rand() % 2;
        if(aleatorio == 1 && aux != aleatorio){
            usuario[i] = vocales[rand() % 10];
            aux = aleatorio;
        }
        else if (aleatorio == 1 && aux == aleatorio){
            usuario[i] = consonantes[rand() % 42];
            aux = aleatorio;
        }
        else if (aleatorio == 0 && aux != aleatorio){
            usuario[i] = consonantes[rand() % 42];
            aux = aleatorio;
        }
        else if (aleatorio == 0 && aux == aleatorio){
            usuario[i] = vocales[rand() % 10];
            aux = aleatorio;
        }
    }
    usuario[i] = '\0';
    printf("\nEl usuario es: %s", usuario);
}

void contraseniaAleatoria(int tamanio){
    int i = 0;
    int aleatorio = 0;
    // hace que el generador de numeros aleatorios se sincronize con la hora actual para que los numeros sean diferentes cada vez
    srand((unsigned int) (time (NULL)));

    //array de numeros
    char numeros[] = "0123456789";
    //array de minusculas
    char minuscula[] = "abcdefghijklmnopqrstuvwxyz";
    //array mayusculas
    char mayuscula[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char contrasenia[tamanio];

    //para seleccionar la aleatoriedad dentro del for
    aleatorio = rand() % 3;

    for (i = 0; i < tamanio; i++){
        if(aleatorio == 1){
            contrasenia[i] = numeros[rand() % 10];
            aleatorio = rand() % 4;
        }
        else if(aleatorio == 2){
            contrasenia[i] = minuscula[rand() % 26];
            aleatorio = rand() % 4;
        }
        else{
            contrasenia[i] = mayuscula[rand() % 26];
            aleatorio = rand() % 4;
        }
    }
    contrasenia[i] = '\0';
    printf("La contrase%ca es: %s", 164, contrasenia);
}


void generarUsuario(){
    printf("\n\nGenerador de usuarios\n\n");
    printf("Indique la cantidad de caracteres que desea para su usuario: ");
    int tamanio;
    scanf("%d", &tamanio);
    if(tamanio < 5 || tamanio > 15){
        printf("El usuario deseado debe estar compuest0 entre 5 y 15 caracteres.");
    }else{
        usuarioAleatorio(tamanio);
    }
    getch();
}

void generarContrasenia(){
    printf("\n\nGenerador de contrase%cas\n\n", 164);
    printf("Indique la cantidad de caracteres que desea para su contrase%ca: ", 164);
    int tamanio;
    scanf("%d", &tamanio);
    if(tamanio < 8 || tamanio > 50){
        printf("La contrase%ca deseada debe estar compuesta entre 8 y 50 caracteres.", 164);
    }else{
        contraseniaAleatoria(tamanio);
    }
    getch();
}

int myAtoi(char* str){
    // Initialize result
    int res = 0;

    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';

    // return result.
    return res;
}
