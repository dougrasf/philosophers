/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:38:58 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/25 20:17:28 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	timestamp(long int init_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (init_time == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - init_time);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	negative;
	int	result;

	result = 0;
	negative = 1;
	if (!str)
		return (-1);
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * negative);
}

static int	valid_value(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]) ||
				ft_atoi(argv[i]) > MAXINT ||
				ft_atoi(argv[i]) <= 0)
			{
				printf("Incorrect argument value!\n");
				return (TRUE);
			}
		}
	}
	if (ft_atoi(argv[1]) == 1)
	{
		printf("0 1 has taken a fork\n%s 1 died\n", argv[2]);
		return (TRUE);
	}
	return (FALSE);
}

int	validate_args(int argc, char *argv[])
{
	if (argc > 6)
	{
		printf("Exceeded number of arguments!\n");
		return (TRUE);
	}
	if (argc < 5)
	{
		printf("Insuficient number of arguments!\n");
		return (TRUE);
	}
	if (valid_value(argc, argv))
		return (TRUE);
	return (FALSE);
}
