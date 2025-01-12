#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"


#define MAX_SNAKE_SIZE 100


typedef struct BodyPart {
    Rectangle rect;
    struct BodyPart *next;
} BodyPart;


BodyPart *initBodyPart(Rectangle rect)
{
    BodyPart *part = (BodyPart *)malloc(sizeof(BodyPart));
    part->rect = rect;
    part->next = NULL;
    return part;
}

typedef struct {
    BodyPart *head;
    BodyPart *tail;
} Snake;


Snake *initSnake(BodyPart *head)
{
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    snake->head = head;
    snake->tail = head;
    return snake;
}


void addHead(Snake *snake, BodyPart *part)
{
    BodyPart *current = snake->tail;
    while (current != NULL) {
        if (current->next == NULL) {
            current->next = part;
            break;
        }
        current = current->next;
    }
    snake->head = part;
}


void addTail(Snake *snake, BodyPart *part)
{
    part->next = snake->tail;
    snake->tail = part;
}

void removeTail(Snake *snake)
{
    BodyPart *temp = snake->tail;
    snake->tail = snake->tail->next;
    free(temp);
}


void freeSnake(Snake *snake)
{
    BodyPart *current = snake->tail;
    while (current != NULL) {
        BodyPart *temp = current;
        current = current->next;
        free(temp);
    }
    free(snake);
}


bool HasSnakeCollided(Snake *snake)
{
    BodyPart *head = snake->head;
    BodyPart *current = snake->tail;
       
    while (current->next != NULL) {
        if (head->rect.x == current->rect.x && head->rect.y == current->rect.y) {
            return true;
        }

        current = current->next;
    }

    return false;
}


bool IsFoodInSnake(Snake *snake, Rectangle food)
{
    BodyPart *current = snake->tail;
    while (current != NULL) {
        if (CheckCollisionRecs(current->rect, food))
            return true;
        current = current->next;
    }
    return false;
}


bool IsSnakeBeyond(Snake *snake, int screenWidth, int screenHeight)
{
    BodyPart *head = snake->head;
    
    if (head->rect.x > screenWidth || head->rect.x < 0)
        return true;
    if (head->rect.y > screenHeight || head->rect.y < 0)
        return true;
    return false;
}


int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Snake");

    const int rectSize = 25;

    Rectangle headRect = {
        screenWidth / 2.0f - rectSize,
        screenHeight / 2.0f - rectSize,
        rectSize,
        rectSize
    };

    Rectangle foodRect = {
        GetRandomValue(0, screenWidth / rectSize - 1) * rectSize,
        GetRandomValue(0, screenHeight / rectSize - 1) * rectSize,
        rectSize,
        rectSize,
    };

    BodyPart *head = initBodyPart(headRect);
    Snake *snake = initSnake(head);

    float step = (float) rectSize;
    float interval = 0.2f;
    float timer = 0.0f; 

    SetTargetFPS(60);

    int currentKey = KEY_D;
    int previousKey = currentKey;

    int score = 0;
    bool gameOver = false;
    bool win = false;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        timer += deltaTime;
        
        switch (GetKeyPressed()) {
            case KEY_W:
                if (currentKey != KEY_S) {
                    previousKey = currentKey;
                    currentKey = KEY_W;
                }
                break;
            case KEY_S:
                if (currentKey != KEY_W) {
                    previousKey = currentKey;
                    currentKey = KEY_S;
                }
                break;
            case KEY_A:
                if (currentKey != KEY_D) {
                    previousKey = currentKey;
                    currentKey = KEY_A;
                }
                break;
            case KEY_D:
                if (currentKey != KEY_A) {
                    previousKey = currentKey;
                    currentKey = KEY_D;
                }
                break; 
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (gameOver && !win) {
            DrawText("GAME OVER!", screenWidth / 2 - MeasureText("GAME OVER!", 40) / 2, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press R to Restart", screenWidth / 2 - MeasureText("Press R to Restart", 20) / 2, screenHeight / 2 + 30, 20, GRAY);

            if (IsKeyPressed(KEY_R)) {
                gameOver = false;

                foodRect.x = GetRandomValue(0, screenWidth / rectSize - 1) * rectSize;
                foodRect.y = GetRandomValue(0, screenHeight / rectSize - 1) * rectSize;

                headRect.x = screenWidth / 2.0f - rectSize;
                headRect.y = screenHeight / 2.0f - rectSize;

                head = initBodyPart(headRect);
                snake = initSnake(head);

                currentKey = KEY_D;
                score = 0;
            }
        } else if (gameOver && win) {
            DrawText("YOU WON!", screenWidth / 2 - MeasureText("YOU WIN!", 40) / 2, screenHeight / 2 - 20, 40, WHITE);
            DrawText("Press R to Restart", screenWidth / 2 - MeasureText("Press R to Restart", 20) / 2, screenHeight / 2 + 30, 20, GRAY);

            if (IsKeyPressed(KEY_R)) {
                gameOver = false;
                win = false;

                foodRect.x = GetRandomValue(0, screenWidth / rectSize - 1) * rectSize;
                foodRect.y = GetRandomValue(0, screenHeight / rectSize - 1) * rectSize;

                headRect.x = screenWidth / 2.0f - rectSize;
                headRect.y = screenHeight / 2.0f - rectSize;

                head = initBodyPart(headRect);
                snake = initSnake(head);

                currentKey = KEY_D;
                score = 0;
            }

        } else if (!gameOver) {
            BodyPart *current = snake->tail;
            
            while (current != NULL) {
                DrawRectangleRec(current->rect, GREEN);
                current = current->next;
            }
                
            DrawRectangleRec(foodRect, RED);

            DrawText("Score", 10, 10, 20, GRAY);

            char scoreChar[MAX_SNAKE_SIZE];

            sprintf(scoreChar, "%d", score);

            DrawText(scoreChar, 10, 35, 30, WHITE);

            if ((timer >= interval || currentKey != previousKey) && !gameOver) {
                previousKey = currentKey;

                if (currentKey == KEY_W) headRect.y -= step;
                if (currentKey == KEY_S) headRect.y += step;
                if (currentKey == KEY_A) headRect.x -= step;
                if (currentKey == KEY_D) headRect.x += step;

                BodyPart *newPart = initBodyPart(headRect);
                addHead(snake, newPart);
                
                if (CheckCollisionRecs(headRect, foodRect)) {
                    foodRect.x = GetRandomValue(0, screenWidth / rectSize - 1) * rectSize;
                    foodRect.y = GetRandomValue(0, screenHeight / rectSize - 1) * rectSize;

                    while (IsFoodInSnake(snake, foodRect)) {
                        printf("Food IN snake\n");
                        foodRect.x = GetRandomValue(0, screenWidth / rectSize - 1) * rectSize;
                        foodRect.y = GetRandomValue(0, screenHeight / rectSize - 1) * rectSize;
                    }

                    score++;

                    if (score == MAX_SNAKE_SIZE) {
                        gameOver = true;
                        win = true;
                    }
                } else {
                    removeTail(snake);
                }                

                timer = 0.0f;
            }

            if (HasSnakeCollided(snake)) {
                gameOver = true;
            }

            if (IsSnakeBeyond(snake, screenWidth, screenHeight)) {
                gameOver = true;
            } 
       }

        EndDrawing();
    }

    freeSnake(snake);
    CloseWindow();

    return 0;
}
