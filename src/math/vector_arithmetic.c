/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:46:11 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/21 10:13:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Adds two vectors together and stores the result in res
 * @param res The result of v1 + v2 will be stored in this vector
 * @param v1 First operand
 * @param v2 Second operand
 */
void add_vec(t_vec4 *res, const t_vec4 *v1, const t_vec4 *v2)
{
    (*res)[0] = (*v1)[0] + (*v2)[0];
    (*res)[1] = (*v1)[1] + (*v2)[1];
    (*res)[2] = (*v1)[2] + (*v2)[2];
}

/**
 * @brief Subtracts two vectors together and stores the result in res
 * @param res The result of v1 - v2 will be stored in this vector
 * @param v1 First operand
 * @param v2 Second operand
 */
void sub_vec(t_vec4 *res, const t_vec4 *v1, const t_vec4 *v2)
{
    (*res)[0] = (*v1)[0] - (*v2)[0];
    (*res)[1] = (*v1)[1] - (*v2)[1];
    (*res)[2] = (*v1)[2] - (*v2)[2];
}

/**
 * @brief Scales a vector and stores the result in res
 * @param res The result of scale * v will be stored in this vector
 * @param v Vector to be scaled
 * @param scale scaling factor
 */
void scale_vec(t_vec4 *res, const t_vec4 *v, float scale)
{
    (*res)[0] = scale * (*v)[0];
    (*res)[1] = scale * (*v)[1];
    (*res)[2] = scale * (*v)[2];
}

/**
 * @brief Negates a vector and stores the result in res
 * @param res The result of -v will be stored in this vector
 * @param v Vector to be negated
 */
void negate_vec(t_vec4 *res, const t_vec4 *v)
{
    (*res)[0] = -1 * (*v)[0];
    (*res)[1] = -1 * (*v)[1];
    (*res)[2] = -1 * (*v)[2];
}
