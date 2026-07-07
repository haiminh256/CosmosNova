#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <spdlog/spdlog.h>
#include <vector>
#include <set>
#include <optional>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstddef>
#include <memory>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>	

#ifdef _WIN32
#define COSMOS_API __declspec(dllexport)
#else
#define COSMOS_API __attribute__((visibility("default")))
#endif

template<typename T> using Unique = std::unique_ptr<T>;
template<typename T> using Shared = std::shared_ptr<T>;