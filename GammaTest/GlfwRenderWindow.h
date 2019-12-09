#ifndef BEYOND_ENGINE_RENDER_WIN32_GLFWRENDERWINDOW_H__INCLUDE
#define BEYOND_ENGINE_RENDER_WIN32_GLFWRENDERWINDOW_H__INCLUDE
#include <map>
#include <windows.h>
#include "glew/glew.h"
#include "glfw/glfw3.h"

struct GLFWwindow;
class CGlfwRenderWindow
{
public:
    CGlfwRenderWindow(int nWidth, int nHeight);
    virtual ~CGlfwRenderWindow();

    virtual void SetToCurrent();
    virtual void Render();

    GLFWwindow *GetMainWindow() const;

private:
    bool InitGlew();
    bool BindingFBO();
    bool IsLeftMouseDown() { return m_bLeftMouseDown; }
    void GetMousePos(uint32_t& x, uint32_t& y) { x = m_uCurMousePosX, y = m_uCurMousePosY; }

    static void onGLFWError(int errorID, const char* errorDesc);
    static void onGLFWMouseMoveCallBack(GLFWwindow* window, double x, double y);
    static void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void onGLFWCharCallback(GLFWwindow* window, unsigned int character);
    static void onGLFWSizeChangeCallback(GLFWwindow* window, int nWidth, int nHeight);
private:
    GLFWwindow* m_pMainWindow;
    bool m_bGlewInited;
    bool m_bLeftMouseDown;
    uint32_t m_uLastMousePosX;
    uint32_t m_uLastMousePosY;
    uint32_t m_uCurMousePosX;
    uint32_t m_uCurMousePosY;
    static std::map<GLFWwindow *, CGlfwRenderWindow *> m_sInstanceMap;
};

#endif