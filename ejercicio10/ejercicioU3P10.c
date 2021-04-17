#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){
    mkfifo("/home/ebambi/SistemasOperativos/Unidad_3/ejercicio10", 0666);
    return 0;
}