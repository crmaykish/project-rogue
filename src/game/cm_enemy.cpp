#include "cm_enemy.h"
#include "cm_random.h"
#include "cm_moveaction.h"
#include "cm_abilityaction.h"
#include "cm_waitaction.h"
#include "cm_logger.h"

namespace cm
{
    Enemy::Enemy(int x, int y)
    {
        TileX = x;
        TileY = y;

        // TODO: all enemies just have a melee attack for now
        Abilities.SetAbility(0, std::make_unique<MeleeAbility>());
    }

    void Enemy::Update(GameWorld &world)
    {
        if (!Active)
        {
            return;
        }

        // Can the player see this enemy?
        Visible = world.GetLevel()->GetTile(TileX, TileY)->Brightness > 0;

        if (HP == 0)
        {
            Active = false;
        }
    }

    bool Enemy::ActionReady()
    {
        return true;
    }

    std::unique_ptr<Action> Enemy::NextAction(GameWorld &world)
    {
        auto player = world.GetPlayer();
        auto playerDistance = world.DistanceToPlayer(TileX, TileY);

        if (playerDistance == 1)
        {
            // Set enemy's target to player
            TargetX = player->TileX;
            TargetY = player->TileY;

            // Melee attack the player
            auto meleeAction = std::make_unique<AbilityAction>(0, world);
            return meleeAction;
        }

        else if (playerDistance < 6 || HP < MaxHP)
        {
            // really bad pathfinding to player
            auto diffX = player->TileX - TileX;
            auto diffY = player->TileY - TileY;

            auto dir = MoveDirection::Unknown;

            if (diffX > 0)
            {
                dir = MoveDirection::Right;
            }
            else if (diffX < 0)
            {
                dir = MoveDirection::Left;
            }
            else if (diffY > 0)
            {
                dir = MoveDirection::Up;
            }
            else if (diffY < 0)
            {
                dir = MoveDirection::Down;
            }

            return std::make_unique<MoveAction>(dir, world);
        }

        return std::make_unique<WaitAction>();
    }

    void Enemy::Render(const Renderer &renderer)
    {
        if (Active && Visible)
        {
            renderer.DrawTexture(Texture, TileX * TileSize, TileY * TileSize, TileSize, TileSize);

            renderer.DrawFont(std::to_string(HP) + " / " + std::to_string(MaxHP),
                              AssetKey::UIFont,
                              ColorWhite,
                              TileX * TileSize,
                              (TileY + 1) * TileSize,
                              0.5);
        }
    }

    Inventory *Enemy::GetInventory()
    {
        return nullptr;
    }

    AbilitySet *Enemy::GetAbilitySet()
    {
        return &Abilities;
    }

    std::unique_ptr<Actor> Ghost(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Ghost";
        a->Texture = AssetKey::GhostTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        a->Strength = RandomInt(5, 12);
        a->Vitality = RandomInt(8, 12);
        a->Dexterity = 3;
        a->Intellect = 2;
        
        a->InitStats();

        return a;
    }

    std::unique_ptr<Actor> RandomEnemy(int x, int y, int level)
    {
        return Ghost(x, y, level);
    }

} // namespace cm
