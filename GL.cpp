#include "GL.h"

bool InitGL()
{
#ifdef USE_GLEW
	return glewInit() == GLEW_OK;
#elif defined(USE_GL3W)
	// TODO :: Add GL3W
#elif defined(USE_GLAD)
	// TODO :: Add GLAD
#endif
}
