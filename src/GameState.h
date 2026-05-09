#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GameState {PLAYING, DIED};
GameState currentState = PLAYING;

extern GameState currentState;

#endif