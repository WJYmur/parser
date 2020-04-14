#include <stdlib.h>
#include <stdio.h>
#define MAX 80

int main()
{
    FILE *fp;
    char str[MAX];
    int bytes;
    fp = fopen("output.txt", "r");
    
    if (fp == NULL)
    {
        printf("open file error!!\n");
    }
    else
    {
        //EOF=end of file
        while (!feof(fp))
        {
            bytes=fread(str, sizeof(char), MAX, fp);
            if (bytes<MAX)
                str[bytes]='\0';
            printf("%s\n", str);
        }

        printf("\n");
    }

    fclose(fp);
    return 0;

    //dev | dhcp | ip addr | net mask | getway | dns1 | dns2 | wan
}