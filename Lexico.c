#include <stdio.h>
#include <stdlib.h>

int main(){
 	FILE *archivo;
 	char *cadena;
 	cadena = (char*) malloc(100 * sizeof(char));
 	archivo = fopen("Ejemplo1.lpc","r");

 	if (archivo == NULL)
 		exit(1);
 	else{
 	    while (feof(archivo) == 0){
            fgets(cadena,100,archivo);
            //Aquí se guarda en la memoria cada linea del archivo
            //Así recorriendo lo del apuntador cadena podemos analizar caracter por caracter
            printf("%c",*cadena);
            cadena++;
            printf("%c",*cadena);
            cadena++;
            printf("%c",*cadena);
            cadena++;
            printf("%c\n",*cadena);
 	    }
        system("PAUSE");
    }
    fclose(archivo);
	return 0;
}
