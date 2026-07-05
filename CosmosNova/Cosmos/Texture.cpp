#include <Cosmos/Renderer/Texture.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {
	Texture::Texture() {
		glGenTextures(1, &id);
	}
	void Texture::Load(const std::string& filePath, bool flip) {
		stbi_set_flip_vertically_on_load(flip);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
        if (!data) {
            CORE_ERROR("Texture::Load() failed");
        }
        CORE_INFO("Texture::Load() success");

        GLenum format = GL_RGB;

        switch (channels)
        {
        case 1:
            format = GL_RED;
            break;

        case 3:
            format = GL_RGB;
            break;

        case 4:
            format = GL_RGBA;
            break;
        }

        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);

        glTexParameteri(GL_TEXTURE_2D,
            GL_TEXTURE_MAG_FILTER,
            GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data);

        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
	}
    void Texture::Bind(unsigned int unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, id);
    }
    void Texture::Delete() {
        if (id)
        {
            glDeleteTextures(1, &id);
            id = 0;
        }
    }
}