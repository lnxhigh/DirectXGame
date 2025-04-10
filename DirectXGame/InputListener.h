#pragma once

class InputListener
{
public:
    virtual void OnKeyDown(int key) {}
    virtual void OnKeyUp(int key) {}
    virtual void OnMouseMove(int dx, int dy) {}
    virtual void OnResize(int width, int height) {}
    virtual ~InputListener() = default;
};
