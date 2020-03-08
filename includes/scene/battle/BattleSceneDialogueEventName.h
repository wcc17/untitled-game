#ifndef NEWNEW_BATTLESCENEDIALOGUEEVENTNAME_H
#define NEWNEW_BATTLESCENEDIALOGUEEVENTNAME_H

#include <string>

class BattleSceneDialogueEventName {
    public:
        static const std::string ENEMY_APPEARED;
        static const std::string PARTY_RAN_AWAY;
        static const std::string PARTY_COULD_NOT_RUN;
};

const std::string BattleSceneDialogueEventName::ENEMY_APPEARED = "enemy_appeared";
const std::string BattleSceneDialogueEventName::PARTY_RAN_AWAY = "party_ran_away";
const std::string BattleSceneDialogueEventName::PARTY_COULD_NOT_RUN = "party_could_not_run";

#endif //NEWNEW_BATTLESCENEDIALOGUEEVENTNAME_H
