#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main(void) {
    Libro biblioteca[MAX_LIBROS];
    int contador;
    int opcion;

    inicializarBiblioteca(biblioteca, &contador);

    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Agregar libro\n");
        printf("2. Buscar libro por ID\n");
        printf("3. Buscar libro por titulo\n");
        printf("4. Actualizar estado\n");
        printf("5. Mostrar libros\n");
        printf("6. Eliminar libro\n");
        printf("7. Salir\n");
        printf("Seleccione opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                agregarLibro(biblioteca, &contador);
                break;

            case 2: {
                int id;
                printf("ID: ");
                scanf("%d", &id);
                getchar();
                int pos = buscarLibroPorID(biblioteca, contador, id);
                if (pos >= 0) {
                    printf("Libro encontrado:\n");
                    printf("ID: %d\nTitulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                           biblioteca[pos].id,
                           biblioteca[pos].titulo,
                           biblioteca[pos].autor,
                           biblioteca[pos].anio,
                           biblioteca[pos].estado);
                } else {
                    printf("No existe ese ID.\n");
                }
                break;
            }

            case 3: {
                char titulo[MAX_TITULO];
                printf("Título: ");
                getchar();
                fgets(titulo, MAX_TITULO, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                int pos = buscarLibroPorTitulo(biblioteca, contador, titulo);
                if (pos >= 0) {
                    printf("Libro encontrado:\n");
                    printf("ID: %d\nTitulo: %s\nAutor: %s\nAño: %d\nEstado: %s\n",
                           biblioteca[pos].id,
                           biblioteca[pos].titulo,
                           biblioteca[pos].autor,
                           biblioteca[pos].anio,
                           biblioteca[pos].estado);
                } else {
                    printf("No existe ese título.\n");
                }
                break;
            }

            case 4:
                actualizarEstado(biblioteca, contador);
                break;

            case 5:
                mostrarLibros(biblioteca, contador);
                break;

            case 6:
                eliminarLibro(biblioteca, &contador);
                break;

            case 7:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
                break;
        }

    } while (opcion != 7);

    return 0;
}
