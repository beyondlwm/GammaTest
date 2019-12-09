#include "GlfwRenderWindow.h"

std::map<GLFWwindow *, CGlfwRenderWindow *> CGlfwRenderWindow::m_sInstanceMap;

CGlfwRenderWindow::CGlfwRenderWindow(int nWidth, int nHeight)
    : m_pMainWindow(nullptr)
    , m_bGlewInited(false)
    , m_bLeftMouseDown(false)
    , m_uLastMousePosX(0)
    , m_uLastMousePosY(0)
    , m_uCurMousePosX(0)
    , m_uCurMousePosY(0)
{
    glfwSetErrorCallback(CGlfwRenderWindow::onGLFWError);
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

    m_pMainWindow = glfwCreateWindow(nWidth, nHeight, "StarRaiders", NULL, NULL);
    m_sInstanceMap[m_pMainWindow] = this;

    glfwSetCursorPosCallback(m_pMainWindow,CGlfwRenderWindow::onGLFWMouseMoveCallBack);
    glfwSetCharCallback(m_pMainWindow, CGlfwRenderWindow::onGLFWCharCallback);
    glfwSetKeyCallback(m_pMainWindow, CGlfwRenderWindow::onGLFWKeyCallback);
    glfwSetWindowSizeCallback(m_pMainWindow, CGlfwRenderWindow::onGLFWSizeChangeCallback);
}
CGlfwRenderWindow::~CGlfwRenderWindow()
{
    glfwDestroyWindow(m_pMainWindow);
    glfwTerminate();
}

void CGlfwRenderWindow::SetToCurrent()
{
    glfwMakeContextCurrent(m_pMainWindow);
    if(!m_bGlewInited)
    {
        InitGlew();
        m_bGlewInited = true;
    }
}

void CGlfwRenderWindow::Render()
{
	glfwSwapBuffers(m_pMainWindow);
}

GLFWwindow *CGlfwRenderWindow::GetMainWindow() const
{
    return m_pMainWindow;
}

bool CGlfwRenderWindow::InitGlew()
{
    GLenum GlewInitResult = glewInit();
    bool bRet = GlewInitResult == GLEW_OK;
    bool bFrameBufferSupport = BindingFBO();
    return bRet && bFrameBufferSupport;
}

bool CGlfwRenderWindow::BindingFBO()
{
    const char *gl_extensions = (const char*)glGetString(GL_EXTENSIONS);

    // If the current opengl driver doesn't have framebuffers methods, check if an extension exists
    if (glGenFramebuffers == NULL)
    {
        if (strstr(gl_extensions, "ARB_framebuffer_object"))
        {
            glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbuffer");
            glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbuffer");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffers");
            glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffers");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorage");
            glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameteriv");
            glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebuffer");
            glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebuffer");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffers");
            glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffers");
            glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatus");
            glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1D");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2D");
            glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3D");
            glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbuffer");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmap");
        }
        else if (strstr(gl_extensions, "EXT_framebuffer_object"))
        {
            glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC) wglGetProcAddress("glIsRenderbufferEXT");
            glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC) wglGetProcAddress("glBindRenderbufferEXT");
            glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC) wglGetProcAddress("glDeleteRenderbuffersEXT");
            glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC) wglGetProcAddress("glGenRenderbuffersEXT");
            glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC) wglGetProcAddress("glRenderbufferStorageEXT");
            glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetRenderbufferParameterivEXT");
            glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC) wglGetProcAddress("glIsFramebufferEXT");
            glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC) wglGetProcAddress("glBindFramebufferEXT");
            glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC) wglGetProcAddress("glDeleteFramebuffersEXT");
            glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC) wglGetProcAddress("glGenFramebuffersEXT");
            glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC) wglGetProcAddress("glCheckFramebufferStatusEXT");
            glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC) wglGetProcAddress("glFramebufferTexture1DEXT");
            glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC) wglGetProcAddress("glFramebufferTexture2DEXT");
            glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC) wglGetProcAddress("glFramebufferTexture3DEXT");
            glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC) wglGetProcAddress("glFramebufferRenderbufferEXT");
            glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) wglGetProcAddress("glGetFramebufferAttachmentParameterivEXT");
            glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC) wglGetProcAddress("glGenerateMipmapEXT");
        }
        else
        {
            return false;
        }
    }
    return true;
}

void CGlfwRenderWindow::onGLFWError( int errorID, const char* errorDesc )
{
}


void CGlfwRenderWindow::onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y)
{
  
}

void CGlfwRenderWindow::onGLFWKeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int mods)
{
}

void CGlfwRenderWindow::onGLFWCharCallback(GLFWwindow* /*window*/, unsigned int character)
{
}

void CGlfwRenderWindow::onGLFWSizeChangeCallback(GLFWwindow* /*window*/, int nWidth, int nHeight)
{
}