#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024


// variables para montura
char* path[25];
char* particion[50];
char* montada[50];
char* dir[50];
int numero[25];
int sizeglobal=0;
int bloqueinicial=0;
int inodo_obtenido=-1;
int inodo_adjuntado = -1;
int bloque_obtenido=-1;
int bloque_creado=-1;
int quepos=-1;
//variable format
int contadorformat=1;

// variables globales para el login
char* logusr;
char* loggrp;
int estoylogueado=-1;

int existeusuario =-1;
int existegrupo =-1;
int existepass =-1;
int incrementable=1;
int incrementablegrp=1;
int iduser=-1;
int idgrp=-1;

void reviso_grupo(char* grupo){
    char buf[100];
    int count=0;
    FILE *arch;
    arch=fopen("/home/jorge/kaya.txt","r");
    while(fgets(buf,sizeof(buf),arch))
    {
        count=count+1;
        verificar_grupo(buf,grupo);
        printf("    ---- %s ",buf);
    }
    printf(" Lines %d ",count);
    fclose(arch);
}

void reviso_user(char* user){
    char buf[100];
    int count=0;
    FILE *arch;
    arch=fopen("/home/jorge/kaya.txt","r");
    while(fgets(buf,sizeof(buf),arch))
    {
        count=count+1;
        verificar_usuario(buf,user);
        printf("    ---- %s ",buf);
    }
    printf(" Lines %d ",count);
    fclose(arch);
}

void reviso_login(char* user,char* pass){
    char buf[100];
    int count=0;
    FILE *arch;
    arch=fopen("/home/jorge/kaya.txt","r");
    while(fgets(buf,sizeof(buf),arch))
    {
        count=count+1;
        Login(buf,user,pass);
        printf("    ---- %s ",buf);
    }
    printf(" Lines %d ",count);
    fclose(arch);
}

void verificar_grupo(char* cadena,char* grupo){
    int longitud = strlen(cadena);
    int i=0;
    int contador=0;
    int carray=0;
    char auxiliar[20];
    int estado = -1;
    int nivel = 0;
    int auxidgrp=-1;
    //int auxidgrp = -1;
    int flag=-1; // 1 es grupo      2 es usuario
    printf("\n Longitud ~ %d",longitud);
    printf("\n          VERIFICAR GRUPO");
    for(i=0;i<=longitud;i++){

        if((cadena[i]==',')||(i==longitud)){

           // printf("\n Encontre coma");
           // printf("\n token %s ",auxiliar);
           // printf("\n %d",i);


            if(nivel==0){
                auxidgrp = convertir_cadena_a_entero(auxiliar);
            }

            if(flag==1){
                printf("\n flag = 1");
                if(strcmp(grupo,auxiliar)==0){
                    existegrupo = 1;
                    idgrp = auxidgrp;
                    printf("\n el grupo existe %d       id %d",existegrupo,idgrp);

                }else{
                    printf("\n el grupo no existe %d",existegrupo);
                    auxidgrp = -1;
                }
            }
            if(strcmp("G",auxiliar)==0){
                printf("\n Encontre un grupo ");
                contador = 0;
                carray++;
                flag = 1;
            }

            nivel++;

            int j=0;
            for(j=0;j<20;j++){
                auxiliar[j]=NULL;
            }
            contador=0;

        }
        else{
            if(cadena[i]=='\n'){

            }else{
                auxiliar[contador] = cadena[i];
                contador++;
            }
        }
    }


}



void verificar_usuario(char* cadena,char* usuario){
    int longitud = strlen(cadena);
    int i=0;
    int contador=0;
    int carray=0;
    char auxiliar[20];
    int flag=-1; // 1 es usuario
    int nivel=0;
    int estado=-1;
    printf("\n Longitud ~ %d",longitud);
    for(i=0;i<=longitud;i++){

        if((cadena[i]==',')||(i==longitud)){

           // printf("\n Encontre coma");
           // printf("\n token %s ",auxiliar);
           // printf("\n %d",i);

            if(nivel==0){
                if(strcmp("0",auxiliar)==0){

                }else{
                    estado = 1;
                    printf("\n Estado = 1");
                }
            }
            if(flag==1 && nivel==3){
                printf("\n flag = 1");
                printf("\n nivel = %d",nivel);
                if(strcmp(usuario,auxiliar)==0){
                    existeusuario = 1;
                    printf("\n el usuario existe %d",existeusuario);

                }else{
                    printf("\n el usuario no existe %d %s",existeusuario,auxiliar);
                }
            }
            if(strcmp("U",auxiliar)==0){
                printf("\n Encontre user ");
                contador = 0;
                carray++;
                flag = 1;
            }

            nivel++;

            int j=0;
            for(j=0;j<20;j++){
                auxiliar[j]=NULL;
            }
            contador=0;

        }
        else{
            if(cadena[i]=='\n'){

            }else{
                auxiliar[contador] = cadena[i];
                contador++;
            }
        }
    }


}



void Login(char* cadena,char* user,char* pass){
    int longitud = strlen(cadena);
    int i=0;
    int contador=0;
    int carray=0;
    int nivel=0;
    int estado = -1;
    char auxiliar[20];
    int auxiduser= -1;
    int auxidgrp = -1;
    int flag=-1; // 1 es grupo      2 es usuario
    int contrasena=-1; // 1 coincide contrasena
    char grupo[10];
    printf("\n Longitud ~ %d",longitud);
    for(i=0;i<=longitud;i++){

        if((cadena[i]==',')||(i==longitud)){

           // printf("\n Encontre coma");
           // printf("\n token %s ",auxiliar);
           // printf("\n %d",i);

            if(nivel==0){
                auxiduser = convertir_cadena_a_entero(auxiliar);
            }
            if(nivel==2){
                strcpy(grupo,auxiliar);
            }
            if(contrasena==1 && nivel==4){
                printf("\n contrasena = 1");
                if(strcmp(pass,auxiliar)==0){
                    printf("\n                 GRUPO AUXILIAR %s ",grupo);
                    reviso_grupo(grupo);
                    iduser = auxiduser;
                    printf("\n          El password es valido....  id %d    grp %d",iduser);
                    existepass = 1;
                }
                else{
                    printf("\n          El password No es valido....");
                    iduser = -1;
                    idgrp = -1;
                }
            }
            if(flag==2 && nivel==3){
                printf("\n flag = 2");
                if(strcmp(user,auxiliar)==0){
                    existeusuario = 1;
                    contrasena = 1;
                    printf("\n      el usuario existe %d     flag contrasena %d",existeusuario,contrasena);
                }else{
                    printf("\n el usuario no existe     flag contrasena %d",contrasena);
                }
            }
            if(strcmp("U",auxiliar)==0){
                printf("\n Encontre user ");
                contador = 0;
                carray++;
                flag = 2;
            }

            nivel++;

            int j=0;
            for(j=0;j<20;j++){
                auxiliar[j]=NULL;
            }
            contador=0;

        }
        else{
            if(cadena[i]=='\n'){

            }else{
                auxiliar[contador] = cadena[i];
                contador++;
            }
        }
    }


}

void mkusr(char* user,char* pass,char* grupo){
    existeusuario=-1;
    existegrupo=-1;
    existepass=-1;
    reviso_user(user);
    reviso_grupo(grupo);
    if(existeusuario==-1){
        if(strlen(user)<=10){
            if(strlen(pass)<=10){
                if(existegrupo!=-1){
                    escribir_usuario(user,pass,grupo);
                    printf("\n El usuario se creo exitosamente");
                }
                else{
                    printf("\n El grupo no existe");
                }

            }
            else{
                printf("\n  Password Max 10. caracteres ");
            }
        }
        else{
            printf("\n User Max 10. caracteres \n");
        }
    }
    else{
        printf("\n Usuario Ya existe \n");
    }
}


void mkgrp(char* grupo){
    existeusuario=-1;
    existegrupo=-1;
    existepass=-1;

    reviso_grupo(grupo);

    if(existegrupo==-1){
        if(strlen(grupo)<=10){
          printf("\n El grupo se creo exitosamente");
          escribir_grupo(grupo);
        }else{
            printf("\n Grupo Max 10. caracteres \n");
        }
    }else{
        printf("\n Grupo Ya existe \n");
    }
}

void escribir_usuario(char* user,char* pass,char* grupo){
    FILE* arch;
    char auxp[18];
    incrementable++;
    arch = fopen("/home/jorge/kaya.txt","a");
    sprintf(auxp,"%d",incrementable);
    fprintf(arch,auxp);
    fprintf(arch,",U,");
    sprintf(auxp,"%s",grupo);
    fprintf(arch,auxp);
    fprintf(arch,",");
    sprintf(auxp,"%s",user);
    fprintf(arch,auxp);
    fprintf(arch,",");
    sprintf(auxp,"%s",pass);
    fprintf(arch,auxp);
    fprintf(arch,"\n");
    fclose(arch);
}

void escribir_grupo(char* grupo){
    FILE* arch;
    char auxp[18];
    incrementablegrp++;
    arch = fopen("/home/jorge/kaya.txt","a");
    sprintf(auxp,"%d",incrementablegrp);
    fprintf(arch,auxp);
    fprintf(arch,",G,");
    sprintf(auxp,"%s",grupo);
    fprintf(arch,auxp);
    fprintf(arch,"\n");
    fclose(arch);
}

//-------------------------------------------------------------------------------------------------

int convertir_cadena_a_entero(char *cad)
{   int num;
    num = atoi(cad);
    return num;
}

char* darid(char*dir[50],char* particion[50],char* montada[50],char* newpath,char* newpart){
    int i=0;
    int flag=0;
    char* vacio="";
    char* id="";
    printf("\n id = %s",newpart);
    for(i=0;i<51;i++){
        if(strcmp(newpath,dir[i])==0 && strcmp(newpart,particion[i])==0){
            id = montada[i];
            printf("\n id encontrado...");
            flag=1;
            break;
        }
    }
    if(flag==0){
        printf("\n No existe id correlativo...");
        //id = "";
    }
    return id;

}

void desmontar(char*dir[50],char* particion[50],char* montada[50],char* newpart){
    int i=0;
    int flag=0;
    char* vacio="";
    printf("\n id = %s",newpart);
    for(i=0;i<51;i++){
        if(strcmp(newpart,montada[i])==0){
            particion[i] = strdup(vacio);
            montada[i] = strdup(vacio);
            dir[i] = strdup(vacio);
            printf("\n desmontada exitosa...");
            flag=1;
            break;
        }else{
            printf("\n montada[%d] ...... %s",i,montada[i]);
            printf("\n particion[%d] .... %s",i,particion[i]);
            printf("\n dir[%d] .......... %s",i,dir[i]);
            printf("\n i ................ %d",i);
        }
    }
    if(flag==0){
        printf("\n No existe id correlativo...");
    }
}

int verificar_particion(char* particion[50], char* newpart){
    int i=0;
    int bandera=0;
    for(i=0;i<51;i++){
        if(strcmp(newpart,particion[i])==0){
            bandera = 1;
            break;
        }
    }
    return bandera;
}

char* darpath(char* montada[50],char* particion[50],char* newid){
    int i=0;
    char* retorno;
    for(i=0;i<51;i++){
        if(strcmp(newid,montada[i])==0){
            retorno = particion[i];
            printf("\n newid %s",newid);
            printf("\n montada[%d] %s",i,montada[i]);
            printf("\n particion[%d] %s",i,particion[i]);
            printf("\n retorno %s",retorno);
            printf("\n i %d",i);

            break;
        }
    }
    if(retorno==NULL){
        printf("\n La particion montada no existe");
    }
    return retorno;
}

char* dardirectory(char* montada[50],char* dir[50],char* newid){
    int i=0;
    char* retorno="-1";
    for(i=0;i<51;i++){
        if(strcmp(newid,montada[i])==0){
            retorno = dir[i];
            printf("\n montada[%d] %s",i,montada[i]);
            printf("\n i %d",i);
            printf("\n DarDirectory---- %s",retorno);
            break;
        }
    }
    if(retorno==NULL){
        printf("\n La particion montada no existe");
    }
    return retorno;
}

void mount(char*dir[50],char* path[25],char* particion[50],char* montada[50], int numero[25],char* newpath,char* newpart){

    printf("\n montando....");
    // 97 = a       122 = z
    int existe = 0;
    int i=0;
    int pospart=30;
    int letra = 0;
    char concatenar[10];
    char aux[10];

    existe = existename(newpath,newpart);

    if(existe==1){

        for(i=0;i<26;i++){
            if(strcmp(newpath,path[i])==0){
                pospart = i;
                printf("\n path[%d] %s",i,path[i]);
                printf("\n newpath %s",newpath);
                printf("\n Se encontro path en la posicion %d ",pospart);
                break;
            }
            else{
                //printf("\n encontrando...");
            }
        }
        // existe path

        if(pospart!=30){
            letra = pospart+97;
            printf("\n Letra: %c",letra);

            strcpy(concatenar,"vd");
            sprintf(aux,"%c",letra);
            strcat(concatenar,aux);


            numero[pospart]=numero[pospart]+1;
            sprintf(aux,"%d",numero[pospart]);
            strcat(concatenar,aux);

            int j=0;
            char *p= concatenar;
            char *sector=newpart;
            char *dd= newpath;
            for(j=0;j<51;j++){
                if(strcmp("",montada[j])==0){
                        montada[j]=strdup(p);
                        particion[j]=strdup(sector);
                        dir[j]=strdup(dd);
                        printf("\n La particion se monto correctamente.... %d %s",j,particion[j]);
                        break;
                }
            }

            printf("\n name: %s",concatenar);
            printf("\n p %s",p);

        }
        // no existe path
        else if(pospart==30){

            for(i=0;i<26;i++){
                char *alu = newpath;
                if(strcmp("",path[i])==0){
                    path[i] = strdup(alu);
                    printf("\n Inserte path i = %d",i);
                    letra = i+97;
                    printf("\n 30 Letra: %c",letra);

                    numero[i]=1;

                    strcpy(concatenar,"vd");
                    sprintf(aux,"%c",letra);
                    strcat(concatenar,aux);

                    aux[10]=NULL;
                    sprintf(aux,"%d",1);
                    strcat(concatenar,aux);

                    int j=0;
                    char *p= concatenar;
                    char*dd= newpath;
                    for(j=0;j<51;j++){
                        if(strcmp("",montada[j])==0){
                                montada[j]=strdup(p);
                                particion[j]=strdup(newpart);
                                dir[j]=strdup(dd);
                                printf("\n La particion se monto correctamente.... %d %s",j,particion[j]);
                                break;
                        }

                    }

                    printf("\n name: %s",concatenar);
                    printf("\n p %s",p);
                    break;
                }
            }

        }


    }
    else{

        printf("\n Mount: La particion no existe ");
    }


}

void checkcreatedir(char* path){
    int lon = strlen(path);
    int i;
    char* cadena;
    char* directorio;
    int longarchivo=0;
    int estado=0;

    cadena = malloc(strlen(path)); // tamaño de comando mas 1
    strcpy(cadena,path);             // copia a cadena el valor de comando

    directorio = malloc(strlen(path));
    strcpy(directorio,path);
    //reconozco el nombre del archivo

    for(i=lon-1;i>0;i--){
        switch(estado){
            case 0:
            printf("\n estado 0 posicion %d caracter %c",i,cadena[i]);
            if(cadena[i]>=48 && cadena[i]<=122){        //0-9 a-z
                estado=0;
                longarchivo=longarchivo+1;

            }else if(cadena[i]==45 || cadena[i]==46){   // -  y .
                estado=0;
                longarchivo=longarchivo+1;

            }else if(cadena[i]==32){
                estado=0;
                longarchivo=longarchivo+1;

            }else if(cadena[i]==47){                    // slash (/)
                estado=1;
            }
            break;
        }
    }

    //char dir[longarchivo-1];
    //char cleandir[longarchivo-1];

    char dir[100];
    char cleandir[100];
    for(i=0;i<lon-longarchivo;i++){
        dir[i]=directorio[i];
    }
    strcpy(cleandir,dir);
    printf("\n Long archivo %d STRLEN %d",longarchivo,lon);
    printf("\n Directorio %s",cleandir);
    //int status;
    //status = mkdir(cleandir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    char sys[]="mkdir -p ";
    strcat(sys,"'");
    strcat(sys,cleandir);
    strcat(sys,"'");
    system(sys);

}

int checkpath(char* path){
    FILE *f;
    int bandera=0;
    f = fopen(path, "r");
    if(!f){
       printf("\n Error: No existe el archivo \n");
       bandera=0;
    }
    else{
       printf("\n Si existe el archivo \n");
       bandera=1;
    }

    return bandera;
}

int analizador(char* comando){
    char* cadena;       // variable que concatena la linea de comando con  el simbolo "$"
    char* simbolo="$";  // variable que contiene el simbolo "$"

    cadena = malloc(strlen(comando)+1); // tamaño de comando mas 1
    strcpy(cadena,comando);             // copia a cadena el valor de comando
    strcat(cadena,simbolo);             // concatena a cadena el simbolo "$"
    int lon = strlen(cadena);             // Longitud de la cadena
    //printf("\n comando %s",comando);    // imprime el comando original
    //printf("\n cadena  %s",cadena);     // imprime el comando + "$"
    //printf("\n Longitud %d",lon);         // imprime la longitud de cadena

//    int i;
//    for(i=0;i<lon;i++){
//        cadena[i] = tolower(cadena[i]);
//    }
    // printf("\n cadena en minusculas %s\n", cadena); // muestra  la cadena en minusculas

    //analizador lexico de entrada
    int estado=0;       // estado del automata
    char* palabra;      // variable que concatena en el automata
    char prueba [lon];  // array donde se concatenan las letras
    int counter = 0;
    int recursivo=-1;
    int action=0;       // 1 = mkdisk       2 = rmdisk      3 = fdisk    4 = mount       5 = unmount         6 = rep
                        // 7 = exec         8 = fdisk  (add)  9 = fdisk  (delete)    10 = fdisk (crear)
    //variables para mkdisk
    char mkauxsize [100]; //auxiliar de tamaño
    int mksize=0;       // tamaño del disco
    int mkunit=-1;       // 1 = kilo 2 = mega
    char mkpath [100];
    strcpy(mkpath,"");

    //variables para rmdisk
    char rmpath [100];
    strcpy(rmpath,"");

    //variables para fdisk
    int fsize=0;
    int funit=4;        // 1 = byte 2 = kilo 3 = mega
    char fauxsize [100];
    char fpath[100];
    strcpy(fpath,"");
    int ftype=4;        // 1 = primaria 2 = extendida 3 = logica
    char fname[16];
    strcpy(fname,"");
    int fdelete=0;      // 1 = fast 2 = full
    char fauxadd [100];
    int fadd=0;

    //variables para mount
    char mopath [100];
    strcpy(mopath,"");
    char moname [16];
    strcpy(moname,"");

    //variables para unmount
    char unid [16];
    strcpy(unid,"");

    //variable para rep
    char repname[16];
    strcpy(repname,"");
    char repid[16];
    strcpy(repid,"");
    char reppath[100];
    strcpy(reppath,"");

    //variables para fit
    int ffit=0; // 1 best 2 first 3 worst

    //variable para exec
    char exepath[100];
    strcpy(exepath,"");

    //variable para SEGUNDA FASE
    char id2[16];
    int type2=-1;    // 1 = fast 2 = full
    char addaux2[16];
    int add2=-1;
    int unit2=-1;    // 1 = bit  2 = kilo 3 = Mega
    char usr2[10];
    char pwd2[10];
    char name2[20];
    char grp2[10];
    char path2[100];
    char ugoaux2[16];
    int ugo2=-1;
    char sizeaux2[16];
    int size2=-1;
    char cont2[100];
    char dest2[100];
    char iddest2[16];
    char ruta2[100];
    palabra = malloc(lon);
    int j;              // variable del ciclo
    int d;
    for(j=0;j<=lon;j++){
        switch(estado){
            case 0: //detecto todas las posibles acciones a realizar mkdisk etc
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=0;
                    //printf("\n Estado 0: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    //printf("\n palabra: ");
                    //for(d=0;d<=j;d++){
                    //    printf("%c",prueba[d]);
                    //}
                    counter++;
                }
                else if(cadena[j]==45){                        // guion alto
                  //   printf("\n detecte un -");
                        //pasa todo a minuscula xD
                        int i;
                        for(i=0;i<counter;i++){
                            prueba[i] = tolower(prueba[i]);
                        }

                         if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='d') && (prueba[3]=='i') && (prueba[4]=='s') && (prueba[5]=='k')){
                            printf("\n comando: mkdisk");
                            action = 1;
                            estado = 1;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }

                         }
                         else if((prueba[0]=='r') && (prueba[1]=='m') && (prueba[2]=='d') && (prueba[3]=='i') && (prueba[4]=='s') && (prueba[5]=='k')){
                            printf("\n comando: rmdisk");
                            action = 2;
                            estado = 9;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='f') && (prueba[1]=='d') && (prueba[2]=='i') && (prueba[3]=='s') && (prueba[4]=='k')){
                            printf("\n comando: fdisk");
                            action = 3;
                            estado = 34;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='m') && (prueba[1]=='o') && (prueba[2]=='u') && (prueba[3]=='n') && (prueba[4]=='t')){
                            printf("\n comando: mount");
                            action = 4;
                            estado = 22;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='n') && (prueba[2]=='m') && (prueba[3]=='o') && (prueba[4]=='u') && (prueba[5]=='n') && (prueba[6]=='t')){
                            printf("\n comando: unmount");
                            action = 5;
                            estado = 26;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }

                         else if((prueba[0]=='r') && (prueba[1]=='e') && (prueba[2]=='p')){
                            printf("\n comando: rep");
                            action = 6;
                            estado = 28;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='e') && (prueba[1]=='x') && (prueba[2]=='e') && (prueba[3]=='c')){
                            printf("\n comando: exec");
                            action = 7;
                            estado = 60;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }


                         //Segunda Fase

                         else if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='f') && (prueba[3]=='s')){
                            printf("\n comando: mkfs");
                            action = 20;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='l') && (prueba[1]=='o') && (prueba[2]=='g') && (prueba[3]=='i') && (prueba[4]=='n')){
                            printf("\n comando: login");
                            action = 21;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }

                         else if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='g') && (prueba[3]=='r') && (prueba[4]=='p')){
                            printf("\n comando: mkgrp");
                            action = 23;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='r') && (prueba[1]=='m') && (prueba[2]=='g') && (prueba[3]=='r') && (prueba[4]=='p')){
                            printf("\n comando: rmgrp");
                            action = 24;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='u') && (prueba[3]=='s') && (prueba[4]=='r')){
                            printf("\n comando: mkusr");
                            action = 25;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='r') && (prueba[1]=='m') && (prueba[2]=='u') && (prueba[3]=='s') && (prueba[4]=='r')){
                            printf("\n comando: rmusr");
                            action = 26;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='h') && (prueba[2]=='m') && (prueba[3]=='o') && (prueba[4]=='d')){
                            printf("\n comando: chmod");
                            action = 27;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='f') && (prueba[3]=='i') && (prueba[4]=='l') && (prueba[5]=='e')){
                            printf("\n comando: mkfile");
                            action = 28;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='a') && (prueba[2]=='t')){
                            printf("\n comando: cat");
                            action = 29;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='r') && (prueba[1]=='e') && (prueba[2]=='m')){
                            printf("\n comando: rem");
                            action = 30;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='e') && (prueba[1]=='d') && (prueba[2]=='i') && (prueba[3]=='t')){
                            printf("\n comando: edit");
                            action = 31;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='r') && (prueba[1]=='e') && (prueba[2]=='n')){
                            printf("\n comando: ren");
                            action = 32;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='m') && (prueba[1]=='k') && (prueba[2]=='d') && (prueba[3]=='i') && (prueba[4]=='r')){
                            printf("\n comando: mkdir");
                            action = 33;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='p')){
                            printf("\n comando: cp");
                            action = 34;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='m') && (prueba[1]=='v')){
                            printf("\n comando: mv");
                            action = 35;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='f') && (prueba[1]=='i') && (prueba[2]=='n') && (prueba[3]=='d')){
                            printf("\n comando: find");
                            action = 36;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='h') && (prueba[2]=='o') && (prueba[3]=='w') && (prueba[4]=='n')){
                            printf("\n comando: chown");
                            action = 37;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='h') && (prueba[2]=='g') && (prueba[3]=='r') && (prueba[4]=='p')){
                            printf("\n comando: chgrp");
                            action = 38;
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }


                         else {
                            printf("\n comando: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=0;
                     //printf("\n vacio");
                }

                else if(cadena[j]==35){                        // #
                     estado=8;
                     printf("comentarios: ");
                }
                //****************LOGOUT
                else if(cadena[j]=='\n' || cadena[j]=='$'){
                    //pasa todo a minuscula xD
                    int i;
                    for(i=0;i<counter;i++){
                        prueba[i] = tolower(prueba[i]);
                    }

                    if((prueba[0]=='l') && (prueba[1]=='o') && (prueba[2]=='g') && (prueba[3]=='o') && (prueba[4]=='u') && (prueba[5]=='t')){
                       printf("\n comando: logout");
                       action = 22;
                       counter = 0;
                       int k;
                       for(k=0;k<lon;k++){
                            prueba[k]=NULL;
                       }

                       printf("    ACTION: %d   COMANDO \n",action);
                       printf("        ~Cerro sesion %d \n",iduser);
                       iduser = -1;
                       idgrp = -1;

                       printf("\n LOGOUT ~ ");
                    }
                }

            break;

            case 1: //detecta los parametros para el comando mkdisk (size,unit,path)
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=1;
                    //printf("\n Estado 1: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==58){                        // igual
                     //printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='s') && (prueba[1]=='i') && (prueba[2]=='z') && (prueba[3]=='e')){
                            printf("\n parametro: size");
                            estado = 2;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='n') && (prueba[2]=='i') && (prueba[3]=='t')){
                            printf("\n parametro: unit");
                            estado = 3;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 4;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }

                         else {
                            printf("\n parameter: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=1;
                     //printf("\n vacio");
                }
                else {
                    printf(" simbolo erroneo ");

                }

            break;

            case 2: //detecta los numeros para el parametro size
                //printf("\n Posicion %d",j);

                if((cadena[j]>=48) && (cadena[j]<=57)){    // numeros 0-9
                    estado=2;
                    //printf("\n Estado 2: numero %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=2;
                     //printf("\n vacio");
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n size: ");

                     strcpy(mkauxsize,prueba);

                     printf("\n  ");
                     mksize = convertir_cadena_a_entero(mkauxsize);
                     //printf(" convertido: %d",mksize);
                     //printf("\n fin");
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                     estado = 1;
                     printf("\n size: ");

                     strcpy(mkauxsize,prueba);

                     mksize = convertir_cadena_a_entero(mkauxsize);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(mkauxsize,prueba);

                    mksize = convertir_cadena_a_entero(mkauxsize);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;

                     strcpy(mkauxsize,prueba);

                     mksize = convertir_cadena_a_entero(mkauxsize);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else{
                    printf("\n parametro: error size rango no valido");
                }

            break;

            case 3: // detecta las unidades k y m
                //printf("\n Estado 3 Posicion %d",j);

                if(cadena[j]=='k' || cadena[j]=='K'){
                    printf("\n unit: k");
                    mkunit = 1;
                }
                else if(cadena[j]=='m' || cadena[j]=='M'){
                    printf("\n unit: m");
                    mkunit = 2;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=3;
                     printf("\n vacio");
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n fin");
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                     estado = 1;
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else {
                    printf("\n parametro: unit error medida no valida");
                }


            break;

            case 4: // decide si el path lleva espacios o no
                //printf("\n Estado 4 Posicion %d",j);

                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 6;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=4;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(mkpath,prueba);

                     printf("%d counter ",counter);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=4;
                 }
                else if(cadena[j]=='-'){                    // -
                    //printf("\n direccion: ");

                    strcpy(mkpath,prueba);

                    estado=1;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(mkpath,prueba);

                    printf(" \n %s using s \n ",mkpath);
                    printf("    size path %d",strlen(mkpath));
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(mkpath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
               }
            break;

            case 5:
                // 1 = mkdisk       2 = rmdisk      3 = fdisk    4 = mount       5 = unmount         6 = rep
                // 8 = fdisk  (add)  9 = fdisk  (delete)    10 = fdisk (crear)
                printf("\n Estado 5 Posicion: %d",j);
                int i;
                if(action==1){

                    printf("    ACTION: %d COMANDO MKDISK SIZE = %d UNIT = %d PATH %d",action,mksize,mkunit,strlen(mkpath));
                    printf("%s",mkpath);
                    int flag=0;

                    flag = checkpath(mkpath);
                    if(flag==0){
                        checkcreatedir(mkpath);
                    }
                    if(mksize>0){
                        mkdisk(mkpath,mksize,mkunit);
                    }
                    else{
                        printf("\n  TAMAÑO PARA DISCO INVALIDO ");
                    }

                }
                else if(action==2){
                    printf("    ACTION: %d COMANDO RMDISK PATH ",action);
                    printf("%s",rmpath);
                    int flag=0;
                    flag = checkpath(rmpath);

                    if(flag==1){
                        rmdisk(rmpath);
                    }else{
                        printf("\n Error disco no existe \n ");
                    }

                }
                else if(action==3){
                    printf("    ACTION: %d COMANDO FDISK",action);
                }
                else if(action==4){
                    printf("    ACTION: %d COMANDO MOUNT PATH ",action);
                    printf("%s",mopath);
                    printf(" NAME =  ");
                    printf("%s",moname);

                    int flag=0;
                    flag = checkpath(mopath);

                    if(flag==1){
//                        if(existe==1){
                            mount(dir,path,particion,montada,numero,mopath,moname);
  //                      }else{
  //                          printf("\n Error no existe particion ");
  //                      }


                    }else
                    {
                        printf("\n Error disco no existe \n ");
                    }


                }
                else if(action==5){
                    printf("    ACTION: %d COMANDO UNMOUNT ID = ",action);
                    printf("%s",unid);

                    char* aux = darpath(montada,particion,unid);

                    desmontar(dir,particion,montada,unid);
                    int k=0;
                    for(k=0;k<51;k++){
                        printf("\n %d particion  %s direc %s montada %s",k,particion[k],dir[k],montada[k]);
                    }

                    char* aux1 = darpath(montada,particion,unid);

                }
                else if(action==6){
                    printf("    ACTION: %d COMANDO REP NAME = ",action);
                    printf("%s",repname);
                    printf(" PATH ");
                    printf("%s",reppath);
                    printf(" ID = ");
                    printf("%s",repid);
                    checkcreatedir(reppath);

                    int flag = 0;

                    /*int i;
                    for(i=0;i<counter;i++){
                        prueba[i] = tolower(prueba[i]);
                    }*/

                        if(strcmp(repname,"mbr")==0 || strcmp(repname,"MBR")==0){
                            printf("\n Report MBR");
                            char* auxdisk = dardirectory(montada,dir,repid);
                            flag = checkpath(auxdisk);

                            if(flag==1){
                                if(strcmp(auxdisk,"-1")!=0){
                                graphmbr(auxdisk,reppath);
                                graphebr(auxdisk,reppath);
                                }else{
                                    printf("\n ID invalido");
                                }

                            }else{

                                printf("\n ID invalido");
                            }

                        }else if(strcmp(repname,"disk")==0 || strcmp(repname,"DISK")==0){
                            printf("\n Report DISK");
                            char* auxdisk = dardirectory(montada,dir,repid);
                            flag = checkpath(auxdisk);

                            if(flag==1){
                                if(strcmp(auxdisk,"-1")!=0){
                                    graphdisk(auxdisk,reppath);
                                }else{
                                    printf("\n ID invalido");
                                }

                            }else{

                                printf("\n ID invalido");
                            }

                        }else if(strcmp(repname,"inode")==0 || strcmp(repname,"INODE")==0){
   /*                         char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            //graphInodo(auxdisk,reppath,part);
                            //graphInodo("/home/jorge/SS.dsk","/home/jorge/Inodo.png","part1");
*/
                        }else if(strcmp(repname,"block")==0 || strcmp(repname,"BLOCK")==0){
                        /*    char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            graphBloque(auxdisk,reppath,part);
*/
                        }else if(strcmp(repname,"bm_inode")==0 || strcmp(repname,"BM_INODE")==0){
/*                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapbitInodo(auxdisk,reppath,part);

   */                     }else if(strcmp(repname,"bm_block")==0 || strcmp(repname,"BM_BLOCK")==0){
      /*                      char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapbitBloque(auxdisk,reppath,part);
*/
                        }else if(strcmp(repname,"tree")==0 || strcmp(repname,"TREE")==0){
   /*                         char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            graphThree(auxdisk,reppath,part);
*/
                        }else if(strcmp(repname,"sb")==0 || strcmp(repname,"SB")==0){
     /*                       char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapSuperBloque(auxdisk,reppath,part);
*/
                        }else if(strcmp(repname,"file")==0 || strcmp(repname,"FILE")==0){
   /*                         char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            leer_archivo(auxdisk,part,ruta2,iduser,idgrp);
                            grapharchivo(part);
*/
                        }

                }
                else if(action==7){
                    printf("    ACTION: %d COMANDO EXEC PATH ",action);
                    printf("%s",exepath);
                    int flag=0;
                    flag = checkpath(exepath);

                    if(flag==1){
                        leercode(exepath);
                    }else{
                        printf("\n NO existe Script \n ");
                    }

                }
                else if(action==8){
                    printf("    ACTION: %d COMANDO FDISK (ADD) ADD = %d UNIT = %d PATH ",action,fadd,funit);
                    printf("%s",fpath);
                    printf(" NAME= %s",fname);
                    int flag = checkpath(fpath);

                    if(flag==1){
                    if(funit==4){ funit=0;}

                        if(fadd>0){
                           printf("\n add positivo   agregando...");
                           sumar(fpath,fname,funit,fadd);

                        }else{
                           printf("\n add eliminando   agregando...");
                           fadd=fadd*-1;
                           quitar(fpath,fname,funit,fadd);
                        }

                    }else{
                        printf("\n Directorio invalido");
                    }


                }
                else if(action==9){
                    printf("    ACTION: %d COMANDO FDISK (DELETE) PATH ",action);
                    printf("%s",fpath);
                    printf(" NAME= %s",fname);
                    printf(" DELETE= %d",fdelete);
                    int flag = checkpath(fpath);
                    if(flag==1){
                    char res;
                    printf("\n Desea eliminar las particiones? s/n");
                    gets(&res);
                        if(res=='s'){
                            //darid(dir,particion,montada,fpath,fname);
                            if(fdelete==1){
                                deletefast(fpath,fname);
                                deletefast_logic(fpath,fname);
                            }
                            if(fdelete==2){
                                deletefull(fpath,fname);
                                deletefull_logic(fpath,fname);

                            }

                        }else{
                            printf("\n Se cancelo eliminado de particion");
                        }

                    }else{
                        printf("\n Directorio invalido");
                    }

                }
                else if(action==10){
                    printf("    ACTION: %d COMANDO FDISK (CREATE) SIZE=%d UNIT= %d TYPE=%d  FIT=%d PATH ",action,fsize,funit,ftype,ffit);
                    printf("%s",fpath);
                    printf(" NAME= %s",fname);
                    char ajuste;

                    int existe = 0;
                    existe = existename(fpath,fname);
                    printf(" existe name? %d",existe);


                    if(ftype==4){
                        ftype = 1;
                    }
                    if(ffit==0 || ffit==3){
                       ajuste = 'W';
                    }

                    else if(ffit==1){
                       ajuste = 'B';
                    }

                    else if(ffit==2){
                       ajuste = 'F';
                    }else{
                        printf("\n Ajuste Invalido se aplicara el Peor ajuste ");
                    }

                    if(fsize>0){

                        if((funit==4) || (funit==1) || (funit==2) || (funit==3)){
                            if(funit==4){   funit=0; }
                            int flag=0;
                            flag=checkpath(fpath);


                            if(existe==0){
                                if(flag==1){

                                        if((ftype==1)||(ftype==2)){

                                            add_particion(fpath,ftype,fsize,fname,ajuste,funit);


                                        }else if(ftype==3){
                                            add_logica(fpath,ftype,fsize,fname,ajuste,funit);
                                        }

                                }
                                else{
                                    printf("\n EL ARCHIVO NO EXISTE");
                                }

                            }// if existe = 0
                            else{
                                printf("Nombre de particion repetida... \n ");

                            }
                        } // if funit
                        else{
                            printf("\n EL VALOR DE LA UNIDAD ES INVALIDO");
                        }
                    }
                    else{
                        printf("\n EL TAMAÑO PARA PARTICION INVALIDO");
                    }
                }else if(action==20){
                    //printf("    ACTION: %d COMANDO FDISK (CREATE) SIZE=%d UNIT= %d TYPE=%d  FIT=%d PATH ",action,fsize,funit,ftype,ffit);
                    printf("    ACTION: %d   COMANDO \n",action);
                    printf("        ~ID: %s",id2);
                    printf("        ~TYPE: %d \n",type2);
                    printf("        ~UNIT: %d \n",unit2);
                    printf("        ~ADD: %d \n",add2);
                    char* auxdisk = dardirectory(montada,dir,id2);
                    char* part = darpath(montada,particion,id2);
                    printf("\n          path %s         particion %s",auxdisk,part);
                    //mkfs(auxdisk,part);
                    if(contadorformat==1){
                     //   raizu();
                    }else{
                        //int ajuste = fit_particion(auxdisk,part);
                        //eliminar(auxdisk,part,"/users.txt",1,1);
                        //crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/kaya.txt",1,1,1,0);
                    }
                    contadorformat++;
                  /*printf("        ~USR: %s \n",usr2);
                    printf("        ~PWD: %s \n ",pwd2);
                    printf("        ~NAME: %s \n ",name2);
                    printf("        ~GRP: %s \n ",grp2);
                    printf("        ~PATH: %s \n ",path2);
                    printf("        ~UGO: %d \n ",ugo2);
                    printf("        ~SIZE: %d \n ",size2);
                    printf("        ~CONT: %s \n ",cont2);
                    printf("        ~DEST: %s \n ",dest2);
                    printf("        ~IDDEST: %s \n ",iddest2);
                    printf("        ~RECURSIVO:%d \n",recursivo);*/
                }else if(action==21){
                    printf("    ACTION: %d   COMANDO \n",action);
                    printf("        ~USR: %s \n",usr2);
                    printf("        ~PWD: %s \n ",pwd2);
                    iduser = -1;
                    idgrp = -1;
                    reviso_login(usr2,pwd2);
                    if(iduser !=-1){
                        printf("\n USUARIO LOGUEADO ~");
                    }else{
                        printf("\n USUARIO NO LOGUEADO");
                    }
                }else if(action==23){
                    if(iduser == 1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~GRP: %s \n ",grp2);
                        mkgrp(grp2);

               /*         char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);

                        int ajuste = fit_particion(auxdisk,part);
                        eliminar(auxdisk,part,"/users.txt",1,1);
                        crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/kaya.txt",1,1,1,0);
                 */   }else{
                        printf("\n      NO ES USUARIO ROOT");
                    }

                }else if(action==25){
                    if(iduser == 1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~USR: %s \n ",usr2);
                        printf("        ~GRP: %s \n ",grp2);
                        printf("        ~PWD: %s \n ",pwd2);
                        mkusr(usr2,pwd2,grp2);

                       /* char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);

                        //int ajuste = fit_particion(auxdisk,part);
                       // eliminar(auxdisk,part,"/users.txt",1,1);
                    */ //crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/kaya.txt",1,1,1,0);
                    }else{
                        printf("\n      NO ES USUARIO ROOT");
                    }
                }else if(action==28){
                    if(iduser != -1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);
                        printf("        ~RECURSIVO:%d \n",recursivo);
                        printf("        ~SIZE: %d \n ",size2);
                        printf("        ~CONT: %s \n ",cont2);

                        /*char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
*/
                        //printf("\n          path %s         particion %s        fit %d",auxdisk,part,ajuste);
                        if(size2==-1){
//                             crear_archivo(auxdisk,part,ajuste,path2,cont2,iduser,idgrp,recursivo,0);
                        }else{
   //                          archivo_numeros(size2);
      //                       crear_archivo(auxdisk,part,ajuste,path2,"/home/jorge/numeros.txt",iduser,idgrp,recursivo,0);
                        }

                    }
                    else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==29){
                    if(iduser != -1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        printf("\n          path %s         particion %s",auxdisk,part);

                        //leer_archivo(auxdisk,part,path2,iduser,idgrp);
                    }else{
                         printf("\n      NO SE HA LOGUEADO");
                    }

                }else if(action==30){
                    if(iduser != -1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        printf("\n          path %s         particion %s",auxdisk,part);
                        //eliminar(auxdisk,part,path2,iduser,idgrp);
                    }
                    else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==31){
                    if(iduser != -1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);
                        printf("        ~SIZE: %d \n ",size2);
                        printf("        ~CONT: %s \n ",cont2);

                     /*   char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
*/
//                        printf("\n          path %s         particion %s        fit %d",auxdisk,part,ajuste);
                        if(size2==-1){
   //                          eliminar(auxdisk,part,path2,iduser,idgrp);
      //                       crear_archivo(auxdisk,part,ajuste,path2,cont2,iduser,idgrp,0,0);
                        }else{
         //                    eliminar(auxdisk,part,path2,iduser,idgrp);
            //                 archivo_numeros(size2);
               //              crear_archivo(auxdisk,part,ajuste,path2,"/home/jorge/numeros.txt",iduser,idgrp,0,0);
                        }

                    }
                    else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==32){
                    if(iduser!=-1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);
                        printf("        ~NAME: %s \n ",name2);

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        //renombrar(auxdisk,part,name2,path2,iduser,idgrp);
                    }else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==33){
                    if(iduser!=-1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);

                      /*  char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
                        crear_directorio(auxdisk,part,ajuste,path2,iduser,idgrp,recursivo);
                    */}else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==35){
                    if(iduser!=-1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);
                        printf("        ~DEST: %s \n ",dest2);
                        printf("        ~IDDEST: %s \n ",iddest2);

                        /*char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
                        mover(auxdisk,path2,part,dest2,ajuste,iduser,idgrp);
                    */}else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }

                estado=70;
                //variables mkdisk
                action=0;
                mksize=0;
                mkunit=0;
                mkpath[100]=NULL;
                //variables rmdisk
                rmpath[150]=NULL;
            break;

            case 6:
                //printf("\n Estado 6 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=6;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=6;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(mkpath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=100;
                    //printf("\n direccion: ");

                    strcpy(mkpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='-'){                    // -
                    //printf("\n direccion: ");

                    strcpy(mkpath,prueba);

                    estado=1;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(mkpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(mkpath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }

            break;


            case 8:
                //printf("\n Estado 8 Posicion xD %d",j);

                if((cadena[j]>=37) && (cadena[j]<=165)){    // letras a-z
                    estado=8;
                    prueba[counter] = cadena[j];
                    counter++;
                }else if(cadena[j]==32){                    // espacio
                    estado=8;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]=='\n' || cadena[j]=='$'){                     // enter

                    printf("\n comment : \n %s \n",prueba);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
            break;

            case 9: //detecta los parametros para el comando rmdisk (path)
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=9;
                    //printf("\n Estado 9: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if((cadena[j]==58)){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 10;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else {
                            printf("\n parametro invalido");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=9;
                     printf("\n vacio");
                }
                else{
                    printf("\n simbolo erroneo ");
                }

            break;



            case 10: // decide si el path lleva espacios o no rmdisk
                //printf("\n Estado 10 Posicion %d",j);

                if(cadena[j]=='"'){
                    //printf("\n con espacios");
                    estado = 11;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=10;
                    //printf("\n %c",cadena[i]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(rmpath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=10;
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(rmpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(rmpath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;


            case 11: // path del comando rmdisk con espacios
                //printf("\n Estado 11 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=11;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=11;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(rmpath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=105;
                    printf("\n direccion: ");

                    strcpy(rmpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(rmpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(rmpath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 22: // comando mount parametros
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=22;
                  //  printf("\n Estado 22: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if((cadena[j]==58)){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='n') && (prueba[1]=='a') && (prueba[2]=='m') && (prueba[3]=='e')){
                            printf("\n parametro: name");
                            estado = 25;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 23;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }

                         else {
                            printf("\n parameter: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=22;
                     printf("\n vacio");
                }
                else{
                    printf("\n simbolo erroneo ");
                }
            break;

            case 23: //detectar el path del comando mount
                //printf("\n Estado 23 Posicion %d",j);

                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 24;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=23;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(mopath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=23;
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(mopath,prueba);

                    estado=22;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(mopath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(mopath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;


            case 24:
                //printf("\n Estado 24 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=24;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=24;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(mopath,prueba);

                    estado=22;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(mopath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(mopath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==34){                     // "
                    estado=80;
                    printf("\n direccion: ");

                    strcpy(mopath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]==35){                        // #

                     strcpy(mopath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 25:
                //printf("\n Estado 25 Posicion %d",j);

                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=25;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n name: ");

                     strcpy(moname,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=25;
                 }
                else if(cadena[j]=='"'){                    // comilla
                    estado=25;
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n name: ");

                    strcpy(moname,prueba);

                    estado=22;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(moname,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(moname,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 26:
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=26;
                    printf("\n Estado 26: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if((cadena[j]==58)){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='i') && (prueba[1]=='d')){
                            printf("\n parametro: id");
                            estado = 27;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else {
                            printf("\n parametro invalido");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=26;
                     printf("\n vacio");
                }
                else {
                    printf("\n simbolo erroneo");
                }
            break;

            case 27:
                //printf("\n Estado 27 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=27;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n id: ");

                     strcpy(unid,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=27;
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(unid,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(unid,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else {
                    estado=27;
                    printf("\n simbolo erroneo");
                }

            break;

            case 28:
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=28;
                    //printf("\n Estado 28: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if((cadena[j]==58)){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='n') && (prueba[1]=='a') && (prueba[2]=='m') && (prueba[3]=='e')){
                            printf("\n parametro: name");
                            estado = 29;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='i') && (prueba[1]=='d')){
                            printf("\n parametro: unit");
                            estado = 30;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 31;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='r') && (prueba[1]=='u') && (prueba[2]=='t') && (prueba[3]=='a')){
                            printf("\n parametro: ruta");
                            estado = 236;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else {
                            printf("\n parameter: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=28;
                     printf("\n vacio");
                }
                else{
                     printf("\n simbolo erroneo ");
                }
            break;

            case 29:
                //printf("\n Estado 29 Posicion %d",j);

                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=29;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n name: ");

                     strcpy(repname,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=29;
                 }
                else if(cadena[j]=='"'){                    // comilla
                    estado=29;
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n name: ");

                    strcpy(repname,prueba);

                    estado=28;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(repname,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(repname,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 30:
                //printf("\n Estado 30 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=30;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n id: ");

                     strcpy(repid,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=30;
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(repid,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(repid,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n name: ");

                    strcpy(repid,prueba);

                    estado=28;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else {
                    printf("\n simbolo erroneo");

                }

            break;

            case 31: // decide si el path lleva espacios o no rep
                //printf("\n Estado 31 Posicion %d",j);

                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 32;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=31;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(reppath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=31;
                 }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(reppath,prueba);

                    estado=28;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(reppath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(reppath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 32:
                //printf("\n estado 32 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=32;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=32;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(reppath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=85;
                    printf("\n direccion: ");

                    strcpy(reppath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(reppath,prueba);

                    estado=28;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(reppath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(reppath,prueba);

                    estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }

            break;

            case 34:

                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=34;
                    //printf("\n Estado 34: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==58){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='s') && (prueba[1]=='i') && (prueba[2]=='z') && (prueba[3]=='e')){
                            printf("\n parametro: size");
                            estado = 35;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='n') && (prueba[2]=='i') && (prueba[3]=='t')){
                            printf("\n parametro: unit");
                            estado = 36;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 37;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='t') && (prueba[1]=='y') && (prueba[2]=='p') && (prueba[3]=='e')){
                            printf("\n parametro: type");
                            estado = 39;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='n') && (prueba[1]=='a') && (prueba[2]=='m') && (prueba[3]=='e')){
                            printf("\n parametro: name");
                            estado = 44;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='d') && (prueba[1]=='e') && (prueba[2]=='l') && (prueba[3]=='e')&& (prueba[4]=='t')&& (prueba[5]=='e')){
                            printf("\n parametro: delete");
                            estado = 41;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='a') && (prueba[1]=='d') && (prueba[2]=='d')){
                            printf("\n parametro: add");
                            estado = 42;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='f') && (prueba[1]=='i') && (prueba[2]=='t')){
                            printf("\n parametro: fit");
                            estado = 40;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else {
                            printf("\n parameter: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                     estado=34;
                     printf("\n vacio");
                }
                else {
                    printf(" simbolo erroneo ");

                }

            break;

            case 35:
                //printf("\n Posicion %d",j);

                if((cadena[j]>=48) && (cadena[j]<=57)){    // numeros 0-9
                    estado=35;
                  //printf("\n Estado 35: numero %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=35;
                     printf("\n vacio");
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n size: ");

                     strcpy(fauxsize,prueba);

                     printf("\n  ");
                     fsize = convertir_cadena_a_entero(fauxsize);
                     printf("\n fin");
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     action = 10;
                }
                else if(cadena[j]==45){                        // -
                     estado = 34;
                     printf("\n size: ");

                     strcpy(fauxsize,prueba);

                     fsize = convertir_cadena_a_entero(fauxsize);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     action = 10;
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(fauxsize,prueba);

                    fsize = convertir_cadena_a_entero(fauxsize);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                    action = 10;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;

                     strcpy(fauxsize,prueba);

                     fsize = convertir_cadena_a_entero(fauxsize);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                     action = 10;
                }
                else{
                    printf("\n parametro: error size rango no valido");
                }
            break;

            case 36:
                //printf("\n Estado 36 Posicion %d",j);
                if(cadena[j]=='b' || cadena[j]=='B'){
                    printf("\n unit: b");
                    funit = 1;
                }
                if(cadena[j]=='k' || cadena[j]=='K'){
                    printf("\n unit: k");
                    funit = 2;
                }
                else if(cadena[j]=='m' || cadena[j]=='M'){
                    printf("\n unit: m");
                    funit = 3;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=36;
                     printf("\n vacio");
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n fin");
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                     estado = 34;
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else {
                    printf("\n parametro: unit error medida no valida");
                }
            break;

            case 37:
                //printf("\n Estado 37 Posicion %d",j);

                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 38;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=37;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(fpath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=37;
                 }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(fpath,prueba);

                    estado=34;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(fpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                     strcpy(fpath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }


            break;

            case 38:
                //printf("\n Estado 38 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=38;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=38;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(fpath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=90;
                    printf("\n direccion: ");

                    strcpy(fpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n direccion: ");

                    strcpy(fpath,prueba);

                    estado=34;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(fpath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(fpath,prueba);

                    estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 39:
                //printf("\n Estado 39 Posicion %d",j);
                if(cadena[j]=='p' || cadena[j]=='P'){
                    printf("\n type: primaria");
                    ftype = 1;
                }
                else if(cadena[j]=='e' || cadena[j]=='E'){
                    printf("\n type: extendida");
                    ftype = 2;
                }
                else if(cadena[j]=='l' || cadena[j]=='L'){
                    printf("\n type: logica");
                    ftype = 3;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=39;
                     printf("\n vacio");
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n fin");
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                     estado = 34;
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else {
                    printf("\n parametro: unit error medida no valida");
                }
            break;

            case 40:
                //printf("\n Estado 40 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=122)){    // letras a-z
                    estado=40;
                    prueba[counter] = cadena[j];
                    counter++;
                }else if((cadena[j]=='-') || (cadena[j]=='$') || (cadena[j]=='\n')){                        // guion alto

                       int i;
                       for(i=0;i<counter;i++){
                           prueba[i] = tolower(prueba[i]);
                       }
                        if((prueba[0]=='b') && (prueba[1]=='f')){
                           printf("\n best fit");
                           ffit = 1;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                        }
                        else if((prueba[0]=='f') && (prueba[1]=='f')){
                           printf("\n first fit");
                           ffit = 2;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                        }
                        else if((prueba[0]=='w') && (prueba[1]=='f')){
                           printf("\n worst fit");
                           ffit = 3;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                        }
                        else {
                           printf("\n ajuste invalido");
                        }

                        if(cadena[j]=='-'){
                            estado = 34;
                        }
                        if(cadena[j]=='$' || (cadena[j]=='\n')){
                            estado = 5;
                        }

               }
               else if(cadena[j]==32){                        // espacio
                    estado=40;
                    printf("\n vacio");
               }

               else if(cadena[j]==35){                        // #
                    estado=8;
                    printf("comentarios: ");
               }
            break;

            case 41:
                if(action==3){
                  //  printf("\n Estado 41 Posicion %d",j);
                    if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                        estado=41;
                        prueba[counter] = cadena[j];
                        counter++;
                    }else if((cadena[j]=='-') || (cadena[j]=='$') || (cadena[j]=='\n')){                        // guion alto

                           int i;
                           for(i=0;i<counter;i++){
                               prueba[i] = tolower(prueba[i]);
                           }
                            if((prueba[0]=='f') && (prueba[1]=='a') && (prueba[2]=='s') && (prueba[3]=='t')){
                               printf("\n delete fast");
                               fdelete = 1;
                               counter = 0;
                               int k;
                               for(k=0;k<lon;k++){
                                    prueba[k]=NULL;
                               }
                            }
                            else if((prueba[0]=='f') && (prueba[1]=='u') && (prueba[2]=='l') && (prueba[3]=='l')){
                               printf("\n delete full");
                               fdelete = 2;
                               counter = 0;
                               int k;
                               for(k=0;k<lon;k++){
                                    prueba[k]=NULL;
                               }
                            }
                            else {
                               printf("\n parametro: delete invalido");
                            }

                            if(cadena[j]=='-'){
                                estado = 34;
                            }
                            if(cadena[j]=='$' || (cadena[j]=='\n')){
                                estado = 5;
                            }
                            action = 9;
                   }
                   else if(cadena[j]==32){                        // espacio
                        estado=41;
                        printf("\n vacio");
                   }

                   else if(cadena[j]==35){                        // #
                        estado=8;
                        printf("comentarios: ");
                   }

                }
            break;

            case 42:
                if(action==3){
                    if((cadena[j]>=48) && (cadena[j]<=57)){    // numeros 0-9
                        estado=42;
                    //    printf("\n Estado 42: numero %c",cadena[j]);
                        prueba[counter] = cadena[j];
                        counter++;
                    }
                    else if(cadena[j]==32){                        // espacio
                         estado=42;
                         printf("\n vacio");
                    }
                    else if(cadena[j]==36){                        // $
                         estado=5;
                         printf("\n add: ");

                         strcpy(fauxadd,prueba);

                         printf("\n  ");
                         fadd = convertir_cadena_a_entero(fauxadd);
                         printf("\n fin");
                         counter = 0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                         action = 8;
                    }
                    else if(cadena[j]==45){                        // -
                         if((cadena[j+1]>=48) && (cadena[j+1]<=57)){
                             estado=42;
                             printf("\n Estado 42: numero %c",cadena[j]);
                             prueba[counter] = cadena[j];
                             counter++;
                         }else if((cadena[j+1]>=46) && (cadena[j+1]<=122)){

                             estado = 34;
                             printf("\n add: ");

                             strcpy(fauxadd,prueba);

                             fadd = convertir_cadena_a_entero(fauxadd);
                             counter = 0;
                             int k;
                             for(k=0;k<lon;k++){
                                  prueba[k]=NULL;
                             }
                             action = 8;
                         }

                    }
                    else if(cadena[j]=='\n'){                     // enter

                        strcpy(fauxadd,prueba);

                        fadd = convertir_cadena_a_entero(fauxadd);

                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                        estado=5;
                        action = 8;
                    }
                    else if(cadena[j]==35){                        // #
                         estado=8;

                         strcpy(fauxadd,prueba);

                         fadd = convertir_cadena_a_entero(fauxadd);
                         counter=0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                         action = 8;
                         printf("comentarios: ");
                    }
                    else{
                        printf("\n parametro: error add");
                    }
                }

            break;
            case 44:
                //printf("\n Estado 44 Posicion %d",j);

                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=44;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n name: ");

                     strcpy(fname,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=44;
                 }
                else if(cadena[j]=='"'){                    // comilla
                    estado=44;
                }
                else if(cadena[j]=='-'){                    // -
                    printf("\n name: ");

                    strcpy(fname,prueba);

                    estado=34;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(fname,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(fname,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }

            break;

            case 60:
                //printf("\n Estado 60 Posicion %d",j);

                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 61;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=60;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(exepath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=60;
                 }
                else if(cadena[j]=='\n'){                     // enter

                    strcpy(exepath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                     strcpy(exepath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;

            case 61:
                //printf("\n Estado 61 Posicion %d",j);
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=61;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=61;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     printf("\n direccion: ");

                     strcpy(exepath,prueba);

                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=95;
                    printf("\n direccion: ");

                    strcpy(exepath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }

                else if(cadena[j]=='\n'){                     // enter

                    strcpy(exepath,prueba);

                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #

                    strcpy(exepath,prueba);

                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }

            break;

            case 80:
                if(cadena[j]=='-'){                    // -
                    estado=22;
                }else if(cadena[j]==32){               // espacio
                    estado=80;
                }

                else if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){             // enter
                    estado =5;
                }
                else if(cadena[j]==35){                        // #
                    estado =8;
                }

                else{
                    estado=80;
                    printf("\n Error 80");
                }

            break;

            case 85:
                if(cadena[j]=='-'){                    // -
                    estado=28;
                }else if(cadena[j]==32){               // espacio
                    estado=85;
                }

                else if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){            // enter
                    estado =5;
                }
                else if(cadena[j]==35){               // #
                    estado =8;
                }

                else{
                    estado=85;
                    printf("\n Error 85");
                }

            break;

            case 90:
                if(cadena[j]=='-'){                    // -
                    estado=34;
                }else if(cadena[j]==32){               // espacio
                    estado=90;
                }

                else if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){            // enter
                    estado =5;
                }
                else if(cadena[j]==35){               // #
                    estado =8;
                }

                else{
                    estado=90;
                    printf("\n Error 90");
                }

            break;

            case 95:

                if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){       // enter
                    estado =5;
                }
                else if(cadena[j]==35){          // #
                    estado =8;
                }

            break;

            case 100:
                if(cadena[j]=='-'){                    // -
                    estado=1;
                }else if(cadena[j]==32){               // espacio
                    estado=100;
                }

                else if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){            // enter
                    estado =5;
                }
                else if(cadena[j]==35){               // #
                    estado =8;
                }

                else{
                    estado=100;
                    printf("\n Error 100");
                }

            break;

            case 105:
                if(cadena[j]=='-'){                    // -
                    estado=9;
                }else if(cadena[j]==32){               // espacio
                    estado=105;
                }

                else if(cadena[j]==36){               // $
                    estado=5;
                }else if(cadena[j]=='\n'){            // enter
                    estado =5;
                }
                else if(cadena[j]==35){               // #
                    estado =8;
                }

                else{
                    estado=105;
                    printf("\n Error 105");
                }

            break;



                // COMANDOS SEGUNDA FASE

            case 201: //detecta los parametros de la segunda fase
                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=201;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]=='\n' || cadena[j]=='$'){
                    estado = 5;
                }
                else if(cadena[j]==61){                        // igual
                     printf("\n detecte un =");
                     int i;
                     for(i=0;i<counter;i++){
                         prueba[i] = tolower(prueba[i]);
                     }
                         if((prueba[0]=='i') && (prueba[1]=='d')){
                            printf("\n parametro: id");
                            estado = 220;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='t') && (prueba[1]=='y') && (prueba[2]=='p') && (prueba[3]=='e')){
                            printf("\n parametro: type");
                            estado = 221;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='a') && (prueba[1]=='d') && (prueba[2]=='d')){
                            printf("\n parametro: add");
                            estado = 222;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='n') && (prueba[2]=='i') && (prueba[3]=='t')){
                            printf("\n parametro: unit");
                            estado = 223;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='s') && (prueba[2]=='r')){
                            printf("\n parametro: usr");
                            estado = 224;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='w') && (prueba[2]=='d')){
                            printf("\n parametro: pwd");
                            estado = 225;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='n') && (prueba[1]=='a') && (prueba[2]=='m') && (prueba[3]=='e')){
                            printf("\n parametro: name");
                            estado = 226;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='g') && (prueba[1]=='r') && (prueba[2]=='p')){
                            printf("\n parametro: grp");
                            estado = 227;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='p') && (prueba[1]=='a') && (prueba[2]=='t') && (prueba[3]=='h')){
                            printf("\n parametro: path");
                            estado = 228;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='u') && (prueba[1]=='g') && (prueba[2]=='o')){
                            printf("\n parametro: ugo");
                            estado = 229;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='s') && (prueba[1]=='i') && (prueba[2]=='z') && (prueba[3]=='e')){
                            printf("\n parametro: size");
                            estado = 232;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='c') && (prueba[1]=='o') && (prueba[2]=='n') && (prueba[3]=='t')){
                            printf("\n parametro: cont");
                            estado = 233;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='d') && (prueba[1]=='e') && (prueba[2]=='s') && (prueba[3]=='t')){
                            printf("\n parametro: dest");
                            estado = 234;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else if((prueba[0]=='i') && (prueba[1]=='d') && (prueba[2]=='d') && (prueba[3]=='e') && (prueba[4]=='s') && (prueba[5]=='t')){
                            printf("\n parametro: iddest");
                            estado = 235;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }
                         else {
                            printf("\n parameter: erroneo");
                         }

                }
                else if(cadena[j]==32){                        // espacio
                    printf("\n detecte un espacio");
                    int i;
                    for(i=0;i<counter;i++){
                        prueba[i] = tolower(prueba[i]);
                    }
                        if((prueba[0]=='r')){
                           printf("\n parametro: r");
                           estado = 201;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                           recursivo = 1;
                        }else if((prueba[0]=='p')){
                            printf("\n parametro: p");
                            estado = 201;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                            recursivo = 1;
                         }else{
                            estado=201;
                        }

                }
                else {
                    printf("\n simbolo erroneo %s %d",prueba,j);
                }

            break;
            //                      id
            case 220:
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=220;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(id2,prueba);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=220;
                 }
                else if(cadena[j]=='-'){                    // -
                    strcpy(id2,prueba);
                    estado=201;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(id2,prueba);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                    strcpy(id2,prueba);
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
            break;
        //                      type
        case 221:
                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=221;
                    prueba[counter] = cadena[j];
                    counter++;
                }else if((cadena[j]=='-') || (cadena[j]=='$') || (cadena[j]=='\n')){                        // guion alto

                       int i;
                       for(i=0;i<counter;i++){
                           prueba[i] = tolower(prueba[i]);
                       }
                        if((prueba[0]=='f') && (prueba[1]=='a') && (prueba[2]=='s') && (prueba[3]=='t')){
                           printf("\n Format fast");
                           type2 = 1;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                        }
                        else if((prueba[0]=='f') && (prueba[1]=='u') && (prueba[2]=='l') && (prueba[3]=='l')){
                           printf("\n Format full");
                           type2 = 2;
                           counter = 0;
                           int k;
                           for(k=0;k<lon;k++){
                                prueba[k]=NULL;
                           }
                        }
                        else {
                           printf("\n parametro: type invalido");
                        }

                        if(cadena[j]=='-'){
                            estado = 201;
                        }
                        if(cadena[j]=='$' || (cadena[j]=='\n')){
                            estado = 5;
                        }
                        //action=50;
               }
               else if(cadena[j]==32){                        // espacio
                    estado=221;
               }

               else if(cadena[j]==35){                        // #
                    estado=8;
                    printf("comentarios: ");
               }

        break;
        //                  add
        case 222:
            if((cadena[j]>=45) && (cadena[j]<=57)){    // numeros 0-9 y el simbolo -  .  /
                    estado=222;
                    prueba[counter] = cadena[j];
                    counter++;
            }
            else if(cadena[j]==32){                        // espacio
                 estado=222;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(addaux2,prueba);
                 add2 = convertir_cadena_a_entero(addaux2);
                 counter = 0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }
            /*else if(cadena[j]==45){                        // -
                 estado = 201;
                 strcpy(addaux2,prueba);
                 add2 = convertir_cadena_a_entero(addaux2);
                 counter = 0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }*/
            else if(cadena[j]==45){                        // -
                 if((cadena[j+1]>=48) && (cadena[j+1]<=57)){
                     estado=222;
                     prueba[counter] = cadena[j];
                     counter++;
                 }else if((cadena[j+1]>=46) && (cadena[j+1]<=57)){

                     estado = 201;

                     strcpy(addaux2,prueba);

                     add2 = convertir_cadena_a_entero(addaux2);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }

                 }

            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(addaux2,prueba);
                add2 = convertir_cadena_a_entero(addaux2);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #
                 estado=8;
                 strcpy(addaux2,prueba);
                 add2 = convertir_cadena_a_entero(addaux2);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
            else{
//                printf("\n parametro: error add rango no valido");
            }
        break;
        //                  unit
        case 223:
            if(cadena[j]=='b' || cadena[j]=='B'){
                printf("\n unit: b");
                unit2 = 1;
            }
            if(cadena[j]=='k' || cadena[j]=='K'){
                printf("\n unit: k");
                unit2 = 2;
            }
            else if(cadena[j]=='m' || cadena[j]=='M'){
                printf("\n unit: m");
                unit2 = 3;
            }
            else if(cadena[j]==32){                        // espacio
                 estado=223;
                 printf("\n vacio");
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 counter = 0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }
            else if(cadena[j]==45){                        // -
                 estado = 201;
                 counter = 0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }
            else if(cadena[j]=='\n'){                     // enter
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #
                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
            else {
                printf("\n parametro: unit error medida no valida");
            }

        break;
        //                      user
        case 224:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                estado=224;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(usr2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
           }

            else if(cadena[j]==32){                     // espacio
                estado=224;
             }
            else if(cadena[j]=='"'){                    // comilla
                estado=224;
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(usr2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(usr2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #

                strcpy(usr2,prueba);

                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
        break;
        //                  pwd
        case 225:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                estado=225;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(pwd2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
           }

            else if(cadena[j]==32){                     // espacio
                estado=225;
             }
            else if(cadena[j]=='"'){                    // comilla
                estado=225;
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(pwd2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(pwd2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #

                strcpy(pwd2,prueba);

                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
        break;
        //                  name
        case 226:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                estado=226;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(name2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
           }

            else if(cadena[j]==32){                     // espacio
                estado=226;
             }
            else if(cadena[j]=='"'){                    // comilla
                estado=226;
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(name2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(name2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #

                strcpy(name2,prueba);

                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
        break;
       //               grp
        case 227:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                estado=227;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(grp2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
           }

            else if(cadena[j]==32){                     // espacio
                estado=227;
             }
            else if(cadena[j]=='"'){                    // comilla
                estado=227;
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(grp2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(grp2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #

                strcpy(grp2,prueba);

                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }
        break;
        //                  path
        case 228:
            if(cadena[j]=='"'){
                printf("\n con espacios");
                estado = 240;
                counter = 0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                estado=228;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(path2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
           }

            else if(cadena[j]==32){                     // espacio
                estado=228;
             }
            else if(cadena[j]=='-'){                    // -
                strcpy(path2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(path2,prueba);
                printf(" \n %s using s \n ",path2);
                printf("    size path %d",strlen(path2));
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #
                strcpy(path2,prueba);
                 estado=8;
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
           }
        break;




            //                  ugo
        case 229:
                if((cadena[j]>=48) && (cadena[j]<=55)){    // numeros 0-9 y el simbolo -  .  /
                    estado=229;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=229;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(ugoaux2,prueba);
                     ugo2 = convertir_cadena_a_entero(ugoaux2);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                     estado = 201;
                     strcpy(ugoaux2,prueba);
                     ugo2 = convertir_cadena_a_entero(ugoaux2);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(ugoaux2,prueba);
                    ugo2 = convertir_cadena_a_entero(ugoaux2);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;
                     strcpy(ugoaux2,prueba);
                     ugo2 = convertir_cadena_a_entero(ugoaux2);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else{
                    printf("\n parametro: error add rango no valido");
                }
        break;




            //                  size
        case 232:
                if((cadena[j]>=48) && (cadena[j]<=57)){    // numeros 0-9 y el simbolo -  .  /
                    estado=232;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                        // espacio
                     estado=232;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(sizeaux2,prueba);
                     size2 = convertir_cadena_a_entero(sizeaux2);
                     counter = 0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]==45){                        // -
                    estado=201;
                    strcpy(sizeaux2,prueba);
                    size2 = convertir_cadena_a_entero(sizeaux2);
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(sizeaux2,prueba);
                    size2 = convertir_cadena_a_entero(sizeaux2);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                     estado=8;
                     strcpy(sizeaux2,prueba);
                     size2 = convertir_cadena_a_entero(sizeaux2);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }
                else{
                    //printf("\n parametro: error add rango no valido");
                }
        break;




            //                  cont
        case 233:
                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 241;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=233;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(cont2,prueba);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=233;
                 }
                else if(cadena[j]=='-'){                    // -
                    strcpy(cont2,prueba);
                    estado=201;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(cont2,prueba);
                    printf(" \n %s using s \n ",cont2);
                    printf("    size path %d",strlen(cont2));
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                    strcpy(cont2,prueba);
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
               }
         break;
        //              dest
        case 234:
                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 242;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=234;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(dest2,prueba);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=234;
                 }
                else if(cadena[j]=='-'){                    // -
                    strcpy(dest2,prueba);
                    estado=201;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(dest2,prueba);
                    printf(" \n %s using s \n ",dest2);
                    printf("    size path %d",strlen(dest2));
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                    strcpy(dest2,prueba);
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
               }
         break;

                //              iddest
         case 235:
                    if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                        estado=235;
                        prueba[counter] = cadena[j];
                        counter++;
                    }
                    else if(cadena[j]==36){                        // $
                         estado=5;
                         strcpy(iddest2,prueba);
                         counter=0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                   }

                    else if(cadena[j]==32){                     // espacio
                        estado=235;
                     }
                    else if(cadena[j]=='"'){                    // comilla
                        estado=235;
                    }
                    else if(cadena[j]=='-'){                    // -
                        strcpy(iddest2,prueba);
                        estado=201;
                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                    }
                    else if(cadena[j]=='\n'){                     // enter
                        strcpy(iddest2,prueba);
                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                        estado=5;
                    }
                    else if(cadena[j]==35){                        // #

                        strcpy(iddest2,prueba);

                         estado=8;
                         counter=0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                         printf("comentarios: ");
                    }
         break;
        //                  ruta
        case 236:
                if(cadena[j]=='"'){
                    printf("\n con espacios");
                    estado = 243;
                    counter = 0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                if((cadena[j]>=46) && (cadena[j]<=126)){    // simbolos numeros letras a-z
                    estado=236;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(ruta2,prueba);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
               }

                else if(cadena[j]==32){                     // espacio
                    estado=236;
                 }
                else if(cadena[j]=='-'){                    // -
                    strcpy(ruta2,prueba);
                    estado=201;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(ruta2,prueba);
                    printf(" \n %s using s \n ",ruta2);
                    printf("    size path %d",strlen(ruta2));
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                    strcpy(ruta2,prueba);
                     estado=8;
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
               }
         break;

        //              path con espacios
        case 240:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                estado=240;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==32){                     // espacio
                estado=240;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(path2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }
            else if(cadena[j]=='"'){                         // "
                estado=245;
                strcpy(path2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(path2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(path2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #
                strcpy(path2,prueba);
                estado=8;
                counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }

        break;


        //              cont con espacios
        case 241:
            if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                estado=241;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==32){                     // espacio
                estado=241;
                prueba[counter] = cadena[j];
                counter++;
            }
            else if(cadena[j]==36){                        // $
                 estado=5;
                 strcpy(cont2,prueba);
                 counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
            }
            else if(cadena[j]=='"'){                         // "
                estado=245;
                strcpy(cont2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='-'){                    // -
                strcpy(cont2,prueba);
                estado=201;
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
            }
            else if(cadena[j]=='\n'){                     // enter
                strcpy(cont2,prueba);
                counter=0;
                int k;
                for(k=0;k<lon;k++){
                     prueba[k]=NULL;
                }
                estado=5;
            }
            else if(cadena[j]==35){                        // #
                strcpy(cont2,prueba);
                estado=8;
                counter=0;
                 int k;
                 for(k=0;k<lon;k++){
                      prueba[k]=NULL;
                 }
                 printf("comentarios: ");
            }

        break;

            //              dest con espacios
        case 242:
                if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                    estado=242;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==32){                     // espacio
                    estado=242;
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if(cadena[j]==36){                        // $
                     estado=5;
                     strcpy(dest2,prueba);
                     counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                }
                else if(cadena[j]=='"'){                         // "
                    estado=245;
                    strcpy(dest2,prueba);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='-'){                    // -
                    strcpy(dest2,prueba);
                    estado=201;
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                }
                else if(cadena[j]=='\n'){                     // enter
                    strcpy(dest2,prueba);
                    counter=0;
                    int k;
                    for(k=0;k<lon;k++){
                         prueba[k]=NULL;
                    }
                    estado=5;
                }
                else if(cadena[j]==35){                        // #
                    strcpy(dest2,prueba);
                    estado=8;
                    counter=0;
                     int k;
                     for(k=0;k<lon;k++){
                          prueba[k]=NULL;
                     }
                     printf("comentarios: ");
                }

        break;

                //              ruta con espacios
        case 243:
                    if((cadena[j]>=46) && (cadena[j]<=126)){    // letras a-z
                        estado=243;
                        prueba[counter] = cadena[j];
                        counter++;
                    }
                    else if(cadena[j]==32){                     // espacio
                        estado=243;
                        prueba[counter] = cadena[j];
                        counter++;
                    }
                    else if(cadena[j]==36){                        // $
                         estado=5;
                         strcpy(ruta2,prueba);
                         counter=0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                    }
                    else if(cadena[j]=='"'){                         // "
                        estado=85;
                        strcpy(ruta2,prueba);
                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                    }
                    else if(cadena[j]=='-'){                    // -
                        strcpy(ruta2,prueba);
                        estado=28;
                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                    }
                    else if(cadena[j]=='\n'){                     // enter
                        strcpy(ruta2,prueba);
                        counter=0;
                        int k;
                        for(k=0;k<lon;k++){
                             prueba[k]=NULL;
                        }
                        estado=5;
                    }
                    else if(cadena[j]==35){                        // #
                        strcpy(ruta2,prueba);
                        estado=8;
                        counter=0;
                         int k;
                         for(k=0;k<lon;k++){
                              prueba[k]=NULL;
                         }
                         printf("comentarios: ");
                    }

        break;

        case 245:
            if(cadena[j]=='-'){                    // -
                estado=201;
            }else if(cadena[j]==32){               // espacio
                estado=245;
            }

            else if(cadena[j]==36){               // $
                estado=5;
            }else if(cadena[j]=='\n'){            // enter
                estado=5;
            }
            else if(cadena[j]==35){               // #
                estado=8;
            }

            else{
                estado=245;
                printf("\n Error 245");
            }

        break;

            }
        }


    return 0;
}

struct estructura{
    int id;
};


struct partition{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name [16];

};
typedef struct partition part;
struct master_boot_record{
    int mbr_tamano;
    char mbr_fecha_creacion [18];
    int mbr_disk_signature;
    part mbr_partition_1;
    part mbr_partition_2;
    part mbr_partition_3;
    part mbr_partition_4;
};
typedef struct master_boot_record mbr;

struct extended_boot_record{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name [16];
};
typedef struct extended_boot_record ebr;

void crear_dir(char* path){
    int status;
    status = mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

int mkdisk(char* path,int size,int unit){
    FILE *disk;
    char cadena[1024] = "\0";
    disk = fopen(path,"w+b");
    int i;
    int sizeunit;
    // si numero es 0 y 2 la unidad es mega si numero es 1 la unidad es kilo
    if(unit==0){
        sizeunit = size*1024;
    }
    else if(unit==1){
        sizeunit = size;
    }
    else if(unit==2){
        sizeunit = size*1024;
    }
    for(i=0;i<sizeunit;i++){
        fwrite( cadena,sizeof(char), sizeof(cadena), disk ); //char cadena[]... cada posición es de tamaño 'char'
    }
    fclose (disk);

    FILE *mbrdisco = fopen(path,"rb+");
    if(mbrdisco){
        printf("si se pudo abrir el archivo");
        //struct estructura t;
        //t.id = 222;
        mbr nuevombr;
        int sizedisk = sizeunit * 1024; //tamaño para el disco en bytes
        nuevombr.mbr_tamano=sizedisk;
        //fecha del sistema
        time_t t;
        struct tm *tm;
        char fechayhora[18];

        t=time(NULL);
        tm=localtime(&t);
        strftime(fechayhora,18,"%d/%m/%Y %H:%M", tm);

        int i;

        //asignacion al struct de fecha del sistema y hora
        for(i=0;i<18;i++){
            nuevombr.mbr_fecha_creacion[i]=fechayhora[i];
        }
        int aleatorio;
        aleatorio = rand() % 1001;
        nuevombr.mbr_disk_signature=aleatorio;
        nuevombr.mbr_partition_1.part_start = sizeof(nuevombr);
        nuevombr.mbr_partition_2.part_start = sizeof(nuevombr);
        nuevombr.mbr_partition_3.part_start = sizeof(nuevombr);
        nuevombr.mbr_partition_4.part_start = sizeof(nuevombr);

        nuevombr.mbr_partition_1.part_size = 0;
        nuevombr.mbr_partition_2.part_size = 0;
        nuevombr.mbr_partition_3.part_size = 0;
        nuevombr.mbr_partition_4.part_size = 0;

        nuevombr.mbr_partition_1.part_status = '0';
        nuevombr.mbr_partition_2.part_status = '0';
        nuevombr.mbr_partition_3.part_status = '0';
        nuevombr.mbr_partition_4.part_status = '0';

        fseek(mbrdisco,0,SEEK_SET);

        // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
        fwrite(&nuevombr,sizeof(nuevombr),1,mbrdisco);

        printf("\n Se inserto el MBR exitosamente \n");

    }else{
        printf("\n No se inserto el MBR Fail \n");
    }
    fclose(mbrdisco);

    return 0;

}


void deletefull_logic(char* path,char* namepart){
    int punteroext;
    int finext;
    int existe=0;
    int c = 0;
    char cadena[0] = "\0";
    FILE *mn = fopen(path,"r+b");
    if(mn != NULL){
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);

          if(lectura.mbr_partition_1.part_type=='e' || lectura.mbr_partition_1.part_type=='E'){
              punteroext = lectura.mbr_partition_1.part_start;
              if(lectura.mbr_partition_1.part_status=='1'){ existe = 1;}
          }
          else if(lectura.mbr_partition_2.part_type=='e' || lectura.mbr_partition_2.part_type=='E'){
              punteroext = lectura.mbr_partition_2.part_start;
              if(lectura.mbr_partition_2.part_status=='1'){ existe = 1;}
          }
          else if(lectura.mbr_partition_3.part_type=='e' || lectura.mbr_partition_3.part_type=='E'){
              punteroext = lectura.mbr_partition_3.part_start;
              if(lectura.mbr_partition_3.part_status=='1'){ existe = 1; }

          }
          else if(lectura.mbr_partition_4.part_type=='e' || lectura.mbr_partition_4.part_type=='E'){
              punteroext = lectura.mbr_partition_4.part_start;
              if(lectura.mbr_partition_4.part_status=='1'){ existe = 1; }
          }
          else{
              printf("\n ERROR NO EXISTE PARTICION");
              existe = 0;
          }

          if(existe==1){
              printf("\n Delete Full Logic-----");
              printf("\n Inicio de particion Extendida...%d",punteroext);
              ebr q;
              ebr t;
              ebr anterior;
              ebr aux1;
              ebr aux2;
              fseek(mn,punteroext,SEEK_SET);
              fread(&q,sizeof(ebr),1,mn);

              t.part_fit = q.part_fit;
              strcpy(t.part_name,q.part_name);
              t.part_next = q.part_next;
              t.part_size = q.part_size;
              t.part_start = q.part_start;
              t.part_status = q.part_status;


              if(strcmp(q.part_name,namepart)==0){
                  finext = q.part_size;
                  printf("\n Partida a eliminar Primer EBR");
                  t.part_status = '0';

                  fseek(mn,punteroext,SEEK_SET);
                  fwrite(&t,sizeof(ebr),1,mn);

                  fseek(mn,punteroext+sizeof(ebr),SEEK_SET);
                  for(c=0;c<finext;c++){
                       fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
                  }

              }
              else{
                  int punwhile = q.part_next;
                  int ant = punteroext;
                  int bandera = 0;
                  int contador = 0;
                  int ap =0;
                  printf("\n Punwhile inicial...%d",punwhile);
                  printf("\n Anterior inicial...%d",ant);
                       while(bandera==0){
                            if(punwhile!=-1){

                                fseek(mn,punwhile,SEEK_SET);
                                fread(&q,sizeof(ebr),1,mn);

                                if(strcmp(namepart,q.part_name)==0){
                                    int flag=0;
                                    printf("\n Encontre particion a eliminar");
                                    printf("\n Punwhile actual...%d",punwhile);
                                    printf("\n Anterior actual...%d",ant);


                                    fseek(mn,punwhile,SEEK_SET);
                                    fread(&t,sizeof(ebr),1,mn);
                                    flag = t.part_next;

                                    //si la particion a eliminar es la ultima

                                    if(flag==-1){
                                        printf("------Eliminando ultima particion logica");
                                        //esta es la particion que debe tener status 0
                                        fseek(mn,punwhile,SEEK_SET);
                                        fread(&t,sizeof(ebr),1,mn);
                                        t.part_status='0';
                                        t.part_next=-1;
                                        ap = t.part_start;
                                        finext = sizeof(ebr)+t.part_size;

                                        fseek(mn,punwhile,SEEK_SET);
                                        fwrite(&t,sizeof(ebr),1,mn);


                                        //esta es la particion anterior a la de status 0
                                        //fseek();
                                        fseek(mn,ant,SEEK_SET);
                                        fread(&aux1,sizeof(ebr),1,mn);
                                        aux1.part_next=-1;
                                        fseek(mn,ant,SEEK_SET);
                                        fwrite(&aux1,sizeof(ebr),1,mn);

                                        fseek(mn,ap,SEEK_SET);
                                        for(c=0;c<finext;c++){
                                             fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
                                        }

                                    }else{
                                        printf("-----Eliminando particion logica (entre particiones)");
                                        //esta es la particion que debe tener status 0
                                        fseek(mn,punwhile,SEEK_SET);
                                        fread(&t,sizeof(ebr),1,mn);
                                        ap = t.part_start;
                                        finext = sizeof(ebr) + t.part_size;
                                        t.part_status='0';
                                        t.part_next=-1;
                                        fseek(mn,punwhile,SEEK_SET);
                                        fwrite(&t,sizeof(ebr),1,mn);


                                        //esta es la particion anterior a la de status 0
                                        fseek(mn,ant,SEEK_SET);
                                        fread(&aux1,sizeof(ebr),1,mn);
                                        aux1.part_next=flag;
                                        fseek(mn,ant,SEEK_SET);
                                        fwrite(&aux1,sizeof(ebr),1,mn);

                                        fseek(mn,ap,SEEK_SET);
                                        for(c=0;c<finext;c++){
                                             fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
                                        }
                                    }


                                    bandera = 1;
                                }else{
                                    printf("\n buscando...");
                                    bandera = 0;
                                    punwhile = q.part_next;
                                    ant = q.part_start;
                                    printf("\n punwhile siguiente...%d",punwhile);
                                    printf("\n anterior siguiente...%d",ant);

                                }

                            }
                            else if(punwhile==-1){
                                printf("\n NO existe particion");
                                bandera = 1;
                            }

                      }
                  } //fin del else
          } // existe


    }else {

        printf("\n Error al abrir archivo");
    }

    fclose(mn);

}

void deletefast_logic(char* path,char* namepart){
    int punteroext;
    int finext;
    int existe=0;
    FILE *mn = fopen(path,"r+b");
    if(mn != NULL){
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);

          if(lectura.mbr_partition_1.part_type=='e' || lectura.mbr_partition_1.part_type=='E'){
              punteroext = lectura.mbr_partition_1.part_start;
              if(lectura.mbr_partition_1.part_status=='1'){existe = 1;}
          }
          else if(lectura.mbr_partition_2.part_type=='e' || lectura.mbr_partition_2.part_type=='E'){
              punteroext = lectura.mbr_partition_2.part_start;
              if(lectura.mbr_partition_2.part_status=='1'){existe = 1;}
          }
          else if(lectura.mbr_partition_3.part_type=='e' || lectura.mbr_partition_3.part_type=='E'){
              punteroext = lectura.mbr_partition_3.part_start;
              if(lectura.mbr_partition_3.part_status=='1'){existe = 1;}
          }
          else if(lectura.mbr_partition_4.part_type=='e' || lectura.mbr_partition_4.part_type=='E'){
              punteroext = lectura.mbr_partition_4.part_start;
              if(lectura.mbr_partition_4.part_status=='1'){existe = 1;}

          }
          else{
              printf("\n ERROR NO EXISTE PARTICION");
              existe = 0;
          }

          if(existe==1){
              printf("\n Delete Fast Logic-----");
              printf("\n Inicio de particion Extendida...%d",punteroext);
              ebr q;
              ebr t;
              ebr anterior;
              ebr aux1;
              ebr aux2;
              fseek(mn,punteroext,SEEK_SET);
              fread(&q,sizeof(ebr),1,mn);

              t.part_fit = q.part_fit;
              strcpy(t.part_name,q.part_name);
              t.part_next = q.part_next;
              t.part_size = q.part_size;
              t.part_start = q.part_start;
              t.part_status = q.part_status;

              if(strcmp(q.part_name,namepart)==0){
                  printf("\n Partida a eliminar Primer EBR");
                  t.part_status = '0';
                  fseek(mn,punteroext,SEEK_SET);
                  fwrite(&t,sizeof(ebr),1,mn);
              }
              else{
                  int punwhile = q.part_next;
                  int ant = punteroext;
                  int bandera = 0;
                  int contador = 0;
                  printf("\n Punwhile inicial...%d",punwhile);
                  printf("\n Anterior inicial...%d",ant);
                       while(bandera==0){
                            if(punwhile!=-1){

                                fseek(mn,punwhile,SEEK_SET);
                                fread(&q,sizeof(ebr),1,mn);

                                if(strcmp(q.part_name,namepart)==0){
                                    int flag=0;
                                    printf("\n Encontre particion a eliminar");
                                    printf("\n Punwhile actual...%d",punwhile);
                                    printf("\n Anterior actual...%d",ant);


                                    fseek(mn,punwhile,SEEK_SET);
                                    fread(&t,sizeof(ebr),1,mn);
                                    flag = t.part_next;

                                    //si la particion a eliminar es la ultima

                                    if(flag==-1){
                                        printf("------Eliminando ultima particion logica");
                                        //esta es la particion que debe tener status 0
                                        fseek(mn,punwhile,SEEK_SET);
                                        fread(&t,sizeof(ebr),1,mn);
                                        t.part_status='0';
                                        t.part_next=-1;
                                        fseek(mn,punwhile,SEEK_SET);
                                        fwrite(&t,sizeof(ebr),1,mn);


                                        //esta es la particion anterior a la de status 0
                                        //fseek();
                                        fseek(mn,ant,SEEK_SET);
                                        fread(&aux1,sizeof(ebr),1,mn);
                                        aux1.part_next=-1;
                                        fseek(mn,ant,SEEK_SET);
                                        fwrite(&aux1,sizeof(ebr),1,mn);
                                    }else{
                                        printf("-----Eliminando particion logica (entre particiones)");
                                        //esta es la particion que debe tener status 0
                                        fseek(mn,punwhile,SEEK_SET);
                                        fread(&t,sizeof(ebr),1,mn);
                                        t.part_status='0';
                                        t.part_next=-1;
                                        fseek(mn,punwhile,SEEK_SET);
                                        fwrite(&t,sizeof(ebr),1,mn);

                                        //esta es la particion anterior a la de status 0
                                        fseek(mn,ant,SEEK_SET);
                                        fread(&aux1,sizeof(ebr),1,mn);
                                        aux1.part_next=flag;
                                        fseek(mn,ant,SEEK_SET);
                                        fwrite(&aux1,sizeof(ebr),1,mn);
                                    }


                                    bandera = 1;
                                }else{
                                    printf("\n buscando...");
                                    bandera = 0;
                                    punwhile = q.part_next;
                                    ant = q.part_start;
                                    printf("\n punwhile siguiente...%d",punwhile);
                                    printf("\n anterior siguiente...%d",ant);

                                }

                            }
                            else if(punwhile==-1){
                                printf("\n NO existe particion");
                                bandera = 1;
                            }

                      }
                  } //fin del else
          } // existe


    }else {

        printf("\n Error al abrir archivo");
    }

    fclose(mn);

}
void deletefast(char* path,char* namepart){
    int punteroext;
    int finext;
    printf("    \n- Delete Fast");
    FILE *mn = fopen(path,"r+b");
    if(mn != NULL){
        printf("    \n Leyendo Disco Duro...");
        mbr lectura;
        mbr escritura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
            printf(" \n    ");
            escritura.mbr_disk_signature = lectura.mbr_disk_signature;
            strcpy(escritura.mbr_fecha_creacion,lectura.mbr_fecha_creacion);
            escritura.mbr_partition_1 = lectura.mbr_partition_1;
            escritura.mbr_partition_2 = lectura.mbr_partition_2;
            escritura.mbr_partition_3 = lectura.mbr_partition_3;
            escritura.mbr_partition_4 = lectura.mbr_partition_4;
            escritura.mbr_tamano = lectura.mbr_tamano;
            printf("          Particiones leidas....");
          if(strcmp(lectura.mbr_partition_1.part_name,namepart)==0){
                escritura.mbr_partition_1.part_status = '0';
                punteroext=lectura.mbr_partition_1.part_start;
                finext=lectura.mbr_partition_1.part_start+lectura.mbr_partition_1.part_size;
                printf("\n Delete fast partition 1 ");
          }

          else if(strcmp(lectura.mbr_partition_2.part_name,namepart)==0){
              escritura.mbr_partition_2.part_status = '0';
              punteroext=lectura.mbr_partition_2.part_start;
              finext=lectura.mbr_partition_2.part_start+lectura.mbr_partition_2.part_size;
              printf("\n Delete fast partition 2 ");
          }

          else if(strcmp(lectura.mbr_partition_3.part_name,namepart)==0){
              escritura.mbr_partition_3.part_status = '0';
              punteroext=lectura.mbr_partition_3.part_start;
              finext=lectura.mbr_partition_3.part_start+lectura.mbr_partition_3.part_size;
              printf("\n Delete fast partition 3 ");
          }

          else if(strcmp(lectura.mbr_partition_4.part_name,namepart)==0){
              escritura.mbr_partition_4.part_status = '0';
              punteroext=lectura.mbr_partition_4.part_start;
              finext=lectura.mbr_partition_4.part_start+lectura.mbr_partition_4.part_size;
              printf("\n Delete fast partition 4 ");
          }
          else{
              printf("\n ERROR NO EXISTE PARTICION");
          }
          fread(&lectura,sizeof(mbr),1,mn);

          fseek(mn,0,SEEK_SET);
          // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
          fwrite(&escritura,sizeof(mbr),1,mn);
    }else{
        printf("Error al eliminar fast particion ");
    }
    fclose(mn);

}
void deletefull(char* path, char* namepart){
    int punteroext;
    int finext;
    char cadena[0] = "\0";
    int c=0;

    printf("    \n- Delete Fast");
    FILE *mn = fopen(path,"r+b");

    if(mn != NULL){
        printf("    \n Leyendo Disco Duro...");
        mbr lectura;
        mbr escritura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
            printf(" \n    ");
            escritura.mbr_disk_signature = lectura.mbr_disk_signature;
            strcpy(escritura.mbr_fecha_creacion,lectura.mbr_fecha_creacion);
            escritura.mbr_partition_1 = lectura.mbr_partition_1;
            escritura.mbr_partition_2 = lectura.mbr_partition_2;
            escritura.mbr_partition_3 = lectura.mbr_partition_3;
            escritura.mbr_partition_4 = lectura.mbr_partition_4;
            escritura.mbr_tamano = lectura.mbr_tamano;
            printf("          Particiones leidas....");
          if(strcmp(lectura.mbr_partition_1.part_name,namepart)==0){
                escritura.mbr_partition_1.part_status = '0';
                punteroext=lectura.mbr_partition_1.part_start;
                finext=lectura.mbr_partition_1.part_size;

                printf("\n Delete fast partition 1 ");

                fseek(mn,punteroext,SEEK_SET);
                for(c=0;c<finext;c++){
                    fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
                }

          }

          else if(strcmp(lectura.mbr_partition_2.part_name,namepart)==0){
              escritura.mbr_partition_2.part_status = '0';
              punteroext=lectura.mbr_partition_2.part_start;
              finext=lectura.mbr_partition_2.part_size;

              printf("\n Delete fast partition 2 ");

              fseek(mn,punteroext,SEEK_SET);
              for(c=0;c<finext;c++){
                   fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
              }

          }

          else if(strcmp(lectura.mbr_partition_3.part_name,namepart)==0){
              escritura.mbr_partition_3.part_status = '0';
              punteroext=lectura.mbr_partition_3.part_start;
              finext=lectura.mbr_partition_3.part_size;

              printf("\n Delete fast partition 3 ");

              fseek(mn,punteroext,SEEK_SET);
              for(c=0;c<finext;c++){
                   fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
              }

          }

          else if(strcmp(lectura.mbr_partition_4.part_name,namepart)==0){
              escritura.mbr_partition_4.part_status = '0';
              punteroext=lectura.mbr_partition_4.part_start;
              finext=lectura.mbr_partition_4.part_size;

              printf("\n Delete fast partition 4 ");

              fseek(mn,punteroext,SEEK_SET);
              for(c=0;c<finext;c++){
                   fwrite( cadena,sizeof(char), 1, mn ); //char cadena[]... cada posición es de tamaño 'char'
              }

          }
          else{
              printf("\n ERROR NO EXISTE PARTICION");
          }
          fread(&lectura,sizeof(mbr),1,mn);

          fseek(mn,0,SEEK_SET);
          // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
          fwrite(&escritura,sizeof(escritura),1,mn);
    }else{
        printf("Error al eliminar full particion ");
    }
    fclose(mn);

}

void sumar(char* path, char* namep, int unit, int sizepart){

    if(unit==0){        // si es cero se tomara como kilo
        sizepart = sizepart*1024;
    }else if(unit==1){  // byte
        sizepart = sizepart;
    }else if(unit==2){  // kilo
        sizepart = sizepart*1024;
    }else if(unit==3){  // Mega
        sizepart = sizepart*1024*1024;
    }

    int ban=0;
    int existe = 0;
    //ARREGLOS DE INICIO Y FIN
    int iniciop[4];
    int finp[4];

    //TEMPORAES QUE CALCULAN POSICION FINAL
    int tempf0;
    int tempf1;
    int tempf2;
    int tempf3;
    //VALORES DEL ESPACIO LIBRE
    int size1;
    int size2;
    int size3;
    int size4;

    //TAMAÑO DEL DISCO DURO
    int sizedisk;
    int tamano=0;
    int idpart=0;
    int finpart=0;
    int puntero=0;
    printf("\n CALCULANDO ESPACIO....");
    FILE *mn = fopen(path,"rb+");
    if(mn != NULL){
        mbr lectura;
        mbr escritura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);

        escritura.mbr_disk_signature = lectura.mbr_disk_signature;
        strcpy(escritura.mbr_fecha_creacion,lectura.mbr_fecha_creacion);
        escritura.mbr_partition_1 = lectura.mbr_partition_1;
        escritura.mbr_partition_2 = lectura.mbr_partition_2;
        escritura.mbr_partition_3 = lectura.mbr_partition_3;
        escritura.mbr_partition_4 = lectura.mbr_partition_4;
        escritura.mbr_tamano = lectura.mbr_tamano;

        sizedisk = lectura.mbr_tamano;
        printf("\n Aumentando particion....");

            printf(" \n p1 %s",lectura.mbr_partition_1.part_name);
            printf(" \n p2 %s",lectura.mbr_partition_2.part_name);
            printf(" \n p3 %s",lectura.mbr_partition_3.part_name);
            printf(" \n p4 %s",lectura.mbr_partition_4.part_name);

            if(lectura.mbr_partition_1.part_type=='E' && lectura.mbr_partition_1.part_status=='1'){
                puntero = lectura.mbr_partition_1.part_start;
                tamano = lectura.mbr_partition_1.part_size;
                existe = 1;
                printf(" \n add p1 extendida");


            }else if(lectura.mbr_partition_2.part_type=='E' && lectura.mbr_partition_2.part_status=='1'){
                puntero = lectura.mbr_partition_2.part_start;
                tamano = lectura.mbr_partition_2.part_size;
                existe = 1;
                printf(" \n add p1 extendida");

            }else if(lectura.mbr_partition_3.part_type=='E' && lectura.mbr_partition_3.part_status=='1'){
                puntero = lectura.mbr_partition_3.part_start;
                tamano = lectura.mbr_partition_3.part_size;
                existe = 1;
                printf(" \n add p1 extendida");

            }else if(lectura.mbr_partition_4.part_type=='E' && lectura.mbr_partition_4.part_status=='1'){
                puntero = lectura.mbr_partition_4.part_start;
                tamano = lectura.mbr_partition_4.part_size;
                existe = 1;
                printf(" \n add p1 extendida");
            }


            // compara si el nombre de la particion es igual al de las del mbr
            if(strcmp(namep,lectura.mbr_partition_1.part_name)==0 && lectura.mbr_partition_1.part_status=='1'){
                printf("\n Aumentar p1");
                if(lectura.mbr_partition_1.part_type=='P'||lectura.mbr_partition_1.part_type=='E'){
                    ban = 1;
                    idpart = 1;
                }

            }

            else if(strcmp(namep,lectura.mbr_partition_2.part_name)==0 && lectura.mbr_partition_2.part_status=='1'){
                printf("\n Aumentar p2");
                if(lectura.mbr_partition_2.part_type=='P'||lectura.mbr_partition_2.part_type=='E'){
                    ban = 1;
                    idpart = 2;
                }
            }


            else if(strcmp(namep,lectura.mbr_partition_3.part_name)==0 && lectura.mbr_partition_3.part_status=='1'){
                printf("\n Aumentar p3");
                if(lectura.mbr_partition_3.part_type=='P'||lectura.mbr_partition_3.part_type=='E'){
                    ban = 1;
                    idpart = 3;
                }
            }

            else if(strcmp(namep,lectura.mbr_partition_4.part_name)==0 && lectura.mbr_partition_4.part_status=='1'){
                printf("\n Aumentar p4");
                if(lectura.mbr_partition_4.part_type=='P'||lectura.mbr_partition_4.part_type=='E'){
                    ban = 1;
                    idpart = 4;
                }
            }
            if(ban == 1){

                if(lectura.mbr_partition_1.part_status=='1'){
                    iniciop[0]=lectura.mbr_partition_1.part_start;
                    tempf0 = lectura.mbr_partition_1.part_size  + lectura.mbr_partition_1.part_start; // posicion final de cada particion
                }else{

                    tempf0 = lectura.mbr_partition_1.part_start;
                    iniciop[0]=lectura.mbr_partition_1.part_size  + lectura.mbr_partition_1.part_start;;
                }

                if(lectura.mbr_partition_2.part_status=='1'){
                    iniciop[1]=lectura.mbr_partition_2.part_start;
                    tempf1 = lectura.mbr_partition_2.part_size  + lectura.mbr_partition_2.part_start;
                }else{

                    tempf1 = lectura.mbr_partition_2.part_start;
                    iniciop[1]=lectura.mbr_partition_2.part_size  + lectura.mbr_partition_2.part_start;
                }

                if(lectura.mbr_partition_3.part_status=='1'){
                    iniciop[2]=lectura.mbr_partition_3.part_start;
                    tempf2 = lectura.mbr_partition_3.part_size  + lectura.mbr_partition_3.part_start;
                }else{

                    tempf2 = lectura.mbr_partition_3.part_start;
                    iniciop[2]=lectura.mbr_partition_3.part_size  + lectura.mbr_partition_3.part_start;
                }

                if(lectura.mbr_partition_4.part_status=='1'){
                    iniciop[3]=lectura.mbr_partition_4.part_start;
                    tempf3 = lectura.mbr_partition_4.part_size  + lectura.mbr_partition_4.part_start;
                }else{

                    tempf3 = lectura.mbr_partition_4.part_start;
                    iniciop[3]=lectura.mbr_partition_4.part_size  + lectura.mbr_partition_4.part_start;
                }

                printf("          \n temp1 %d ",tempf0);
                printf("          \n temp2 %d ",tempf1);
                printf("          \n temp3 %d ",tempf2);
                printf("          \n temp4 %d ",tempf3);

                finp[0]=tempf0;
                finp[1]=tempf1;
                finp[2]=tempf2;
                finp[3]=tempf3;
                ordenar(iniciop);
                ordenar(finp);

                size1 = iniciop[1] - finp[0];
                size2 = iniciop[2] - finp[1];
                size3 = iniciop[3] - finp[2];
                size4 = sizedisk - finp[3];
                printf("\n    size1 -----------%d",size1);
                printf("\n    size2 -----------%d",size2);
                printf("\n    size3 -----------%d",size3);
                printf("\n    size4 -----------%d",size4);


                if(idpart==1){
                    finpart = lectura.mbr_partition_1.part_start + lectura.mbr_partition_1.part_size;
                        if(finpart==finp[0]){
                            printf("\n fin[0]");
                            if(size1>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_1.part_size = escritura.mbr_partition_1.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[1]){
                            printf("\n fin[1]");
                            if(size2>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_1.part_size = escritura.mbr_partition_1.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[2]){
                            printf("\n fin[2]");
                            if(size3>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_1.part_size = escritura.mbr_partition_1.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[3]){
                            printf("\n fin[3]");
                            if(size4>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_1.part_size = escritura.mbr_partition_1.part_size + sizepart;
                            }else{

                                printf("\n Espacio insuficiente....");
                            }

                        }

                        fseek(mn, 0, SEEK_SET);
                        fwrite(&escritura,sizeof(mbr),1,mn);

                }// fin del idpart ==1


                if(idpart==2){
                    finpart = lectura.mbr_partition_2.part_start + lectura.mbr_partition_2.part_size;
                        if(finpart==finp[0]){
                            printf("\n fin[0]");
                            if(size1>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_2.part_size = escritura.mbr_partition_2.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[1]){
                            printf("\n fin[1]");
                            if(size2>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_2.part_size = escritura.mbr_partition_2.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[2]){
                            printf("\n fin[2]");
                            if(size3>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_2.part_size = escritura.mbr_partition_2.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[3]){
                            printf("\n fin[3]");
                            if(size4>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_2.part_size = escritura.mbr_partition_2.part_size + sizepart;
                            }else{

                                printf("\n Espacio insuficiente....");
                            }

                        }

                        fseek(mn, 0, SEEK_SET);
                        fwrite(&escritura,sizeof(mbr),1,mn);

                }// fin del idpart ==2


                if(idpart==3){
                    finpart = lectura.mbr_partition_3.part_start + lectura.mbr_partition_3.part_size;
                        if(finpart==finp[0]){
                            printf("\n fin[0]");
                            if(size1>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_3.part_size = escritura.mbr_partition_3.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[1]){
                            printf("\n fin[1]");
                            if(size2>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_3.part_size = escritura.mbr_partition_3.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[2]){
                            printf("\n fin[2]");
                            if(size3>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_3.part_size = escritura.mbr_partition_3.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[3]){
                            printf("\n fin[3]");
                            if(size4>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_3.part_size = escritura.mbr_partition_3.part_size + sizepart;
                            }else{

                                printf("\n Espacio insuficiente....");
                            }

                        }

                        fseek(mn, 0, SEEK_SET);
                        fwrite(&escritura,sizeof(mbr),1,mn);

                }// fin del idpart ==3


                if(idpart==4){
                    finpart = lectura.mbr_partition_4.part_start + lectura.mbr_partition_4.part_size;
                        if(finpart==finp[0]){
                            printf("\n fin[0]");
                            if(size1>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_4.part_size = escritura.mbr_partition_4.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[1]){
                            printf("\n fin[1]");
                            if(size2>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_4.part_size = escritura.mbr_partition_4.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[2]){
                            printf("\n fin[2]");
                            if(size3>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_4.part_size = escritura.mbr_partition_4.part_size + sizepart;
                            }else{
                                printf("\n Espacio insuficiente....");
                            }
                        }else if(finpart==finp[3]){
                            printf("\n fin[3]");
                            if(size4>=sizepart){
                                printf("\n Se añadio mas espacio a la particion....");
                                escritura.mbr_partition_4.part_size = escritura.mbr_partition_4.part_size + sizepart;
                            }else{

                                printf("\n Espacio insuficiente....");
                            }

                        }

                        fseek(mn, 0, SEEK_SET);
                        fwrite(&escritura,sizeof(mbr),1,mn);

                }// fin del idpart ==4

            }// fin del si ban == 1
            else{
                printf("\n ************ else**************");
                if(existe==1){
                    printf(" \n   else sumar");
                    ebr logica;
                    ebr aux;
                    fseek(mn,puntero,SEEK_SET);
                    fread(&logica,sizeof(ebr),1,mn);

                    aux.part_fit = logica.part_fit;
                    strcpy(aux.part_name,logica.part_name);
                    aux.part_next = logica.part_next;
                    aux.part_size = logica.part_size;
                    aux.part_start = logica.part_start;
                    aux.part_status = logica.part_status;

                    if(logica.part_next==-1){
                        printf("\n    logica.part_next == -1");
                            if(logica.part_size!=0 && logica.part_status!='0'){
                                    if(strcmp(namep,logica.part_name)==0 && logica.part_status=='1'){
                                        printf("    logica = 0 & status = 1     ");
                                        int result= tamano - logica.part_size - sizeof(ebr);
                                        printf("\n Tamanio disponible %d",result);
                                            if(result >= sizepart){
                                                 aux.part_size = aux.part_size + sizepart;
                                                 fseek(mn,puntero,SEEK_SET);
                                                 fwrite(&aux,sizeof(ebr),1,mn);
                                             }
                                     }

                             }
                     } // fin logica == -1


                    else{
                        printf("\n    else");
                        int bandera=0;
                        puntero = logica.part_start;
                        int inicio = logica.part_start;
                        while(bandera==0){

                           fseek(mn,puntero,SEEK_SET);
                           fread(&logica,sizeof(ebr),1,mn);
                           aux.part_fit = logica.part_fit;
                           strcpy(aux.part_name,logica.part_name);
                           aux.part_next = logica.part_next;
                           aux.part_size = logica.part_size;
                           aux.part_start = logica.part_start;
                           aux.part_status = logica.part_status;

                           printf("\n    while Puntero %d",puntero);
                           printf("\n     tamano %d",tamano);
                           if(puntero!=-1){
                                   if(strcmp(namep,logica.part_name)==0 && logica.part_status=='1'){
                                       printf("\n logica name = 0   status = 1");
                                       if(logica.part_next==-1){
                                           printf("\n   part_next == -1 ");
                                       int result=tamano - logica.part_start - logica.part_size - sizeof(ebr) + inicio;
                                            printf("\n result %d",result);
                                            if(result >= sizepart){
                                                  aux.part_size = aux.part_size + sizepart;

                                            }
                                       }
                                       else if(logica.part_next!=-1){
                                            printf("\n   part_next dif -1 ");
                                       int result=logica.part_next - logica.part_start - logica.part_size - sizeof(ebr);
                                           printf("\n result %d",result);
                                           if(result >= sizepart){
                                                  aux.part_size = aux.part_size + sizepart;

                                           }
                                       }

                                          fseek(mn,puntero,SEEK_SET);
                                          fwrite(&aux,sizeof(ebr),1,mn);
                                          bandera = 1;
                                    }
                                    puntero = aux.part_next;
                            }else{
                                   printf("\n    else bandera = 1");
                                   printf("\n    PARTICION NO EXISTE ");
                                   bandera = 1;
                            }
                       }
                  } // fin del else

                }

            }

    }fclose(mn);


}
void quitar(char* path, char* namep, int unit,int quitar){

    if(unit==0){        // si es cero se tomara como kilo
        quitar = quitar*1024;
    }else if(unit==1){  // byte
        quitar = quitar;
    }else if(unit==2){  // kilo
        quitar = quitar*1024;
    }else if(unit==3){  // Mega
        quitar = quitar*1024*1024;
    }


    FILE *mn = fopen(path,"r+b");
    int calculo=0;
    int puntero=0;
    int existe=0;
    if(mn != NULL){
        mbr lectura;
        mbr escritura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);

        escritura.mbr_disk_signature = lectura.mbr_disk_signature;
        strcpy(escritura.mbr_fecha_creacion,lectura.mbr_fecha_creacion);
        escritura.mbr_partition_1 = lectura.mbr_partition_1;
        escritura.mbr_partition_2 = lectura.mbr_partition_2;
        escritura.mbr_partition_3 = lectura.mbr_partition_3;
        escritura.mbr_partition_4 = lectura.mbr_partition_4;
        escritura.mbr_tamano = lectura.mbr_tamano;
        printf("\n Disminuyendo particion....");

            printf(" \n p1 %s",lectura.mbr_partition_1.part_name);
            printf(" \n p2 %s",lectura.mbr_partition_2.part_name);
            printf(" \n p3 %s",lectura.mbr_partition_3.part_name);
            printf(" \n p4 %s",lectura.mbr_partition_4.part_name);

            if(lectura.mbr_partition_1.part_type=='E'){ existe = 1;puntero=lectura.mbr_partition_1.part_start; printf("puntero p1 %d",puntero);  }
            if(lectura.mbr_partition_2.part_type=='E'){ existe = 1;puntero=lectura.mbr_partition_2.part_start; printf("puntero p2 %d",puntero);  }
            if(lectura.mbr_partition_3.part_type=='E'){ existe = 1;puntero=lectura.mbr_partition_3.part_start; printf("puntero p3 %d",puntero);  }
            if(lectura.mbr_partition_4.part_type=='E'){ existe = 1;puntero=lectura.mbr_partition_4.part_start; printf("puntero p4 %d",puntero);  }



            if(strcmp(namep,lectura.mbr_partition_1.part_name)==0 && lectura.mbr_partition_1.part_status=='1'){
                printf("\n quitar p1");
                if(lectura.mbr_partition_1.part_type=='E'){existe = 1;}
                if(lectura.mbr_partition_1.part_type=='P' || lectura.mbr_partition_1.part_type=='E'){


                    if(lectura.mbr_partition_1.part_size > quitar){
                          calculo = lectura.mbr_partition_1.part_size - quitar;
                          escritura.mbr_partition_1.part_size = calculo;
                    }
                }

            }

            else if(strcmp(namep,lectura.mbr_partition_2.part_name)==0 && lectura.mbr_partition_2.part_status=='1'){
                printf("\n quitar p2");
                if(lectura.mbr_partition_2.part_type=='E'){existe = 1;}
                if(lectura.mbr_partition_2.part_type=='P' || lectura.mbr_partition_2.part_type=='E'){


                    if(lectura.mbr_partition_2.part_size > quitar){
                          calculo = lectura.mbr_partition_2.part_size - quitar;
                          escritura.mbr_partition_2.part_size = calculo;
                    }
                }
            }


            else if(strcmp(namep,lectura.mbr_partition_3.part_name)==0 && lectura.mbr_partition_3.part_status=='1'){
                printf("\n quitar p3");
                if(lectura.mbr_partition_3.part_type=='E'){existe = 1;}
                if(lectura.mbr_partition_3.part_type=='P' || lectura.mbr_partition_3.part_type=='E'){


                    if(lectura.mbr_partition_3.part_size > quitar){
                          calculo = lectura.mbr_partition_3.part_size - quitar;
                          escritura.mbr_partition_3.part_size = calculo;
                    }
                }
            }

            else if(strcmp(namep,lectura.mbr_partition_4.part_name)==0 && lectura.mbr_partition_4.part_status=='1'){
                printf("\n quitar p4");
                if(lectura.mbr_partition_4.part_type=='E'){existe = 1;}
                if(lectura.mbr_partition_4.part_type=='P' || lectura.mbr_partition_4.part_type=='E'){


                    if(lectura.mbr_partition_4.part_size > quitar){
                          calculo = lectura.mbr_partition_4.part_size - quitar;
                          escritura.mbr_partition_4.part_size = calculo;
                    }
                }
            }
            else{
                if(existe==1){
                    printf(" \n   else quitar");
                    ebr logica;
                    ebr aux;
                    fseek(mn,puntero,SEEK_SET);
                    fread(&logica,sizeof(ebr),1,mn);

                    aux.part_fit = logica.part_fit;
                    strcpy(aux.part_name,logica.part_name);
                    aux.part_next = logica.part_next;
                    aux.part_size = logica.part_size;
                    aux.part_start = logica.part_start;
                    aux.part_status = logica.part_status;

                    if(logica.part_next==-1){
                        printf("\n    logica.part_next == -1");
                            if(logica.part_size!=0 && logica.part_status!='0'){
                                    if(strcmp(namep,logica.part_name)==0 && logica.part_status=='1'){
                                            if(logica.part_size > quitar){
                                                 calculo = logica.part_size - quitar;
                                                 aux.part_size = calculo;
                                                 fseek(mn,puntero,SEEK_SET);
                                                 fwrite(&aux,sizeof(ebr),1,mn);
                                             }
                                     }

                             }
                     }

                     else{
                         printf("\n    else");
                         int bandera=0;
                         puntero = logica.part_start;
                         while(bandera==0){

                            fseek(mn,puntero,SEEK_SET);
                            fread(&logica,sizeof(ebr),1,mn);
                            aux.part_fit = logica.part_fit;
                            strcpy(aux.part_name,logica.part_name);
                            aux.part_next = logica.part_next;
                            aux.part_size = logica.part_size;
                            aux.part_start = logica.part_start;
                            aux.part_status = logica.part_status;

                            printf("\n    while Puntero %d",puntero);

                            if(puntero!=-1){
                                    if(strcmp(namep,logica.part_name)==0 && logica.part_status=='1'){
                                           if(logica.part_size > quitar){
                                                   calculo = logica.part_size - quitar;
                                                   aux.part_size = calculo;
                                                   fseek(mn,puntero,SEEK_SET);
                                                   fwrite(&aux,sizeof(ebr),1,mn);
                                            }
                                           bandera = 1;
                                     }
                                     puntero = aux.part_next;
                             }else{
                                    printf("\n    else bandera = 1");
                                    printf("\n    PARTICION NO EXISTE ");
                                    bandera = 1;
                             }
                        }
                   }
                }//fin del si existe == 1
                else{
                    printf("\n Particion no existe");
                }

            }// fin del else

          fseek(mn, 0, SEEK_SET);
          fwrite(&escritura,sizeof(mbr),1,mn);

    }
    fclose(mn);

}
void graphdisk(char* name,char* ruta){
    printf("    Entre al metodo ebr");
    int start_partition=0;
    int puntero=0;
    char auxp[10];
    int contador=0;
    FILE *mn = fopen(name,"r+b");
    FILE *disk = fopen("graphdisk.txt","w+");
    fprintf(disk,"digraph Grafica{ rankdir = TB; \n node [shape=record, style = filled, fillcolor = lightblue]; \n node [shape=record]; \n subgraph D{ nodoM[label=\"MBR\",height=0.9];");
    if(mn != NULL){
        printf("    Abri graph");
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
          if(lectura.mbr_partition_1.part_status=='1'){
              if(lectura.mbr_partition_1.part_type=='P'){
                  fprintf(disk,"nodeP1[label=\"Primaria\",height=0.9];");
              }
              if(lectura.mbr_partition_1.part_type=='E'){
                  fprintf(disk,"nodeP1[label=\"Extendida\",height=0.9];");
                  ebr logica;
                  fseek(mn,lectura.mbr_partition_1.part_start,SEEK_SET);
                  fread(&logica,sizeof(ebr),1,mn);
                  printf("\n    P1 EBR PUNTERO %d",lectura.mbr_partition_1.part_start);

                  if(logica.part_next==-1){
                          printf("\n    logica.part_next == -1");
                          if(logica.part_size!=0 && logica.part_status!='0'){
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              fprintf(disk,"nodeB1[label=\"EBR\",height=0.9,fillcolor = orange];");
                              fprintf(disk,"nodeL1[label=\"Logica\",height=0.9,fillcolor = orange];");
                              //fprintf(disk,"}");
                          }
                          if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                              fprintf(disk,"nodeFree");
                              sprintf(auxp,"%d",contador);
                              fprintf(disk,auxp);
                              fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                          }
                  }

                          else{
                              printf("\n    else");
                              int bandera=0;
                              puntero = logica.part_start;
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              while(bandera==0){

                                  fseek(mn,puntero,SEEK_SET);
                                  fread(&logica,sizeof(ebr),1,mn);
                                  printf("\n    while Puntero %d",puntero);
                                  contador = contador + 1;
                                  if(puntero!=-1){

                                      printf("\n    entre al puntero !=-1 p1");



                                      if(logica.part_status=='1'){

                                          fprintf(disk,"nodeB");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"EBR\",height=0.9,fillcolor = orange];");

                                          fprintf(disk,"nodeL");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Logica\",height=0.9,fillcolor=orange];");

                                      }else{
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }


                                      if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }

                                      puntero = logica.part_next;


                                  }else{
                                      printf("\n    else bandera = 1");
                                      bandera = 1;
                                  }
                             }
                             //fprintf(disk,"}");
                          }
              }
          }
          else{
              fprintf(disk,"nodeP1[label=\"Libre\",height=0.9];");
          }
          if(lectura.mbr_partition_2.part_status=='1'){
              if(lectura.mbr_partition_2.part_type=='P'){
                  fprintf(disk,"nodeP2[label=\"Primaria\",height=0.9];");
              }
              if(lectura.mbr_partition_2.part_type=='E'){
                  fprintf(disk,"nodeP2[label=\"Extendida\",height=0.9];");

                  ebr logica;
                  fseek(mn,lectura.mbr_partition_2.part_start,SEEK_SET);
                  fread(&logica,sizeof(ebr),1,mn);
                  printf("\n    P2 EBR PUNTERO %d",lectura.mbr_partition_2.part_start);

                  if(logica.part_next==-1){
                          printf("\n    logica.part_next == -1");
                          if(logica.part_size!=0 && logica.part_status!='0'){
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              fprintf(disk,"nodeB1[label=\"EBR\",height=0.9,fillcolor = orange];");
                              fprintf(disk,"nodeL1[label=\"Logica\",height=0.9,fillcolor=orange];");
                              //fprintf(disk,"}");
                          }
                          if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                              fprintf(disk,"nodeFree");
                              sprintf(auxp,"%d",contador);
                              fprintf(disk,auxp);
                              fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                          }
                  }

                          else{
                              printf("\n    else");
                              int bandera=0;
                              puntero = logica.part_start;
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              while(bandera==0){

                                  fseek(mn,puntero,SEEK_SET);
                                  fread(&logica,sizeof(ebr),1,mn);
                                  printf("\n    while Puntero %d",puntero);
                                  contador = contador + 1;
                                  if(puntero!=-1){
                                      printf("\n    entre al puntero !=-1");

                                      if(logica.part_status=='1'){

                                          fprintf(disk,"nodeB");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"EBR\",height=0.9,fillcolor = orange];");

                                          fprintf(disk,"nodeL");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"Logica\",height=0.9,fillcolor=orange];");

                                      }else{
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }


                                      if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }

                                      puntero = logica.part_next;
                                  }else{
                                      printf("\n    else bandera = 1");
                                      bandera = 1;
                                  }
                             }
                              //fprintf(disk,"}");
                          }
              }
          }
          else {
               fprintf(disk,"nodeP2[label=\"Libre\",height=0.9];");
          }
          if(lectura.mbr_partition_3.part_status=='1'){
              if(lectura.mbr_partition_3.part_type=='P'){
                  fprintf(disk,"nodeP3[label=\"Primaria\",height=0.9];");
              }
              if(lectura.mbr_partition_3.part_type=='E'){
                  fprintf(disk,"nodeP3[label=\"Extendida\",height=0.9];");

                  ebr logica;
                  fseek(mn,lectura.mbr_partition_3.part_start,SEEK_SET);
                  fread(&logica,sizeof(ebr),1,mn);
                  printf("\n    P3 EBR PUNTERO %d",lectura.mbr_partition_3.part_start);

                  if(logica.part_next==-1){
                          printf("\n    logica.part_next == -1");
                          if(logica.part_size!=0 && logica.part_status!='0'){
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              fprintf(disk,"nodeB1[label=\"EBR\",height=0.9,fillcolor = orange];");
                              fprintf(disk,"nodeL1[label=\"Logica\",height=0.9,fillcolor=orange];");
                              //fprintf(disk,"}");
                          }
                          if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                              fprintf(disk,"nodeFree");
                              sprintf(auxp,"%d",contador);
                              fprintf(disk,auxp);
                              fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                          }
                  }

                          else{
                              printf("\n    else");
                              int bandera=0;
                              puntero = logica.part_start;
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              while(bandera==0){

                                  fseek(mn,puntero,SEEK_SET);
                                  fread(&logica,sizeof(ebr),1,mn);
                                  printf("\n    while Puntero %d",puntero);
                                  contador = contador + 1;
                                  if(puntero!=-1){
                                      printf("\n    entre al puntero !=-1");


                                      if(logica.part_status=='1'){

                                          fprintf(disk,"nodeB");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"EBR\",height=0.9,fillcolor = orange];");

                                          fprintf(disk,"nodeL");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"Logica\",height=0.9,fillcolor=orange];");

                                      }else{
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }


                                      if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }


                                      puntero = logica.part_next;
                                  }else{
                                      printf("\n    else bandera = 1");
                                      bandera = 1;
                                  }
                             }
                             //fprintf(disk,"}");
                          }
              }
          }
          else{
               fprintf(disk,"nodeP3[label=\"Libre\",height=0.9];");
          }
          if(lectura.mbr_partition_4.part_status=='1'){
              if(lectura.mbr_partition_4.part_type=='P'){
                  fprintf(disk,"nodeP4[label=\"Primaria\",height=0.9];");
              }
              if(lectura.mbr_partition_4.part_type=='E'){
                  fprintf(disk,"nodeP4[label=\"Extendida\",height=0.9];");
                  ebr logica;
                  fseek(mn,lectura.mbr_partition_4.part_start,SEEK_SET);
                  fread(&logica,sizeof(ebr),1,mn);
                  printf("\n   p4 EBR PUNTERO %d",lectura.mbr_partition_4.part_start);

                  if(logica.part_next==-1){
                          printf("\n    logica.part_next == -1");
                          if(logica.part_size!=0 && logica.part_status!='0'){
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              fprintf(disk,"nodeB1[label=\"EBR\",height=0.9,fillcolor = orange];");
                              fprintf(disk,"nodeL1[label=\"Logica\",height=0.9,fillcolor=orange];");
                              //fprintf(disk,"}");
                          }
                          if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                              fprintf(disk,"nodeFree");
                              sprintf(auxp,"%d",contador);
                              fprintf(disk,auxp);
                              fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                          }
                  }

                          else{
                              printf("\n    else");
                              int bandera=0;
                              puntero = logica.part_start;
                              //fprintf(disk,"subgraph cluster_01 { label=\"Extendida\";");
                              while(bandera==0){

                                  fseek(mn,puntero,SEEK_SET);
                                  fread(&logica,sizeof(ebr),1,mn);
                                  printf("\n    while Puntero %d",puntero);
                                  contador = contador + 1;
                                  if(puntero!=-1){
                                      printf("\n    entre al puntero !=-1");


                                      if(logica.part_status=='1'){

                                          fprintf(disk,"nodeB");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"EBR\",height=0.9,fillcolor = orange];");

                                          fprintf(disk,"nodeL");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          fprintf(disk,"[label=\"Logica\",height=0.9,fillcolor=orange];");

                                      }else{
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }


                                      if(logica.part_next>logica.part_start+logica.part_size+sizeof(ebr)){
                                          fprintf(disk,"nodeFree");
                                          sprintf(auxp,"%d",contador);
                                          fprintf(disk,auxp);
                                          //fprintf(disk,logica.part_name);
                                          fprintf(disk,"[label=\"Libre\",height=0.9,fillcolor = yellow];");
                                      }

                                      puntero = logica.part_next;
                                  }else{
                                      printf("\n    else bandera = 1");
                                      bandera = 1;
                                  }
                             }
                              //fprintf(disk,"}");
                          }


              }
          }
          else{
                  fprintf(disk,"nodeP4[label=\"Libre\",height=0.9];");
          }





          int libre=lectura.mbr_partition_1.part_start;
          int cal = lectura.mbr_partition_1.part_start + lectura.mbr_partition_1.part_size;
          if(libre<lectura.mbr_partition_2.part_start){
                libre = lectura.mbr_partition_2.part_start;
                cal = lectura.mbr_partition_2.part_start + lectura.mbr_partition_2.part_size;
          }else{
              if(libre<lectura.mbr_partition_3.part_start){
                  libre = lectura.mbr_partition_3.part_start;
                  cal = lectura.mbr_partition_3.part_start + lectura.mbr_partition_3.part_size;
              }else{
                  if(libre<lectura.mbr_partition_4.part_start){
                      libre = lectura.mbr_partition_4.part_start;
                      cal = lectura.mbr_partition_4.part_start + lectura.mbr_partition_4.part_size;
                  }
              }
          }

          if(cal<lectura.mbr_tamano){
              fprintf(disk,"nodeP5[label=\"Libre\",height=0.9];");
          }
          fprintf(disk,"} }");  // close del archivo

          fclose (disk);

          //system("dot -Tpng graphdisk.txt -o disk.png");
          char sys[]="dot -Tpng graphdisk.txt -o ";
          strcat(sys,"'");
          strcat(sys,ruta);
          strcat(sys,"'");

          system(sys);

          char sys2[]="display ";

          strcat(sys2,"'");
          strcat(sys2,ruta);
          strcat(sys2,"'");

          system(sys2);
    }
    fclose(mn);

}
void graphebr(char* name,char* ruta){
    printf("    Entre al metodo ebr");
    int start_partition=0;
    int puntero=0;
    FILE *mn = fopen(name,"r+b");
    if(mn != NULL){
        printf("    Abri graph");
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
          if(lectura.mbr_partition_1.part_type=='E' && lectura.mbr_partition_1.part_status=='1'){
              start_partition = lectura.mbr_partition_1.part_start;
              printf("    graph p1 %d",start_partition);
          }
          else if(lectura.mbr_partition_2.part_type=='E' && lectura.mbr_partition_2.part_status=='1'){
              start_partition = lectura.mbr_partition_2.part_start;
              printf("    graph p2 %d",start_partition);
          }
          else if(lectura.mbr_partition_3.part_type=='E' && lectura.mbr_partition_3.part_status=='1'){
              start_partition = lectura.mbr_partition_3.part_start;
              printf("    graph p3 %d",start_partition);
          }
          else if(lectura.mbr_partition_4.part_type=='E' && lectura.mbr_partition_4.part_status=='1'){
              start_partition = lectura.mbr_partition_4.part_start;
              printf("    graph p4 %d",start_partition);
          }else{
              start_partition = -1;
              printf("    graph -1");
          }

          if(start_partition!=-1){

                ebr logica;
                FILE* disk;
                char auxp[10];
                int contador = 0;
                disk = fopen("graphebr.txt","w+");
                fprintf(disk,"digraph grafica { \n rankdir = LR; \n \"node1\"[label= \"{REPORTE EBR}|");

                fseek(mn,start_partition,SEEK_SET);
                fread(&logica,sizeof(ebr),1,mn);


                if(logica.part_next==-1){
                    printf("   adentro del part next == -1");

                        if(logica.part_size!=0 && logica.part_status!='0'){
                            printf(" adentro del size status");
                            fprintf(disk,"{EBR 1}");
                            fprintf(disk,"|{part_status_1|");
                            sprintf(auxp,"%c",logica.part_status);
                            fprintf(disk,auxp);

                            fprintf(disk,"}|{part_fit_1|");
                            sprintf(auxp,"%c",logica.part_fit);
                            fprintf(disk,auxp);

                            fprintf(disk,"}|{part_start_1|");
                            sprintf(auxp,"%d",logica.part_start);
                            fprintf(disk,auxp);

                            fprintf(disk,"}|{part_size_1|");
                            sprintf(auxp,"%d",logica.part_size);
                            fprintf(disk,auxp);

                            fprintf(disk,"}|{part_next_1|");
                            sprintf(auxp,"%d",logica.part_next);
                            fprintf(disk,auxp);

                            fprintf(disk,"}|{part_name_1|");
                            fprintf(disk,logica.part_name);

                    }

                    printf("    Creando ebr logica ==-1");
                }
                else{

                    printf("    Creando ebr logica dif -1");
                    int bandera=0;
                    puntero = logica.part_start;


                    while(bandera==0){

                        fseek(mn,puntero,SEEK_SET);
                        fread(&logica,sizeof(ebr),1,mn);

                        contador = contador + 1;
                        if(puntero!=-1){
                            if(logica.part_status=='1'){
                                fprintf(disk,"{EBR ");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_status_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                sprintf(auxp,"%c",logica.part_status);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_fit_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                sprintf(auxp,"%c",logica.part_fit);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_start_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                sprintf(auxp,"%d",logica.part_start);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_size_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                sprintf(auxp,"%d",logica.part_size);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_next_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                sprintf(auxp,"%d",logica.part_next);
                                fprintf(disk,auxp);

                                fprintf(disk,"}|{part_name_");
                                sprintf(auxp,"%d",contador);
                                fprintf(disk,auxp);
                                fprintf(disk,"|");
                                fprintf(disk,logica.part_name);
                                fprintf(disk,"}|");

                            }

                            puntero = logica.part_next;
                        }else{
                            bandera = 1;
                        }
                   }

                }

                fprintf(disk,"}\" shape = \"record\"];}");  // close del archivo

                fclose (disk);

                //system("dot -Tpng graph.txt -o mbr.png");
                char sys[]="dot -Tpng graphebr.txt -o ";
                strcat(sys,"'");
                strcat(sys,ruta);
                strcat(sys,"'");
                system(sys);
                char sys2[]="display ";

                strcat(sys2,"'");
                strcat(sys2,ruta);
                strcat(sys2,"'");

                system(sys2);

           } // si start_partition != -1

    }
    fclose(mn);

}
void graphmbr(char* name,char* ruta){
    //variables
    int mbr_tamano; //tamaño del mbr;
    char auxmbr_tamano[10]; //char auxiliar para tamaño del mbr
    char auxmbr_disk_signature[10]; //char auxiliar para el disk signature
    char mbr_fecha_creacion[18]; //fecha del mbr
    int mbr_disk_signature; //id del disco duro

    //variables para particion 1
    char auxp1[10];
    int p1_status;
    char p1_type;
    char p1_fit;
    int p1_start;
    int p1_size;
    char p1_name[16];

    //variables para particion 2
    char auxp2[10];
    int p2_status;
    char p2_type;
    char p2_fit;
    int p2_start;
    int p2_size;
    char p2_name[16];

    //variables para particion 3
    char auxp3[10];
    int p3_status;
    char p3_type;
    char p3_fit;
    int p3_start;
    int p3_size;
    char p3_name[16];

    //variables para particion 4
    char auxp4[10];
    int p4_status;
    char p4_type;
    char p4_fit;
    int p4_start;
    int p4_size;
    char p4_name[16];
    int qq=0;
    int q=0;
    //variables para ebr
    int ebrpuntero=-1;

    FILE *mn = fopen(name,"r+b");
    if(mn != NULL){
        mbr lectura;
        ebr logica;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
            mbr_tamano=lectura.mbr_tamano;
            mbr_disk_signature=lectura.mbr_disk_signature;
            //particion 1
                if(lectura.mbr_partition_1.part_status==49){ p1_status=1;}
                if(lectura.mbr_partition_1.part_status==48){ p1_status=0;}
                if(lectura.mbr_partition_1.part_type=='2'){ ebrpuntero=lectura.mbr_partition_1.part_start; }
                p1_type = lectura.mbr_partition_1.part_type;
                p1_fit = lectura.mbr_partition_1.part_fit;
                p1_start = lectura.mbr_partition_1.part_start;
                p1_size = lectura.mbr_partition_1.part_size;
                strcpy(p1_name,lectura.mbr_partition_1.part_name);
            //particion 2
                if(lectura.mbr_partition_2.part_status==49){ p2_status=1;}
                if(lectura.mbr_partition_2.part_status==48){ p2_status=0;}
                if(lectura.mbr_partition_2.part_type=='2'){ ebrpuntero=lectura.mbr_partition_2.part_start; }
                p2_type = lectura.mbr_partition_2.part_type;
                p2_fit = lectura.mbr_partition_2.part_fit;
                p2_start = lectura.mbr_partition_2.part_start;
                p2_size = lectura.mbr_partition_2.part_size;
                strcpy(p2_name,lectura.mbr_partition_2.part_name);
            //particion 3
                if(lectura.mbr_partition_3.part_status==49){ p3_status=1;}
                if(lectura.mbr_partition_3.part_status==48){ p3_status=0;}
                if(lectura.mbr_partition_3.part_type=='2'){ ebrpuntero=lectura.mbr_partition_3.part_start; }
                p3_type = lectura.mbr_partition_3.part_type;
                p3_fit = lectura.mbr_partition_3.part_fit;
                p3_start = lectura.mbr_partition_3.part_start;
                p3_size = lectura.mbr_partition_3.part_size;
                strcpy(p3_name,lectura.mbr_partition_3.part_name);

            //particion 4
                if(lectura.mbr_partition_4.part_status==49){ p4_status=1;}
                if(lectura.mbr_partition_4.part_status==48){ p4_status=0;}
                if(lectura.mbr_partition_4.part_type=='2'){ ebrpuntero=lectura.mbr_partition_4.part_start;}
                p4_type = lectura.mbr_partition_4.part_type;
                p4_fit = lectura.mbr_partition_4.part_fit;
                p4_start = lectura.mbr_partition_4.part_start;
                p4_size = lectura.mbr_partition_4.part_size;
                strcpy(p4_name,lectura.mbr_partition_4.part_name);

                strcpy(mbr_fecha_creacion,lectura.mbr_fecha_creacion);


            fread(&lectura,sizeof(mbr),1,mn);

            //fseek(mn,ebrpuntero, SEEK_SET);
            //fread(&logica,sizeof(ebr),1,mn);
    }
    fclose(mn);

//    printf("FECHA DE GRAFICA: %s",mbr_fecha_creacion);
    FILE *disk;
    disk = fopen("graph.txt","w+");
    fprintf(disk,"digraph grafica { \n rankdir = LR; \n \"node1\"[label= \"{MBR}|{Nombre|Valor}|{mbr_tamano|");

    sprintf(auxmbr_tamano,"%d",mbr_tamano);
    fprintf(disk,auxmbr_tamano);
    fprintf(disk,"}|{mbr_fecha_creacion|");
    fprintf(disk,mbr_fecha_creacion);

    fprintf(disk,"}|{mbr_disk_signature|");
    sprintf(auxmbr_disk_signature,"%d",mbr_disk_signature);
    fprintf(disk,auxmbr_disk_signature);

    if(p1_status==1){
    //particion 1
    fprintf(disk,"}|{Part_status_1|");
    sprintf(auxp1,"%d",p1_status);
    fprintf(disk,auxp1);

    fprintf(disk,"}|{Part_type_1|");
    sprintf(auxp1,"%c",p1_type);
    fprintf(disk,auxp1);

    fprintf(disk,"}|{Part_fit_1|");
    sprintf(auxp1,"%c",p1_fit);
    fprintf(disk,auxp1);

    fprintf(disk,"}|{Part_start_1|");
    sprintf(auxp1,"%d",p1_start);
    fprintf(disk,auxp1);

    fprintf(disk,"}|{Part_size_1|");
    sprintf(auxp1,"%d",p1_size);
    fprintf(disk,auxp1);

    fprintf(disk,"}|{Part_name_1|");
    fprintf(disk,p1_name);
    }
    if(p2_status==1){
    //particion 2
    fprintf(disk,"}|{Part_status_2|");
    sprintf(auxp2,"%d",p2_status);
    fprintf(disk,auxp2);

    fprintf(disk,"}|{Part_type_2|");
    sprintf(auxp2,"%c",p2_type);
    fprintf(disk,auxp2);

    fprintf(disk,"}|{Part_fit_2|");
    sprintf(auxp2,"%c",p2_fit);
    fprintf(disk,auxp2);

    fprintf(disk,"}|{Part_start_2|");
    sprintf(auxp2,"%d",p2_start);
    fprintf(disk,auxp2);

    fprintf(disk,"}|{Part_size_2|");
    sprintf(auxp2,"%d",p2_size);
    fprintf(disk,auxp2);

    fprintf(disk,"}|{Part_name_2|");
    fprintf(disk,p2_name);
    }

    if(p3_status==1){
    //particion 3
    fprintf(disk,"}|{Part_status_3|");
    sprintf(auxp3,"%d",p3_status);
    fprintf(disk,auxp3);

    fprintf(disk,"}|{Part_type_3|");
    sprintf(auxp3,"%c",p3_type);
    fprintf(disk,auxp3);

    fprintf(disk,"}|{Part_fit_3|");
    sprintf(auxp3,"%c",p3_fit);
    fprintf(disk,auxp3);

    fprintf(disk,"}|{Part_start_3|");
    sprintf(auxp3,"%d",p3_start);
    fprintf(disk,auxp3);

    fprintf(disk,"}|{Part_size_3|");
    sprintf(auxp3,"%d",p3_size);
    fprintf(disk,auxp3);

    fprintf(disk,"}|{Part_name_3|");
    fprintf(disk,p3_name);
    }

    if(p4_status==1){
    //particion 4
    fprintf(disk,"}|{Part_status_4|");
    sprintf(auxp4,"%d",p4_status);
    fprintf(disk,auxp4);

    fprintf(disk,"}|{Part_type_4|");
    sprintf(auxp4,"%c",p4_type);
    fprintf(disk,auxp4);

    fprintf(disk,"}|{Part_fit_4|");
    sprintf(auxp4,"%c",p4_fit);
    fprintf(disk,auxp4);

    fprintf(disk,"}|{Part_start_4|");
    sprintf(auxp4,"%d",p4_start);
    fprintf(disk,auxp4);

    fprintf(disk,"}|{Part_size_4|");
    sprintf(auxp4,"%d",p4_size);
    fprintf(disk,auxp4);

    fprintf(disk,"}|{Part_name_4|");
    fprintf(disk,p4_name);
    }

    fprintf(disk,"}\" shape = \"record\"];}");  // close del archivo

    fclose (disk);

    //system("dot -Tpng graph.txt -o mbr.png");
    char sys[]="dot -Tpng graph.txt -o ";
    strcat(sys,"'");
    strcat(sys,ruta);
    strcat(sys,"'");
    system(sys);

    char sys2[]="display ";

    strcat(sys2,"'");
    strcat(sys2,ruta);
    strcat(sys2,"'");

    system(sys2);
}

int ordenar(int a[]){
    int i;
    int j;
    int aux;
    for(i=1;i<4;i++){
        for(j=0;j<4-i;j++){
            if(a[j] > a[j+1]){
                aux = a[j];
                a[j]=a[j+1];
                a[j+1]=aux;
            }
        }
    }
    for(i=0;i<4;i++){
        printf("    \n  ------%d",a[i]);
    }
}

void add_logica(char* path,int typepart,int sizenuevo,char namep[16],char ajuste,int unit){
    int extstart;
    int extsize;
    int existe=0;

    if(unit==0){        // si es cero se tomara como kilo
        sizenuevo = sizenuevo*1024;
    }else if(unit==1){  // byte
        sizenuevo = sizenuevo;
    }else if(unit==2){  // kilo
        sizenuevo = sizenuevo*1024;
    }else if(unit==3){  // Mega
        sizenuevo = sizenuevo*1024*1024;
    }

    FILE *mn = fopen(path,"rb+");
    if(mn != NULL){
        printf("\n ACCEDI AL --MBR");
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
        if((lectura.mbr_partition_1.part_type=='e'||lectura.mbr_partition_1.part_type=='E')){
            if(lectura.mbr_partition_1.part_status=='1'){
                extstart = lectura.mbr_partition_1.part_start;
                extsize = lectura.mbr_partition_1.part_size;
                existe = 1;
            }
        }
        else if((lectura.mbr_partition_2.part_type=='e'||lectura.mbr_partition_2.part_type=='E')){
            if(lectura.mbr_partition_2.part_status=='1'){
                extstart = lectura.mbr_partition_2.part_start;
                extsize = lectura.mbr_partition_2.part_size;
                existe = 1;
            }

        }
        else if((lectura.mbr_partition_3.part_type=='e'||lectura.mbr_partition_3.part_type=='E')){
            if(lectura.mbr_partition_3.part_status=='1'){
                extstart = lectura.mbr_partition_3.part_start;
                extsize = lectura.mbr_partition_3.part_size;
                existe = 1;
            }

        }
        else if((lectura.mbr_partition_4.part_type=='e'||lectura.mbr_partition_4.part_type=='E')){
            if(lectura.mbr_partition_4.part_status=='1'){
                extstart = lectura.mbr_partition_4.part_start;
                extsize = lectura.mbr_partition_4.part_size;
                existe = 1;
            }

        }else{
            printf("NO EXISTE PARTICION EXTENDIDA");
            existe = 0;
        }
        printf("\n ---------EXTENDIDA EMPIEZA EN BYTE %d",extstart);
    }else{
        printf("\n NO SE PUDO ACCEDER AL DISCO");
    }
    fclose(mn);

    if(existe==1){

        FILE *arch = fopen(path,"rb+");
        if(arch!=NULL){
            printf("\n ACCEDI AL EBR");
            ebr q;
            ebr t;
            ebr nuevo;
            fseek(arch,extstart,SEEK_SET);
            fread(&q,sizeof(ebr),1,arch);
            printf("\n  SIZE DE LA PARTICION %d",extsize);
            //SI NO EXISTE NINGUNA PARTICION LÓGICA
            if(q.part_status=='0' && q.part_start==extstart && q.part_next==-1 && q.part_size==0){

                printf("\n NO EXISTE NINGUNA PARTICION LÓGICA ");

                int espacio = extsize - sizeof(ebr);
                printf("\n ESPACIO EN PARTICION EXTENDIDA... %d",espacio);
                printf("\n INICIO DE PARTICION EXTENDIDA... %d",extstart);
                if(sizenuevo<=espacio){
                    q.part_fit = ajuste;
                    int g=0;
                    for(g=0;g<=15;g++){
                      q.part_name[g] = namep[g];
                    }
                    q.part_next = -1;
                    q.part_size = sizenuevo;
                    q.part_start = extstart;
                    q.part_status = '1';
                    printf("\n      SE INSERTO PARTICION LOGICA");

                    fseek(arch,extstart,SEEK_SET);
                    // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                    fwrite(&q,sizeof(q),1,arch);
                }
                else{
                    printf("\n      ESPACIO INSUFICIENTE EN PARTICION EXTENDIDA");
                }

            }
            //SI EL PRIMER EBR FUE ELIMINADO PERO EXISTEN PARTICIONES LOGICAS
            else if(q.part_status=='0' && q.part_start==extstart && q.part_next!=-1 && q.part_size!=0){

                printf("\n PRIMER EBR  EXISTEN MAS PARTICIONES LOGICAS");

                int espacio = q.part_next - q.part_start - sizeof(ebr);

                printf("\n ESPACIO EN PARTICION EXTENDIDA... %d",espacio);
                printf("\n INICIO DE PARTICION EXTENDIDA... %d",extstart);

                int nextaux = q.part_next;

                if(sizenuevo<=espacio){
                    q.part_fit = ajuste;
                    int g=0;
                    for(g=0;g<=15;g++){
                        q.part_name[g] = namep[g];
                    }
                    q.part_next = nextaux;
                    q.part_size = sizenuevo;
                    q.part_start = extstart;
                    q.part_status = '1';
                    printf("\n      SE INSERTO PARTICION LOGICA");

                    fseek(arch,extstart,SEEK_SET);
                    // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                    fwrite(&q,sizeof(q),1,arch);
                }
                else{

                                    int bandera=0;
                                    int punwhile=extstart;
                                    while(bandera==0){

                                        fseek(arch,punwhile,SEEK_SET);
                                        fread(&q,sizeof(ebr),1,arch);
                                        //calculo espacio entre particiones
                                        if(q.part_next!=-1){
                                            int espacio = q.part_next - sizeof(ebr) -q.part_start - sizeof(ebr) - q.part_size;

                                            if(espacio>=sizenuevo){
                                                printf("\n ---------INSERTAR ENTRE PARTICIONES");
                                                printf("\n ESPACIO ENTRE PARTICIONES... %d",espacio);
                                                printf("\n INICIO DE CALCULO.... %d",q.part_start);
                                                //escribo el bloque actual en el que estoy y modifico su puntero next que ahora apunta al inicio

                                                int inicio = q.part_start + sizeof(ebr) + q.part_size;
                                                printf("\n INICIO DE NUEVA PARTICION...%d",inicio);
                                                printf("\n SIZE DE NUEVA PARTICION...%d",sizenuevo);
                                                int inicionuevo = q.part_next;
                                                t.part_fit = q.part_fit;
                                                strcpy(t.part_name,q.part_name);
                                                t.part_next = inicio;
                                                t.part_size = q.part_size;
                                                t.part_start = q.part_start;
                                                t.part_status = q.part_status;

                                                fseek(arch,t.part_start,SEEK_SET);
                                                // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                                fwrite(&t,sizeof(ebr),1,arch);

                                                //escribo el bloque nuevo inicia en inicio con next -1
                                                nuevo.part_fit = ajuste;
                                                int g=0;
                                                for(g=0;g<=15;g++){
                                                    nuevo.part_name[g] = namep[g];
                                                }
                                                nuevo.part_next = inicionuevo;
                                                nuevo.part_size = sizenuevo;
                                                nuevo.part_start = inicio;
                                                nuevo.part_status = '1';
                                                fseek(arch,inicio,SEEK_SET);
                                                printf("\n      INICIO DE PARTICION... %d",inicio);
                                                // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                                fwrite(&nuevo,sizeof(ebr),1,arch);
                                                printf("\n      SE INSERTO PARTICION LOGICA");
                                                bandera = 1;
                                            }else{
                                                punwhile = q.part_next;
                                                bandera = 0;
                                            }

                                        } // fin del if next!=-1
                                        else if(q.part_next==-1){
                                            printf("        extsize %d extstart %d",extsize,extstart);
                                            int espacio = extsize - sizeof(ebr) - q.part_size - sizeof(ebr)-q.part_start + extstart;

                                            printf("\n ESPACIO LIBRE... %d",espacio);
                                                if(espacio>=sizenuevo){

                                                    printf("\n extsize %d Q.START  %d  SIZEOF(EBR) %d      Q.SIZE %d  ",extsize,q.part_start,sizeof(ebr),q.part_size);
                                                    printf("\n ---------INSERTAR PARTICION AL FINAL");


                                                    //escribo el bloque actual
                                                    int inicio = q.part_start + sizeof(ebr) + q.part_size;
                                                    printf("\n INICIO DE NUEVA PARTICION...%d",inicio);
                                                    printf("\n SIZE DE NUEVA PARTICION...%d",sizenuevo);
                                                    t.part_fit = q.part_fit;
                                                    strcpy(t.part_name,q.part_name);
                                                    t.part_next = inicio;
                                                    t.part_size = q.part_size;
                                                    t.part_start = q.part_start;
                                                    t.part_status = q.part_status;

                                                    fseek(arch,t.part_start,SEEK_SET);
                                                    // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                                    fwrite(&t,sizeof(ebr),1,arch);

                                                    //escribo el bloque nuevo inicia en inicio con next -1
                                                    nuevo.part_fit = ajuste;
                                                    int g=0;
                                                    for(g=0;g<=15;g++){
                                                        nuevo.part_name[g] = namep[g];
                                                    }
                                                    nuevo.part_next = -1;
                                                    nuevo.part_size = sizenuevo;
                                                    nuevo.part_start = inicio;
                                                    nuevo.part_status = '1';
                                                    fseek(arch,inicio,SEEK_SET);
                                                    printf("\n      INICIO DE PARTICION.. %d",inicio);

                                                    // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                                    fwrite(&nuevo,sizeof(ebr),1,arch);
                                                    printf("\n SE INSERTO PARTICION LOGICA");
                                                    bandera = 1;

                                                }else{
                                                    printf("\n  NO HAY SUFICIENTE ESPACIO PARA PARTICION LOGICA");
                                         //         punwhile = q.part_next;
                                                    bandera = 1;
                                                }
                                        } //fin del else if next ==-1

                                        fseek(arch,extstart,SEEK_SET);
                                        fread(&q,sizeof(ebr),1,arch);

                                    }   //fin del while

                    //printf("\n    ESPACIO INSUFICIENTE EN PARTICION EXTENDIDA");
                }
            }else{

                int bandera=0;
                int punwhile=extstart;
                while(bandera==0){

                    fseek(arch,punwhile,SEEK_SET);
                    fread(&q,sizeof(ebr),1,arch);
                    //calculo espacio entre particiones
                    if(q.part_next!=-1){
                        int espacio = q.part_next - sizeof(ebr) -q.part_start - sizeof(ebr) - q.part_size;

                        if(espacio>=sizenuevo){
                            printf("\n ---------INSERTAR ENTRE PARTICIONES");
                            printf("\n ESPACIO ENTRE PARTICIONES... %d",espacio);
                            printf("\n INICIO DE CALCULO.... %d",q.part_start);
                            //escribo el bloque actual en el que estoy y modifico su puntero next que ahora apunta al inicio

                            int inicio = q.part_start + sizeof(ebr) + q.part_size;
                            printf("\n INICIO DE NUEVA PARTICION...%d",inicio);
                            printf("\n SIZE DE NUEVA PARTICION...%d",sizenuevo);
                            int inicionuevo = q.part_next;
                            t.part_fit = q.part_fit;
                            strcpy(t.part_name,q.part_name);
                            t.part_next = inicio;
                            t.part_size = q.part_size;
                            t.part_start = q.part_start;
                            t.part_status = q.part_status;

                            fseek(arch,t.part_start,SEEK_SET);
                            // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                            fwrite(&t,sizeof(ebr),1,arch);

                            //escribo el bloque nuevo inicia en inicio con next -1
                            nuevo.part_fit = ajuste;
                            int g=0;
                            for(g=0;g<=15;g++){
                                nuevo.part_name[g] = namep[g];
                            }
                            nuevo.part_next = inicionuevo;
                            nuevo.part_size = sizenuevo;
                            nuevo.part_start = inicio;
                            nuevo.part_status = '1';
                            fseek(arch,inicio,SEEK_SET);
                            printf("\n      INICIO DE PARTICION... %d",inicio);
                            // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                            fwrite(&nuevo,sizeof(ebr),1,arch);
                            printf("\n      SE INSERTO PARTICION LOGICA");
                            bandera = 1;
                        }else{
                            punwhile = q.part_next;
                            bandera = 0;
                        }

                    } // fin del if next!=-1
                    else if(q.part_next==-1){
                        printf("        extsize %d extstart %d",extsize,extstart);
                        int espacio = extsize - sizeof(ebr) - q.part_size - sizeof(ebr)-q.part_start + extstart;

                        printf("\n ESPACIO LIBRE... %d",espacio);
                            if(espacio>=sizenuevo){

                                printf("\n extsize %d Q.START  %d  SIZEOF(EBR) %d      Q.SIZE %d  ",extsize,q.part_start,sizeof(ebr),q.part_size);
                                printf("\n ---------INSERTAR PARTICION AL FINAL");


                                //escribo el bloque actual
                                int inicio = q.part_start + sizeof(ebr) + q.part_size;
                                printf("\n INICIO DE NUEVA PARTICION...%d",inicio);
                                printf("\n SIZE DE NUEVA PARTICION...%d",sizenuevo);
                                t.part_fit = q.part_fit;
                                strcpy(t.part_name,q.part_name);
                                t.part_next = inicio;
                                t.part_size = q.part_size;
                                t.part_start = q.part_start;
                                t.part_status = q.part_status;

                                fseek(arch,t.part_start,SEEK_SET);
                                // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                fwrite(&t,sizeof(ebr),1,arch);

                                //escribo el bloque nuevo inicia en inicio con next -1
                                nuevo.part_fit = ajuste;
                                int g=0;
                                for(g=0;g<=15;g++){
                                    nuevo.part_name[g] = namep[g];
                                }
                                nuevo.part_next = -1;
                                nuevo.part_size = sizenuevo;
                                nuevo.part_start = inicio;
                                nuevo.part_status = '1';
                                fseek(arch,inicio,SEEK_SET);
                                printf("\n      INICIO DE PARTICION.. %d",inicio);

                                // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
                                fwrite(&nuevo,sizeof(ebr),1,arch);
                                printf("\n SE INSERTO PARTICION LOGICA");
                                bandera = 1;

                            }else{
                                printf("\n  NO HAY SUFICIENTE ESPACIO PARA PARTICION LOGICA");
                     //         punwhile = q.part_next;
                                bandera = 1;
                            }
                    } //fin del else if next ==-1

                    fseek(arch,extstart,SEEK_SET);
                    fread(&q,sizeof(ebr),1,arch);

                }   //fin del while
            }

        }
        else{
            printf("NO SE PUDO ACCEDER AL EBR");
        }
        fclose(arch);

    }

}
void add_particion(char* path,int typepart,int sizepart,char namep[16],char ajuste,int unit){
    FILE *mn = fopen(path,"rb+");
    if(unit==0){        // si es cero se tomara como kilo
        sizepart = sizepart*1024;
    }else if(unit==1){  // byte
        sizepart = sizepart;
    }else if(unit==2){  // kilo
        sizepart = sizepart*1024;
    }else if(unit==3){  // Mega
        sizepart = sizepart*1024*1024;
    }
    int existe=0;
    int unitdisk=0; // unidad de almacenamiento del disco duro
    int bandera=2;  // indica si es posible o no el añadir una nueva particion P o E    1 = si 0 = no
    int pri=0;  // contador de partidas P
    int ext=0;  // contador de partidas E
    int npart=0;// contador de partidas P y E
    //ARREGLOS DE INICIO Y FIN
    int iniciop[4];
    int finp[4];
    //TEMPORAES QUE CALCULAN POSICION FINAL
    int tempf0;
    int tempf1;
    int tempf2;
    int tempf3;
    //VALORES DEL ESPACIO LIBRE
    int size1;
    int size2;
    int size3;
    int size4;
    //TAMAÑO DEL DISCO DURO
    int sizedisk;
    //VARIABLE TYPO
    char typo;
    //VARIABLE PARA EL CICLO DEL PART_NAME
    int g;
    //VARIABLE PARA EL BYTE DE PARTICION EXTENDIDA
    int punteroext;
    if(mn != NULL){
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
        // cuento cuantas extendidas existen  max. 1
                                                                    //  TAMAÑO DEL DISCO DURO
        sizedisk=lectura.mbr_tamano;

        printf("    \n DISCO DURO  SIZE %d",sizedisk);
        if(lectura.mbr_partition_1.part_status=='1' && lectura.mbr_partition_1.part_type=='E'){
            ext = ext + 1;
        }
        if(lectura.mbr_partition_2.part_status=='1' && lectura.mbr_partition_2.part_type=='E'){
            ext = ext + 1;
        }
        if(lectura.mbr_partition_3.part_status=='1' && lectura.mbr_partition_3.part_type=='E'){
            ext = ext + 1;
        }
        if(lectura.mbr_partition_4.part_status=='1' && lectura.mbr_partition_4.part_type=='E'){
            ext = ext + 1;
        }
        // cuento cuantas primarias existen max. 4
        if(lectura.mbr_partition_1.part_status=='1' && lectura.mbr_partition_1.part_type=='P'){
            pri=pri+1;
        }
        if(lectura.mbr_partition_2.part_status=='1' && lectura.mbr_partition_2.part_type=='P'){
            pri=pri+1;
        }
        if(lectura.mbr_partition_3.part_status=='1' && lectura.mbr_partition_3.part_type=='P'){
            pri=pri+1;
        }
        if(lectura.mbr_partition_4.part_status=='1' && lectura.mbr_partition_4.part_type=='P'){
            pri=pri+1;
        }
        npart = pri + ext;
        if(typepart==2){ // si es una particion extendida
            printf("\n particion extendida");
            if(pri<=3){
                if(ext==0){
                    bandera = 1;
                    printf("\n Si existe espacio para particion");
                }
                else{
                    bandera = 0;
                    printf("\n Ya existe 1 particion Extendida \n");
                }
            }
            else{
                bandera = 0;
                printf(" \n Error ya existen 4 particiones \n ");
            }
        }
        if(typepart==1){ // si es una particion primaria
            printf("\n particion primaria");
            if(npart<=3){
                bandera = 1;
                printf("\n Si existe espacio para particion");
            }
            else{
                bandera = 0;
                printf("\n Ya existen 4 particiones \n");
            }
        }

        //TYPO DE PARTICION

        if(typepart==1){
            typo='P';
        }
        if(typepart==2){
            typo='E';
        }
        if(bandera==1){ // si podemos insertar nueva particion
              printf("\n CALCULANDO ESPACIO....");
              if(lectura.mbr_partition_1.part_status=='1'){
                  tempf0 = lectura.mbr_partition_1.part_size  + lectura.mbr_partition_1.part_start; // posicion final de cada particion
              }else{
                  tempf0 = lectura.mbr_partition_1.part_start;
              }

              if(lectura.mbr_partition_2.part_status=='1'){
                  tempf1 = lectura.mbr_partition_2.part_size  + lectura.mbr_partition_2.part_start;
              }else{
                  tempf1 = lectura.mbr_partition_2.part_start;
              }

              if(lectura.mbr_partition_3.part_status=='1'){
                  tempf2 = lectura.mbr_partition_3.part_size  + lectura.mbr_partition_3.part_start;
              }else{
                  tempf2 = lectura.mbr_partition_3.part_start;
              }

              if(lectura.mbr_partition_4.part_status=='1'){
                  tempf3 = lectura.mbr_partition_4.part_size  + lectura.mbr_partition_4.part_start;
              }else{
                  tempf3 = lectura.mbr_partition_4.part_start;
              }

              printf("          \n temp1 %d ",tempf0);
              printf("          \n temp2 %d ",tempf1);
              printf("          \n temp3 %d ",tempf2);
              printf("          \n temp4 %d ",tempf3);
              iniciop[0]=lectura.mbr_partition_1.part_start;    //posicion inicial de cada particion
              iniciop[1]=lectura.mbr_partition_2.part_start;
              iniciop[2]=lectura.mbr_partition_3.part_start;
              iniciop[3]=lectura.mbr_partition_4.part_start;
              finp[0]=tempf0;
              finp[1]=tempf1;
              finp[2]=tempf2;
              finp[3]=tempf3;
              ordenar(iniciop);
              ordenar(finp);
              size1 = iniciop[1] - finp[0];
              size2 = iniciop[2] - finp[1];
              size3 = iniciop[3] - finp[2];
              size4 = sizedisk - finp[3];
              printf("\n    size1 -----------%d",size1);
              printf("\n    size2 -----------%d",size2);
              printf("\n    size3 -----------%d",size3);
              printf("\n    size4 -----------%d",size4);
              printf("\n SIZE OF PARTITION ----%d ",sizepart);
              if(size1>=sizepart){
                  printf("\n SIZE 1");
                  punteroext = finp[0];
                  if(lectura.mbr_partition_1.part_status=='0'){
                      printf("\n        PART1");
                      lectura.mbr_partition_1.part_start = finp[0];
                      lectura.mbr_partition_1.part_size = sizepart;
                      lectura.mbr_partition_1.part_status = '1';
                      lectura.mbr_partition_1.part_type = typo;
                      lectura.mbr_partition_1.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_1.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_2.part_status=='0'){
                      printf("\n        PART2");
                      lectura.mbr_partition_2.part_start = finp[0];
                      lectura.mbr_partition_2.part_size = sizepart;
                      lectura.mbr_partition_2.part_status = '1';
                      lectura.mbr_partition_2.part_type = typo;
                      lectura.mbr_partition_2.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_2.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_3.part_status=='0'){
                      printf("\n        PART3");
                      lectura.mbr_partition_3.part_start = finp[0];
                      lectura.mbr_partition_3.part_size = sizepart;
                      lectura.mbr_partition_3.part_status = '1';
                      lectura.mbr_partition_3.part_type = typo;
                      lectura.mbr_partition_3.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_3.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_4.part_status=='0'){
                      printf("\n        PART4");
                      lectura.mbr_partition_4.part_start = finp[0];
                      lectura.mbr_partition_4.part_size = sizepart;
                      lectura.mbr_partition_4.part_status = '1';
                      lectura.mbr_partition_4.part_type = typo;
                      lectura.mbr_partition_4.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_4.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
              }else if(size2>=sizepart){
                  punteroext = finp[1];
                  printf("\n        SIZE 2");
                  if(lectura.mbr_partition_1.part_status=='0'){
                      printf("\n        PART1");
                      lectura.mbr_partition_1.part_start = finp[1];
                      lectura.mbr_partition_1.part_size = sizepart;
                      lectura.mbr_partition_1.part_status = '1';
                      lectura.mbr_partition_1.part_type = typo;
                      lectura.mbr_partition_1.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_1.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_2.part_status=='0'){
                      printf("\n        PART2");
                      lectura.mbr_partition_2.part_start = finp[1];
                      lectura.mbr_partition_2.part_size = sizepart;
                      lectura.mbr_partition_2.part_status = '1';
                      lectura.mbr_partition_2.part_type = typo;
                      lectura.mbr_partition_2.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_2.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_3.part_status=='0'){
                      printf("\n        PART3");
                      lectura.mbr_partition_3.part_start = finp[1];
                      lectura.mbr_partition_3.part_size = sizepart;
                      lectura.mbr_partition_3.part_status = '1';
                      lectura.mbr_partition_3.part_type = typo;
                      lectura.mbr_partition_3.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_3.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_4.part_status=='0'){
                      printf("\n        PART4");
                      lectura.mbr_partition_4.part_start = finp[1];
                      lectura.mbr_partition_4.part_size = sizepart;
                      lectura.mbr_partition_4.part_status = '1';
                      lectura.mbr_partition_4.part_type = typo;
                      lectura.mbr_partition_4.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_4.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
              }else if(size3>=sizepart){
                  punteroext = finp[2];
                  printf("\n        SIZE 3");
                  if(lectura.mbr_partition_1.part_status=='0'){
                      printf("\n        PART1");
                      lectura.mbr_partition_1.part_start = finp[2];
                      lectura.mbr_partition_1.part_size = sizepart;
                      lectura.mbr_partition_1.part_status = '1';
                      lectura.mbr_partition_1.part_type = typo;
                      lectura.mbr_partition_1.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_1.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_2.part_status=='0'){
                      printf("\n        PART2");
                      lectura.mbr_partition_2.part_start = finp[2];
                      lectura.mbr_partition_2.part_size = sizepart;
                      lectura.mbr_partition_2.part_status = '1';
                      lectura.mbr_partition_2.part_type = typo;
                      lectura.mbr_partition_2.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_2.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_3.part_status=='0'){
                      printf("\n        PART3");
                      lectura.mbr_partition_3.part_start = finp[2];
                      lectura.mbr_partition_3.part_size = sizepart;
                      lectura.mbr_partition_3.part_status = '1';
                      lectura.mbr_partition_3.part_type = typo;
                      lectura.mbr_partition_3.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_3.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_4.part_status=='0'){
                      printf("\n        PART4");
                      lectura.mbr_partition_4.part_start = finp[2];
                      lectura.mbr_partition_4.part_size = sizepart;
                      lectura.mbr_partition_4.part_status = '1';
                      lectura.mbr_partition_4.part_type = typo;
                      lectura.mbr_partition_4.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_4.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
              }else if(size4>=sizepart){
                  punteroext = finp[3];
                  printf("\n SIZE 4");
                  if(lectura.mbr_partition_1.part_status=='0'){
                      //printf("\n        PART1");
                      lectura.mbr_partition_1.part_start = finp[3];
                      //printf("\n        PART1 start");
                      lectura.mbr_partition_1.part_size = sizepart;
                      //printf("\n        PART1 size");

                      lectura.mbr_partition_1.part_status = '1';
                      //printf("\n        PART1 status");

                      lectura.mbr_partition_1.part_type = typo;

                      //printf("\n        PART1 type");
                      lectura.mbr_partition_1.part_fit = ajuste;

                      //printf("\n        PART1  fit");
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_1.part_name[g] = namep[g];
                      }
                      //printf("\n        PART1 name");
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_2.part_status=='0'){
                      printf("\n        PART2");
                      lectura.mbr_partition_2.part_start = finp[3];
                      lectura.mbr_partition_2.part_size = sizepart;
                      lectura.mbr_partition_2.part_status = '1';
                      lectura.mbr_partition_2.part_type = typo;
                      lectura.mbr_partition_2.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_2.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_3.part_status=='0'){
                      printf("\n        PART3");
                      lectura.mbr_partition_3.part_start = finp[3];
                      lectura.mbr_partition_3.part_size = sizepart;
                      lectura.mbr_partition_3.part_status = '1';
                      lectura.mbr_partition_3.part_type = typo;
                      lectura.mbr_partition_3.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_3.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
                  else if(lectura.mbr_partition_4.part_status=='0'){
                      printf("\n        PART4");
                      lectura.mbr_partition_4.part_start = finp[3];
                      lectura.mbr_partition_4.part_size = sizepart;
                      lectura.mbr_partition_4.part_status = '1';
                      lectura.mbr_partition_4.part_type = typo;
                      lectura.mbr_partition_4.part_fit = ajuste;
                      for(g=0;g<=15;g++){
                        lectura.mbr_partition_4.part_name[g] = namep[g];
                      }
                      existe = 1;
                  }
              }else {

                  printf("\n No hay suficiente espacio en el disco \n");
                  existe = 0;
              }
              fseek(mn,0,SEEK_SET);
              // escribo la estructura de tipo mbr, con un tamaño de mbr, una vez, en el archivo mbrdisco
              fwrite(&lectura,sizeof(lectura),1,mn);
        }

    }
    fclose(mn);

    if(bandera==1 && typepart==2 && existe==1){
        printf("   \n --- Partition Extendida start %d ",punteroext);
        add_ebr(path,ajuste,punteroext);
    }


}

int add_ebr(char* path,int ajuste,int start){
    FILE *mbrdisco = fopen(path,"rb+");
    if(mbrdisco){
        ebr nuevoebr;

        nuevoebr.part_fit = ajuste;
        //nuevoebr.part_name = '';
        nuevoebr.part_next = -1;
        nuevoebr.part_size = 0;
        nuevoebr.part_start = start;
        nuevoebr.part_status = '0';
        fseek(mbrdisco,start,SEEK_SET);
        // escribo la estructura de tipo ebr, con un tamaño de ebr, una vez, en el archivo ebrdisco
        fwrite(&nuevoebr,sizeof(nuevoebr),1,mbrdisco);
        printf("\n Se inserto el EBR exitosamente \n");
    }else{
        printf("\n No se inserto el EBR Fail \n");
    }
    fclose(mbrdisco);
    return 0;
}
int leer_ebr(char* path,int puntero){
        FILE *mn = fopen(path,"r+b");
        if(mn != NULL){
            ebr lectura;
            fseek(mn, puntero, SEEK_SET);
            fread(&lectura,sizeof(ebr),1,mn);
            //while(!feof(mn)){
                printf("\n");
                printf("\n EBR\n ebr_status: %c",lectura.part_status);
                printf("\n ebr_fit: %c",lectura.part_fit);
                printf("\n ebr_name: %s",lectura.part_name);
                printf("\n ebr_next: %d",lectura.part_next);
                printf("\n ebr_size: %d",lectura.part_size);
                printf("\n ebr_start: %d",lectura.part_start);

                fread(&lectura,sizeof(ebr),1,mn);
           // }
        }
        fclose(mn);
    return 0;
}
int leer_mbs(char* path){
        FILE *mn = fopen(path,"r+b");
        if(mn != NULL){
            mbr lectura;
            fseek(mn, 0, SEEK_SET);
            fread(&lectura,sizeof(mbr),1,mn);
            //while(!feof(mn)){
                printf("\nmbs_tamano: %d\n",lectura.mbr_tamano);
                int k;
                printf("mbs_fecha_creacion ");
                //for(k=0;k<16;k++){
                printf("%s",lectura.mbr_fecha_creacion);
                //}
                printf("\n");
                printf("mbs_disk_signature: %d\n",lectura.mbr_disk_signature);
                printf("mbs_partition_1 start: %d size: %d name: %s fit: %c type: %c status: %c\n",lectura.mbr_partition_1.part_start,lectura.mbr_partition_1.part_size,lectura.mbr_partition_1.part_name,lectura.mbr_partition_1.part_fit,lectura.mbr_partition_1.part_type,lectura.mbr_partition_1.part_status);
                printf("mbs_partition_2 start: %d size: %d name: %s fit: %c type: %c status: %c\n",lectura.mbr_partition_2.part_start,lectura.mbr_partition_2.part_size,lectura.mbr_partition_2.part_name,lectura.mbr_partition_2.part_fit,lectura.mbr_partition_2.part_type,lectura.mbr_partition_2.part_status);
                printf("mbs_partition_3 start: %d size: %d name: %s fit: %c type: %c status: %c\n",lectura.mbr_partition_3.part_start,lectura.mbr_partition_3.part_size,lectura.mbr_partition_3.part_name,lectura.mbr_partition_3.part_fit,lectura.mbr_partition_3.part_type,lectura.mbr_partition_3.part_status);
                printf("mbs_partition_4 start: %d size: %d name: %s fit: %c type: %c status: %c\n",lectura.mbr_partition_4.part_start,lectura.mbr_partition_4.part_size,lectura.mbr_partition_4.part_name,lectura.mbr_partition_4.part_fit,lectura.mbr_partition_4.part_type,lectura.mbr_partition_4.part_status);
                fread(&lectura,sizeof(mbr),1,mn);
           // }
        }
        fclose(mn);
    return 0;
}

//metodo para eliminar disco

int rmdisk(char* path){
        char confirmar='r';
        int estado=2;
        FILE *mbrdisco = fopen(path,"r+b");

        if(mbrdisco!=NULL){
            estado=1;
            printf("\n Se encontro disco \n");
        }else if(mbrdisco==NULL){
            estado=0;
        }
        fclose(mbrdisco);
        printf("\n ...");

        if(estado==1){

            printf("\n Desea eliminar el disco?  %s  s/n ?",path);
            //scanf("%c",&confirmar);

            gets(&confirmar);

            printf("\n confirmar close %c",confirmar);
            if(confirmar=='s' || confirmar=='S'){
                if(remove(path)==0) // Eliminamos el archivo
                      printf("\n El disco fue eliminado satisfactoriamente \n");
                else
                      printf("\n No se pudo eliminar el disco \n");
            }
            else{
                        printf("\n Se cancelo eliminacion");
            }

        }
        else if(estado==0){
            printf("\n No se encontro disco... \n");
        }

        return 0;
}

int leerbin(char* path){
    FILE *pFichero;
    unsigned char byte; /* Un char suele ser 8 bits = byte (No siempre)  */
    pFichero=fopen("/home/jorge/kilo.txt", "r+b"); /* "rb" posiblemente tambien funcione */
    while(!feof(pFichero)){ /* feof comprueba si llegas al final del fichero */
       byte=fgetc(pFichero); /* Cada vez que es invocada la funcion fgetc el puntero del fichero se incrementa un byte */
       printf("%c",byte);
    }
    fclose(pFichero);

   getchar();
   return 0;

}
//metodo para leer script spliteado por medio de enter

void leercode(char *ruta){
            char buf[BUFFER_SIZE];
            int count=0;
            FILE *arch;
            arch=fopen(ruta,"r");
            while(fgets(buf,sizeof(buf),arch))
            {
                count=count+1;
                analizador(buf);
                //printf("    ---- %s ",buf);
            }
            printf(" Lines %d ",count);
            fclose(arch);
}


//metodo para verificar si existe el nombre de una particion en el sistema de archivos retorna 0 si no existe nombre y 1 si existe el nombre.

int existename(char* path,char* name){
    int retorno=0;
    int puntero=-1;
    FILE *mn = fopen(path,"r+b");

    if(mn != NULL){
        mbr lectura;
        fseek(mn, 0, SEEK_SET);
        fread(&lectura,sizeof(mbr),1,mn);
        printf("\n verificando name en mbr....");
        //si existe partida extendida
        if(lectura.mbr_partition_1.part_status=='1' && lectura.mbr_partition_1.part_type=='E'){  puntero=lectura.mbr_partition_1.part_start;  }
        if(lectura.mbr_partition_2.part_status=='1' && lectura.mbr_partition_2.part_type=='E'){  puntero=lectura.mbr_partition_2.part_start;  }
        if(lectura.mbr_partition_3.part_status=='1' && lectura.mbr_partition_3.part_type=='E'){  puntero=lectura.mbr_partition_3.part_start;  }
        if(lectura.mbr_partition_4.part_status=='1' && lectura.mbr_partition_4.part_type=='E'){  puntero=lectura.mbr_partition_4.part_start;  }

        //si la partida existe
        if(lectura.mbr_partition_1.part_status=='1' && strcmp(name,lectura.mbr_partition_1.part_name)==0){  retorno=1; }
        else if(lectura.mbr_partition_2.part_status=='1' && strcmp(name,lectura.mbr_partition_2.part_name)==0){  retorno=1; }
        else if(lectura.mbr_partition_3.part_status=='1' && strcmp(name,lectura.mbr_partition_3.part_name)==0){  retorno=1; }
        else if(lectura.mbr_partition_4.part_status=='1' && strcmp(name,lectura.mbr_partition_4.part_name)==0){  retorno=1; }
        else{

            if(puntero!=-1){
                printf("\n verificando name en logicas.... puntero %d",puntero);
                ebr logica;
                fseek(mn,puntero,SEEK_SET);
                fread(&logica,sizeof(ebr),1,mn);


                if(logica.part_next==-1){
                        if(logica.part_size!=0 && logica.part_status!='0'){
                                if(strcmp(name,logica.part_name)==0 && logica.part_status=='1'){
                                        retorno=1;
                                 }
                         }
                 } // fin logica == -1


                else{
                    printf("\n    else");
                    int bandera=0;
                    puntero = logica.part_start;

                    while(bandera==0){

                       fseek(mn,puntero,SEEK_SET);
                       fread(&logica,sizeof(ebr),1,mn);

                       printf("\n    while Puntero %d",puntero);
                       if(puntero!=-1){
                               if(strcmp(name,logica.part_name)==0 && logica.part_status=='1'){
                                      printf("\n logica name = 0   status = 1");
                                      retorno = 1;
                                      bandera = 1;
                                }
                                puntero = logica.part_next;
                        }else{
                               printf("\n    No existeparticion ------");
                               bandera = 1;
                        }
                   }
              } // fin del else

            }//puntero !=-1
        }// else despues del else if


    ;}// fin del if mn
    fclose(mn);

    return retorno;

}



int main(void)
{



    char cadena [100];
    printf("\n CONSOLA!\n");

    printf(" SYSTEMA DE ARCHIVOS EXT2 \n USAC \n 201314631 \n IMPLEMENTACION EXT2 \n");

    int i=0;
    int j=0;
    for(i=0;i<26;i++){
        path[i]="";
        numero[i]=0;
    }

    for(i=0;i<51;i++){
        montada[i]="";
        particion[i]="";
        dir[j]="";
    }

    int enc=0;
    while(enc==0){
        printf("\n >: ");
        gets(cadena);
        //printf("\n command %s \n",cadena);
        analizador(cadena);
    }


    printf("\n estoy aqui");

    return 0;

}

