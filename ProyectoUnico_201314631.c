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
/*
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
*/



//------------------------------------------PRIMERA PARTE---------------------------------------------------------------------------------------------------------------------------------------------


int convertir_cadena_a_entero(char *cad)
{
    int num;
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



//----------------------------AQUI EMPEZAMOS CON LA PRIMERA FASE "PARTES CREADORAS"----------------------------------------




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

int mkdisk(char* path,int size,int unit,char* nombre){
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
                else if((cadena[j]==45)||(cadena[j]==43)){                        // guion normal o signo mas
                  //   printf("\n detecte un - o un +);
                        //pasa todo a minuscula
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

            case 1: //detecta los parametros para el comando mkdisk (size,unit,path,name)
                //printf("\n Posicion %d",j);

                if((cadena[j]>=65) && (cadena[j]<=122)){    // letras a-z
                    estado=1;
                    //printf("\n Estado 1: letra %c",cadena[j]);
                    prueba[counter] = cadena[j];
                    counter++;
                }
                else if((cadena[j]==58)&&(cadena[j+1]==58)){            //DOS PUNTOS
                     printf("\n detecte dos dos puntos");
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
                         }//----------------NAME------------------------------------------------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                           else if((prueba[0]=='n') && (prueba[1]=='a') && (prueba[2]=='m') && (prueba[3]=='e')){
                            printf("\n parametro: path");
                            estado = PENDIENTE;
                            counter = 0;
                            int k;
                            for(k=0;k<lon;k++){
                                 prueba[k]=NULL;
                            }
                         }

                         else {
                            printf("\n parameter: erroneo ");
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
                else if((cadena[j]==45)||(cadena[j]==43)){                        // - o +
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
                        mkdisk(mkpath,mksize,mkunit,mknombre);
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
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            graphInodo(auxdisk,reppath,part);
                            //graphInodo("/home/jorge/SS.dsk","/home/jorge/Inodo.png","part1");

                        }else if(strcmp(repname,"block")==0 || strcmp(repname,"BLOCK")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            graphBloque(auxdisk,reppath,part);

                        }else if(strcmp(repname,"bm_inode")==0 || strcmp(repname,"BM_INODE")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapbitInodo(auxdisk,reppath,part);

                        }else if(strcmp(repname,"bm_block")==0 || strcmp(repname,"BM_BLOCK")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapbitBloque(auxdisk,reppath,part);

                        }else if(strcmp(repname,"tree")==0 || strcmp(repname,"TREE")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            graphThree(auxdisk,reppath,part);

                        }else if(strcmp(repname,"sb")==0 || strcmp(repname,"SB")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            grapSuperBloque(auxdisk,reppath,part);

                        }else if(strcmp(repname,"file")==0 || strcmp(repname,"FILE")==0){
                            char* auxdisk = dardirectory(montada,dir,repid);
                            char* part = darpath(montada,particion,repid);
                            leer_archivo(auxdisk,part,ruta2,iduser,idgrp);
                            grapharchivo(part);

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
                    mkfs(auxdisk,part);
                    if(contadorformat==1){
                        raizu();
                    }else{
                        int ajuste = fit_particion(auxdisk,part);
                        eliminar(auxdisk,part,"/users.txt",1,1);
                        crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/hola.txt",1,1,1,0);
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

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);

                        int ajuste = fit_particion(auxdisk,part);
                        eliminar(auxdisk,part,"/users.txt",1,1);
                        crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/hola.txt",1,1,1,0);
                    }else{
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

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);

                        int ajuste = fit_particion(auxdisk,part);
                        eliminar(auxdisk,part,"/users.txt",1,1);
                        crear_archivo(auxdisk,part,1,"/users.txt","/home/jorge/hola.txt",1,1,1,0);
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

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);

                        printf("\n          path %s         particion %s        fit %d",auxdisk,part,ajuste);
                        if(size2==-1){
                             crear_archivo(auxdisk,part,ajuste,path2,cont2,iduser,idgrp,recursivo,0);
                        }else{
                             archivo_numeros(size2);
                             crear_archivo(auxdisk,part,ajuste,path2,"/home/jorge/numeros.txt",iduser,idgrp,recursivo,0);
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

                        leer_archivo(auxdisk,part,path2,iduser,idgrp);
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
                        eliminar(auxdisk,part,path2,iduser,idgrp);
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

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);

                        printf("\n          path %s         particion %s        fit %d",auxdisk,part,ajuste);
                        if(size2==-1){
                             eliminar(auxdisk,part,path2,iduser,idgrp);
                             crear_archivo(auxdisk,part,ajuste,path2,cont2,iduser,idgrp,0,0);
                        }else{
                             eliminar(auxdisk,part,path2,iduser,idgrp);
                             archivo_numeros(size2);
                             crear_archivo(auxdisk,part,ajuste,path2,"/home/jorge/numeros.txt",iduser,idgrp,0,0);
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
                        renombrar(auxdisk,part,name2,path2,iduser,idgrp);
                    }else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==33){
                    if(iduser!=-1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
                        crear_directorio(auxdisk,part,ajuste,path2,iduser,idgrp,recursivo);
                    }else{
                        printf("\n      NO SE HA LOGUEADO");
                    }
                }else if(action==35){
                    if(iduser!=-1){
                        printf("    ACTION: %d   COMANDO \n",action);
                        printf("        ~ID: %s",id2);
                        printf("        ~PATH: %s \n ",path2);
                        printf("        ~DEST: %s \n ",dest2);
                        printf("        ~IDDEST: %s \n ",iddest2);

                        char* auxdisk = dardirectory(montada,dir,id2);
                        char* part = darpath(montada,particion,id2);
                        int ajuste = fit_particion(auxdisk,part);
                        mover(auxdisk,path2,part,dest2,ajuste,iduser,idgrp);
                    }else{
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
                //printf("\n Estado 8 Posicion %d",j);

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
                else if((cadena[j]==58)&&(cadena[j+1]==58)){                        // DOS PUNTOS
                     printf("\n detecte DOS PUNTOS");
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
                else if((cadena[j]==58)&&(CADENA[J+1]==58)){                        // DOS PUNTOS
                     printf("\n detecte 2 DOS PUNTOS");
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
                else if((cadena[j]==58)&&(cadena[j+1]==58)){                        // DOS PUNTOS
                     printf("\n detecte 2 DOS PUNTOS");
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
                else if((cadena[j]==58)&&(cadena[j+1]==58)){                        // DOS PUNTOS
                     printf("\n detectaron 2 DOS PUNTOS");
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
                else if((cadena[j]==58)&&(cadena[j+1]==58)){                        // DOS PUNTOS
                     printf("\n detecte 2 DOS PUNTOS");
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
                else if((cadena[j]==45)||(cadena[j]==43)){                        // - o +
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
                else if((cadena[j]==45)||(cadena[j]==43)){                        // -
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
                }else if((cadena[j]=='+') ||(cadena[j]=='-') || (cadena[j]=='$') || (cadena[j]=='\n')){                        // guion alto o +

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
                    }else if((cadena[j]=='+') ||(cadena[j]=='-') || (cadena[j]=='$') || (cadena[j]=='\n')){                        // guion alto

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
                    else if((cadena[j]==43) ||(cadena[j]==45)){                        // - o +
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
                else if((cadena[j]=='+') ||(cadena[j]=='-')){                    // - o +
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
                if((cadena[j]=='+') ||(cadena[j]=='-')){                    // - o +
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
                else if((cadena[j]==58)&&(CADENA[J+1]==58)){                        // DOS PUNTOS
                     printf("\n detecte 2 DOS PUNTOS");
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






int main()
{
    printf("Hello world!\n");
    return 0;
}

