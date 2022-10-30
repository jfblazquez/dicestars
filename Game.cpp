#include "Game.h"

void Game::Init(int nplayers) {
    for (int i = 0; i < nplayers; i++) {
        players.push_back(std::make_shared<PlayerSheet>());
    }
    dice.Init();
    vectorDie vDice = dice.GetDice();
    bag.AddToBag(vDice);
    reserve.dice.clear();
    playerShift = 0;
}

bool Game::TakeFromBag(int n) {
    vectorDie newDice;
    bool ret = bag.TakeFromBag(n, newDice);
    if (ret) {
        reserve.dice.insert(reserve.dice.end(), newDice.begin(), newDice.end());
    }
    return ret;
}

bool Game::PlayNumber(int n) {
    return false;
}

bool Game::PlayColor(Colours color) {
    return false;
}

bool Game::PlayStars(int n, bool restToBag) {
    return false;
}

void Game::PrintBag() {
    std::cout << "Bag: ";
    for (const Die& it : bag.dice) {
        std::cout << it.Text();
    }
    std::cout << '\n';
}

void Game::PrintReserve() {
    std::cout << "Reserve: ";
    for (const Die& it : reserve.dice) {
        std::cout << it.Text();
    }
    std::cout << '\n';
}

void Game::PrintDiscard() {
    std::cout << "Discard: ";
    for (const Die& it : discard.dice) {
        std::cout << it.Text();
    }
    std::cout << '\n';
}

int Game::nextPlayer() {
    playerShift = (playerShift + 1) % players.size();
    return playerShift;
}

PlayerSheet& Game::currentPlayer() {
    return *players[playerShift].get();
}

Actions Game::ActionsForCurrentPlayer() {
    Actions actionsFromReserve = reserve.GetActions();
    Actions ret;
    for (auto& action : actionsFromReserve.actions) {
        if (currentPlayer().CanDoAction(action)) {
            ret.actions.push_back(action);
        }
    }
    return ret;
}

bool Game::DoAction(Action& action)
{
    bool ret = currentPlayer().DoAction(action);
    reserve.TakeFromReserve(action.dice);
    discard.Add(action.dice);
    if (bag.dice.empty() || action.actionType == ActionType::STARS) {
        bag.AddToBag(discard.dice);
        discard.dice.clear();
        if (action.onEndReserveToBag) {
            bag.AddToBag(reserve.dice);
            reserve.dice.clear();
        }
    }
    return ret;
}
