#include "Initializer.h"

namespace Viewer
{

    Initializer::Initializer()
    {
    }

    /*virtual*/
    Initializer::~Initializer()
    {
    }

    /*virtual*/ void
    Initializer::apply() const
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
}

