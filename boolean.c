/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:15:29 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 13:19:02 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_visible(int size, t_coord start, t_coord end)
{
	if (start.x > size && end.x > size)
		return (0);
	if (start.x < 0 && end.x < 0)
		return (0);
	if (start.y > size && end.y > size)
		return (0);
	if (start.y < 0 && end.y < 0)
		return (0);
	return (1);
}
