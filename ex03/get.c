#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


size_t  ft_strlen(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char    *ft_strdup(char *str)
{
    int i = 0;
    char *s2;

    i = ft_strlen(str);
    s2 = malloc((i + 1));
    i = 0;
    while (str[i])
    {
        s2[i] = str[i];
        i++;
    }
    s2[i] = '\0';
    return s2;
}

char    *ft_strjoin(char *str, char c)
{
    int i = 0;
    int len = ft_strlen(str);
    char *ptr;

    ptr = malloc(len + 2);
    while (str[i])
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = c ;
    ptr[i + 1] = '\0';
    free(str);
    return ptr;
}

char *get_next_line(int fd)
{
    char *str;
    char buff;
    int rd;

    rd = read(fd, &buff, 1);
    str = ft_strdup("");
    while (rd > 0)
    {
        str = ft_strjoin(str, buff);
        if (buff == '\n')
            break;
        rd = read(fd, &buff, 1);
    }
    if (rd < 0)
    {
        free(str);
        return NULL;
    }
    if (rd == 0 && str[0] == '\0')
    {
        free(str);
        return NULL;
    }
    return str;
}

int main()
{
    int fd = open("t.c", O_CREAT | O_RDWR , 0777);
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
    printf ("%s" , get_next_line(fd));
}