#pragma once
class pause
{
public: 
	pause(class game* pGame);
	~pause();

	void togglePause();
	virtual void runPause();

protected:
	class game* pGame;
};

