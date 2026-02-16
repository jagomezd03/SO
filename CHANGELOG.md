# 📅 Historial de Cambios (Changelog)

El objetivo de este archivo es llevar un registro cronológico de las versiones, nuevas funcionalidades y correcciones de errores del sistema operativo.

## [v1.1.0] - 2026-02-16
### Añadido
- **Gestor de Historial**: Sistema de historial de comandos implementado en `history_manager.c`.
- **Comandos Avanzados Expandidos**: Nuevas funcionalidades en `advanced_commands.c`.
- **Mejoras del Parser**: Optimización del analizador de comandos.

### Mejorado
- **Shell Loop**: Optimizaciones en el bucle principal de la shell interactiva.
- **Makefile**: Actualización de scripts de compilación con soporte a nuevas características.

### Documentación
- **CONTRIBUTORS.md**: Actualización de tareas asignadas reflejando trabajo real del equipo.

## [v1.0.0] - 2026-02-04
### Añadido
- **Shell Interactiva**: Bucle REPL funcional.
- **Comandos Básicos**: `listar`, `leer`, `tiempo`, `calc`, `ayuda`, `salir`.
- **Arquitectura Modular**: Separación en `core`, `commands`, `utils`.
- **Sistema de Documentación**: Soporte para Doxygen.

### Cambios
- Migración de `main.c` monolítico a estructura modular.