#include <windows.h>
#include <iostream>

#include "Game.h"

static void setConsoleSize(int width, int height)
{
    // Obtenir le handle de la console
    HWND console = GetConsoleWindow();
    if (console == NULL) {
        std::cerr << "Erreur : impossible d'obtenir le handle de la console" << std::endl;
        return;
    }

    // Définir la taille de la fenêtre de la console
    RECT r;
    GetWindowRect(console, &r); // Obtenir la taille actuelle de la fenêtre
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

int main()
{
    setConsoleSize(300, 800);

	Game game;

	return 0;
}