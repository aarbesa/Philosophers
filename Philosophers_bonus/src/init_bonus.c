/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:48 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:48:51 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static int		ft_get_data_from_argv(t_room *room, char **argv, int argc);
static void		ft_semaphores(t_room *room);
static int		ft_atoi(char *s);
static time_t	ft_think_time(t_room *room, time_t eat_time, time_t sleep_time);

int	ft_init(t_room *room, char **argv, int argc)
{
	int	i;

	room->nb_philos = ft_atoi(argv[1]);
	if (room->nb_philos <= 0 || room->nb_philos > 200)
	{
		write(2, "Bad input for the number of philosophers.\n", 42);
		return (1);
	}
	room->tab_philo = malloc(sizeof(t_philo) * room->nb_philos);
	if (!room->tab_philo)
		return (1);
	memset(room->tab_philo, 0, sizeof(t_philo) * room->nb_philos);
	i = 0;
	while (i < room->nb_philos)
	{
		room->tab_philo[i] = malloc(sizeof(t_philo));
		if (!room->tab_philo[i])
			return (ft_free_philos(room), 1);
		i++;
	}
	if (ft_get_data_from_argv(room, argv, argc) == 1)
		return (ft_free_philos(room), 1);
	ft_semaphores(room);
	room->death_variable = 0;
	return (0);
}

static int	ft_get_data_from_argv(t_room *room, char **argv, int argc)
{
	room->death_time = ft_atoi(argv[2]);
	room->eat_time = ft_atoi(argv[3]);
	room->sleep_time = ft_atoi(argv[4]);
	room->nb_of_meals_needed = -1;
	if (argc == 6)
		room->nb_of_meals_needed = ft_atoi(argv[5]);
	if (room->death_time < 10 || room->eat_time < 10 || \
		room->sleep_time < 10 || room->nb_of_meals_needed <= -2)
	{
		write(2, "Bad inputs, only positive intergers allowed.\n", 45);
		return (1);
	}
	if (room->nb_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(room->death_time * 1000);
		printf("%ld 1 died\n", room->death_time);
		return (1);
	}
	room->think_time = ft_think_time(room, room->eat_time, room->sleep_time);
	return (0);
}

static void	ft_semaphores(t_room *room)
{
	int		i;
	t_philo	*philo;

	sem_unlink("death_sem");
	sem_unlink("write_sem");
	sem_unlink("forks");
	room->death_sem = sem_open("death_sem", O_CREAT, 0644, 1);
	room->write_sem = sem_open("write_sem", O_CREAT, 0644, 1);
	room->forks = sem_open("forks", O_CREAT, 0644, room->nb_philos);
	i = 0;
	room->starting_time = ft_time() + 1000;
	while (i < room->nb_philos)
	{
		philo = room->tab_philo[i];
		philo->id = i + 1;
		philo->room = room;
		philo->nb_of_meals = 0;
		philo->last_meal = room->starting_time;
		philo->forks_sem = room->forks;
		i++;
	}
}

static int	ft_atoi(char *s)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	while (s[i] && s[i] >= '0' && s[i] <= '9' && i < 11)
	{
		result = result * 10 + s[i] - 48;
		i++;
	}
	if (i == 0 || s[i] != '\0')
		return (-42);
	if (result > 2147483647)
		return (-42);
	return (result);
}

static time_t	ft_think_time(t_room *room, time_t eat_time, time_t sleep_time)
{
	time_t	think_time;
	int		nb_of_philos;

	nb_of_philos = room->nb_philos;
	if (nb_of_philos % 2 == 0)
	{
		think_time = eat_time - sleep_time;
		if (think_time < 0)
			think_time = 0;
		return (think_time);
	}
	else
	{
		think_time = 2 * eat_time - sleep_time;
		if (think_time < 0)
			think_time = 0;
		return (think_time);
	}
	return (0);
}
