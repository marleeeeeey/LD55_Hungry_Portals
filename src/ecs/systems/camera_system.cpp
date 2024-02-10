#include "camera_system.h"
#include <SDL.h>
#include <ecs/components/all_components.h>
#include <imgui_impl_sdl2.h>
#include <my_common_cpp_utils/Logger.h>

void CameraSystem(entt::registry& registry)
{
    auto& gameState = registry.get<GameState>(registry.view<GameState>().front());

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
        {
            gameState.quit = true;
        }

        else if (event.type == SDL_MOUSEWHEEL)
        {
            float prevScale = gameState.cameraScale;

            // Calculate the new scale of the camera
            const float scaleSpeed = 0.1f;
            if (event.wheel.y > 0)
                gameState.cameraScale += scaleSpeed;
            else if (event.wheel.y < 0)
                gameState.cameraScale -= scaleSpeed;
            gameState.cameraScale = glm::clamp(gameState.cameraScale, 0.2f, 6.0f);

            // Get the cursor coordinates in world coordinates
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            glm::vec2 mouseWorldBeforeZoom =
                (glm::vec2(mouseX, mouseY) - gameState.windowSize * 0.5f) / prevScale + gameState.cameraCenter;

            gameState.debugMsg2 = MY_FMT("mouseWorldBeforeZoom {}", mouseWorldBeforeZoom);

            // Calculate the new position of the camera so that the point under the cursor remains in the same place
            gameState.cameraCenter = mouseWorldBeforeZoom -
                (glm::vec2(mouseX, mouseY) - gameState.windowSize * 0.5f) / gameState.cameraScale;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT)
        {
            gameState.isSceneCaptured = true;
        }
        else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_RIGHT)
        {
            gameState.isSceneCaptured = false;
        }
        else if (event.type == SDL_MOUSEMOTION && gameState.isSceneCaptured)
        {
            gameState.debugMsg = MY_FMT("Mouse moved to ({}, {})", event.motion.x, event.motion.y);

            float deltaX = event.motion.xrel / gameState.cameraScale;
            float deltaY = event.motion.yrel / gameState.cameraScale;
            gameState.cameraCenter.x -= deltaX;
            gameState.cameraCenter.y -= deltaY;
        }
    }
}
