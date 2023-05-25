/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:32:31 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/25 20:22:21 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long int time, t_philo *philo, char *str)
{
	if (philo->dead != TRUE)
		printf("%li %i %s\n", time, philo->id, str);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->fork_left);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
}

void	ft_sleep(t_philo *philo)
{
	print_action(timestamp(philo->time->birth), philo, "is sleeping");
	usleep(philo->time->sleep * 1000);
}

void	eat(t_philo *philo)
{
	philo->time->last_meal = timestamp(philo->time->birth);
	print_action(timestamp(philo->time->birth), philo, "has taken a fork");
	print_action(timestamp(philo->time->birth), philo, "has taken a fork");
	print_action(timestamp(philo->time->birth), philo, "is eating");
	usleep(philo->time->eat * 1000);
	if (philo->id % 2)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	philo->meals += 1;
}
