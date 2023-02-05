#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#undef Rectangle
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

struct Rectangle CreateRect(float x, float y, float width, float height)
{
    Rectangle temp;
    temp.x = x;
    temp.y = y;
    temp.width = width;
    temp.height = height;
    return temp;
}

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
        segments.push_back(CreateRect(player[i].x, player[i].y, 30.0f, 30.0f));
    }
    foodO = CreateRect(food.x, food.y, 30.0f, 30.0f);
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
            player[player.size() - 1].prev = player.size() - 2;
            food.x = (rand() % 19) * 30;
            food.y = (rand() % 19) * 30;
            player[player.size() - 1].isVisible = false;
            player[player.size() - 1].x = 600;
            player[player.size() - 1].y = 600;
            segments.push_back(CreateRect(player[player.size() - 1].x, player[player.size() - 1].y, 30.0f, 30.0f));
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
            for (int i = 1; i < player.size(); i++)
            {
                if (i != 0)
                    player[i].prev = i - 1;
            }

            player[0].moveHead();

            for (int j = player.size() - 1; j != 0; j--)
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
            for (int k = 0; k != segments.size(); k++)
            {
                segments[k] = CreateRect(player[k].x, player[k].y, 30.0f, 30.0f);
                if (player[k].isVisible)
                {
                    DrawRectangle(segments[k].x, segments[k].y, segments[k].width, segments[k].height, GREEN);
                }
                else
                {
                    player[k].isVisible = true;
                }
            }
            foodO = CreateRect(food.x, food.y, 30.0f, 30.0f);
            DrawRectangle(foodO.x, foodO.y, foodO.width, foodO.height, RED);
            DrawText(TextFormat("Score: %d", score), 0, 0, 36, LIGHTGRAY);
            EndDrawing();
            break;
        case 1:
            DrawText("Game Over", 150, 200, 54, RED);
            EndDrawing();
            break;
        }
    }
    CloseWindow();
    return 0;
}
