#include <stdio.h>
#include <string.h>

#define OK     0
#define ERROR -1

#define MAX_OFFSET       4
#define MAX_BUFF_SIZE 1024

int get_func_from_symbol(unsigned int address, char *func, const char *name)
{
    FILE *p = NULL;
    char line[MAX_BUFF_SIZE + 1] = { 0 };

    sprintf(line, "addr2line -e %s -f -s 0x%x", name, address);
    p = popen(line, "r");
    if (p == NULL)
    {
        printf("popen() failed\n");
        return ERROR;
    }
    else
    {
        fread(line, MAX_BUFF_SIZE, 1, p);
        for (int i = 0; i < strlen(line); i++)
        {
            if ((line[i] == 0x0d) || (line[i] == 0x0a))
            {
                func[i] = 0;
                break;
            }
            else
            {
                func[i] = line[i];
            }
        }
        pclose(p);
    }

    return OK;
}

int main(int argc, char **argv)
{
    char type;
    char func[80];
    FILE *fp = NULL;
    unsigned int address;
    int i = -1;

    if (argc != 3)
    {
        printf("Usage: %s <test.exe> <trace.txt>\n", argv[0]);
        return ERROR;
    }

    fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        printf("fopen() failed\n");
        return ERROR;
    }

    while (!feof(fp))
    {
        fscanf(fp, "%c0x%x\n", &type, &address);
        memset(func, 0, sizeof(func));

        // 通过函数地址获取函数名称
        if (get_func_from_symbol(address, func, argv[1]) == ERROR)
        {
            fclose(fp);
            return ERROR;
        }

        // 进入函数
        if (type == 'E')
        {
            i ++;
            for (int j = 0; j < i * MAX_OFFSET; j++)
                printf(" ");

            printf("--> %s() [%d]\n", func, i);
        }
        // 退出函数
        else if (type == 'X')
        {
            for (int j = 0; j < i * MAX_OFFSET; j++)
                printf(" ");

            printf("<-- %s() [%d]\n", func, i);
            i --;
        }
    }

    fclose(fp);

    return OK;
}
