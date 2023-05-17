/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:37:19 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/17 20:16:00 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *monitor(void *arg)
{
    t_philo **philo;
    int i;

    philo = (t_philo **)arg;
    i = -1;
    while(++i < 5)
        printf("monitor id:%i\n", philo[i]->id);
    return NULL;
}

void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    printf("routine id:%i\n", philo->id);
    return NULL;
}

void init_data(int argc, char *argv[], t_data *data)
{
    int i;
    
    data->nop = ft_atoi(argv[1]);
    data->philo = malloc(data->nop * sizeof(t_philo *));
    i = -1;
    while(++i < data->nop)
    {
        data->philo[i] = malloc(sizeof(t_philo));
       // printf("nop:%i\n", data->nop); 
        // data->philo[i]->time->to_time = timestamp(0); 
        // data->philo[i]->time->to_die = ft_atoi(argv[2]) * 1000;
        // data->philo[i]->time->to_eat = ft_atoi(argv[3]) * 1000;
        // data->philo[i]->time->to_sleep = ft_atoi(argv[4]) * 1000;
        // data->philo[i]->nop = data->nop;
        data->philo[i]->id = i;
        data->philo[i]->state = HUNGRY;
        if(argc == 6)
            data->philo[i]->meals = ft_atoi(argv[5]);
    }
}

void init_philos(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->nop)
        pthread_create(&data->philo[i]->tid, NULL, routine, (void *)data->philo[i]);
    pthread_create(&data->tid_monitor, NULL, monitor, (void *)data->philo);
    i = -1;
    while(++i < data->nop)
        pthread_join(data->philo[i]->tid, NULL);
    pthread_join(data->tid_monitor, NULL);
}

void memory_free(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->nop)
        free(data->philo[i]);
    free(data->philo);
    free(data);
}

int main(int argc, char *argv[])
{
    t_data *data;

    if(validate_args(argc, argv))
        return(1);
    data = malloc(sizeof(t_data));
    init_data(argc, argv, data);
    init_philos(data);
    memory_free(data);
    return (FALSE);
}

/*
int main(int argc, char *argv[])
{
    t_data *data;
    pthread_t tid_philo[ft_atoi(argv[1])];
    pthread_t tid_monitor;
    int i;

    data = malloc(sizeof(t_data));
    if(validate_args(argc, argv) == 1)
        return(TRUE);
    // init_data(argc, argv, philo[i]);
    put_value_philos(argc, argv, data->philo);

    pthread_create(&tid_monitor, NULL, monitor, data->philo);
    i = -1;
    while(++i < ft_atoi(argv[1]))
    {
        pthread_create(&tid_philo[i], NULL, routine, (void *)data->philo[i]);
    }
    i = -1;
    while(++i < ft_atoi(argv[1]))
            pthread_join(tid_philo[i], NULL);
    pthread_join(tid_monitor, NULL);
    // while(++i < ft_atoi(argv[1]))
    //     free(philo[i]);
    return (FALSE);
}
*/