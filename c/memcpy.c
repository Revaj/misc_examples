#include <stdio.h>
#include <string.h>

void memcopy(void *dest, const void * src, size_t len) {

    const char * from =  src;
    char * to =  dest;

    for (int i = 0; i < len; i++) {
        to[i] = from[i];
    }

}

int main() {
    char hello [] = {"Hello"};
    char world [] = {"World!"};

    printf("%s\n", world);
    memcopy(world, hello, sizeof(hello));
    printf("%s", world);

    return 0;
}