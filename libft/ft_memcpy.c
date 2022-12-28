/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:45:53 by hsarhan           #+#    #+#             */
/*   Updated: 2022/12/28 12:48:02 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char			*dst_bytes;
	const char		*src_bytes;

	dst_bytes = dst;
	src_bytes = src;
	while (--len)
	{
		dst_bytes[len] = src_bytes[len];
	}
	return (dst);
}
