#ifndef __PotionCommand_h__
#define __PotionCommand_h__
////////////////////////////////////////////////////////////////////////////////
#include "Command.h"
class Game;
#include "Dungeon.h"
#include <sstream>
////////////////////////////////////////////////////////////////////////////////
class PotionCommand  : public Command
{
public:
  PotionCommand( Game *pGame ) : Command(pGame) { }

  
  void Execute() {
	GetGame()->GetPlayer().UsePotion();
  }
};
#endif