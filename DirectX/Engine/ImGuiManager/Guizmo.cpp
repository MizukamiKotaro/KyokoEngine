#include "Guizmo.h"
#ifdef _DEBUG
#include "Externals/imgui/ImGuizmo.h"
#include "Externals/imgui/imgui.h"

namespace ImGuiCommon {
    Vector3 ShowTransformGizmo(const ImGuiCommon::Type& type, const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, Matrix4x4& objectMatrix)
    {
        static ImGuizmo::OPERATION currentOperation = ImGuizmo::TRANSLATE;
        switch (type)
        {
        case ImGuiCommon::Type::TRANSLATE:
            currentOperation = ImGuizmo::TRANSLATE;
            break;
        case ImGuiCommon::Type::SCALE:
            currentOperation = ImGuizmo::SCALE;
            break;
        default:
            break;
        }

        ImGuizmo::Manipulate(&viewMatrix.m[0][0], &projectionMatrix.m[0][0], currentOperation, ImGuizmo::WORLD, &objectMatrix.m[0][0]);

        switch (type)
        {
        case ImGuiCommon::Type::TRANSLATE:
            return Vector3(objectMatrix.m[3][0], objectMatrix.m[3][1], objectMatrix.m[3][2]);
            break;
        case ImGuiCommon::Type::SCALE:
            return Vector3(objectMatrix.m[0][0], objectMatrix.m[1][1], objectMatrix.m[2][2]);
            break;
        default:
            break;
        }
        return Vector3();
    }
}
#endif // _DEBUG
