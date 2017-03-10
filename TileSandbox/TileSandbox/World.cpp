#include "World.h"
#include <iostream>
#include <limits>

//Simple helper method to run the input loop
static void doInput(World * world)
{
	world->input();
}

void World::init(int Width, int Height)
{
	gridWidth = Width; gridHeight = Height;
	windowWidth = rw.getSize().x; windowHeight = rw.getSize().y;	

	MAX_SCALE = ((rw.getSize().x + rw.getSize().y) / 2) / 4.0;
	
	if(MAX_SCALE == -1)
		MAX_SCALE = std::numeric_limits<int>::max();
	if (MIN_SCALE == -1)
		MIN_SCALE = 0;

	for (int i = 0; i < gridWidth; i++) {
		std::vector<Tile> temp;
		for (int j = 0; j < gridHeight; j++)
			temp.push_back(Tile(i, j, (PrimaryState)((i + j) % 2)));
		tiles.push_back(temp);
	}

	frameRateTimer.setInterval(1/5.f);

	inputThread = std::thread(doInput, this);
	start();
}

World::World(int Width, int Height, const sf::RenderWindow &w) : rw(w)
{
	init(Width, Height);
}

World::World(int Width, int Height, float Scale, const sf::RenderWindow &w) : rw(w)
{
	scale = Scale;

	init(Width, Height);
}

void World::update()
{
	currentFrameTime = frameRateTimer.getCurrentFrameTime();
	for (int i = 0;i < eventQueue.EVENT_COUNT;i++)
	{
		eTemp = eventQueue.next();
		switch (eTemp.type)
		{
		case ZOOM_IN:
			scale -= ZOOM_AMOUNT * currentFrameTime;
			break;
		case ZOOM_OUT:
			scale += ZOOM_AMOUNT * currentFrameTime;
			break;
		case MOVE_UP:
			cameraY -= MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_UP_LEFT:
			cameraY -= MOVE_AMOUNT * currentFrameTime;
			cameraX -= MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_UP_RIGHT:
			cameraY -= MOVE_AMOUNT * currentFrameTime;
			cameraX += MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_DOWN:
			cameraY += MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_DOWN_LEFT:
			cameraY += MOVE_AMOUNT * currentFrameTime;
			cameraX -= MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_DOWN_RIGHT:
			cameraY += MOVE_AMOUNT * currentFrameTime;
			cameraX += MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_LEFT:
			cameraX -= MOVE_AMOUNT * currentFrameTime;
			break;
		case MOVE_RIGHT:
			cameraX += MOVE_AMOUNT * currentFrameTime;
			break;
		case CLICK:
			break;
		case MOUSE_ENTER:
			try { tiles.at(eTemp.coordX).at(eTemp.coordY).hovering(true); }
			catch (...) {}
			break;
		case MOUSE_LEAVE:
			try { tiles.at(eTemp.coordX).at(eTemp.coordY).hovering(false); }
			catch (...) {}
			break;
		case HOVER:
			break;
		case PLACE:
			try { tiles.at(eTemp.coordX).at(eTemp.coordY).setPrimaryState(eTemp.pState); }
			catch (...) {}
			break;
		case NONE:
			break;
		}
	}
}

void World::input()
{
	//TODO: How mant events do we want to take in every second, or time unit for that matter
	while (runInput)
	{
		if (goStart)
		{
			//Camera movement MOVE
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))		eventQueue.add(eInfo(eType::MOVE_UP_RIGHT));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	eventQueue.add(eInfo(eType::MOVE_UP_LEFT));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	eventQueue.add(eInfo(eType::MOVE_DOWN_RIGHT));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))	eventQueue.add(eInfo(eType::MOVE_DOWN_LEFT));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))														eventQueue.add(eInfo(eType::MOVE_UP));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))													eventQueue.add(eInfo(eType::MOVE_DOWN));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))													eventQueue.add(eInfo(eType::MOVE_LEFT));
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))													eventQueue.add(eInfo(eType::MOVE_RIGHT));

			//Scaling ZOOM
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
			{
				if (scale > MIN_SCALE)										eventQueue.add(eInfo(eType::ZOOM_IN));
				else if (scale < MIN_SCALE)	scale = MIN_SCALE;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
			{
				if (scale < MAX_SCALE)										eventQueue.add(eInfo(eType::ZOOM_OUT));
				else if (scale > MAX_SCALE) scale = MAX_SCALE;
			}

			//Get the mouse's position according to the grid
			//Mouse action CLICK
			int mouseI = (int)floor((sf::Mouse::getPosition().x - (rw.getPosition().x + 8) + cameraX) / scale);
			int mouseJ = (int)floor((sf::Mouse::getPosition().y - (rw.getPosition().y + 31) + cameraY) / scale);
			if (mouseI >= 0 && mouseI < tiles.size() && mouseJ >= 0 && mouseJ < tiles.at(0).size())
			{
				//Determine if a tile is being hovered over
				if (tiles.at(mouseI).at(mouseJ).isHovering())
				{
					//Tile is being heovered over, and has been in a previous frame
				}
				else if ((mouseI != hoverI || mouseJ != hoverJ) && !tiles.at(mouseI).at(mouseJ).isHovering())
				{
					/*Tile is no longer being hovered over*/					eventQueue.add(eInfo(eType::MOUSE_LEAVE, hoverI, hoverJ));
					hoverI = mouseI; hoverJ = mouseJ;
				}
				else if(mouseI == hoverI && mouseJ == hoverJ && !tiles.at(mouseI).at(mouseJ).isHovering())
				{
					/*Tile is now being hovered over (first frame)*/			eventQueue.add(eInfo(eType::MOUSE_ENTER, mouseI, mouseJ));
				}
				//Mouse buttons
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))				eventQueue.add(eInfo(eType::PLACE, mouseI, mouseJ, (PrimaryState)2));
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))			eventQueue.add(eInfo(eType::PLACE, mouseI, mouseJ, (PrimaryState)1));
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))			eventQueue.add(eInfo(eType::PLACE, mouseI, mouseJ, (PrimaryState)0));
			}
			else
			{
				eventQueue.add(eInfo(eType::MOUSE_LEAVE, hoverI, hoverJ));
				hoverI = -1; hoverJ = -1;
			}
		}
		//update();
	}
}

void World::draw(sf::RenderWindow &w)
{
	update();
	for (int i = 0; i < gridWidth; i++)
	{
		for (int j = 0; j < gridHeight; j++)
		{
			data = tiles.at(i).at(j).set(scale, cameraX, cameraY);
			if ((hoverI != data.x || hoverJ != data.y) && data.hovered)
			{
				tiles.at(i).at(j).hovering(false);
				data = tiles.at(i).at(j).set(scale, cameraX, cameraY);
			}
			if (data.windowX < windowWidth && data.windowY < windowHeight && data.windowX > -data.width && data.windowY > -data.height)
				w.draw(tiles.at(i).at(j).shape());
		}
	}
	if (hoverI == -1 || hoverJ == -1 || hoverI > tiles.size() - 1 || hoverJ > tiles.at(0).size() - 1);
	else w.draw(tiles.at(hoverI).at(hoverJ).shape());
	w.draw(frameRateTimer.text());
	frameRateTimer.Increment();
}

void World::start()
{
	goStart = true;
}

void World::close()
{
	goStart = false;
	runInput = false;
	inputThread.join();
	//tiles.clear();
}