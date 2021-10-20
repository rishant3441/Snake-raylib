#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Food.h"
#include "Segment.h"
#include "raylib.h"


// Global Variables
std::vector<Segment> playerO(4);
std::vector<Segment> &player = playerO;
std::vector<Rectangle> segments;
bool shouldDraw = true;
int gameState = 0;
// 0 = game play
// 1 = end
Rectangle foodO;
Food food;
int score = 0;

void InitializeWindow()
{
    InitWindow(570, 570, "Snake");
    SetTargetFPS(10);

    player[0].isHead = true;
    player[1].y = player[0].y + 30;
    player[2].y = player[1].y + 30;
    player[3].y = player[2].y + 30;

    for (int i = 0; i != player.size(); i++)
    {
        segments.push_back((Rectangle){player[i].x, player[i].y, 30, 30});
    }
    foodO = (Rectangle){food.x, food.y, 30, 30};
    gameState = 0;
}

void playerMove(int i)
{
    switch (player[i].direction)
    {
    case 'N':
        if (player[i + 2].y == player[i].y - 30)
        {
            player[i].direction = player[i].tmpDirection;
            playerMove(i);
            break;
        }
        if (player[i].y <= 0)
        {
            gameState = 1;
            break;
        }

        player[i].y -= 30;
        player[i].tmpDirection = player[i].direction;
        break;
    case 'S':
        if (player[i + 2].y == player[i].y + 30)
        {
            player[i].direction = player[i].tmpDirection;
            playerMove(i);
            break;
        }
        if (player[i].y >= 540)
        {
            gameState = 1;
            break;
        }

        player[i].y += 30;
        player[i].tmpDirection = player[i].direction;
        break;
    case 'E':
        if (player[i + 2].x == player[i].x + 30)
        {
            player[i].direction = player[i].tmpDirection;
            playerMove(i);
            break;
        }

        if (player[i].x >= 540)
        {
            gameState = 1;
            break;
        }

        player[i].x += 30;
        player[i].tmpDirection = player[i].direction;
        break;
    case 'W':
        if (player[i + 2].x == player[i].x - 30)
        {
            player[i].direction = player[i].tmpDirection;
            playerMove(i);
            break;
        }
        if (player[i].x <= 0)
        {
            gameState = 1;
            break;
        }

        player[i].x -= 30;
        player[i].tmpDirection = player[i].direction;
        break;
    }
    for (int j = 0; j != segments.size(); j++)
    {
        if (CheckCollisionRecs(segments[j], foodO))
        {
            player.push_back(Segment());
            player[player.size()].prev = player.size() - 1;
            food.x = (rand() % 19) * 30;
            food.y = (rand() % 19) * 30;
            player[player.size() - 1].isVisible = false;
            player[player.size() - 1].x = 600;
            player[player.size() - 1].y = 600;
            score++;
        }
    }
}

int main()
{
    InitializeWindow();
    while (!WindowShouldClose())
    {
        switch (gameState)
        {
        case 0:
            ClearBackground(BLACK);
            for (int i = 1; i <= player.size(); i++)
            {
                if (i != 0)
                    player[i].prev = i - 1;
            }

            player[0].moveHead();

            for (int j = player.size(); j != 0; j--)
            {
                player[j].x = player[player[j].prev].x;
                player[j].y = player[player[j].prev].y;
            }

            playerMove(0);
            for (int j = 0; j != player.size(); j++)
            {
                for (int l = 0; l != player.size(); l++)
                {
                    if (j != l && player[j].x == player[l].x && player[j].y == player[l].y)
                    {
                        gameState = 1;
                    }
                }
            }
            break;
        case 1:
            ClearBackground(BLACK);
            break;
        default:
            ClearBackground(BLACK);
            break;
        }

        BeginDrawing();
        switch (gameState)
        {
        case 0:
            for (int k = 0; k != player.size(); k++)
            {
                segments[k] = (Rectangle){player[k].x, player[k].y, 30, 30};
                if (player[k].isVisible)
                {
                    DrawRectangle(segments[k].x, segments[k].y, segments[k].width, segments[k].height, GREEN);
                }
                else
                {
                    player[k].isVisible = true;
                }
            }
            foodO = (Rectangle){food.x, food.y, 30, 30};
            DrawRectangle(foodO.x, foodO.y, foodO.width, foodO.height, RED);
            DrawText(TextFormat("Score: %d", score), 0, 0, 36, LIGHTGRAY);
            EndDrawing();
            break;
        case 1:
            DrawText("GameOver", 287, 287, 54, RED);
            EndDrawing();
            break;
        }
    }
    CloseWindow();
    return 0;
}
