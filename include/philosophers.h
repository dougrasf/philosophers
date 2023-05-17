/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:29:42 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/17 19:49:31 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>

# define MAXINT 2147483647

typedef enum e_state
{
	HUNGRY,
	EATING,
	SLEEPING,
	THINKING,
	DIED
}	t_state;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_time
{
	long int	to_time;
	long int	to_die;
	long int	to_eat;
	long int	to_sleep;
	long int	must_eat;
}	t_time;

typedef struct s_philo
{
	int				nop;
	pthread_t		tid;
	int				id;
    int				state;
    int				meals;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_time	*time; 
}   t_philo;

typedef struct s_data
{
	t_philo		**philo;
	pthread_t	tid_monitor;
	int			nop;

}	t_data;
//funções
int			ft_atoi(const char *str);
long int    timestamp(long int init_time);
int validate_args(int argc, char *argv[]);

#endif