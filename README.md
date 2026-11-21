# Examen final F604 — Programación en C

**Nombre:** Luis Pedro Mejicano Lara  
**Carné:** 202003944  
**Curso:** Laboratorio de Electrónica Digital F604  
**Institución:** ECFM-USAC

Parte II: diez programas independientes de C. Cada archivo comienza con un comentario descriptivo. No se requieren bibliotecas externas. La solución fue preparada con asistencia de ChatGPT y verificada mediante ejecución real.

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

## Criterios de entrada

Como en los ejemplos introductorios del curso, los caracteres se procesan por bytes, no por puntos de código Unicode. En particular, invertir texto UTF-8 con tildes puede separar sus bytes; usar texto ASCII para el ejercicio 7. Este ejercicio trabaja con cadenas C de texto, sin bytes NUL internos. Las longitudes en e6 y e10 se cuentan en bytes. No hay un límite fijo de longitud de línea; la memoria disponible limita los programas que usan arreglos dinámicos.

El separador de línea es `\n`; las pruebas se hicieron con archivos LF en Linux. En Windows, la biblioteca C en modo texto normalmente convierte CRLF en LF al leer. Si se ejecuta en Linux con archivos CRLF, `\r` se considera contenido; convertir esos archivos a LF primero. La verificación binaria de e9 se realizó en Linux, sin traducción de finales de línea.

En e2 una línea vacía (`Enter`) produce `Hola  `; EOF sin ninguna línea es un error de entrada, como ocurre con `input()` en Python. e1 espera un entero representable por `int`. e10 considera separadores exclusivamente espacio, tabulación y salto de línea; la puntuación forma parte de la palabra. Solo muestra longitudes que aparecen, y cada asterisco representa una palabra.

## Pruebas realizadas

Entorno: GCC 14.2.0, Linux. Se ejecutaron 20 compilaciones sin advertencias: diez con `gcc -Wall` y diez con `gcc -std=c11 -Wall -Wextra -pedantic -Werror`.

Se aprobaron **590 verificaciones** con entradas y salidas esperadas comparadas por bytes o valores numéricos:

| Programa | Verificaciones |
|---|---:|
| e1 | 3 |
| e2 | 6 |
| e3 | 16 filas |
| e4 | 11 filas |
| e5 | 111 |
| e6 | 115 |
| e7 | 106 |
| e8 | 107 |
| e9 | 6 |
| e10 | 109 |

Incluyen 100 entradas pseudoaleatorias reproducibles (semilla 202003944) para cada uno de e5, e6, e7, e8 y e10, líneas y palabras de 100 000 bytes, entradas vacías y ausencia de salto final. Las conversiones se comprobaron con las fórmulas matemáticas y sus formatos. También se ejecutaron una prueba de e5 con redirección y `diff`, y `od -An -tx1` para e9. No se afirma haber probado los binarios en Windows.

Pruebas cortas reproducibles en Git Bash/Linux:

```bash
printf '25\n' | ./bin/e1
printf 'Luis Pedro\n' | ./bin/e2
printf 'uno  \n\t\nfin\t' | ./bin/e5
printf 'abc\n\nxyz' | ./bin/e7
printf '  a   b\t  c\n' | ./bin/e8
printf 'a bb bb ccc' | ./bin/e10
```

En la última prueba deben aparecer longitudes 1, 2 y 3, con cantidades 1, 2 y 1, respectivamente.

## Referencias consultadas

Se leyeron los archivos reales del repositorio del profesor mediante sus URLs raw:

- https://github.com/ECFM-USAC/led-F604/blob/main/src/ejemplo1.c
- https://github.com/ECFM-USAC/led-F604/blob/main/src/character_counting.c
- https://github.com/ECFM-USAC/led-F604/blob/main/src/word_counting.c

`ejemplo1.c` usa 0–300 °F con incremento 20 y formato `%4.0f %6.1f`. e3 conserva los valores y añade título y encabezados; e4 adapta la estructura. Aunque su nombre es `word_counting.c`, el archivo consultado cuenta dígitos, espacios y otros caracteres: no contiene un histograma de palabras. El histograma se implementó específicamente para este ejercicio. Las adaptaciones se atribuyen en los comentarios correspondientes.

## Historial Git y contenido de la entrega

Rama `main`. Hay un commit individual por ejercicio y un commit adicional de documentación. `.gitignore` excluye `bin/`, objetos y ejecutables. El ZIP conserva `.git/` y una carpeta `bin/` vacía; no contiene ejecutables. No se configuró ningún remoto ni se publicó nada.

La identidad de los commits es **Autor provisional F604** con correo reservado **f604-provisional@example.invalid**. No es el correo del estudiante. Se configuró solo en este repositorio. Antes de publicar se puede reemplazar en los once commits siguiendo las instrucciones siguientes; no se pierde la separación de un commit por ejercicio.

## Publicar manualmente desde Windows

1. Descargar el ZIP y extraerlo completamente. Conservar el directorio oculto `.git`. No copiar únicamente los archivos visibles.
2. En VS Code, seleccionar **Archivo → Abrir carpeta** y abrir `F604-examen-final-202003944`.
3. Seleccionar **Terminal → Nueva terminal** y escoger **Git Bash**. Ejecutar los comandos desde esa carpeta, no desde su carpeta contenedora.
4. Verificar archivos, rama y commits:

```bash
pwd
ls -la
ls e{1..10}.c README.md .gitignore
git branch --show-current
git log --oneline
git rev-list --count main
git status --short
git remote -v
```

Deben verse los diez programas, `README.md` y `.gitignore`, rama `main` y 11 commits. El estado y la lista de remotos deben estar vacíos. `bin/` no tiene archivos versionados.

5. Configurar tu identidad real. Sustituir `TU_CORREO` por el correo verificado de GitHub o por el correo privado noreply que GitHub te muestra en **Settings → Emails**; no copiar el marcador literalmente:

```bash
git config user.name "Luis Pedro Mejicano Lara"
git config user.email "TU_CORREO"
```

Cambiar la configuración no modifica los commits existentes. Para reemplazar la identidad provisional en los once commits, ejecutar este bloque **antes de publicar** desde Git Bash:

```bash
git filter-branch --env-filter '
export GIT_AUTHOR_NAME="$(git config user.name)"
export GIT_AUTHOR_EMAIL="$(git config user.email)"
export GIT_COMMITTER_NAME="$GIT_AUTHOR_NAME"
export GIT_COMMITTER_EMAIL="$GIT_AUTHOR_EMAIL"
' -- main

git log --format='%h %an <%ae> %s'
git rev-list --count main
```

Git puede mostrar una advertencia general sobre `filter-branch`. Aquí se usa únicamente en este repositorio pequeño y todavía no publicado, para cambiar la identidad. Deben seguir existiendo 11 commits. No usar `git commit --amend` como sustituto: cambiaría solo el último.

6. En el navegador, iniciar sesión en GitHub y crear un repositorio **nuevo y público**, con nombre exacto `F604-examen-final-202003944`. No inicializar README, `.gitignore` ni licencia: el remoto debe estar vacío.
7. Sustituir `MI_USUARIO` por tu usuario real de GitHub y ejecutar:

```bash
git remote add origin https://github.com/MI_USUARIO/F604-examen-final-202003944.git
git remote -v
git push -u origin main
```

Si Git solicita autenticación, completar el flujo que presente Git Credential Manager o el navegador. Nunca escribir un token dentro del código o README.

8. Abrir `https://github.com/MI_USUARIO/F604-examen-final-202003944` y comprobar: visibilidad pública, rama `main`, diez archivos C, README y `.gitignore`, once commits con uno por ejercicio, y ausencia de `bin/` y ejecutables.
9. Copiar la URL del repositorio y entregarla en la U Virtual.

**Pendiente del estudiante:** descargar y extraer, configurar identidad (y reemplazar la provisional si desea que todos los commits figuren a su nombre), crear el remoto público, publicar y enviar la URL. No hace falta ejecutar `git init` ni crear de nuevo los diez commits.
