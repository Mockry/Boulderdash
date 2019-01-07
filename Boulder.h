


//Project includes
#include "GridObject.h"

class Boulder : public GridObject
{
public:
	Boulder();

	bool AttemptFall(sf::Vector2i _direction);
	void Update(sf::Time _frameTime);

private:

};