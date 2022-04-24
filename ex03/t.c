
size_t ft_strlen(const char *str)
{
    int i;
    i = 0;
    while (str[i])
        i++;
    return i;
}

char    *ft_strjoin(char *str, char c)
{
    int    i = 0;
    int len = ft_strlen(str);
    char    *ptr;

    ptr = malloc (len + 2);
    if (!ptr)
        return NULL;
    while (str[i])
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = c;
    ptr[i + 1] = '\0';
    free(str);
    return ptr;
}

char    *ft_strdup(char    *str)
{
    int    i = 0;
    int len = ft_strlen(str);
    char    *ptr;

    ptr = malloc(len + 1);
    while (str[i])
    {
        ptr[i] = str[i];
        i++;
    }
    ptr[i] = '\0';
    return ptr;
}

char    *get_next_line(int fd)
{
    char    buff;
    char    *str;
    int        r;

    r = read(fd, &buff, 1);
    str = ft_strdup("");
    while (r > 0)
    {
        str = ft_strjoin(str, buff);
        if (buff == '\n')
            break;
        r = read(fd,&buff, 1);
    }
    if (r < 0)
    {
        free(str);
        return NULL;
    }
    if (r == 0 && str[0] == '\0')
    {
        free(str);
        return NULL;
    }
    return str;
}