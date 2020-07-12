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
        // TODO fix this
        // Visible = world.TileBrightness(TileX, TileY) > 0;
        Visible = true;

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
            // attack player
            auto meleeAction = std::make_unique<AbilityAction>(0, world);
            meleeAction->SetTarget(player->TileX, player->TileY);
            return meleeAction;
        }

        else if (playerDistance < 500)
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

    int Enemy::GetAttack()
    {
        return BaseAttack * Level;
    }

    int Enemy::GetDefense()
    {
        return BaseDefense * Level;
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

        // Stats
        a->MaxHP = level * (15 + RandomInt(10)); // 15-25 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 5;
        a->BaseDefense = 2;

        return a;
    }

    std::unique_ptr<Actor> Flame(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Flame";
        a->Texture = AssetKey::FlameTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        // Stats
        a->MaxHP = level * (10 + RandomInt(8)); // 10-18 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 10;
        a->BaseDefense = 1;

        return a;
    }

    std::unique_ptr<Actor> Skeleton(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Skeleton";
        a->Texture = AssetKey::SkeletonTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        // Stats
        a->MaxHP = level * (20 + RandomInt(10)); // 20-30 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 12;
        a->BaseDefense = 20;

        return a;
    }

    std::unique_ptr<Actor> Spider(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Spider";
        a->Texture = AssetKey::SpiderTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        // Stats
        a->MaxHP = level * (6 + RandomInt(30)); // 6-36 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 4;
        a->BaseDefense = 5;

        return a;
    }

    std::unique_ptr<Actor> Slime(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Slime";
        a->Texture = AssetKey::SlimeTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        // Stats
        a->MaxHP = level * (12 + RandomInt(4)); // 12-16 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 3;
        a->BaseDefense = 8;

        return a;
    }

    std::unique_ptr<Actor> Mimic(int x, int y, int level)
    {
        auto a = std::make_unique<Enemy>(x, y);
        a->Name = "Mimic";
        a->Texture = AssetKey::MimicTexture;
        a->Visible = true;
        a->Active = true;
        a->Level = level;

        // Stats
        a->MaxHP = level * (20 + RandomInt(20)); // 20-40 health per level
        a->HP = a->MaxHP;
        a->BaseAttack = 15;
        a->BaseDefense = 10;

        return a;
    }

    std::unique_ptr<Actor> RandomEnemy(int x, int y, int level)
    {
        switch (RandomInt(6))
        {
        case 0:
            return Ghost(x, y, level);
            break;
        case 1:
            return Flame(x, y, level);
            break;
        case 2:
            return Spider(x, y, level);
            break;
        case 3:
            return Skeleton(x, y, level);
            break;
        case 4:
            return Slime(x, y, level);
            break;
        case 5:
            return Mimic(x, y, level);
            break;
        default:
            return nullptr;
        }
    }

} // namespace cm
