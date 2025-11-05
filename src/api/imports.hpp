#pragma once

#ifdef _WIN32
#define MCAPI __declspec(dllimport)
#define SELAURA_API extern "C" __declspec(dllexport)
#else
#define SELAURA_API extern "C" __attribute__((visibility("default")))
#endif

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include <string>