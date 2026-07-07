#pragma once
#include <Cosmos/CosmosBase.h>
#include <Cosmos/Shader/Shader.h>

namespace Cosmos {
    class COSMOS_API Renderer {
    public:
        bool Init();
        void SetViewport(int x, int y, int width, int height);
        void SetClearColor(float r, float g, float b, float a);
        void Clear();
        void Draw(unsigned int offset, unsigned int indexCount);
        void DrawArrays(unsigned int offset, unsigned int vertexCount);
    };
}