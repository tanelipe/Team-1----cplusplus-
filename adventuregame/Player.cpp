////////////////////
/// C++ Object-oriented Programming
/// Adventure Game 6
/// Reference answer 
/// anssi.grohn@pkamk.fi
////////////////////
#include "Player.h"
#include "Game.h"
#include "IRenderer.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <fstream>
#include "HealthPotion.h"
#include <algorithm>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
Player::Player()
{
  SetHitpoints(3);
  potions.push(new HealthPotion());
}
////////////////////////////////////////////////////////////////////////////////
Player::~Player()
{
  
}
////////////////////////////////////////////////////////////////////////////////
// Juha Perala - Added '<<' operator overloading for IRenderer
void
Player::Attack( GameObject *pObject )
{
  int hp = pObject->GetHitpoints();
  if ( (rand() % 100) < 63 )
  {
    // convert this into weapon 
    // with damage property
    pObject->SetHitpoints(hp-1); 
    ostringstream s;
    s << GetName() << " hits!\n";
    game->GetRenderer() << s.str();
  }
  else
  {
    ostringstream s;
    s << GetName() << " misses!\n";
    game->GetRenderer() << s.str();
  }
}
////////////////////////////////////////////////////////////////////////////////
void 
Player::PrintSummary()
{

  game->GetRenderer() << "Name:" << GetName() << "\n";
  game->GetRenderer() << "Race: " <<  GetRace() << "\n";
  game->GetRenderer() << "Class: " << GetClass() << "\n";
  game->GetRenderer() << "age: " << GetAge() << "\n";
  game->GetRenderer() << "gender: " << GetGender() << "\n";
  game->GetRenderer() << "experience: " << GetExperience() << "\n";
}
////////////////////////////////////////////////////////////////////////////////
void
Player::AskInfo( Player & p)
{
  ifstream f("playerdata.txt");
  while ( !f.eof()  )
  {
    string line;
    f >> line;
    if ( line == "#player")
    {
      int iTmp;
      string strTmp;
      char g;
      f >> strTmp; p.SetName(strTmp); 
      f >> strTmp; p.SetRace(strTmp);
      f >> iTmp; p.SetClass((Class)iTmp);
      f >> iTmp; p.SetAge(iTmp);
      f >> g; p.SetGender( (g == 'm' ? Male : Female) );
      f >> iTmp; p.SetExperience(iTmp);
      
    }

    /*
  cout << "\nPlease enter your details:\n\n";
  cout << "Your name:"; cin >> p.name;
  cout << "Race: "; cin >> p.race;
  int c;
  cout << "Class: ";cin >> c; p.myClass = (Class)c;
  cout << "age: "; cin >> p.age;
  char g;
  cout << "gender: "; cin >> g; p.gender = g == 'm' ? Male : Female;
  p.experience = 0;*/
  }
}
////////////////////////////////////////////////////////////////////////////////
void 
Player::SetGame( Game * game )
{ 
  this->game = game;
}
////////////////////////////////////////////////////////////////////////////////
void 
Player::UsePotion() {
	if(potions.empty()) {
		game->GetRenderer() << "You don't have any potions left\n";
	} else {
		HealthPotion *potion = potions.top();
		if(potion != NULL) {
			
			if(GetHitpoints() < 3) {
		
			
				auto heal = [] (GameObject* object, int maxHP, int amount) {
					int hitpoints = min(maxHP, object->GetHitpoints() + amount);
					object->SetHitpoints(hitpoints);
				};
	
				heal(this, 3, potion->GetHealAmount());
				
				game->GetRenderer() << "You have been healed to " << GetHitpoints() << " hitpoints\n";
			} else {
				game->GetRenderer() << "You are currently at full HP. Can't use potion(s)\n";
			}
		}
	}
}