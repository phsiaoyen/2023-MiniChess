#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief  get a legal action with minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Submission::get_move(State *state, int depth){
  if(!state->legal_actions.size())state->get_legal_actions();
  auto actions=state->legal_actions;
  Move move=actions[0];
  int value=-1e9;
  for(Move it:actions){
    State *nextState=state->next_state(it);
    int comp=alphabeta(nextState,depth-1,-1e9,1e9,false);
    if(comp>value){
      move=it;
      value=comp;
    }
  }
  return move;
}

int Submission::alphabeta(State *state, int depth, int alpha, int beta, bool maximizingPlayer){
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
      int comp=alphabeta(state->next_state(it),depth-1,alpha,beta,false);
      if(comp>value)value=comp;
      if(value>alpha)alpha=value;
      if(alpha>=beta)break;
    }
    return value;
  }else{
    int value=1e9;
    auto actions=state->legal_actions;
    for(auto &it:actions){
      int comp=alphabeta(state->next_state(it),depth-1,alpha,beta,true);
      if(comp<value)value=comp;
      if(value<beta)beta=value;
      if(beta<=alpha)break;
    }
    return value;
  }
}