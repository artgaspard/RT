/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaspard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:37:56 by agaspard          #+#    #+#             */
/*   Updated: 2018/03/05 23:33:53 by ggaudin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rt.h"

int			stock_cylinder_colors(t_sce *s, int coor_num, int p)
{
	if (coor_num == 8)
	{
		s->forms[p]->col.r = ft_atof(s->tmp);
		if (s->forms[p]->col.r >= 0 && s->forms[p]->col.r <= 1)
			return (0);
		return (1);
	}
	if (coor_num == 9)
	{
		s->forms[p]->col.g = ft_atof(s->tmp);
		if (s->forms[p]->col.g >= 0 && s->forms[p]->col.g <= 1)
			return (0);
		return (1);
	}
	if (coor_num == 10)
	{
		s->forms[p]->col.b = ft_atof(s->tmp);
		if (s->forms[p]->col.b >= 0 && s->forms[p]->col.b <= 1)
			return (0);
		return (1);
	}
	return (0);
}

void		stock_cylinder2(t_sce *s, int coor_num, int p)
{
	int		ret;

	ret = 0;
	if (coor_num == 4)
		s->forms[p]->norm.y = ft_atof(s->tmp);
	if (coor_num == 5)
		s->forms[p]->norm.z = ft_atof(s->tmp);
	if (coor_num == 6)
		s->forms[p]->rad = ft_atof(s->tmp);
	if (coor_num == 7)
		s->forms[p]->high = ft_atof(s->tmp);
	if (coor_num == 8)
		ret = stock_cylinder_colors(s, coor_num, p);
	if (coor_num == 9)
		ret = stock_cylinder_colors(s, coor_num, p);
	if (coor_num == 10)
		ret = stock_cylinder_colors(s, coor_num, p);
	if (ret == 1)
		ft_exit("colors must be comprised between 0 and 1");
}

int			stock_cylinder(t_sce *s, int coor_num, int j, int p)
{
	s->tmp[j] = '\0';
	j = -1;
	while (s->tmp[++j])
		if ((s->tmp[j] < 48 || s->tmp[j] > 57) && (s->tmp[j] != '.') \
	&& (s->tmp[j] != '-'))
			break ;
	if (coor_num >= 3 && coor_num <= 5)
	{
		if (ft_atof(s->tmp) < -1)
			s->tmp = ft_itoa(-1);
		else if (ft_atof(s->tmp) > 1)
			s->tmp = ft_itoa(1);
	}
	if (coor_num == 0)
		s->forms[p]->pos.x = ft_atof(s->tmp);
	if (coor_num == 1)
		s->forms[p]->pos.y = ft_atof(s->tmp);
	if (coor_num == 2)
		s->forms[p]->pos.z = ft_atof(s->tmp);
	if (coor_num == 3)
		s->forms[p]->norm.x = ft_atof(s->tmp);
	stock_cylinder2(s, coor_num, p);
	free(s->tmp);
	return (1);
}

int			check_cylinder(t_env *e, t_sce *s, int p, int x)
{
	int		len;
	int		j;

	j = 0;
	if (s->coor < 11)
	{
		len = (int)ft_strlen(e->map[p]);
		if ((s->tmp = (char*)malloc(sizeof(char) * (len + 1))) == 0)
			ft_exit("error malloc");
		while (e->map[p][x++] && x <= len && s->coor < 11)
			if (e->map[p][x - 1] == '[' || s->coor > 0)
				while ((e->map[p][x] != ',' && e->map[p][x] != ']') \
	&& s->coor < 11)
				{
					if (x < len)
						s->tmp[j++] = e->map[p][x++];
					if ((e->map[p][x] == ',' || x == len) && s->coor < 11)
					{
						s->coor += stock_cylinder(s, s->coor, j, p - P_SCENE);
						check_cylinder(e, s, p, x + 1);
					}
				}
		return (final_check_forms(e, s, p, CYLINDER));
	}
	return (1);
}
