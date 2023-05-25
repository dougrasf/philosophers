/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:33:57 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/25 20:41:40 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_time(t_data *data, char *argv[], int i)
{
	data->philo[i]->time = malloc(sizeof(t_time));
	data->philo[i]->time->birth = timestamp(0);
	data->philo[i]->time->last_meal = timestamp(0);
	data->philo[i]->time->die = ft_atoi(argv[2]);
	data->philo[i]->time->eat = ft_atoi(argv[3]);
	data->philo[i]->time->sleep = ft_atoi(argv[4]);
}

void	init_data(int argc, char *argv[], t_data *data)
{
	int	i;

	data->nop = ft_atoi(argv[1]);
	data->forks = malloc((data->nop * sizeof(pthread_mutex_t)));
	i = -1;
	while (++i < data->nop)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philo = malloc(data->nop * sizeof(t_philo *));
	i = -1;
	while (++i < data->nop)
	{
		data->philo[i] = malloc(sizeof(t_philo));
		data->philo[i]->max_meals = -1;
		data->philo[i]->nop = data->nop;
		data->philo[i]->dead = FALSE;
		data->philo[i]->id = i + 1;
		data->philo[i]->fork_left = &data->forks[(i + 1) % data->nop];
		data->philo[i]->fork_right = &data->forks[i];
		data->philo[i]->meals = 0;
		if (argc == 6)
			data->philo[i]->max_meals = ft_atoi(argv[5]);
		init_time(data, argv, i);
	}
}
