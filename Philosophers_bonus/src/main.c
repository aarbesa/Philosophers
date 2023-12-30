/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:52 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:48:54 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (write(2, "error: 4 or 5 args are needed.\n", 31), 1);
	return (ft_philo(argc, argv));
}
