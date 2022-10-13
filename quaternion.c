/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 14:08:02 by hsarhan           #+#    #+#             */
/*   Updated: 2022/07/13 17:57:31 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	*create_quaternion(float x, float y, float z, float w)
{
	t_quaternion	*q;

	q = ft_calloc(1, sizeof(t_quaternion));
	if (q == NULL)
		return (NULL);
	q->x = x;
	q->y = y;
	q->z = z;
	q->w = w;
	return (q);
}

t_quaternion	*rotate_quaternion(t_quaternion *rot, t_quaternion *q)
{
	t_quaternion	*q_new;
	float			x;
	float			y;
	float			z;
	float			w;

	x = rot->w * q->x + rot->x * q->w + rot->y * q->z - rot->z * q->y;
	y = rot->w * q->y - rot->x * q->z + rot->y * q->w + rot->z * q->x;
	z = rot->w * q->z + rot->x * q->y - rot->y * q->x + rot->z * q->w;
	w = rot->w * q->w - rot->x * q->x - rot->y * q->y - rot->z * q->z;
	q_new = create_quaternion(x, y, z, w);
	free(rot);
	free(q);
	if (q_new == NULL)
		return (NULL);
	return (q_new);
}

t_quaternion	*create_quaternion_rotation(float rot, t_point *axis)
{
	t_quaternion	*q;
	float			s;
	float			c;

	s = sin(rot / 2.0f);
	c = cos(rot / 2.0f);
	q = create_quaternion(axis->x * s, axis->y * s, axis->z * s, c);
	if (q == NULL)
		return (NULL);
	return (q);
}

void	rotate_point(t_quaternion *q, t_point *p)
{
	float	xyz[3];
	float	wx;
	float	wy;
	float	wz;

	xyz[0] = p->x;
	xyz[1] = p->y;
	xyz[2] = p->z;
	wx = q->w * q->x * 2.0f;
	wy = q->w * q->y * 2.0f;
	wz = q->w * q->z * 2.0f;
	p->x = (1.0f - (q->y * q->y * 2.0f + q->z * q->z * 2.0f)) * xyz[0];
	p->x += (q->x * q->y * 2.0f - wz) * xyz[1];
	p->x += (q->x * q->z * 2.0f + wy) * xyz[2];
	p->y = (q->x * q->y * 2.0f + wz) * xyz[0];
	p->y += (1.0f - (q->x * q->x * 2.0f + q->z * q->z * 2.0f)) * xyz[1];
	p->y += (q->y * q->z * 2.0f - wx) * xyz[2];
	p->z = (q->x * q->z * 2.0f - wy) * xyz[0];
	p->z += (q->y * q->z * 2.0f + wx) * xyz[1];
	p->z += (1.0f - (q->x * q->x * 2.0f + q->y * q->y * 2.0f)) * xyz[2];
}
