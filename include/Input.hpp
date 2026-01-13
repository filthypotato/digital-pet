#pragma once

#include "ncurses_app.hpp"
#include "Pet.hpp"
#include "Renderer.hpp"

void keyboardInput(NcursesApp& app, Renderer& renderer, PetState& state);
