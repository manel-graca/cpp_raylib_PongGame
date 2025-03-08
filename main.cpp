#include <raylib.h>

#include <iostream>

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 194, 255};
Color Yellow = Color{243, 213, 91, 255};

const int maxScore = 3;
int playerScore = 0;
int cpuScore = 0;

class Ball
{
   public:
    float x, y;
    float speedX, speedY;
    float radius;
    Color color;

    void Draw() { DrawCircle(x, y, radius, color); }
    void Reset()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        speedX *= -1;
    }

    void Move()
    {
        if (y + radius > GetScreenHeight())
        {
            speedY *= -1;
        }
        else if (y - radius < 0)
        {
            speedY *= -1;
        }
    }
    void Update()
    {
        float deltaTime = GetFrameTime();

        x += speedX * deltaTime;
        y += speedY * deltaTime;

        Move();
        bool reset = false;

        if (x + radius >= GetScreenWidth())
        {
            cpuScore++;
            reset = true;
        }
        else if (x - radius <= 0)
        {
            playerScore++;
            reset = true;
        }
        if (reset) Reset();
    }
};

class Paddle
{
   public:
    float initY;
    float x;
    float y;
    float speedY;
    float height;
    float width;
    Color color;

    void Draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update()
    {
        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_W))
        {
            y -= speedY * deltaTime;
        }
        else if (IsKeyDown(KEY_S))
        {
            y += speedY * deltaTime;
        }
    }
};

class CpuPaddle : public Paddle
{
   public:
    void Update(int ball_y)
    {
        float deltaTime = GetFrameTime();

        if (y > ball_y)
        {
            y -= speedY * deltaTime;
        }
        else if (y < ball_y)
        {
            y += speedY * deltaTime;
        }
    }
};

Paddle player;
CpuPaddle cpu;

Ball ball;

int main(int, char **)
{
    std::cout << "Starting the game!\n";

    const int screenWidth = 1280;
    const int screenHeight = 800;

    const int targetFPS = 144;

    InitWindow(screenWidth, screenHeight, "Trumpong");
    SetTargetFPS(targetFPS);

    float paddleSpeed = 250;
    float paddleHeight = 120;
    float paddleWidth = 25;
    Color paddleColor = WHITE;
    float paddleY = (screenHeight / 2) - (paddleHeight / 2);

    player.initY = paddleY;
    player.x = 10;
    player.y = paddleY;
    player.speedY = paddleSpeed;
    player.height = paddleHeight;
    player.width = paddleWidth;
    player.color = paddleColor;

    cpu.initY = paddleY;
    cpu.x = screenWidth - 25 - 10;
    cpu.y = paddleY;
    cpu.speedY = paddleSpeed;
    cpu.height = paddleHeight;
    cpu.width = paddleWidth;
    cpu.color = paddleColor;

    float random = GetRandomValue(0, 1);

    float ballSpeed = random > 0.5 ? 500 : -500;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = ballSpeed;
    ball.speedY = ballSpeed;
    ball.radius = 15;
    ball.color = Yellow;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DarkGreen);
        DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, LightGreen);
        // Updating

        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speedX *= -1;
        }

        if (CheckCollisionCircleRec(
                Vector2{ball.x, ball.y}, ball.radius,
                Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speedX *= -1;
        }

        // Drawing

        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.Draw();

        player.Draw();
        cpu.Draw();

        DrawText(TextFormat("%i", cpuScore), screenWidth / 4 - 20, 20, 80,
                 WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20,
                 80, WHITE);

        DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}