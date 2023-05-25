/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:02:53 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/25 20:41:20 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_dead(t_data *data)
{
	int	j;

	j = -1;
	while (++j < data->nop)
		data->philo[j]->dead = TRUE;
}

static void	*monitor(void *arg)
{
	t_data	*data;
	int		id;

	data = (t_data *)arg;
	while (TRUE)
	{
		id = -1;
		while (++id < data->nop)
		{
			if ((timestamp(data->philo[id]->time->birth) \
				- data->philo[id]->time->last_meal)
				>= data->philo[id]->time->die)
			{
				set_dead(data);
				printf("%li %i died\n", \
				timestamp(data->philo[id]->time->birth), data->philo[id]->id);
				return (NULL);
			}
			else if (data->philo[id]->max_meals != -1 \
			&& data->philo[id]->meals >= data->philo[id]->max_meals)
				return (NULL);
		}
		usleep(5000);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->dead != TRUE)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (philo->max_meals != -1 && philo->meals >= philo->max_meals)
			return (NULL);
		ft_sleep(philo);
		print_action(timestamp(philo->time->birth), philo, "is thinking");
	}
	return (NULL);
}

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nop)
		pthread_create(&data->philo[i]->tid, NULL, routine, \
		(void *)data->philo[i]);
	pthread_create(&data->tid_monitor, NULL, monitor, (void *)data);
	i = -1;
	while (++i < data->nop)
		pthread_join(data->philo[i]->tid, NULL);
	pthread_join(data->tid_monitor, NULL);
}
