#include "Play.h"
#include "Declarations.h"

Rigidbody** rigidbody;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	rigidbody = new Rigidbody*[21];
	rigidbody[0] = new Ship();
	for (int i = 1; i < 21; i++)
	{
		rigidbody[i] = new Asteroid();
	}
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cBlack );
	Play::CentreAllSpriteOrigins();

	rigidbody[0]->simulate(elapsedTime);
	rigidbody[0]->draw();

	for (int i = 1; i < 21; i++)
	{
		if (rigidbody[0]->collision(rigidbody[i]))
		{
			if (scoreCount > highScore)highScore = scoreCount;
			scoreCount = 0;
		}
		rigidbody[i]->simulate(elapsedTime);
		rigidbody[i]->draw();
	}

	//count score
	if (j == 60)
	{
		scoreCount++;
		j = 0;
	}
	j++;

	//draw score
	std::string s = std::to_string(scoreCount);
	char const* pchar = s.c_str();
	std::string h = std::to_string(highScore);
	char const* hchar = h.c_str();
	Play::DrawDebugText({ 50,260 }, "Score:", Play::cCyan);
	Play::DrawDebugText({ 50,280 }, pchar, Play::cCyan);
	Play::DrawDebugText({ 50,310 }, "Highscore:", Play::cCyan);
	Play::DrawDebugText({ 50,330 }, hchar, Play::cCyan);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}
