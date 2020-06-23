#include "cm_component_player_render.h"
#include "cm_world.h"

namespace cm
{
    PlayerRenderComponent::PlayerRenderComponent(std::shared_ptr<Actor> owner, std::shared_ptr<Renderer> renderer)
        : MainRenderer(renderer), Owner(owner) {}

    void PlayerRenderComponent::OnUpdate() {}

    void PlayerRenderComponent::OnRender()
    {
        float playerOffset = 4;
        float playerSize = TILE_SIZE - 2 * playerOffset;

        MainRenderer->DrawRectangle(Owner->GetX() + playerOffset,
                                    Owner->GetY() + playerOffset,
                                    playerSize,
                                    playerSize,
                                    COLOR_GREEN);
    }

} // namespace cm