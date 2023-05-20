/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dofranci <dofranci@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:37:19 by dofranci          #+#    #+#             */
/*   Updated: 2023/05/18 21:20:12 by dofranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void memory_free(t_data *data)
{
    int i;

    i = -1;
    while(++i < data->nop)
        pthread_mutex_destroy(&data->forks[i]);
    i = -1;
    while(++i < data->nop)
    {
        free(data->philo[i]->time);
        free(data->philo[i]);
    }
    free(data->forks);
    free(data->philo);
    free(data);
}

int main(int argc, char *argv[])
{
    t_data *data;

    if(validate_args(argc, argv))
        return(TRUE);
    data = malloc(sizeof(t_data));
    init_data(argc, argv, data);
    init_philos(data);
    memory_free(data);
    return (FALSE);
}
