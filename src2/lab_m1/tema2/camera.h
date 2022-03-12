#pragma once

#include "utils/glm_utils.h"
#include "utils/math_utils.h"


namespace implementedCamera
{
    class Camera
    {
    public:
        Camera()
        {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            Set(position, center, up);
        }

        ~Camera()
        { }

        void Set(const glm::vec3& position, const glm::vec3& center, const glm::vec3& up)
        {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance)
        {
            glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
            position += dir * distance;
        }

        void TranslateForward(float distance)
        {
            position += forward * distance;
        }

        void TranslateUpward(float distance)
        {
            position += glm::vec3(0, up.y, 0) * distance;
        }

        void TranslateRight(float distance)
        {
            position += glm::vec3(right.x, 0, right.z) * distance;
        }

        void RotateFirstPerson_OX(float angle)
        {
            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, right) * glm::vec4(forward, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OY(float angle)
        {
            forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0)) * glm::vec4(right, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle)
        {
            right = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), angle, forward) * glm::vec4(right, 1)));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateThirdPerson_OX(float angle)
        {
            position = glm::vec3(glm::translate(glm::mat4(1), forward * distanceToTarget) * glm::vec4(position, 1));
            RotateFirstPerson_OX(angle);
            position = glm::vec3(glm::translate(glm::mat4(1), forward * (-distanceToTarget)) * glm::vec4(position, 1));
        }

        void RotateThirdPerson_OY(float angle)
        {
            position = glm::vec3(glm::translate(glm::mat4(1), forward * distanceToTarget) * glm::vec4(position, 1));
            RotateFirstPerson_OY(angle);
            position = glm::vec3(glm::translate(glm::mat4(1), forward * (-distanceToTarget)) * glm::vec4(position, 1));
        }

        void RotateThirdPerson_OZ(float angle)
        {
            position = glm::vec3(glm::translate(glm::mat4(1), forward * distanceToTarget) * glm::vec4(position, 1));
            RotateFirstPerson_OZ(angle);
            position = glm::vec3(glm::translate(glm::mat4(1), forward * (-distanceToTarget)) * glm::vec4(position, 1));
        }

        glm::mat4 GetViewMatrix()
        {
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition()
        {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}   // namespace implementedCamera
