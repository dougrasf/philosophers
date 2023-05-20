/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 22:32:31 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/18 22:36:24 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long int time, t_philo *philo, char *str)
{
	if (philo->dead != TRUE)
		printf("%li %i %s\n", time, philo->id, str);
}

// void take_forks(t_philo *philo)
// {
// }

void thinking(t_philo *philo)
{
    print_action(timestamp(philo->time->to_birth), philo, "is thinking");
}

void ft_sleep(t_philo *philo)
{
    print_action(timestamp(philo->time->to_birth), philo, "is sleeping");
	usleep(philo->time->to_sleep);
}

void eat(t_philo *philo)
{
    if (philo->id % 2)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
	}
	else
	{
        philo->order = TRUE;
		pthread_mutex_lock(philo->fork_right);
		pthread_mutex_lock(philo->fork_left);
	}
    philo->time->last_meal = timestamp(philo->time->to_birth);
	print_action(timestamp(philo->time->to_birth), philo, "has taken a fork");
	print_action(timestamp(philo->time->to_birth), philo, "has taken a fork");
	print_action(timestamp(philo->time->to_birth), philo, "is eating");
    usleep(philo->time->to_eat);  
    if(philo->order == FALSE)
    {
        pthread_mutex_unlock(philo->fork_left);
        pthread_mutex_unlock(philo->fork_right);
    }
    else
    {    
        pthread_mutex_unlock(philo->fork_right);
        pthread_mutex_unlock(philo->fork_left);
    }
    philo->meals++;
}
