#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicion de constantes para las opciones del menu... las "macros"

#define OPCION_INGRESAR 1
#define OPCION_MAXIMOS  2
#define OPCION_MOSTRAR  3
#define OPCION_BUSCAR   4
#define OPCION_SALIR    5

typedef struct {
	
	char nombre[50];
	float tension;
	float corriente;
	
} Maquina;

//Cambio el nombre de algunas variables m -> maquina
// Por lo general lo hago por tiempos o comodidad pero si es verdad que despues termino un poco perdido

void ingresarMaquina(Maquina *maquina) {
	
	printf("Ingrese nombre de la maquina: ");
	scanf(" %[^\n]", maquina->nombre);
	printf("Ingrese tension (V): ");
	scanf("%f", &maquina->tension);
	printf("Ingrese corriente (A): ");
	scanf("%f", &maquina->corriente);
}

/**
 * Calcula y muestra los dos valores maximos de tension o corriente entre las maquinas cargadas
 * @param lista_maquinas puntero al arreglo dinamico de maquinas
 * @param cantidad numero actual de maquinas cargadas
 * @param opcion criterio de busqueda 1 = tension 2 = corriente
 */

void Maximos(Maquina *lista_maquinas, int cantidad, int opcion) {
	
	float max1 = -1, max2 = -1;
	int indice1 = -1, indice2 = -1;
	
	for (int i = 0; i < cantidad; i++) {
		
		float valor = (opcion == 1) ? lista_maquinas[i].tension : lista_maquinas[i].corriente;
		
		if (valor > max1) {
			max2 = max1; 
			indice2 = indice1;
			max1 = valor; 
			indice1 = i;
		} else if (valor > max2) {
			max2 = valor; indice2 = i;
			
		}
	}
	
	printf("\nMaximos:\n");
	
	if (indice1 != -1) {
		printf("1º: %s -> %.2f\n", lista_maquinas[indice1].nombre, (opcion == 1) ? lista_maquinas[indice1].tension : lista_maquinas[indice1].corriente);
	}
	if (indice2 != -1) {
		printf("2º: %s -> %.2f\n", lista_maquinas[indice2].nombre, (opcion == 1) ? lista_maquinas[indice2].tension : lista_maquinas[indice2].corriente);
	}
}

//Aca bandera por lista_maquinas... me habia quedado sin ideas entonces fue mas poner por poner

void mostrarLista(Maquina *lista_maquinas, int cantidad) {
	
	if (cantidad == 0) {
		printf("No hay maquinas cargadas.\n");
		return;
	}
	printf("\nLista completa:\n");
	for (int i = 0; i < cantidad; i++) {
		printf("%d) Nombre: %s | Tensión: %.2f V | Corriente: %.2f A\n",
			   i+1, lista_maquinas[i].nombre, lista_maquinas[i].tension, lista_maquinas[i].corriente);
	}
}

/**
 * Permite buscar una maquina dentro del arreglo por diferentes criterios
 * @param lista_maquinas puntero al arreglo dinamico de maquinas
 * @param cantidad numero actual de maquinas cargadas
 */

void buscarMaquina(Maquina *lista_maquinas, int cantidad) {
	
	if (cantidad == 0) {
		printf("No hay maquinas cargadas.\n");
		return;
	}
	
	int opcion;
	printf("\nBuscar por:\n1. Nombre\n2. Tensión\n3. Corriente\nSeleccione: ");
	scanf("%d", &opcion);
	
	if (opcion == 1) {
		
		char nombre[50];
		
		printf("Ingrese nombre a buscar: ");
		scanf(" %[^\n]", nombre);
		
		for (int i = 0; i < cantidad; i++) {
			if (strcmp(lista_maquinas[i].nombre, nombre) == 0) {
				printf("Encontrado: %s | Tensión: %.2f V | Corriente: %.2f A\n",
					   lista_maquinas[i].nombre, lista_maquinas[i].tension, lista_maquinas[i].corriente);
				return;
			}
		}
		
		printf("No se encontro la máquina.\n");
		
	} else if (opcion == 2) {
		
		float valor;
		printf("Ingrese tension a buscar: ");
		scanf("%f", &valor);
		
		for (int i = 0; i < cantidad; i++) {
			if (lista_maquinas[i].tension == valor) {
				printf("Encontrado: %s | Tensión: %.2f V | Corriente: %.2f A\n",
					   lista_maquinas[i].nombre, lista_maquinas[i].tension, lista_maquinas[i].corriente);
				return;
			}
		}
		printf("No se encontro la máquina.\n");
	} else if (opcion == 3) {
		
		float valor;
		printf("Ingrese corriente a buscar: ");
		scanf("%f", &valor);
		
		for (int i = 0; i < cantidad; i++) {
			if (lista_maquinas[i].corriente == valor) {
				printf("Encontrado: %s | Tension: %.2f V | Corriente: %.2f A\n",
					   lista_maquinas[i].nombre, lista_maquinas[i].tension, lista_maquinas[i].corriente);
				return;
			}
		}
		printf("No se encontro la máquina.\n");
	} else {
		printf("Opcion invalida.\n");
	}
}

int main() {
	
	Maquina *maquinas = NULL;
	
	int cantidad = 0;
	int opcion;
	
	do {
		
		printf("\n--- MENU ---\n");
		printf("1. Ingresar nueva maquina\n");
		printf("2. Mostrar maximos\n");
		printf("3. Mostrar lista completa\n");
		printf("4. Buscar maquina\n");
		printf("5. Salir\n");
		printf("Seleccione opcion: ");
		scanf("%d", &opcion);
		
		switch (opcion) {
			
		case OPCION_INGRESAR:
			cantidad++;
			maquinas = (Maquina*) realloc(maquinas, cantidad * sizeof(Maquina));
			if (maquinas == NULL) {
				printf("Error de memoria.\n");
				exit(1);
			}
			ingresarMaquina(&maquinas[cantidad - 1]);
			break;
		case OPCION_MAXIMOS:
			if (cantidad == 0) {
				printf("No hay datos cargados.\n");
			} else {
				int var;
				printf("Seleccione maximo a buscar (1=Tensión, 2=Corriente): ");
				scanf("%d", &var);
				Maximos(maquinas, cantidad, var);
			}
			break;
		case OPCION_MOSTRAR:
			mostrarLista(maquinas, cantidad);
			break;
		case OPCION_BUSCAR:
			buscarMaquina(maquinas, cantidad);
			break;
		case OPCION_SALIR:
			printf("Saliendo...\n");
			break;
		default:
			printf("Opción inválida.\n");
		}
	} while (opcion != OPCION_SALIR); //Habia un 6 en lugar de 5...
	free(maquinas);
	return 0;
}
