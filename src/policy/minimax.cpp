#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

#define INTMIN -2147483646
#define INTMAX 2147483647


/**
 * @brief  get a legal action with minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth){
  
  int value=minimax(state,depth,true);
  if(!state->legal_actions.size()){
    auto action=state->legal_actions.begin();
    for(auto it=state->legal_actions.begin();it!=state->legal_actions.end();it++){
      if(state->next_state(*it)->heuristic==value){
          action=it;
          break;
      }
    }
    return *action;
  }
  return *(state->legal_actions.begin());
}

int Minimax::minimax(State *state, int depth, bool maximizingPlayer){
  state->get_legal_actions();
  if(maximizingPlayer&&state->game_state==WIN)state->heuristic=INTMAX;return INTMAX;
  if(!maximizingPlayer&&state->game_state==WIN)state->heuristic=INTMIN;return INTMIN;
  if(depth==0||!state->legal_actions.size()){
    state->heuristic=state->evaluate();
    return state->heuristic;
  }
  if(maximizingPlayer){
    int value=INTMIN;
    for(auto it=state->legal_actions.begin();it!=state->legal_actions.end();it++){
      int comp=minimax(state->next_state(*it),depth-1,false);
      if(value<comp)value=comp;
    }
    state->heuristic=value;
    return value;
  }else{
    int value=INTMAX;
    for(auto it=state->legal_actions.begin();it!=state->legal_actions.end();it++){
      int comp=minimax(state->next_state(*it),depth-1,true);
      if(value>comp)value=comp;
    }
    state->heuristic=value;
    return value;
  }
  return state->evaluate();
}