#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_ESTADO 15

typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int anio;
    char estado[MAX_ESTADO];
} Libro;

void inicializarBiblioteca(Libro biblioteca[], int *contador);
void agregarLibro(Libro biblioteca[], int *contador);
void mostrarLibros(const Libro biblioteca[], int contador);
int buscarLibroPorID(const Libro biblioteca[], int contador, int idBuscado);
int buscarLibroPorTitulo(const Libro biblioteca[], int contador, const char *tituloBuscado);
void actualizarEstado(Libro biblioteca[], int contador);
void eliminarLibro(Libro biblioteca[], int *contador);

#endif
