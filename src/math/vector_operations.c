/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:54:26 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 00:56:00 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Returns a vector's magnitude
 * @param vec A vector
 * @return vec's magnitude
 */
float	vec_magnitude(const t_vector *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y \
			+ vec->z * vec->z + vec->w * vec->w));
}

/**
 * @brief Normalizes a vector
 * @param vec Vector to be normalized
 */
void	normalize_vec(t_vector *vec)
{
	scale_vec(vec, vec, 1 / vec_magnitude(vec));
}

/**
 * @brief Returns the dot product of two vectors
 * @param v1 First vector
 * @param v2 Second vector
 * @return The dot product of v1 and v2
 */
float	dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w);
}
