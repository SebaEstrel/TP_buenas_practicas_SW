#include <stdio.h>
#include <string.h>

int menu(void);

struct lib cargar(void);
void mostrar(struct lib biblioteca[32], int i);
void buscar(struct lib biblioteca[32], int cant);

struct lib{
	char titulo[101]={}; //coloco 100+1 por si el usuario ingresa 100 caracteres, el ultimo sea el final de cadena
	char autor[51]={};
	int ano=0;
};

int main(void) {
int op=0;
int cant=0;
int cantaux=0;
int i=0;
int iaux=0;

struct lib biblioteca [32];
	do{
		op=menu();
		switch(op){
			case 1:
				do{
					printf("\n¿Cuantos libros desea guardar(max 32)?");
					scanf("%d", &cant);
				}while(cant<1 || cant>32);
					
				cantaux= cant+cantaux;
				if(cantaux >32){
					printf("\nRebasó el limite de libros permitido.\n");
					cantaux= cantaux - cant; //Se vuelve el auxiliar a su valor original
				}
				
				for(i=iaux;i<cantaux;i++){
					printf("\n\nLIBRO %d\n", i+1);
					biblioteca[i]= cargar();
				}
				iaux=i;
			break; //Cierre caso 1
				
			case 2:
				for(i=0;i<cantaux;i++){
					mostrar(biblioteca,i);
				}
			break; //Cierre caso 2
				
			case 3:
				buscar(biblioteca, cantaux);
			break; //Cierre caso 3
		}
	}while(op!=0);
}

int menu (void){
	int op=0;
	do{
		printf("\n[1] - Ingresar un nuevo libro desde teclado.");
		printf("\n[2] - Mostrar lista de libros.");
		printf("\n[3] - Buscar libro.");
		printf("\n[0] - Salir\n\n");
		
		scanf("%d", &op);
		
	}while(op<0 || op>3);
	return op;
}

struct lib cargar(){
	struct lib libro;
	int i;
	
	while ((i = getchar()) != '\n' && i != EOF); // Libera el buffer 
	
	printf("\nIngrese el Titulo del libro: ");
	fgets(libro.titulo, sizeof(libro.titulo), stdin);
	libro.titulo[strcspn(libro.titulo, "\n")] = '\0';
	
	printf("\nIngrese el Autor: ");
	fgets(libro.autor, sizeof(libro.autor), stdin);
	libro.autor[strcspn(libro.autor, "\n")] = '\0';
	
	printf("\nIngrese el año de publicacion: ");
	scanf("%d", &libro.ano);
	
	return libro;
}

void mostrar(struct lib biblioteca[], int i){
	printf("\n\nLIBRO %d:\n", i+1);
	printf("Titulo: ");
	fputs(biblioteca[i].titulo, stdout);
	
	printf("\nAutor: ");
	fputs(biblioteca[i].autor, stdout);
	
	printf("\nAño: %d\n\n", biblioteca[i].ano);
}

void buscar(struct lib biblioteca[], int cant){
int i=0;
int op1=0, op2=0;
char nombre[30]={};
char aux[101]={};
int anoaux=0;
int bandera=0; //utilizo una bandera para saber si almenos se encontró un libro
	
	do{
		printf("¿Cómo deseas buscar el libro?");
		printf("\n[1] - Teclado");
		printf("\n[2] - Archivo");
		scanf("%d", &op1);
	}while(op1!= 1 && op1!=2);
	
	do{
		printf("¿Que dato quieres ingresar?");
		printf("[1] - Titulo");
		printf("[2] - Autor");
		printf("[3] - Año");
		scanf("%d", &op2);
	} while(op2<1 || op2>3);
	
	
	switch(op1){
		case 1:
			while ((i = getchar()) != '\n' && i != EOF);
			switch(op2){
				case 1:
					printf("Ingrese el Título: ");
					fgets(aux, sizeof(aux), stdin);
					aux[strcspn(aux, "\n")] = '\0';
					
					for(i=0; i<cant; i++){
						if(strcmp(aux, biblioteca[i].titulo)==0){
							mostrar(biblioteca, i); 
							bandera= 1;
						}
					}
					
					if(bandera==0){
						printf("\nNo se ha encontrado ningun libro con ese titulo.\n\n");
					}
					break;	//Cierre Caso 1
					
				case 2:
				
					printf("Ingrese el Autor: ");
					fgets(aux, sizeof(aux), stdin);
					aux[strcspn(aux, "\n")] = '\0';
					
					for(i=0; i<cant; i++){
						if(strcmp(aux, biblioteca[i].autor)==0){
							mostrar(biblioteca, i); 
							bandera= 1;
						}
					}
					
					if(bandera==0){
						printf("\nNo se ha encontrado ningun libro cde ese autor.\n\n");
					}
					
				break;	//Cierre Caso 2
					
				case 3:
				
					printf("Ingrese el Año: ");
					scanf("%d", &anoaux);
					
					for(i=0; i<cant; i++){
						if(biblioteca[i].ano == anoaux){
							mostrar(biblioteca, i); 
							bandera= 1;
						}
					}
					
					if(bandera==0){
						printf("\nNo se ha encontrado ningun libro de ese año.\n\n");
					}
					
				break;	//Cierre Caso 3
			}
			
		break;

		case 2:
			while ((i = getchar()) != '\n' && i != EOF);
			printf("Nombre del archivo (agregando '.txt' al final): ");
			fgets(nombre, sizeof(nombre), stdin);
			nombre[strcspn(nombre, "\n")] = '\0';
			
			FILE *archivo = fopen(nombre, "r");
			if(archivo != NULL){
				switch(op2){
					
					case 1:
						fgets(aux, sizeof(aux), archivo);
						aux[strcspn(aux, "\n")] = '\0';
						
						for(i=0; i<cant; i++){
							if(strcmp(aux, biblioteca[i].titulo)==0){
								mostrar(biblioteca, i); 
								bandera= 1;
							}
						}
						
						if(bandera==0){
							printf("\nNo se ha encontrado ningun libro con ese titulo.\n\n");
						}
						
					break; //Cierre caso 1
					
					case 2:
						fgets(aux, sizeof(aux), archivo);
						aux[strcspn(aux, "\n")] = '\0';
						
						for(i=0; i<cant; i++){
							if(strcmp(aux, biblioteca[i].autor)==0){
								mostrar(biblioteca, i); 
								bandera= 1;
							}
						}
						
						if(bandera==0){
							printf("\nNo se ha encontrado ningun libro cde ese autor.\n\n");
						}
						
					break;	//Cierre caso 2
					
					case 3:
						fscanf(archivo, "%d", &anoaux);
						
						for(i=0; i<cant; i++){
							if(biblioteca[i].ano == anoaux){
								mostrar(biblioteca, i); 
								bandera= 1;
							}
						}
						
						if(bandera==0){
							printf("\nNo se ha encontrado ningun libro de ese año.\n\n");
						}
						
					break;	//Cierre caso 3
				} //switch	
			}	//if
			else{
				printf("\n\nError al Cargar el archivo\n\n");
			}
			fclose(archivo);
		break;
	}
}

