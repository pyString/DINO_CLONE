#include <raylib.h>
#include <iostream>
#include <stdio.h>


class Obstacles
{
	int indexVal = GetRandomValue(0, 2);
	int spd = 1;
	Vector2 pos = { 250.0f, 90.0f };

};

class Player
{
public:

	Vector2 pos = { 25.0f, 90.0f };
	Rectangle rect = { 0, 0, 16, 24 };
	bool jmpActive;
	int aniClock = 0;
	int frameW = 16;
	int crntFrame = 0;
	int grvt = 0;

	void Update() //TODO: colocar a função de animar, fazer o personagem pular
	{
		grvt++;
		aniClock++;
		if (rect.x >= frameW * 2) { rect.x = 0; }
		if (aniClock == 30)
		{
			aniClock = 0;
			rect.x += frameW;
		}
		///Fysics and shit 
		pos.y += grvt;
		if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE))
		{
			grvt = -15;
		}
		if (pos.y >= 90)
		{
			pos.y = 90;
		}
		
	}

	void Draw(Texture2D dino) //TODO: colocar a função de animar
	{
		DrawTextureRec(dino, rect, pos, WHITE);
	}
};

Player player;

int main()
{
	///Definindo as variáveis
	const int SCRN_W = 720;
	const int SCRN_H = 480;
	enum GameScreen
	{
		TITLE,
		INSTRUCTIONS,
		GAME,
		GAMEOVER
	};
	int floorspd = 1;
	int clock = 0;

	///usando a poha da variável
	InitWindow(SCRN_W, SCRN_H, "DINO");


	Image floor = LoadImage("floor.png");
	Texture2D floortx = LoadTextureFromImage(floor);
	UnloadImage(floor);
	Vector2 floorVec = {0, 0};
	Rectangle floorRect = { 0, 0, 240, 160 };
	Texture2D dino = LoadTexture("DinoFrames2.png");
	Camera2D cam = { 0 };
	cam.zoom = 3.0f;


	GameScreen gmScrn = TITLE;

	SetTargetFPS(60);
	while (!WindowShouldClose()) ///Game Loop
	{
		///Update
		if (IsKeyPressed(KEY_ESCAPE)) //Press escape to close
		{
			WindowShouldClose();
		}
		switch (gmScrn)
		{
		case TITLE:
			if (IsKeyPressed(KEY_ENTER))
			{
				gmScrn = GAME;
			}
			break;

		case INSTRUCTIONS:

			break;

		case GAME:
			clock++;
			floorRect.x += floorspd;
			if (floorRect.x >= floorRect.width) { floorRect.x = 0; }
			if (clock == 600)
			{
				clock = 0;
				floorspd++;
				std::cout << "+1!\n";
			}
			player.Update();
			


			break;

		case GAMEOVER:
			break;
		}

		///Render
		BeginDrawing();

		ClearBackground(RAYWHITE);
		switch (gmScrn)
		{
		case TITLE:
			DrawText("DINO CLONE", 120, 190, 80, DARKGRAY);
			DrawText("press ENTER to play", 250, 380, 20, DARKGRAY);
			DrawText("press ESCAPE to exit at any moment", 180, 40, 20, DARKGRAY);
			break;

		case INSTRUCTIONS:

			break;

		case GAME:
			BeginMode2D(cam);

			DrawTextureRec(floortx, floorRect, floorVec, WHITE);
			player.Draw(dino);

			EndMode2D();
			break;

		case GAMEOVER:
			break;
		}

		EndDrawing();
	}

	UnloadTexture(floortx);
	UnloadTexture(dino);

	CloseWindow();

	return 0;
}