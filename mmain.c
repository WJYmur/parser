#include <stdio.h>

static char name[9][8] = {"dev", "dhcp", "ip addr", "mask", "gw", "dns1", "dns2", "wan"};

// int memory(char *a, char *b, int count)
// {
//     int i;

//     for (i=0; i<count; ++i)
//     {
//         a[i] = b[i];
//     }

//     unsigned int *aa = (unsigned int)a;
//     unsigned int *bb = (unsigned int)b;

//     for (i=0; i<count; i=i+4)
//     {
//         a[i] = b[i];
//     }
    
// }

static int parser(char *buf)
{
    char *p[9] = {0};
    int i;
    char tmp[9][32];

    p[0] = buf;

    memset(tmp, 0, sizeof(tmp));

    for (i = 1; i < 9; i++)
    {
        p[i] = strstr(p[i - 1], ",");

        if (p[i] - p[i - 1] < 0) //若p[i]減去p[i-1]是負值，則已經到結尾了，因為[(null) - "wan"] = 負值
            memcpy(tmp[i - 1], p[i - 1], 1);
        else
            memcpy(tmp[i - 1], p[i - 1], p[i] - p[i - 1]);

        p[i]++; //將p[i]所指向的記憶體位址+1 ->排除','
    }

    printf("------------\n");
    for (i = 0; i < 8; i++)
        printf("%8s = %-15s\n", name[i], tmp[i]);
}

int main(int argc, char *argv[])
{
    FILE *fp = NULL;

    char tmpBuf[256];

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Open %s fail !!\n", argv[1]);
        return -1;
    }

    while (fgets(tmpBuf, sizeof(tmpBuf), fp) != NULL)
        parser(tmpBuf);

    return 0;
}