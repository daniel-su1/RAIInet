#ifndef LINK_H
#define LINK_H

#include "boardpiece.h"
enum LinkType {DATA, VIRUS};

class Link: public BoardPiece{
    protected:
        Player* downloader;
        int strength;  
        LinkType type;
        bool identityRevealed;
        bool downloaded; 
        Link(int strength, Coords currCoords, string displayName, Player &owner, LinkType type, string typeAndStrength);
    public:
        // attaches a player (downloader) to the piece
        void attachDownloader(Player *p);
        Player& getDownloader();
        bool isDownloaded();
        void setDownloaded(bool d);
        void setStepSize(int stepSize);
        void polarize(string virusStr, string dataStr);
        string typeAndStrength;
        // returns the strength of the link
        int getStrength();
        // returns the type of the link
        LinkType getType();
        // returns true/false depending on whether identity of the link is known by the other player
        bool isIdentityRevealed();
        // returns step size
        int getStepSize();
        virtual ~Link();
        void setIdentityRevealed(bool b);
};

#endif
