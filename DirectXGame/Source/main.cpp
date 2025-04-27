#include <windows.h>

#include "Core/App.h"

int WINAPI wWinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, PWSTR p_cmd_line, int cmd_show)
{
	App app(h_instance, cmd_show);
	if (!app.Init()) return -1;

	return app.Run();
}
