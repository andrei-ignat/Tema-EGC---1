#pragma once

#include "utils/glm_utils.h"
#include <cmath>
#include <algorithm>


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY) {
        return glm::transpose(glm::mat3(
            1, 0, translateX,
            0, 1, translateY,
            0, 0, 1
        ));
    }

    inline glm::mat3 Translate1() {
        return glm::mat3(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        );
    }

    // Scale matrix
    inline glm::mat3 Scale() {
        return glm::mat3(
            1, 0, 0,
            0, std::max(0, 1), 0,
            0, 0, 1
        );
    }

    inline glm::mat3 Shear() {
        return glm::mat3(
            1, 0, 0,
            (100 - 0)/(100 - 0), 1, 0,
            0, 0, 1
        );
    }

    inline glm::mat3 Scale(float scaleX, float scaleY) {
        return glm::mat3(
            scaleX, 0.0f, 0.0f,
            0.0f, scaleY, 0.0f,
            0.0f, 0.0f, 1.0f
        );
    }

    inline glm::mat3 Shear(float shearX, float shearY) {
        return glm::mat3(
            1.0f, shearY, 0.0f,
            shearX, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        );
    }


    // Rotate matrix
    inline glm::mat3 Rotate(float radians) {
        return glm::transpose(glm::mat3(
            cosf(radians), -sinf(radians), 0,
            sinf(radians), cosf(radians), 0,
            0, 0, 1
        ));
    }
}   // namespace transform2D