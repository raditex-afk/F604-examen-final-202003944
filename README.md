# Examen final F604 — Programación en C

**Nombre:** Luis Pedro Mejicano Lara  
**Carné:** 202003944  
**Curso:** Laboratorio de Electrónica Digital F604  
**Institución:** ECFM-USAC

Parte II: diez programas independientes de C. 
## Compilación y ejecución

Se necesita GCC. En Windows, usar Git Bash con GCC instalado y disponible en PATH (Git Bash por sí solo no incluye GCC), o una terminal Linux/WSL. Para publicar el código basta con Git; no es necesario recompilarlo.

```bash
mkdir -p bin
gcc -Wall -o bin/e1 e1.c
./bin/e1
```

Compilar los diez:

```bash
for f in e*.c; do gcc -Wall -o "bin/${f%.c}" "$f"; done
```

Comprobación estricta:

```bash
for f in e*.c; do gcc -std=c11 -Wall -Wextra -pedantic -o "bin/${f%.c}" "$f"; done
```

Los ejercicios 5 al 10 reciben entrada estándar hasta EOF. Es preferible redirigir un archivo. En terminales Unix se puede indicar EOF con Ctrl+D; en consolas Windows suele ser Ctrl+Z y Enter, según el entorno.

```bash
./bin/e5 < prueba.txt
./bin/e6 < prueba.txt
./bin/e10 < prueba.txt
./bin/e5 < prueba.txt > salida.txt
diff esperado.txt salida.txt
printf '\t\b' | ./bin/e9 | od -An -tx1
```

La última orden debe mostrar `3e 08 2d 3c 08 2d`. No confundir el byte real de retroceso con los dos caracteres `\b`.

## Estado verificado

| Ejercicio | Archivo | Estado | Notas |
|---|---|---|---|
| 1 | e1.c | Completo | Enteros positivo, negativo y cero; mensajes exactos |
| 2 | e2.c | Completo | Nombres con espacios, línea vacía y 100 000 caracteres; dos espacios después de Hola |
| 3 | e3.c | Completo | 16 filas, 0–300 °F con paso 20; título y columnas originales |
| 4 | e4.c | Completo | 11 filas, 0–100 °C con paso 10 |
| 5 | e5.c | Completo | Conserva espacios internos, elimina blancos finales y líneas vacías |
| 6 | e6.c | Completo | 79/80 excluidos; 81/150/100 000 incluidos; sin truncamiento |
| 7 | e7.c | Completo | Función reverse declarada, definida y llamada; conserva orden y saltos |
| 8 | e8.c | Completo | Reduce espacios con variable de estado y conserva tabulaciones |
| 9 | e9.c | Completo | Comparación binaria, incluidos todos los valores de byte |
| 10 | e10.c | Completo | Arreglo dinámico; última palabra, entrada vacía y palabra de 100 000 bytes |
