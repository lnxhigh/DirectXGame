#pragma once

#include <memory>

class Window;
class Renderer;
class Timer;

class App
{
public:
    App(void* h_instance, int cmd_show);
    ~App();

    bool Init();
    int Run();

private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<Timer> m_timer;
};
