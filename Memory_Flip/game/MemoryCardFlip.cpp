#include "Definitions.h"
#include "MemoryCardFlip.h"
#include "Card.h"
#include <iostream>

MemoryCardFlip::MemoryCardFlip()
{

}

void MemoryCardFlip::Start()
{
    for (int i = 1; i <= _gridSize * _gridSize / 2; i++)
    {
        _numbers.push_back(i);
        _numbers.push_back(i);
    }

    int canvasHeight = WINDOW_HEIGHT - UI_SIZE;
    std::vector tempNumbers = _numbers;

    for (int r = 0; r < _gridSize; r++)
    {
        for (int c = 0; c < _gridSize; c++)
        {
            int totalGap = GAP * (_gridSize + 1);
            int widthSpaceForTiles = WINDOW_WIDTH - totalGap;
            int HeightSpaceForTiles = canvasHeight - totalGap;
            int w = widthSpaceForTiles / _gridSize;
            int h = HeightSpaceForTiles / _gridSize;

            int x = GAP + c * (GAP + w);
            int y = GAP + r * (GAP + h);

            Rectangle cardRect = { x,y,w,h };


            int index = rand() % tempNumbers.size();
            int cardValue = tempNumbers[index];
            tempNumbers.erase(tempNumbers.begin() + index);

            Color cardColor;
            switch (cardValue)
            {
            //case 1: { cardColor = RED; break; }
            //case 2: { cardColor = YELLOW; break; }
            //case 3: { cardColor = GREEN; break; }
            //case 4: { cardColor = BLUE; break; }
            //case 5: { cardColor = PURPLE; break; }
            //case 6: { cardColor = ORANGE; break; }
            //case 7: { cardColor = PINK; break; }
            //case 8: { cardColor = BROWN; break; }
            default: { cardColor = DARKBLUE; break; }
            }

            _cards.push_back(Card(cardValue, cardRect, cardColor));
        }
    }
}

void MemoryCardFlip::Main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Raylib App");
    SetTargetFPS(60);

    Start();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        UpdateAll();
        RenderAll();

        EndDrawing();
    }

    CloseWindow();
}

void MemoryCardFlip::CheckIfGameOver()
{
    for (auto& card : _cards) { if (card.GetState() != CardState::matched) { return; } }
    _gameState = GameState::win;
}

void MemoryCardFlip::UpdateAll()
{
    ////////////////////////////////////   CHEATS   /////////////////////////////////////////////
    if (IsKeyPressed(KEY_W)) { for (auto& card : _cards) { card.SetState(CardState::matched); } }
    if (IsKeyPressed(KEY_H)) 
    { 
        _gameState = GameState::hint;
        _hints--;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////

    if (_gameState == GameState::win) { return; }
    else if (_gameState == GameState::hint)
    {
        _hintTimer -= GetFrameTime();
        if (_hintTimer >= 0) // hint timer still going
        {
            return;
        }
        else // hint timer is up
        {
            _hintTimer = HINT_TIMER;
            _gameState = GameState::play;
        }
    }

    CheckIfGameOver();

    if (_flipBackTimer > 0.f)
    {
        _flipBackTimer -= GetFrameTime() / TIMER_DURATION;

        if (_flipBackTimer <= 0.f)
        {
            _firstPick->SetState(CardState::hidden);
            _secondPick->SetState(CardState::hidden);
            _firstPick = nullptr;
            _secondPick = nullptr;
        }
        return;
    }

    for (int i = 0; i < _cards.size(); i++)
    {
        if (_cards[i].GetState() == CardState::hidden && _cards[i].Update())
        {
            if (_firstPick == nullptr) { _firstPick = &_cards[i]; }
            else 
            { 
                _secondPick = &_cards[i]; 
                _attemps++;
            }
        }
    }

    if (_firstPick != nullptr && _secondPick != nullptr)
    {
        if (_firstPick->GetValue() == _secondPick->GetValue())
        {
            _firstPick->SetState(CardState::matched);
            _secondPick->SetState(CardState::matched);
            _firstPick = nullptr;
            _secondPick = nullptr;
        }
        else
        {
            _flipBackTimer = 1.0f;
        }
    }
}

void MemoryCardFlip::RenderAll()
{
    std::string hintsText = "Hints remaining: " + std::to_string(_hints);
    int hintsTextWidth = MeasureText(hintsText.c_str(), UI_SIZE * 0.8);
    DrawText(hintsText.c_str(), WINDOW_WIDTH - GAP - hintsTextWidth, WINDOW_HEIGHT - UI_SIZE + (UI_SIZE * 0.1), UI_SIZE * 0.8, GOLD);

    std::string attemptsText = "Attemps: " + std::to_string(_attemps);
    DrawText(attemptsText.c_str(), GAP, WINDOW_HEIGHT - UI_SIZE + (UI_SIZE * 0.1), UI_SIZE * 0.8, GOLD);

    if (_flipBackTimer > 0.f) { DrawRectangle(0, 0, WINDOW_WIDTH * _flipBackTimer, GAP, RED); }

    if (_gameState == GameState::hint)
    {
        for (auto& card : _cards) { card.DisplayHint(); }

        std::string hintsTimeDisplay = std::to_string((int)_hintTimer);
        hintsTextWidth = 1;

        hintsTextWidth = MeasureText(hintsTimeDisplay.c_str(), HINT_FONT);
        DrawText(hintsTimeDisplay.c_str(), (WINDOW_WIDTH - hintsTextWidth) / 2, (WINDOW_HEIGHT - HINT_FONT) / 2, HINT_FONT, Color{255,255,255,150});
    }
    else { for (auto& card : _cards) { card.Render(); } }
    
    if (_gameState == GameState::win)
    {
        std::string winText = "You Win!";
        int winFont = UI_FONT;

        int winTextWidth = 1;
        while (winTextWidth < WINDOW_WIDTH * 0.9)
        {
            winFont++;
            winTextWidth = MeasureText(winText.c_str(), winFont);
        }
        DrawText(winText.c_str(), (WINDOW_WIDTH - winTextWidth) / 2, (WINDOW_HEIGHT - winFont) / 2, winFont, WHITE);
    }
}