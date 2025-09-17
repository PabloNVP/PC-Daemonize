#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/**
 * @brief Convierte el proceso actual en un daemon (proceso en segundo plano)
 * 
 * Este método implementa el proceso estándar de daemonización POSIX que:
 * 1. Crea un proceso hijo y termina el padre
 * 2. Crea una nueva sesión para desconectarse del terminal
 * 3. Realiza un segundo fork para evitar la asignación de terminal
 * 4. Establece la máscara de permisos a 0
 * 5. Cambia al directorio raíz para no bloquear sistemas de archivos
 * 6. Redirige los descriptores estándar a /dev/null
 * 
 * @note El método no retorna si la daemonización es exitosa
 * @note En caso de error, el proceso termina con EXIT_FAILURE
 * 
 * @param void No requiere parámetros
 * @return void No retorna si tiene éxito, termina el proceso en caso de error
 * 
 * @warning Debe llamarse antes de realizar operaciones que requieran privilegios
 * @warning Requiere incluir las cabeceras: unistd.h, stdlib.h, fcntl.h, sys/stat.h
 */
void daemonize() {
    pid_t pid;

    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);
   
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    pid = fork();
    if (pid < 0) 
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);
}

int main() {
    daemonize();

    while (1) {
        /**
         * Lógica del demonio.
        */ 
        sleep(5);
    }

    return EXIT_SUCCESS;
}
