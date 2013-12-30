#include "aitribe.h"
#include "mgframework/mgframework.h"

using std::string;

int main(int argc, char **argv)
{
	AITribe* ait = 0;

	bool loggingOn = false;
	bool scriptFile = false;
	char scriptFileName[256] = "";

	if(argc==1)
	{
		// No parameters were given
	}
	else
	{
		for(int i=1; i<argc; i++)
		{
			if(strcmp(argv[i], "-logging")==0)
			{
				loggingOn = true;
			}
			else if(strcmp(argv[i], "-script")==0)
			{
				if(i+1 == argc)
				{
					//No parameter after -script
					goto EXIT_MAIN_RIGHT_AWAY;
				}
				else
				{
					//Store argv[++i] as script file name..
					strcpy(scriptFileName, argv[++i]);
					scriptFile = true;
				}
			}
			else
			{
				// Unknown parameter.
			}
		}
	}


	// Create and initialize the framework...


	ait = new AITribe();
	ait->setWindowProperties(MGWindow_RES_1600_900, 32, false, 
							 string("AI Tribe ") + 
							 string(ait->getAITribeVersion())+ 
							 string(" based on MGF ") + 
							 string(ait->getMGFrameworkVersion()));

	if(loggingOn) ait->enableLogging();

	if(ait->windowPropertiesSet())
	{
		// If initialization is ok, run the framework...
		if(ait->init(128, 128, 32, 32))
		{
			if(scriptFile)
			{
				ait->run(scriptFileName);
			}
			else
			{
				ait->run(NULL);
			}
		}
		else
		{

		}
	}
	else 
	{

	}

EXIT_MAIN_RIGHT_AWAY:

	if(ait)
	{
		delete ait;
	}
	else
	{
		return 1;
	}

	return 0;
}
