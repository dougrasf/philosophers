/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:33:57 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/18 22:35:03 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void *monitor(void *arg)
{
    t_philo **philo;
    int id;

    philo = (t_philo **)arg;
    while (TRUE)
	{
		id = -1;
		while (philo[++id])
		{
			if ((timestamp(philo[id]->time->to_birth) - philo[id]->time->last_meal) >= philo[id]->time->to_die)
			{
				philo[id]->dead = 1;
				printf("%li %i died\n", timestamp(philo[id]->time->to_birth), philo[id]->id);
				return (NULL);
			}
		}
		usleep(5000);
	}
	return (NULL);
}

static void *routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while(TRUE)
    {
        // take_forks(philo);
        printf("id:%i\n", philo->id);
        eat(philo);
        if (philo->max_meals != -1 && philo->meals >= philo->max_meals)
			return (NULL);
        ft_sleep(philo);
        thinking(philo);
    }
    return (NULL);
}

void init_data(int argc, char *argv[], t_data *data)
{
    int i;

    data->nop = ft_atoi(argv[1]);
    data->forks = malloc((data->nop * sizeof(pthread_mutex_t)));
    i = -1;
    while(++i < data->nop)
        pthread_mutex_init(&data->forks[i], NULL);
    data->philo = malloc(data->nop * sizeof(t_philo *));
    i = -1;
    while(++i < data->nop)
    {
        data->philo[i] = malloc(sizeof(t_philo));
        data->philo[i]->time = malloc(sizeof(t_time));
        data->philo[i]->time->to_birth = timestamp(0); 
        data->philo[i]->time->to_die = ft_atoi(argv[2]) * 1000;
        data->philo[i]->time->to_eat = ft_atoi(argv[3]) * 1000;
        data->philo[i]->time->to_sleep = ft_atoi(argv[4]) * 1000;
        data->philo[i]->nop = data->nop;
        data->philo[i]->dead = FALSE;
        data->philo[i]->id = i + 1;
        data->philo[i]->fork_left = &data->forks[(i + 1) % data->nop];
        data->philo[i]->fork_right = &data->forks[i]; 
        data->philo[i]->meals = 0;
        data->philo[i]->order = 0;
        if(argc == 6)
            data->philo[i]->max_meals = ft_atoi(argv[5]);
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
