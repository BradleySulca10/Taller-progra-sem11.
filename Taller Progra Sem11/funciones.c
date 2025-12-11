#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funciones.h"

/* ------------------- VALIDADORES ------------------- */

static int soloNumeros(const char *s) {
    if (strlen(s) == 0) return 0;
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

static int soloLetras(const char *s) {
    if (strlen(s) == 0) return 0;
    for (int i = 0; s[i]; i++) {
        if (!isalpha(s[i]) && s[i] != ' ') return 0;
    }
    return 1;
}

/* Leer línea segura */
static void leerLinea(char *buffer, int tam) {
    fgets(buffer, tam, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

/* Comparación case-insensitive */
static int compararCi(const char *a, const char *b) {
    while (*a && *b) {
        char ca = tolower(*a), cb = tolower(*b);
        if (ca != cb) return (ca < cb) ? -1 : 1;
        a++; b++;
    }
    if (*a) return 1;
    if (*b) return -1;
    return 0;
}

/* ----------------- FUNCIONES PRINCIPALES ----------------- */

void inicializarBiblioteca(Libro biblioteca[], int *contador) {
    *contador = 0;
}

int buscarLibroPorID(const Libro biblioteca[], int contador, int idBuscado) {
    for (int i = 0; i < contador; i++) {
        if (biblioteca[i].id == idBuscado)
            return i;
    }
    return -1;
}

int buscarLibroPorTitulo(const Libro biblioteca[], int contador, const char *tituloBuscado) {
    for (int i = 0; i < contador; i++) {
        if (compararCi(biblioteca[i].titulo, tituloBuscado) == 0)
            return i;
    }
    return -1;
}

void agregarLibro(Libro biblioteca[], int *contador) {
    if (*contador >= MAX_LIBROS) {
        printf("ERROR: Biblioteca llena.\n");
        return;
    }

    Libro nuevo;
    char buffer[200];

    /* ----------- VALIDAR ID ----------- */
    do {
        printf("ID (solo números positivos): ");
        leerLinea(buffer, sizeof(buffer));

        if (!soloNumeros(buffer)) {
            printf("Error: solo números.\n");
            continue;
        }

        nuevo.id = atoi(buffer);
        if (nuevo.id <= 0) {
            printf("Error: ID debe ser positivo.\n");
            continue;
        }

        if (buscarLibroPorID(biblioteca, *contador, nuevo.id) != -1) {
            printf("Error: ese ID ya existe.\n");
            continue;
        }

        break;
    } while (1);

    /* ----------- TÍTULO ----------- */
    do {
        printf("Título: ");
        leerLinea(nuevo.titulo, MAX_TITULO);

        if (!soloLetras(nuevo.titulo)) {
            printf("Error: solo letras.\n");
        }
    } while (!soloLetras(nuevo.titulo));

    /* ----------- AUTOR ----------- */
    do {
        printf("Autor: ");
        leerLinea(nuevo.autor, MAX_AUTOR);

        if (!soloLetras(nuevo.autor)) {
            printf("Error: solo letras.\n");
        }
    } while (!soloLetras(nuevo.autor));

    /* ----------- AÑO ----------- */
    int anioTemp;
    do {
        printf("Año de publicación (1000 - 2025): ");
        leerLinea(buffer, sizeof(buffer));

        if (!soloNumeros(buffer)) {
            printf("Error: ingrese solo números.\n");
            continue;
        }

        anioTemp = atoi(buffer);
        if (anioTemp < 1000 || anioTemp > 2025) {
            printf("Error: año fuera de rango.\n");
            continue;
        }

        break;
    } while (1);

    nuevo.anio = anioTemp;

    /* Estado inicial */
    strcpy(nuevo.estado, "Disponible");

    biblioteca[*contador] = nuevo;
    (*contador)++;

    printf("Libro agregado exitosamente.\n");
}

void mostrarLibros(const Libro biblioteca[], int contador) {
    if (contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    printf("\n%-4s | %-6s | %-30s | %-20s | %-6s | %s\n",
           "Pos", "ID", "Título", "Autor", "Año", "Estado");

    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < contador; i++) {
        printf("%-4d | %-6d | %-30s | %-20s | %-6d | %s\n",
               i + 1,
               biblioteca[i].id,
               biblioteca[i].titulo,
               biblioteca[i].autor,
               biblioteca[i].anio,
               biblioteca[i].estado);
    }
}

void actualizarEstado(Libro biblioteca[], int contador) {
    if (contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    char aux[20];
    int id;

    do {
        printf("Ingrese ID para cambiar estado: ");
        leerLinea(aux, sizeof(aux));

        if (!soloNumeros(aux)) {
            printf("Error: solo números.\n");
            continue;
        }

        id = atoi(aux);
        if (id <= 0) {
            printf("Error: ID inválido.\n");
            continue;
        }

        break;
    } while (1);

    int pos = buscarLibroPorID(biblioteca, contador, id);
    if (pos == -1) {
        printf("No existe ese ID.\n");
        return;
    }

    if (strcmp(biblioteca[pos].estado, "Disponible") == 0)
        strcpy(biblioteca[pos].estado, "Prestado");
    else
        strcpy(biblioteca[pos].estado, "Disponible");

    printf("Estado cambiado correctamente.\n");
}

void eliminarLibro(Libro biblioteca[], int *contador) {
    if (*contador == 0) {
        printf("No hay libros registrados.\n");
        return;
    }

    char buffer[50];
    int id;

    do {
        printf("Ingrese ID a eliminar: ");
        leerLinea(buffer, sizeof(buffer));

        if (!soloNumeros(buffer)) {
            printf("Error: solo números.\n");
            continue;
        }

        id = atoi(buffer);
        if (id <= 0) {
            printf("Error: ID inválido.\n");
            continue;
        }

        break;
    } while (1);

    int pos = buscarLibroPorID(biblioteca, *contador, id);
    if (pos == -1) {
        printf("No existe ese ID.\n");
        return;
    }

    for (int i = pos; i < (*contador - 1); i++) {
        biblioteca[i] = biblioteca[i + 1];
    }

    (*contador)--;

    printf("Libro eliminado correctamente.\n");
}
