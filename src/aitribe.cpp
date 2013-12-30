#include "aitribe.h"
#include <iostream>
#include "mgframework/mgframework.h"
#include "mgframework/mgmovingobject.h"

AITribe::AITribe()
{
	unsetWindowProperties(); // Force setWindowProperties to be called before init.
	disableTyping();
	setInstanceType(MGFSINGLEPLAYERINSTANCE);
	disableLogging();
}

bool AITribe::init(int w, int h, int tw, int th)
{
	// The window is created.
	if (windowPropertiesSet())
	{
		if (!m_Window.createWindow()) 
		{
			return false;
		}

		// All graphics should be loaded here.
		m_Floor = loadBMPImage("tileset.bmp");

		m_MO_00 = loadBMPImage("movingobject_00.bmp");
		m_MO_01 = loadBMPImage("movingobject_01.bmp");
		m_MO_02 = loadBMPImage("movingobject_02.bmp");
		m_MO_03 = loadBMPImage("movingobject_03.bmp");
		m_MO_04 = loadBMPImage("movingobject_04.bmp");
		m_MO_05 = loadBMPImage("movingobject_05.bmp");
		m_MO_06 = loadBMPImage("movingobject_06.bmp");
		m_MO_07 = loadBMPImage("movingobject_07.bmp");
		m_MO_08 = loadBMPImage("movingobject_08.bmp");

		m_StationaryObject = loadBMPImage("stationaryobject.bmp");
		m_Mark = loadBMPImage("mark.bmp");

		SDL_SetColorKey(m_MO_00, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_01, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_02, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_03, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_04, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_05, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_06, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_07, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_MO_08, SDL_SRCCOLORKEY, 0);


		SDL_SetColorKey(m_StationaryObject, SDL_SRCCOLORKEY, 0);
		SDL_SetColorKey(m_Mark, SDL_SRCCOLORKEY, 0);


		// Objcts such as the map are initialized here.
		m_Map.init(w, h, tw, th, m_Window.getWidth(), m_Window.getHeight()); // width (in number of tiles), height, tile width (in pixels), tile height, resolution x and y.

		// Setup the edge around the screen to allow scrolling to see the entire map.
		m_Map.setTopEdge(8);
		m_Map.setBottomEdge(64);
		m_Map.setLeftEdge(8);
		m_Map.setRightEdge(64);

		// Setup application specific game logics..

		//runConsoleCommand("open terminalserver", this, NULL);
		runConsoleCommand("logging off", this, NULL); // Turn on logging for the MGFramework class
		runConsoleCommand("map logging off", this, NULL); // Turn on logging for the MGMap class
		runConsoleCommand("minimap on", this, NULL);
		runConsoleCommand("add so 2000", this, NULL);

		runConsoleCommand("add mo 20 -owner 0", this, NULL);
		runConsoleCommand("add mo 20 -owner 1", this, NULL);
		runConsoleCommand("add mo 20 -owner 2", this, NULL);
		runConsoleCommand("add mo 20 -owner 3", this, NULL);
		runConsoleCommand("add mo 20 -owner 4", this, NULL);
		runConsoleCommand("add mo 20 -owner 5", this, NULL);
		runConsoleCommand("add mo 20 -owner 6", this, NULL);
		runConsoleCommand("add mo 20 -owner 7", this, NULL);
		runConsoleCommand("add mo 20 -owner 8", this, NULL);

		return true;
	}
	else
	{
		return false;
	}
}

void AITribe::handleGameLogics()
{
	// Application specific game logics are updated here..
}

void AITribe::draw()
{
	// Draw all tiles visible in the window...
	for (int x=0; x < m_Map.getWidth(); x++)
	{
		for ( int y=0; y < m_Map.getHeight(); y++)
		{
			// Only draw the tiles actually visible (+1 to draw partly visible tiles) in the window...
			if(  ((x * m_Map.getTileWidth() + m_Map.getScrollX()) <= m_Window.getWidth() + m_Map.getTileWidth()) &&
				 ((x * m_Map.getTileWidth() + m_Map.getScrollX()) >= 0 - m_Map.getTileWidth()) &&
				 ((y * m_Map.getTileHeight() + m_Map.getScrollY()) <= m_Window.getHeight() + m_Map.getTileHeight()) &&
				 ((y * m_Map.getTileHeight() + m_Map.getScrollY()) >= 0 - m_Map.getTileHeight())  )
			{
				if(m_Map.getTileProperty(x, y) & MGMAP_TP_PROPERTY_1)
				{
					drawSprite(m_Floor, getSurface(), 0, 0, x * m_Map.getTileWidth() + m_Map.getScrollX(), y * m_Map.getTileHeight() + m_Map.getScrollY(), m_Map.getTileWidth(), m_Map.getTileHeight());
				}
				/*
				else if(m_Map.getTileProperty(x, y) & MGMAP_TP_PROPERTY_2)
				{
					drawSprite(m_Floor, getSurface(), 32, 64, x * m_Map.getTileWidth() + m_Map.getScrollX(), y * m_Map.getTileHeight() + m_Map.getScrollY(), m_Map.getTileWidth(), m_Map.getTileHeight());
				}
				*/
			}
		}
	}

	// Draw all moving objects...
	int oX,oY;
	for(int i=0;i<getNumberOfMO();i++)
	{
		if(m_MO != NULL)
		{
			oX=m_MO[i].getTileX() * m_Map.getTileWidth() + m_Map.getScrollX()+m_MO[i].getXOffset();
			oY=m_MO[i].getTileY() * m_Map.getTileHeight() + m_Map.getScrollY() + m_MO[i].getYOffset();
			// Only draw visible moving objects...
			if(detectCollisionRectangle(oX, oY, oX+m_Map.getTileWidth(), oY+m_Map.getTileHeight(), 0, 0, m_Window.getWidth(), m_Window.getHeight()))
			{
				switch(m_MO[i].getOwner())
				{
					case 0:
					{
						drawSprite(m_MO_00, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 1:
					{
						drawSprite(m_MO_01, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 2:
					{
						drawSprite(m_MO_02, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 3:
					{
						drawSprite(m_MO_03, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 4:
					{
						drawSprite(m_MO_04, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 5:
					{
						drawSprite(m_MO_05, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 6:
					{
						drawSprite(m_MO_06, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 7:
					{
						drawSprite(m_MO_07, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					case 8:
					{
						drawSprite(m_MO_08, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
						break;
					}

					default:
					{
						// ERROR?
						break;
					}
				}

				//drawSprite(m_MovingObject, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
				if(m_MO[i].isMarked())
				{
					drawSprite(m_Mark, getSurface(), 0, 0, oX, oY, m_Map.getTileWidth(), m_Map.getTileHeight());
				}
			}
		}
	}

	// Draw all stationary objects...
	int sX,sY;
	for(int i=0;i<getNumberOfSO();i++)
	{
		if(m_SO != NULL)
		{
			sX=m_SO[i].getTileX() * m_Map.getTileWidth() + m_Map.getScrollX();
			sY=m_SO[i].getTileY() * m_Map.getTileHeight() + m_Map.getScrollY()-16;
			// Only draw visible stationary objects...
			if(detectCollisionRectangle(sX, sY, sX+m_Map.getTileWidth(), sY+m_Map.getTileHeight(), 0, 0, m_Window.getWidth(), m_Window.getHeight()))
			{
				drawSprite(m_StationaryObject, getSurface(), 0, 0, sX, sY, m_Map.getTileWidth(), m_Map.getTileHeight()+16);
			}
		}
	}

	// Draw a frame around the edge of the map
	vLine32(getSurface(), m_Map.getLeftEdge(), m_Map.getTopEdge(), m_Map.getWindowHeight()-m_Map.getBottomEdge()-m_Map.getTopEdge(), 0x000000FF);
	vLine32(getSurface(), m_Map.getWindowWidth()-m_Map.getRightEdge(), m_Map.getTopEdge(), m_Map.getWindowHeight()-m_Map.getBottomEdge()-m_Map.getTopEdge(), 0x000000FF);
	hLine32(getSurface(), m_Map.getLeftEdge(), m_Map.getTopEdge(), m_Map.getWindowWidth()-m_Map.getLeftEdge()-m_Map.getRightEdge(), 0x000000FF);
	hLine32(getSurface(), m_Map.getLeftEdge(), m_Map.getWindowHeight()-m_Map.getBottomEdge(), m_Map.getWindowWidth()-m_Map.getLeftEdge()-m_Map.getRightEdge(), 0x000000FF);


	// Draw the mini map if enabled. Also draw all objects on it...
	if(miniMapEnabled())
	{
		for (int x=0; x < m_Map.getWidth(); x++)
		{
			for ( int y=0; y < m_Map.getHeight(); y++)
			{
				// Only draw the tiles actually visible in the window...
				if(  ((x * m_Map.getTileWidth() + m_Map.getScrollX()) <= m_Window.getWidth()) &&
					 ((x * m_Map.getTileWidth() + m_Map.getScrollX()) >= 0) &&
					 ((y * m_Map.getTileHeight() + m_Map.getScrollY()) <= m_Window.getHeight()) &&
					 ((y * m_Map.getTileHeight() + m_Map.getScrollY()) >= 0)  )
				{
					// Different color for different tile property of each tile...
					if(m_Map.getTileProperty(x, y)  & MGMAP_TP_PROPERTY_1)
					{
						putPixel32(getSurface(), x + m_Window.getWidth() - m_Map.getWidth() - 16, y + 16, 0x3F3F3F3F);
					}
					else if(m_Map.getTileProperty(x, y)  & MGMAP_TP_PROPERTY_2)
					{
						putPixel32(getSurface(), x + m_Window.getWidth() - m_Map.getWidth() - 16, y + 16, 0xFFFFFFFF);
					}
				}
				else
				{
					// Draw it black..
					putPixel32(getSurface(), x + m_Window.getWidth() - m_Map.getWidth() - 16, y + 16, 0x00000000);
				}
			}
		}
		// Draw all moving objects on the mini map..
		for(int i=0;i<getNumberOfMO();i++)
		{
			putPixel32(getSurface(), m_MO[i].getTileX() + m_Window.getWidth() - m_Map.getWidth() - 16, m_MO[i].getTileY() + 16, 0x00FF0000);
		}
	}

	// Example of how text can be printed on the surface.. Here FPS and time left between frames.
#ifndef MGF_DEBUGGING_ENABLED
	drawText(getSurface(), (string("MOs: ") + MGFramework::toString((int)getNumberOfMO())).c_str(), 16, m_Window.getWidth() - m_Map.getWidth() - 16, m_Map.getHeight() + 30, 0, 0, 0, 0, 255, 0);
	drawText(getSurface(), (string("FD : ") + MGFramework::toString((int)getLastFrameDelayTime())).c_str(), 16, m_Window.getWidth() - m_Map.getWidth() - 16, m_Map.getHeight() + 50, 0, 0, 0, 0, 255, 0);
	drawText(getSurface(), (string("FPS: ") + MGFramework::toString((int)getFPS())).c_str(), 16, m_Window.getWidth() - m_Map.getWidth() - 16, m_Map.getHeight() + 70, 0, 0, 0, 0, 255, 0);
#endif


	// Draw marking frame if marking is ongoing
	if(isFramingOngoing())
	{
		int uLX=smallest(getFrameStartX(), getFrameEndX());
		int uLY=smallest(getFrameStartY(), getFrameEndY());
		int xL=abs(getFrameStartX() - getFrameEndX());
		int yL=abs(getFrameStartY() - getFrameEndY());
		hLine32(getSurface(), uLX, uLY, xL, 0x00FF0000);
		hLine32(getSurface(), uLX, uLY+yL, xL, 0x00FF0000);
		vLine32(getSurface(), uLX, uLY, yL, 0x00FF0000);
		vLine32(getSurface(), uLX+xL, uLY, yL, 0x00FF0000);
	}


}