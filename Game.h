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

    void Init(int nplayers);

    bool TakeFromBag(int n);

    bool PlayNumber(int n);

    bool PlayColor(Colours color);

    bool PlayStars(int n, bool restToBag);

    void PrintReserve();

    int nextPlayer();

    PlayerSheet& currentPlayer();

    Actions ActionsForCurrentPlayer();;

};