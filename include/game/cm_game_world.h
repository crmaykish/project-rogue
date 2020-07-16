#ifndef CM_WORLD_H
#define CM_WORLD_H

#include <vector>
#include "cm_tile.h"
#include "cm_actor.h"
#include "cm_renderer.h"
#include "cm_input.h"
#include "cm_map.h"

namespace cm
{
    class Action;
    class Map;

    struct EventLogElem
    {
        std::string event;
        Color color;
    };

    struct CombatText
    {
        std::string Text;
        int X = 0;
        int Y = 0;
        Color RenderColor = ColorRed;
        int Age = 0;
    };

    class GameWorld
    {
    private:
        UserInput &Input;
        bool NextLevel = false;
        int TurnNumber = 0;
        int CurrentActorIndex = 0;

        bool TileSelectMode = false;
        bool TileSelected = false;
        Point SelectedTile;

        int LevelNumber = 0;

        std::unique_ptr<Map> Level;

        std::vector<std::shared_ptr<Actor>> Actors;
        std::shared_ptr<Actor> PlayerOne;

        std::unique_ptr<Action> CurrentAction;

        int EventLogIndex = 1;
        std::vector<EventLogElem> EventLog;

        std::vector<CombatText> ScrollingCombatText;

        void CreateLevel();

        // Return the actor whose turn it is
        Actor *GetCurrentActor();
        void NextActor();

    public:
        GameWorld(UserInput &input);

        void Init();
        void Update();
        void Render(Renderer &renderer);

        void AddPlayer(std::shared_ptr<Actor> player);
        Actor *GetActor(int x, int y) const;
        Actor *GetPlayer() const;

        void SetNextLevel();

        // TODO: this shouldn't really be necessary. operate on the map directly instead
        Map *GetLevel();

        int GetTurnNumber() { return TurnNumber; }
        int GetLevelNumber() { return LevelNumber; }

        bool IsTileSelectMode()
        {
            return TileSelectMode;
        }

        void LogEvent(std::string event, bool friendly);
        std::vector<EventLogElem> &GetEventLog() { return EventLog; }

        void AddCombatText(CombatText combatText);
    };

} // namespace cm

#endif // CM_WORLD_H
