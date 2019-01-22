


//Project includes
#include "GridObject.h"

class Boulder : public GridObject
{
public:
	Boulder();

	bool AttemptFall(sf::Vector2i _direction, sf::Time _frametime);
	bool AttemptPush(sf::Vector2i _direction);
	bool AttemptSlide(sf::Vector2i _direction);
	void Update(sf::Time _frameTime);


private:

	bool m_sliding;
	bool m_falling;
	float m_timer;
	float m_fallDelay;
	float m_slideDelay;
	float m_slideTimer;
};