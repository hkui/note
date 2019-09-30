//系统调用和标准io区别实例

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    putchar('a');
    write(1,"b",1);

    putchar('a');
    write(1,"b",1);

    putchar('a');
    write(1,"b",1);
    return  0;

}



