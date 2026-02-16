/**
 * @file history_manager.c
 * @brief Gestor del historial de comandos
 * 
 * Implementa el almacenamiento y recuperación de los últimos comandos
 * ejecutados por el usuario.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// Definición de las variables globales del historial
char *history[MAX_HISTORY];
int history_count = 0;

/**
 * @brief Añade un comando al historial
 * @param cmd Comando a añadir (cadena de texto)
 * 
 * Mantiene un buffer circular de los últimos MAX_HISTORY comandos.
 * Los comandos vacíos o NULL no se guardan.
 */
void add_to_history(const char *cmd) {
    // Validar: no guardar comandos vacíos o NULL
    if (cmd == NULL || strlen(cmd) == 0) {
        return;
    }
    
    // No duplicar el último comando si es igual al anterior
    if (history_count > 0 && strcmp(history[history_count - 1], cmd) == 0) {
        return;
    }
    
    // Si el historial está lleno, eliminar el más antiguo
    if (history_count == MAX_HISTORY) {
        free(history[0]);  // Liberar memoria del más antiguo
        
        // Desplazar todos los elementos hacia la izquierda
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            history[i] = history[i + 1];
        }
        history_count--;
    }
    
    // Asignar memoria y copiar el comando
    history[history_count] = strdup(cmd);
    if (history[history_count] == NULL) {
        perror("Error: No se pudo guardar en historial");
        return;
    }
    
    history_count++;
}

/**
 * @brief Libera toda la memoria utilizada por el historial
 * 
 * Debe llamarse al salir de la shell para evitar memory leaks.
 */
void free_history() {
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
        history[i] = NULL;
    }
    history_count = 0;
}