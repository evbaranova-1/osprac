#include <stdio.h>
int main(int argc, char *argv[], char *envp[])
{
printf ("Arr agrv: ");
for (int i = 0; i < argc; i++ )
{
printf("%s, ", argv[i]);
}

printf("\nArr envp: ");
int j = 0;
char *check = "";
while (check != NULL)
{
printf("%s, ", envp[j]);
check = envp[j];
j++;
}
}
