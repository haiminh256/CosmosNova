#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <set>
#include <optional>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#define COSMOS_API __declspec(dllexport)
#else
#define COSMOS_API __attribute__((visibility("default")))
#endif