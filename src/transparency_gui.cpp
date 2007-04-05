/* $Id$ */

#include "stdafx.h"
#include "openttd.h"
#include "table/sprites.h"
#include "table/strings.h"
#include "functions.h"
#include "window.h"
#include "gui.h"
#include "viewport.h"
#include "gfx.h"
#include "sound.h"
#include "variables.h"

static void Transparent_Click(byte widget)
{
	TOGGLEBIT(_transparent_opt, widget);
	SndPlayFx(SND_15_BEEP);
}

static void TransparencyToolbWndProc(Window *w, WindowEvent *e)
{
	switch (e->event) {
		case WE_PAINT:
			for (uint i = 0; i < 7; i++) {
				SetWindowWidgetLoweredState(w, i + 3, HASBIT(_transparent_opt, i));
			}
			DrawWindowWidgets(w);
			break;

		case WE_CLICK:
			if (e->we.click.widget >= 3) {
				Transparent_Click(e->we.click.widget - 3);
				MarkWholeScreenDirty();
			}
			break;
	}
}

static const Widget _transparency_widgets[] = {
{ WWT_CLOSEBOX,   RESIZE_NONE,  7,   0,  10,   0,  13, STR_00C5,                 STR_018B_CLOSE_WINDOW},
{  WWT_CAPTION,   RESIZE_NONE,  7,  11, 162,   0,  13, STR_TRANSPARENCY_TOOLB,   STR_018C_WINDOW_TITLE_DRAG_THIS},
{WWT_STICKYBOX,   RESIZE_NONE,  7, 163, 174,   0,  13, STR_NULL,                 STR_STICKY_BUTTON},

/* transparency widgets: transparent signs, trees, houses, industries, player's buildings */
{   WWT_IMGBTN,   RESIZE_NONE,  7,   0,  21,  14,  35, SPR_IMG_PLACE_SIGN,   STR_TRANSPARENT_SIGNS_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7,  22,  43,  14,  35, SPR_IMG_PLANTTREES,   STR_TRANSPARENT_TREES_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7,  44,  65,  14,  35, SPR_IMG_TOWN,         STR_TRANSPARENT_HOUSES_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7,  66,  87,  14,  35, SPR_IMG_INDUSTRY,     STR_TRANSPARENT_INDUSTRIES_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7,  88, 109,  14,  35, SPR_IMG_COMPANY_LIST, STR_TRANSPARENT_BUILDINGS_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7, 110, 152,  14,  35, SPR_IMG_BRIDGE,       STR_TRANSPARENT_BRIDGES_DESC},
{   WWT_IMGBTN,   RESIZE_NONE,  7, 153, 174,  14,  35, SPR_IMG_TRANSMITTER,  STR_TRANSPARENT_STRUCTURES_DESC},

{   WIDGETS_END},
};

static const WindowDesc _transparency_desc = {
	WDP_ALIGN_TBR, 58+36, 175, 36,
	WC_TRANSPARENCY_TOOLBAR, WC_NONE,
	WDF_STD_TOOLTIPS | WDF_STD_BTN | WDF_DEF_WIDGET | WDF_STICKY_BUTTON,
	_transparency_widgets,
	TransparencyToolbWndProc
};

void ShowTransparencyToolbar(void)
{
	AllocateWindowDescFront(&_transparency_desc, 0);
}
