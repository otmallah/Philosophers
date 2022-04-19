#include "../minishell.h"

void    ft_print(t_list *n)
{
    while (n != NULL)
    {
        printf("%s\n" , n->content);
        n = n->next;
    }
}

int main(int ac, char **av)
{
    char *str;
    int i;
    t_list *list;

    i = 0;
    while (1)
    {
        str = readline("> ");
        if (i == 0)
        {
            list = ft_lstnew(str);
            printf("%s\n" , list->content);
            i++;
        }
        else
        {
            ft_lstadd_back(&list, ft_lstnew(str));
            ft_print(list);
        }
    }
}