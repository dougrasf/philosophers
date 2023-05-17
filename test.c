#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NOP 5

typedef struct s_philo
{
    int id;
} t_philo;

typedef struct s_data
{
    t_philo **philo;
} t_data;

void *monitor(void *arg)
{
    t_philo **philo;
    philo = (t_philo **)arg;

    for(int i = 0; i < NOP; i++)
        printf("from monitor id:%i\n", philo[i]->id);
}

void *routine(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    printf("from routine id:%i\n", philo->id);
}

int main(void)
{
     t_data *data;

     data = malloc(sizeof(t_data));
     data->philo = malloc(NOP * sizeof(t_philo *));
     for(int i = 0; i < NOP; i++)
     {
        data->philo[i] = malloc(sizeof(t_philo));
        data->philo[i]->id = i;
     }
     for(int i = 0; i < NOP; i++)
        pthread_create(&tid[i], NULL, routine, (void *)data->philo[i]);
     pthread_create(&tid_monitor, NULL, monitor, (void *)data->philo);
     for(int i = 0; i < NOP; i++)
        pthread_join(tid[i], NULL);
     pthread_join(tid_monitor, NULL);
     for (int i = 0; i < NOP; i++)
        free(data->philo[i]);
     free(data->philo);
     free(data);
     return (0);
}
