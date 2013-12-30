#ifndef _AITRIBE_H
#define _AITRIBE_H

#include "mgframework/mgframework.h"

#define AITRIBEVERSION "0.0.0.2"

class AITribe : public MGFramework
{
	private:

		// These methods have to be implemented in a class derived from MGFramework.
		virtual void handleGameLogics();
		virtual void draw();

		// Graphics (which is not part of the framework) should be added here.
		SDL_Surface *m_Floor;

		SDL_Surface *m_MO_00;
		SDL_Surface *m_MO_01;
		SDL_Surface *m_MO_02;
		SDL_Surface *m_MO_03;
		SDL_Surface *m_MO_04;
		SDL_Surface *m_MO_05;
		SDL_Surface *m_MO_06;
		SDL_Surface *m_MO_07;
		SDL_Surface *m_MO_08;

		SDL_Surface *m_StationaryObject;
		SDL_Surface *m_Mark;

	public:
		AITribe();
		virtual bool init(int w, int h, int tw, int th); // Has to be implemented in a class derived from MGFramework

		virtual const char* getAITribeVersion(){ return AITRIBEVERSION; }
};

#endif




