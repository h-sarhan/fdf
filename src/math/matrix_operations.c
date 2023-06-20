/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:42:19 by hsarhan           #+#    #+#             */
/*   Updated: 2023/06/20 20:03:54 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Multiplies matrix m1 by matrix m2 and stores the result in res
 * @param res Result of m1 * m2 will be stored in this matrix
 * @param m1 First matrix
 * @param m2 Second matrix
 */
void mat_multiply(t_mat4 res, const t_mat4 m1, const t_mat4 m2)
{
    unsigned char row;
    t_mat4 temp;

    row = 0;
    while (row < 4)
    {
        temp[row][0] = m1[row][0] * m2[0][0] + m1[row][1] * m2[1][0] +
                       m1[row][2] * m2[2][0] + m1[row][3] * m2[3][0];

        temp[row][1] = m1[row][0] * m2[0][1] + m1[row][1] * m2[1][1] +
                       m1[row][2] * m2[2][1] + m1[row][3] * m2[3][1];

        temp[row][2] = m1[row][0] * m2[0][2] + m1[row][1] * m2[1][2] +
                       m1[row][2] * m2[2][2] + m1[row][3] * m2[3][2];

        temp[row][3] = m1[row][0] * m2[0][3] + m1[row][1] * m2[1][3] +
                       m1[row][2] * m2[2][3] + m1[row][3] * m2[3][3];
        row++;
    }
    memcpy(res, temp, sizeof(t_mat4));
}

/**
 * @brief Multiplies a matrix by a vector and stores the result in res
 * @param res Vector that stores the result of a matrix multiplied by a vector
 * @param mat Matrix to be multiplied
 * @param vec Vector to be multiplied
 */
void mat_vec_multiply(t_vector res, const t_mat4 mat, const t_vector vec)
{
    res[0] = vec[0] * mat[0][0] + vec[1] * mat[0][1] + vec[2] * mat[0][2] +
             mat[0][3];
    res[1] = vec[0] * mat[1][0] + vec[1] * mat[1][1] + vec[2] * mat[1][2] +
             mat[1][3];
    res[2] = vec[0] * mat[2][0] + vec[1] * mat[2][1] + vec[2] * mat[2][2] +
             mat[2][3];
}
