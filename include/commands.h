/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistema.
 * 
 * Define las funciones que implementan la lógica de cada comando disponible
 * en la shell. Todas siguen la firma `void cmd_nombre(char **args)`.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

// --- Prototipos de Comandos ---

/**
 * @brief Lista los archivos del directorio actual.
 */
void cmd_listar(char **args);

/**
 * @brief Lee y muestra el contenido de un archivo.
 */
void cmd_leer(char **args);

/**
 * @brief Muestra la hora del sistema.
 */
void cmd_tiempo(char **args);

/**
 * @brief Realiza operaciones matemáticas simples.
 */
void cmd_calc(char **args);

/**
 * @brief Muestra la lista de ayuda.
 */
void cmd_ayuda(char **args);

/**
 * @brief Termina la ejecución de la shell.
 */
void cmd_salir(char **args);

// --- Prototipos de Comandos Avanzados ---

/** 
 * @brief Muestra el historial de comandos ejecutados.
*/
void cmd_historial(char **args);

/**
 * @brief Limpia la pantalla de la terminal.
 */
void cmd_limpiar(char **args);

/** 
 * @brief Busca un archivo por nombre en el directorio actual.
*/
void cmd_buscar(char **args);

/**
 * @brief Muestra estadísticas del sistema, como uso de CPU y memoria.
 */
void cmd_estadisticas(char **args);

// --- Utilidades del Registro de Comandos ---

/**
 * @brief Retorna el número total de comandos registrados.
 * @return int Cantidad de comandos.
 */
int num_comandos();

#endif
