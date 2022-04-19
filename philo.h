#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define TRUE 1 

typedef struct s_philo {
    pthread_mutex_t mutex;
    pthread_t       *philosophers;
    int             holder[4];
    int             a;
    struct s_philo *next;
}   t_philo;


typedef struct s_list {
	struct s_list	*next;
}   t_list;

t_list	*ft_lstnew(pthread_t *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
