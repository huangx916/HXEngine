#ifndef __VAPP_H__
#define __VAPP_H__

#include "vgl.h"

class VermillionApplication
{
protected:
    inline VermillionApplication(void) {}
    virtual ~VermillionApplication(void) {}

    static VermillionApplication * s_app;

    static void DisplayFunc(void);
    static void ReshapeFunc(int width, int height);

#ifdef _DEBUG
    static void APIENTRY DebugOutputCallback(GLenum source,
                                             GLenum type,
                                             GLuint id,
                                             GLenum severity,
                                             GLsizei length,
                                             const GLchar* message,
                                             GLvoid* userParam);
#endif

public:
    static void MainLoop(void);

    virtual void Initialize(const char * title = 0)
    {
        int one = 1;
        char * name = "name";

#ifdef _DEBUG
        glutInitContextFlags(GLUT_DEBUG);
#endif
        // glutInitContextProfile(GLUT_CORE_PROFILE);
        // glutInitContextVersion(4, 3);

        glutInitWindowSize(1024, 768);
        glutInitWindowPosition (140, 140);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
        glutInit(&one, &name);

        glutCreateWindow( title ? title : "OpenGL Application" );
        glutDisplayFunc(DisplayFunc);
        glutReshapeFunc(ReshapeFunc);

#ifdef USE_GL3W
        gl3wInit();
#else
        glewInit();
#endif

#ifdef _DEBUG
        if (glDebugMessageCallbackARB != NULL)
            glDebugMessageCallbackARB(DebugOutputCallback, this);
#endif
    }

    virtual void Display(bool auto_redraw = true)
    {
        glutSwapBuffers();
        if (auto_redraw)
        {
            glutPostRedisplay();
        }
    }

    virtual void Finalize(void)
    {

    }

    virtual void Reshape(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
};

#define BEGIN_APP_DECLARATION(appclass)                     \
class appclass : public VermillionApplication               \
{                                                           \
public:                                                     \
    typedef class VermillionApplication base;               \
    static VermillionApplication * Create(void)             \
    {                                                       \
        return (s_app = new appclass);                      \
    }

#define END_APP_DECLARATION()                               \
};

#ifdef _DEBUG
#define DEBUG_OUTPUT_CALLBACK                                                   \
void APIENTRY VermillionApplication::DebugOutputCallback(GLenum source,         \
                                                         GLenum type,           \
                                                         GLuint id,             \
                                                         GLenum severity,       \
                                                         GLsizei length,        \
                                                         const GLchar* message, \
                                                         GLvoid* userParam)     \
{                                                                               \
    OutputDebugStringA(message);                                                \
    OutputDebugStringA("\n");                                                   \
}
#else
#define DEBUG_OUTPUT_CALLBACK
#endif

#define DEFINE_APP(appclass,title)                          \
VermillionApplication * VermillionApplication::s_app;       \
                                                            \
void VermillionApplication::DisplayFunc(void)               \
{                                                           \
    s_app->Display();                                       \
}                                                           \
                                                            \
void VermillionApplication::ReshapeFunc(int width,          \
                                        int height)         \
{                                                           \
    s_app->Reshape(width, height);                          \
}                                                           \
                                                            \
void VermillionApplication::MainLoop(void)                  \
{                                                           \
    for (;;)                                                \
        glutMainLoopEvent();                                \
}                                                           \
                                                            \
int main(int argc, char ** argv)                            \
{                                                           \
    VermillionApplication * app = appclass::Create();       \
                                                            \
    app->Initialize(title);                                 \
    app->MainLoop();                                        \
    app->Finalize();                                        \
                                                            \
    return 0;                                               \
}                                                           \
                                                            \
DEBUG_OUTPUT_CALLBACK

#endif /* __VAPP_H__ */
