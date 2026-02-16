/**
 * @file advanced_commands.c
 * @brief Implementación de comandos avanzados
 * 
 * Incluye: historial, limpiar, buscar y estadisticas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "commands.h"
#include "shell.h"

// ============================================
// COMANDO 1: HISTORIAL
// ============================================

/**
 * @brief Muestra los últimos comandos ejecutados
 * @param args Argumentos (no utilizados)
 * 
 * Recupera el historial almacenado en las variables globales
 * definidas en history_manager.c
 */
void cmd_historial(char **args) {
    (void)args;  // Silenciar warning
    
    printf("\n=== HISTORIAL DE COMANDOS (últimos %d) ===\n", history_count);
    
    if (history_count == 0) {
        printf("  El historial está vacío.\n");
        printf("  Ejecuta algunos comandos para verlos aquí.\n\n");
        return;
    }
    
    for (int i = 0; i < history_count; i++) {
        printf("  %2d: %s\n", i + 1, history[i]);
    }
    printf("\n");
}

// ============================================
// COMANDO 2: LIMPIAR
// ============================================

/**
 * @brief Limpia la pantalla de la terminal
 * @param args Argumentos (no utilizados)
 * 
 * Usa secuencias ANSI para portabilidad entre sistemas.
 */
void cmd_limpiar(char **args) {
    (void)args;
    
    // Secuencias ANSI (funciona en Linux/macOS/terminales modernos)
    printf("\033[2J");  // Limpiar toda la pantalla
    printf("\033[H");   // Mover cursor a inicio (1,1)
    
    // Banner personalizado
    printf("╔══════════════════════════════════════╗\n");
    printf("║           EAFITos v1.0               ║\n");
    printf("║       Shell Educativa - SO           ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Escribe 'ayuda' para ver los comandos.\n\n");
}

// ============================================
// COMANDO 3: BUSCAR
// ============================================

/**
 * @brief Busca un texto dentro de un archivo
 * @param args args[1] = texto a buscar, args[2] = nombre del archivo
 * 
 * Implementa una versión simplificada de grep.
 * Muestra línea número y contenido donde aparece el texto.
 */
void cmd_buscar(char **args) {
    // Validación de argumentos
    if (args[1] == NULL || args[2] == NULL) {
        printf("Uso: buscar <texto> <archivo>\n");
        printf("Ejemplo: buscar \"función\" main.c\n");
        printf("Ejemplo: buscar hola documento.txt\n");
        return;
    }
    
    const char *search_text = args[1];
    const char *filename = args[2];
    
    // Abrir archivo
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: No se pudo abrir '%s'\n", filename);
        printf("       Verifica que el archivo exista y tengas permisos.\n");
        return;
    }
    
    char line[1024];
    int line_num = 1;
    int matches = 0;
    
    printf("\n🔍 Buscando '%s' en %s:\n", search_text, filename);
    printf("────────────────────────────────────\n");
    
    // Leer línea por línea
    while (fgets(line, sizeof(line), file)) {
        // Eliminar salto de línea para mejor presentación
        line[strcspn(line, "\n")] = '\0';
        
        // Buscar el texto (case-sensitive)
        if (strstr(line, search_text) != NULL) {
            // Resaltar en amarillo el número de línea
            printf("\033[1;33m%4d:\033[0m %s\n", line_num, line);
            matches++;
        }
        line_num++;
    }
    
    fclose(file);
    
    // Resultado final con color
    if (matches == 0) {
        printf("\033[1;31m✗ Texto '%s' no encontrado.\033[0m\n", search_text);
    } else {
        printf("\033[1;32m✓ Encontrado %d ocurrencia(s).\033[0m\n", matches);
    }
    printf("\n");
}

// ============================================
// COMANDO 4: ESTADISTICAS
// ============================================

/**
 * @brief Muestra estadísticas detalladas de un archivo
 * @param args args[1] = nombre del archivo
 * 
 * Combina stat() con análisis de contenido para mostrar:
 * - Tamaño, líneas, palabras, caracteres
 * - Permisos en formato octal y rwx
 * - Fechas de modificación y acceso
 * - Tipo de archivo
 */
void cmd_estadisticas(char **args) {
    // Validación
    if (args[1] == NULL) {
        printf("Uso: estadisticas <archivo>\n");
        printf("Ejemplo: estadisticas README.md\n");
        return;
    }
    
    const char *filename = args[1];
    struct stat file_stat;
    
    // Obtener información del sistema de archivos
    if (stat(filename, &file_stat) == -1) {
        printf("Error: No se pudo acceder a '%s'\n", filename);
        printf("       Verifica que el archivo exista.\n");
        return;
    }
    
    printf("\n📊 \033[1;36m=== ESTADÍSTICAS DE: %s ===\033[0m\n", filename);
    printf("────────────────────────────────────\n");
    
    // 1. TAMAÑO
    printf("\033[1;33mTamaño:\033[0m        %ld bytes", file_stat.st_size);
    if (file_stat.st_size > 1024) {
        printf(" (%.2f KB)", file_stat.st_size / 1024.0);
    }
    if (file_stat.st_size > 1024 * 1024) {
        printf(" (%.2f MB)", file_stat.st_size / (1024.0 * 1024.0));
    }
    printf("\n");
    
    // 2. ANÁLISIS DE CONTENIDO (líneas, palabras, caracteres)
    FILE *file = fopen(filename, "r");
    if (file) {
        int lines = 0, words = 0, chars = 0;
        int in_word = 0;
        char c;
        
        while ((c = fgetc(file)) != EOF) {
            chars++;
            if (c == '\n') lines++;
            
            if (isspace(c)) {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                words++;
            }
        }
        fclose(file);
        
        // Ajustar: última línea sin \n
        if (chars > 0 && lines == 0) lines = 1;
        
        printf("\033[1;33mLíneas:\033[0m        %d\n", lines);
        printf("\033[1;33mPalabras:\033[0m      %d\n", words);
        printf("\033[1;33mCaracteres:\033[0m    %d\n", chars);
    } else {
        printf("⚠️  No se pudo leer el contenido para análisis.\n");
    }
    
    // 3. PERMISOS
    printf("\033[1;33mPermisos:\033[0m      %o (", file_stat.st_mode & 0777);
    
    // Formato rwx (como ls -l)
    printf("%c", (file_stat.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (file_stat.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (file_stat.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (file_stat.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (file_stat.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (file_stat.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (file_stat.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (file_stat.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (file_stat.st_mode & S_IXOTH) ? 'x' : '-');
    printf(")\n");
    
    // 4. FECHAS
    char time_buffer[80];
    struct tm *tm_info;
    
    tm_info = localtime(&file_stat.st_mtime);
    strftime(time_buffer, sizeof(time_buffer), "%d/%m/%Y %H:%M:%S", tm_info);
    printf("\033[1;33mModificado:\033[0m    %s\n", time_buffer);
    
    tm_info = localtime(&file_stat.st_atime);
    strftime(time_buffer, sizeof(time_buffer), "%d/%m/%Y %H:%M:%S", tm_info);
    printf("\033[1;33mAccedido:\033[0m      %s\n", time_buffer);
    
    // 5. TIPO DE ARCHIVO
    printf("\033[1;33mTipo:\033[0m          ");
    if (S_ISREG(file_stat.st_mode)) printf("Archivo regular\n");
    else if (S_ISDIR(file_stat.st_mode)) printf("Directorio\n");
    else if (S_ISLNK(file_stat.st_mode)) printf("Enlace simbólico\n");
    else printf("Otro\n");
    
    printf("────────────────────────────────────\n\n");
}