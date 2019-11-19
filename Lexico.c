#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool FLAG_LITERAL = false;
const char *reservadas[] = {"VAR","PROCEDURE","CALL","OUTPUT","END"};
int N_TOKS=0;
/******* FUNCIONES DE LA LISTA DE TOKENS **********/
typedef struct t{
	int pos;
	int tipo;
	char *val;
	struct t *sig;
}Token;
Token *LISTA_TOKENS;
void pushTok(char * nuevo){
	Token *aux;
	N_TOKS++;
	aux = LISTA_TOKENS;
	if(aux->pos == 0){
        aux->pos = N_TOKS;
        aux->tipo = 1;
        aux->val = nuevo;
        aux->sig = NULL;
	}else{
	    Token *ntok;
        ntok = (Token*)malloc(sizeof(Token));
        ntok->pos = N_TOKS;
        ntok->tipo = 1;
        ntok->val = nuevo;
        ntok->sig = NULL;
        while(aux->sig != NULL){
            aux=aux->sig;
        }
        aux->sig = ntok;
	}
}
void imprimirTokens(){
    Token *aux;
    aux = LISTA_TOKENS;
    while(aux->sig != NULL){
        //printf("%s",aux->val);
        aux=aux->sig;
	}
}
/******* FIN FUNCIONES DE LA LISTA DE TOKENS *******/
bool esReservada(char * palabra){
    int longitud = sizeof(reservadas) / sizeof(reservadas[0]);
    for (int c=0;c<longitud;c++){
        if(strcmp(palabra,reservadas[c]) == 0){
            return true;
        }
    }
    return false;
}
void obtenerIds(char * cadena){
    int estado=0;
    char * desde; //MARCA EL INICIO DE LAS CADENAS
    char * nuevo; //DONDE VA A QUEDAR EL STRING EXTRAÍDO
    while (*cadena != '\n'){
        switch(estado){
        case 0:
            if(isalpha(*cadena) !=0 && !FLAG_LITERAL){
                estado = 1;
                desde = cadena;
                cadena++;
            }else if( !FLAG_LITERAL && *cadena == '"'){
                FLAG_LITERAL = true;
                cadena ++;
            }else if( FLAG_LITERAL && *cadena == '"' ){
                FLAG_LITERAL = false;
                cadena++;
            }
            else{
                cadena ++;
            }
            break;
        case 1:
            if( isalpha(*cadena)!=0 || isdigit(*cadena) != 0 ){
                estado = 1;
                cadena++;
            }else{
                estado = 2;
            }
            break;
        case 2:
            nuevo = desde;
            while(*desde != *cadena){
                desde++;
            }
            *desde = '\0'; //SE AGREGA EL FIN DE CADENA
            if (esReservada(nuevo)){
                //pushTok(nuevo);
                printf("RESERVADA: %s\n",nuevo);
            }else{
                printf("ID: %s\n",nuevo);
            }
            estado = 0;
            break;
        }
    }
}
int main(){
    LISTA_TOKENS = (Token*)malloc(sizeof(Token));
    LISTA_TOKENS->pos = N_TOKS;
    LISTA_TOKENS->sig = NULL;
    LISTA_TOKENS->tipo = NULL;
    LISTA_TOKENS->val = NULL;
 	FILE *archivo;
 	char *cadena;
 	int linea=0;
 	cadena = (char*) malloc(100 * sizeof(char));
 	archivo = fopen("Ejemplo1.lpc","r");
 	if (archivo == NULL)
 		exit(1);
 	else{
 	    while (feof(archivo) == 0){
            fgets(cadena,100,archivo);
            linea++;
            //Aquí se guarda en la memoria cada linea del archivo
            //Así recorriendo lo del apuntador cadena podemos analizar caracter por caracter
            obtenerIds(cadena);
            if(FLAG_LITERAL){
                printf("ERROR LEXICO COMILLAS NO CERRADAS EN LA LINEA: %d\n",linea);
                break;
            }
 	    }
 	    imprimirTokens();
        system("PAUSE");
    }
    fclose(archivo);
	return 0;
}
