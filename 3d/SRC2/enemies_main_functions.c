/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_main_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:05:36 by dbolilyi          #+#    #+#             */
/*   Updated: 2019/03/05 12:05:37 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../guardians.h"

int		move_enemy(t_sdl *iw, t_sprite *s)
{
	t_point2d		vect_norm;
	t_intpoint2d	vect;
	float			len;
	clock_t			t;

	vect_norm.x = s->e.vis_esp.px - s->e.vis_esp.ex;
	vect_norm.y = s->e.vis_esp.py - s->e.vis_esp.ey;
	len = sqrtf(powf(vect_norm.x, 2.0f) + powf(vect_norm.y, 2.0f));
	vect_norm.x /= len;
	vect_norm.y /= len;
	t = clock();
	vect.x = vect_norm.x * (float)(t - s->e.prev_update_time)
		/ (float)CLKS_P_S * 1000.0f;
	vect.y = vect_norm.y * (float)(t - s->e.prev_update_time)
		/ (float)CLKS_P_S * 1000.0f;
	if (in_sec_xy(iw, s->num_sec, s->x + vect.x, s->y + vect.y))
	{
		s->x += vect.x;
		s->y += vect.y;
		return (1);
	}
	return (move_enemy_in_portal(iw, s, &vect));
}

void	sprite_physics(t_sdl *iw, t_sprite *s)
{
	int		tmp;

	if (s->fall_time != 1 && (s->e.enemy_numb != 0 || s->e.status >= 4))
		s->z -= (int)(iw->l.accel * ((float)(clock() - s->fall_time) /
			(float)CLKS_P_S) * 50.0f);
	tmp = get_ceil_z_sec(iw, s->x, s->y, s->num_sec);
	if (s->z + SPRITE_HEIGHT > tmp)
		s->z = tmp - SPRITE_HEIGHT;
	tmp = get_floor_z_sec(iw, s->x, s->y, s->num_sec);
	if (s->z < tmp)
	{
		s->z = tmp;
		s->fall_time = 1;
	}
	else
		s->fall_time = clock() - CLKS_P_S / 10;
}

void	check_enemies(t_sdl *iw)
{
	t_sprite	*tmp;

	tmp = *iw->sprite;
	while (tmp)
	{
		if (tmp->type == 2)
		{
			if (tmp->e.enemy_numb == 0)
				enemy_intelligence0(iw, tmp);
			else if (tmp->e.enemy_numb == 1)
				enemy_intelligence1(iw, tmp);
			else if (tmp->e.enemy_numb == 2)
				enemy_intelligence2(iw, tmp, 0);
			tmp->e.prev_update_time = clock();
		}
		tmp = tmp->next;
	}
}