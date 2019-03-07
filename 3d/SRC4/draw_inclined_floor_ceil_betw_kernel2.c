/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inclined_floor_ceil_betw_kernel2.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:22:49 by dbolilyi          #+#    #+#             */
/*   Updated: 2019/03/05 17:22:51 by dbolilyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../guardians.h"

void	draw_inclined_floor_ceil_betw_tex_kernel1(t_sdl *iw, t_save_wall *left,
	t_draw_wall_floor_ceil_tex_kernel *d)
{
	if (iw->sectors[iw->d.cs].light == 0 ||
		iw->sectors[iw->d.cs].light->t != 18)
		d->cint[25] = 1;
	else
		d->cint[25] = 0;
	d->cint[0] = iw->t[left->wall->t]->w;
	d->cint[1] = iw->t[left->wall->t]->h;
	d->cint[2] = iw->t[iw->sectors[iw->d.cs].fr.t]->w;
	d->cint[3] = iw->t[iw->sectors[iw->d.cs].fr.t]->h;
	if (iw->sectors[iw->d.cs].cl.t >= 0)
	{
		d->cint[4] = iw->t[iw->sectors[iw->d.cs].cl.t]->w;
		d->cint[5] = iw->t[iw->sectors[iw->d.cs].cl.t]->h;
	}
	else
	{
		d->cint[4] = iw->t[iw->l.skybox]->w;
		d->cint[5] = iw->t[iw->l.skybox]->h;
	}
	d->cint[6] = WINDOW_W;
	d->cint[7] = WINDOW_H;
	d->cint[8] = left->x;
	d->cint[9] = left->p.x;
	d->cint[10] = left->p.y;
	d->cint[21] = iw->d.screen_left;
}