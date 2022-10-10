#pragma once
#include <vector>
#include "Bag.h"
#include "Reserve.h"
#include "Actions.h"
#include "Action.h"
#include "PlayerSheet.h"

struct Game {
    Bag bag;
    Reserve reserve;
    std::vector<PlayerSheet> players;
    int playerShift{};

    void Init(int nplayers) {
        players = std::vector<PlayerSheet>(nplayers, PlayerSheet());
        Die black{ Colours::BLACK,0 };
        Die purple{ Colours::PURPLE,0 };
        Die blue{ Colours::BLUE,0 };
        Die orange{ Colours::ORANGE,0 };
        for (int i = 0; i < 2; ++i) {
            bag.dice.push_back(black);
        }
        for (int i = 0; i < 3; ++i) {
            bag.dice.push_back(purple);
        }
        for (int i = 0; i < 4; ++i) {
            bag.dice.push_back(blue);
        }
        for (int i = 0; i < 4; ++i) {
            bag.dice.push_back(orange);
        }
        reserve.dice.clear();
        playerShift = 0;
        PlayerSheet& currentPlayer2 = players[playerShift];
        //currentPlayer = 
    }
    bool TakeFromBag(int n) {
        std::vector<Die> newDice;
        bool ret = bag.TakeFromBag(n, newDice);
        if (ret) {
            reserve.dice.insert(reserve.dice.end(), newDice.begin(), newDice.end());
        }
        return ret;
    }
    bool PlayNumber(int n) {
        return false;
    }
    bool PlayColor(Colours color) {
        return false;
    }
    bool PlayStars(int n, bool restToBag) {
        return false;
    }
    void PrintReserve() {
        std::cout << "Reserve: ";
        for (const auto& it : reserve.dice) {
            std::cout << it.Text();
        }
        std::cout << '\n';
    }
    int nextPlayer() {
        playerShift = (playerShift + 1) % players.size();
        return playerShift;
    }
    PlayerSheet& currentPlayer() {
        return players[playerShift];
    }

    Actions ActionsForCurrentPlayer() {
        Actions actionsFromReserve = reserve.GetActions();
        Actions ret;
        for (auto& action : actionsFromReserve.actions) {
            if (currentPlayer().CanDoAction(action)) {
                ret.actions.push_back(action);
            }
        }
        return ret;
    };

};