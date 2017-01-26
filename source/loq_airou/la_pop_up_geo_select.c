#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "verse.h"
#include "enough.h"
#include "seduce.h"


typedef struct{
	float *tri;
	float *quad;
	uint tri_count;
	uint quad_count;
	uint version;
	float scale;
	float center[3];
	float brightness;
}LOPopupPreview;

void lo_preview_geometry_destroy(LOPopupPreview *g)
{
	if(g != NULL)
	{
		if(g->tri != NULL)
			free(g->tri);
		if(g->quad != NULL)
			free(g->quad);
		free(g);
	}
}


LOPopupPreview *lo_preview_geometry_update(ENode *node, LOPopupPreview *g)
{
	egreal *vertex;
	float f, range[6];
	uint i, *ref, ref_length, length;
	if(g == NULL)
	{
		g = malloc(sizeof *g);
		g->tri = NULL;
		g->quad = NULL;
		g->version = 0;
		g->tri_count = 0;
		g->quad_count = 0;
		g->brightness = 0;
	}
	if(g->version != e_ns_get_node_version_data(node))
	{
		g->version = e_ns_get_node_version_data(node);
		vertex = e_nsg_get_layer_data(node, e_nsg_get_layer_by_id(node, 0));
		ref = e_nsg_get_layer_data(node, e_nsg_get_layer_by_id(node, 1));
		length = e_nsg_get_vertex_length(node);
		ref_length = e_nsg_get_polygon_length(node);
		g->quad_count = 0;
		g->tri_count = 0;
		if(g->tri != NULL)
			free(g->tri);
		if(g->quad != NULL)
			free(g->quad);
		for(i = 0; i < ref_length; i++)
		{
			if(ref[i * 4] < length && ref[i * 4 + 1] < length && ref[i * 4 + 2] < length && vertex[ref[i * 4] * 3] != V_REAL64_MAX && vertex[ref[i * 4 + 1] * 3] != V_REAL64_MAX && vertex[ref[i * 4 + 2] * 3] != V_REAL64_MAX)
			{
				if(ref[i * 4 + 3] < length && vertex[ref[i * 4 + 3] * 3] != V_REAL64_MAX)
				{
					g->quad_count++;
				}else
				{
					g->tri_count++;
				}
			}
		}
		if(g->tri_count != 0)
			g->tri = malloc((sizeof *g->tri) * 3 * 3 * g->tri_count);
		else
			g->tri = NULL;
		if(g->quad_count != 0)
			g->quad = malloc((sizeof *g->quad) * 4 * 3 * g->quad_count);
		else
			g->quad = NULL;
		g->quad_count = 0;
		g->tri_count = 0;
		for(i = 0; i < ref_length; i++)
		{
			if(ref[i * 4] < length && ref[i * 4 + 1] < length && ref[i * 4 + 2] < length && vertex[ref[i * 4] * 3] != V_REAL64_MAX && vertex[ref[i * 4 + 1] * 3] != V_REAL64_MAX && vertex[ref[i * 4 + 2] * 3] != V_REAL64_MAX)
			{
				if(ref[i * 4 + 3] < length && vertex[ref[i * 4 + 3] * 3] != V_REAL64_MAX)
				{
					g->quad[g->quad_count * 12 + 0] = vertex[ref[i * 4 + 0] * 3 + 0];
					g->quad[g->quad_count * 12 + 1] = vertex[ref[i * 4 + 0] * 3 + 1];
					g->quad[g->quad_count * 12 + 2] = vertex[ref[i * 4 + 0] * 3 + 2];
					g->quad[g->quad_count * 12 + 3] = vertex[ref[i * 4 + 1] * 3 + 0];
					g->quad[g->quad_count * 12 + 4] = vertex[ref[i * 4 + 1] * 3 + 1];
					g->quad[g->quad_count * 12 + 5] = vertex[ref[i * 4 + 1] * 3 + 2];
					g->quad[g->quad_count * 12 + 6] = vertex[ref[i * 4 + 2] * 3 + 0];
					g->quad[g->quad_count * 12 + 7] = vertex[ref[i * 4 + 2] * 3 + 1];
					g->quad[g->quad_count * 12 + 8] = vertex[ref[i * 4 + 2] * 3 + 2];
					g->quad[g->quad_count * 12 + 9] = vertex[ref[i * 4 + 3] * 3 + 0];
					g->quad[g->quad_count * 12 + 10] = vertex[ref[i * 4 + 3] * 3 + 1];
					g->quad[g->quad_count * 12 + 11] = vertex[ref[i * 4 + 3] * 3 + 2];
					g->quad_count++;
				}else
				{
					g->tri[g->tri_count * 9 + 0] = vertex[ref[i * 4 + 0] * 3 + 0];
					g->tri[g->tri_count * 9 + 1] = vertex[ref[i * 4 + 0] * 3 + 1];
					g->tri[g->tri_count * 9 + 2] = vertex[ref[i * 4 + 0] * 3 + 2];
					g->tri[g->tri_count * 9 + 3] = vertex[ref[i * 4 + 1] * 3 + 0];
					g->tri[g->tri_count * 9 + 4] = vertex[ref[i * 4 + 1] * 3 + 1];
					g->tri[g->tri_count * 9 + 5] = vertex[ref[i * 4 + 1] * 3 + 2];
					g->tri[g->tri_count * 9 + 6] = vertex[ref[i * 4 + 2] * 3 + 0];
					g->tri[g->tri_count * 9 + 7] = vertex[ref[i * 4 + 2] * 3 + 1];
					g->tri[g->tri_count * 9 + 8] = vertex[ref[i * 4 + 2] * 3 + 2];
					g->tri_count++;
				}
			}
		}
		if(g->tri_count != 0)
		{
			range[0] = g->tri[0];
			range[1] = g->tri[0];
			range[2] = g->tri[1];
			range[3] = g->tri[1];
			range[4] = g->tri[2];
			range[5] = g->tri[2];
		}
		else if(g->quad_count != 0)
		{
			range[0] = g->quad[0];
			range[1] = g->quad[0];
			range[2] = g->quad[1];
			range[3] = g->quad[1];
			range[4] = g->quad[2];
			range[5] = g->quad[2];
		}

		for(i = 0; i < g->tri_count * 3 * 3; i += 3)
		{
			if(g->tri[i] > range[0])
				range[0] = g->tri[i];
			if(g->tri[i] < range[1])
				range[1] = g->tri[i];
			if(g->tri[i + 1] > range[2])
				range[2] = g->tri[i + 1];
			if(g->tri[i + 1] < range[3])
				range[3] = g->tri[i + 1];
			if(g->tri[i + 2] > range[4])
				range[4] = g->tri[i + 2];
			if(g->tri[i + 2] < range[5])
				range[5] = g->tri[i + 2];
		}
		for(i = 0; i < g->quad_count * 4 * 3; i += 3)
		{
			if(g->quad[i] > range[0])
				range[0] = g->quad[i];
			if(g->quad[i] < range[1])
				range[1] = g->quad[i];
			if(g->quad[i + 1] > range[2])
				range[2] = g->quad[i + 1];
			if(g->quad[i + 1] < range[3])
				range[3] = g->quad[i + 1];
			if(g->quad[i + 2] > range[4])
				range[4] = g->quad[i + 2];
			if(g->quad[i + 2] < range[5])
				range[5] = g->quad[i + 2];
		}
		f = range[0] - range[1];
		if(f < range[2] - range[3])
			f = range[2] - range[3];
		if(f < range[4] - range[5])
			f = range[4] - range[5];
		g->scale = 1 / f;
		g->center[0] = (range[0] + range[1]) / 2.0;
		g->center[1] = (range[2] + range[3]) / 2.0;
		g->center[2] = (range[4] + range[5]) / 2.0;
	}	
	return g;
}

boolean lo_preview_geometry_draw(LOPopupPreview *g, float brightness)
{
	if(g == NULL)
		return FALSE;
	g->brightness = g->brightness * 0.98 + brightness * 0.02;
	if(g->tri_count == 0 && g->quad_count == 0)
		return FALSE;
	glPushMatrix();
	glScaled(g->scale, g->scale, g->scale);
	glTranslated(-g->center[0], -g->center[1], -g->center[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(g->tri_count != 0)
		sui_draw_gl(GL_TRIANGLES, g->tri, g->tri_count * 3, 3, g->brightness, g->brightness, g->brightness, g->brightness);
	if(g->quad_count != 0)
		sui_draw_gl(GL_QUADS, g->quad, g->quad_count * 4,  3, g->brightness, g->brightness, g->brightness, g->brightness);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
	return TRUE;
}



