#include "textdisplay.h"

TextDisplay::TextDisplay(){
    theDisplay = vector<vector<char>>(8, vector<char>(8, '.'));
}

void TextDisplay::notify(Link &link) {
  int x = link.getCurrCoords().getX();
  int y = link.getCurrCoords().getY();
  theDisplay[y][x] = link.getDisplayName()[0];
}

void TextDisplay::notify(GameBoard &gb) {
}

void TextDisplay::init(GameBoard& gb) {
    myGb = &gb;
    vector<ServerPort> sp = gb.getServerPort();
    for (int i = 0; i < sp.size(); i++) {
      int x = sp[i].getCoords().getX();
      int y = sp[i].getCoords().getY();
      theDisplay[y][x] = sp[i].getDisplayName()[0];
    }
}

void printPlayerInfo(Player& p, GameBoard* gb, ostream& out) {
  out << p.getPlayerName() << ":" << endl;
  out << "Downloaded: " << p.getNumDataDownloads() << "D, " << p.getNumVirusDownloads() << "V" << endl;
  out << "Abilities: " << p.getAbilityCount() << endl;
  vector<shared_ptr<Link>> playerLinks = *gb->getPlayerLinks(p);
  for (int i = 0; i < playerLinks.size(); i++) {
    if (i == playerLinks.size() / 2) { // halfway point
      out << "\n";
    }
    shared_ptr<Link> curLink = playerLinks[i];
    out << curLink->getDisplayName() << ": ";
    if (curLink->isIdentityRevealed()) {
      if (curLink->getType() == LinkType::data) {
        out << "D";
      } else {
        out << "V";
      }
    out << to_string(curLink->getStrength());
    }
  }
  out << endl;
}

void printBoardBoundaries(int boundarySize, ostream& out) {
  for (int i = 0; i < boundarySize; i++) {
    out << "=";
  }
  out << endl;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  Player &p1 = (td.myGb->getPlayers())[td.myGb->getCurrPlayerIndex()];
  Player &p2 = (td.myGb->getPlayers())[td.myGb->getNextPlayerIndex()];
  // player 1
  printPlayerInfo(p1, td.myGb, out);
  // board top edge
  printBoardBoundaries(td.myGb->BOARD_SIZE, out);
  // board
  for (int i = 0; i < td.myGb->BOARD_SIZE; i++) { 
    for (int j = 0; j < td.myGb->BOARD_SIZE; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  // board bottom edge
  printBoardBoundaries(td.myGb->BOARD_SIZE, out);
  // player 2
  printPlayerInfo(p2, td.myGb, out);
  return out;
}
