#ifndef SCAN_H
#define SCAN_H
#include "../abilitycard.h"
class Scan: public AbilityCard {
    public:
        void activate() override;
        Scan(int abilityID, Player &owner, string DisplayName);
};

#endif

