#include <Cosmos/Renderer/Transform.h>

namespace Cosmos
{
	glm::mat4 Transform::GetModelMatrix() const
	{
        // 1. Khởi tạo ma trận đơn vị
        glm::mat4 model = glm::mat4(1.0f);

        // 2. Dịch chuyển trước (Translation)
        model = glm::translate(model, Position);

        // 3. Xoay các trục theo thứ tự chuẩn toán học để không bị lệch hệ trục cục bộ
        model = glm::rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z trước
        model = glm::rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y giữa
        model = glm::rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X sau

        // 4. Co giãn sau cùng (Scale)
        model = glm::scale(model, Scale);

        return model;
	}
}