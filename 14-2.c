#include <signal.h>
#include <stdio.h>

void handler(int nsig) {
    if (nsig == SIGINT) {
        printf("Pressed CTRL + С");
    } else if (nsig == SIGQUIT) {
        printf("Pressed CTRL + 4");
    }
}

int main(void) {
    (void) signal(SIGINT, handler); //ctrl+c
    (void) signal(SIGQUIT, handler); //ctrl+4

    while (1);
    return 0;
}