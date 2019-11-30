#include "IGameObject.h"

vec2 IGameObject::Position()
{
	return posistion;
}

void IGameObject::Position(vec2 pos)
{
	//cout << "NewPos: " <<to_string(pos(0)) << ", " << to_string(pos(1)) << endl;
	posistion = pos;
}
