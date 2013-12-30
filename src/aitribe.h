#ifndef _AITRIBE_H
#define _AITRIBE_H

#include "mgframework/mgframework.h"

class AITribe : public MGFramework
{
	private:

		// These methods have to be implemented in a class derived from MGFramework.
		virtual void handleGameLogics();
		virtual void draw();

		// Graphics (which is not part of the framework) should be added here.
		SDL_Surface *m_Floor;
		SDL_Surface *m_MovingObject;
		SDL_Surface *m_StationaryObject;
		SDL_Surface *m_Mark;

	public:
		AITribe();
		virtual bool init(int w, int h, int tw, int th); // Has to be implemented in a class derived from MGFramework
};

#endif




