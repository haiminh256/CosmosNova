#include <Cosmos/Renderer/Texture.h>
#include <Cosmos/Core/Log.h>

namespace Cosmos {
	Texture::Texture() {
		glGenTextures(1, &id);
	}
	bool Texture::Load(const std::string& filePath, bool flip) {
		stbi_set_flip_vertically_on_load(flip);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
        if (!data) {
            CORE_ERROR("Texture::Load() failed");
            return false;
        }
        CORE_INFO("Texture::Load() success");
        CORE_INFO(filePath);
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
        return true;
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
    void Texture::setType(std::string Type) {
        this->Type = Type;
    }
    void Texture::setPath(std::string Path) {
        this->Path = Path;
    }
    bool Texture::LoadFromMemory(const unsigned char* buffer, int bufferSize, bool flip) {
        stbi_set_flip_vertically_on_load(flip);

        // Sử dụng hàm stbi_load_from_memory thay vì stbi_load thông thường
        unsigned char* data = stbi_load_from_memory(buffer, bufferSize, &width, &height, &channels, 0);
        if (!data) {
            CORE_ERROR("Texture::LoadFromMemory() failed");
            return false;
        }

        GLenum format = GL_RGB;
        if (channels == 1) format = GL_RED;
        else if (channels == 3) format = GL_RGB;
        else if (channels == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
        return true;
    }
}