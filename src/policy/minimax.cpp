#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief  get a legal action with minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move Minimax::get_move(State *state, int depth){
  if(!state->legal_actions.size())state->get_legal_actions();
  auto actions=state->legal_actions;
  Move move=actions[0];
  int value=-1e9;
  for(Move it:actions){
    State *nextState=state->next_state(it);
    int comp=minimax(nextState,depth-1,false);
    if(comp>value){
      move=it;
      value=comp;
    }
  }
  return move;
  /*if(state->player==0){
    int value=-1e9;
    for(Move it:actions){
     State *nextState=state->next_state(it);
      int comp=minimax(nextState,depth-1,false);
      if(comp>value){
        move=it;
        value=comp;
      }
    }
    return move;
  }else{
    int value=1e9;
    for(Move it:actions){
     State *nextState=state->next_state(it);
      int comp=minimax(nextState,depth-1,true);
      if(comp<value){
        move=it;
        value=comp;
      }
    }
    return move;
  }*/
}

int Minimax::minimax(State *state, int depth, bool maximizingPlayer){
  if(state->legal_actions.size()==0)state->get_legal_actions();
  if(state->game_state==WIN&&maximizingPlayer)return 1e9;
  if(state->game_state==WIN&&!maximizingPlayer)return -1e9;
  if((depth==0||!state->legal_actions.size())&&!maximizingPlayer){
    return state->evaluate();
  }
  if((depth==0||!state->legal_actions.size())&&maximizingPlayer){
    return state->evaluate2();
  }
  if(maximizingPlayer){
    int value=-1e9;
    auto actions=state->legal_actions;
    for(auto &it:actions){
      int comp=minimax(state->next_state(it),depth-1,false);
      if(comp>value)value=comp;
    }
    return value;
  }else{
    int value=1e9;
    auto actions=state->legal_actions;
    for(auto &it:actions){
      int comp=minimax(state->next_state(it),depth-1,true);
      if(comp<value)value=comp;
    }
    return value;
  }
}