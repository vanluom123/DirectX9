#ifndef PLAYER_DATA_H
#define PLAYER_DATA_H

class GamePlayer;
class GameState;

class PlayerData
{
private:
	GamePlayer* gamePlayer;
	GameState* gameState;

public:
	PlayerData();
	~PlayerData();

	GameState* GetGameState() const;
	void SetGameState(GameState* val);

	GamePlayer* GetGamePlayer() const;
	void SetGamePlayer(GamePlayer* val);
};
#endif // PLAYER_DATA_H


