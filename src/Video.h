/*
 This file is part of DMGBoy.
 
 DMGBoy is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 DMGBoy is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with DMGBoy.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __VIDEO_H__
#define __VIDEO_H__

#include "map"
#include "Def.h"

class Memory;
class IGBScreenDrawable;

struct VideoPixel
{
	int x, y;
	int rowMap, tileDataSelect;
	int color, indexColor, xScrolled;
	int palette[4];
	int mapIni;
	BYTE yTile;
    BYTE r, g, b;
};

class Video
{
private:
	Memory *m_mem;
    bool m_colorMode;
	std::multimap<int, int> m_orderedOAM;	//posicion x, dir. memoria
	bool m_priorityBGWnd[GB_SCREEN_W][GB_SCREEN_H]; // Aqui se almacena la prioridad de pintado de BG y Window
	IGBScreenDrawable *m_screen;
	VideoPixel *m_pixel;
public:
	Video(IGBScreenDrawable * screen);
	~Video(void);
    void SetScreen(IGBScreenDrawable * screen);
    void SetColorMode(bool value);
	void SetMem(Memory *mem);
	void RefreshScreen();
	void ClearScreen();
	void UpdateLine(BYTE line);
    void GetTile(BYTE *buffer, int widthSize, int tile, int bank);
    void GetColorPalette(BYTE palette[4][3], int address);
private:
	void UpdateBG(int line);
	void UpdateWin(int line);
	void OrderOAM(int line);
	void UpdateOAM(int line);
	inline void GetColor(VideoPixel * p);
	void GetDMGPalette(int * palette, int dir);
    bool ObjAboveBG(BYTE oamBit7, int x, int y);
};

#endif
