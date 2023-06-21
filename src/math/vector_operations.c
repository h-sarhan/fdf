/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:54:26 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 10:13:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Returns a vector's magnitude
 * @param vec A vector
 * @return vec's magnitude
 */
float vec_magnitude(const t_vec4 vec)
{
    return (sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]));
}

/**
 * @brief Normalizes a vector
 * @param vec Vector to be normalized
 */
void normalize_vec(t_vec4 vec)
{
    scale_vec(vec, vec, 1 / vec_magnitude(vec));
}

/**
 * @brief Returns the dot product of two vectors
 * @param v1 First vector
 * @param v2 Second vector
 * @return The dot product of v1 and v2
 */
float dot_product(const t_vec4 v1, const t_vec4 v2)
{
    return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

void cross_product(t_vec4 res, const t_vec4 v1, const t_vec4 v2)
{
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
