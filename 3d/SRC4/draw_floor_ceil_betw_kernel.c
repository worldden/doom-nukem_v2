#include "../guardians.h"

void	draw_floor_ceil_betw_tex_kernel2(t_sdl *iw, t_save_wall *left,
	t_draw_wall_floor_ceil_tex_kernel *d)
{
	if (iw->sectors[iw->d.cs].light == 0 || iw->sectors[iw->d.cs].light->t != 18)
		d->cint[16] = 1;
	else
		d->cint[16] = 0;
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
	d->cint[12] = iw->d.screen_left;
	d->cint[13] = iw->d.screen_right;
}

void	draw_floor_ceil_betw_tex_kernel3(t_sdl *iw, t_save_wall *left,
	t_save_wall *right, t_draw_wall_floor_ceil_tex_kernel *d)
{
	d->cint[14] = iw->sectors[iw->d.cs].cl.t;
	d->cint[15] = iw->p.rotup;
	d->cfloat[5] = iw->d.screen.a;
	d->cfloat[6] = iw->d.screen.b;
	d->cfloat[7] = iw->d.screen.c;
	d->cfloat[8] = iw->d.screen_len;
	d->cfloat[13] = left->olen;
	d->cfloat[14] = iw->tsz[left->wall->t];
	d->cfloat[17] = iw->p.rot;
	d->cfloat[18] = iw->v.angle;
	d->lv.x = (float)(left->p.x - iw->p.x);
	d->lv.y = (float)(left->p.y - iw->p.y);
	d->rv.x = (float)(right->p.x - iw->p.x);
	d->rv.y = (float)(right->p.y - iw->p.y);
	d->ang = acosf((d->lv.x * d->rv.x + d->lv.y * d->rv.y) /
		(sqrtf(d->lv.x * d->lv.x + d->lv.y * d->lv.y) *
			sqrtf(d->rv.x * d->rv.x + d->rv.y * d->rv.y)));
	d->cfloat[0] = d->ang / (float)(right->x - left->x + 1);
	d->ang = 0.0f;
	d->rv.x = (float)(-right->p.x + left->p.x);
	d->rv.y = (float)(-right->p.y + left->p.y);
	d->cfloat[2] = G180 - acosf((d->lv.x * d->rv.x + d->lv.y * d->rv.y)
		/ (sqrtf(d->lv.x * d->lv.x + d->lv.y * d->lv.y) *
			sqrtf(d->rv.x * d->rv.x + d->rv.y * d->rv.y)));
}

void	draw_floor_ceil_betw_tex_kernel4(t_sdl *iw, t_save_wall *left,
	t_save_wall *right, t_draw_wall_floor_ceil_tex_kernel *d)
{
	d->cfloat[1] = sqrtf(powf(iw->p.x - left->p.x, 2.0f) +
		powf(iw->p.y - left->p.y, 2.0f));
	d->len_lr = sqrtf(powf(left->p.x - right->p.x, 2.0f) +
		powf(left->p.y - right->p.y, 2.0f));
	d->cfloat[3] = (float)(right->p.x - left->p.x) / d->len_lr;
	d->cfloat[4] = (float)(right->p.y - left->p.y) / d->len_lr;
	d->cfloat[15] = get_ceil_z(iw, iw->p.x, iw->p.y);
	d->cfloat[16] = get_floor_z(iw, iw->p.x, iw->p.y);
	d->cint[11] = (int)(d->cfloat[15] - d->cfloat[16]);
	d->cfloat[9] = (float)d->cint[11] / ((float)iw->p.z - d->cfloat[16]);
	d->cfloat[10] = (float)d->cint[11] / (d->cfloat[15] - (float)iw->p.z);
	d->cfloat[11] = (float)iw->p.x / 1000.0f;
	d->cfloat[12] = (float)iw->p.y / 1000.0f;
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_wallTop, CL_TRUE,
		0, (right->x - left->x + 1) * sizeof(int), iw->d.wallTop, 0, NULL, NULL);
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_wallBot, CL_TRUE,
		0, (right->x - left->x + 1) * sizeof(int), iw->d.wallBot, 0, NULL, NULL);
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_cint, CL_TRUE,
		0, 17 * sizeof(int), d->cint, 0, NULL, NULL);
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_cfloat, CL_TRUE,
		0, 19 * sizeof(float), d->cfloat, 0, NULL, NULL);
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_top_betw, CL_TRUE,
		0, (right->x - left->x + 1) * sizeof(int),
		iw->d.save_top_betw, 0, NULL, NULL);
}

void	draw_floor_ceil_betw_tex_kernel(t_sdl *iw, t_save_wall *left,
	t_save_wall *right, int len)
{
	t_draw_wall_floor_ceil_tex_kernel	d;

	draw_floor_ceil_betw_tex_kernel2(iw, left, &d);
	draw_floor_ceil_betw_tex_kernel3(iw, left, right, &d);
	draw_floor_ceil_betw_tex_kernel4(iw, left, right, &d);
	clEnqueueWriteBuffer(iw->k.command_queue, iw->k.m_bot_betw, CL_TRUE,
		0, (right->x - left->x + 1) * sizeof(int),
		iw->d.save_bot_betw, 0, NULL, NULL);
	clSetKernelArg(iw->k.kernel3, 3, sizeof(cl_mem),
		(void *)&iw->k.m_t[left->wall->t]);
	clSetKernelArg(iw->k.kernel3, 4, sizeof(cl_mem),
		(void *)&iw->k.m_t[iw->sectors[iw->d.cs].fr.t]);
	if (iw->sectors[iw->d.cs].cl.t >= 0)
		clSetKernelArg(iw->k.kernel3, 5, sizeof(cl_mem),
		(void *)&iw->k.m_t[iw->sectors[iw->d.cs].cl.t]);
	else
		clSetKernelArg(iw->k.kernel3, 5, sizeof(cl_mem),
		(void *)&iw->k.m_t[iw->l.skybox]);
	d.global_item_size = len;
	d.local_item_size = 1;
	iw->k.ret = clEnqueueNDRangeKernel(iw->k.command_queue, iw->k.kernel3, 1, NULL,
		&d.global_item_size, &d.local_item_size, 0, NULL, NULL);
	clFlush(iw->k.command_queue);
	clFinish(iw->k.command_queue);
}