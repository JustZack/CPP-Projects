#include "graph.h"
void Graph::setup()
{
	lines.clear();
	center = sf::Vector2f(windowSize.x / 2, windowSize.y / 2);
	intervalCount = sf::Vector2f(abs(graphDomain.xMin - graphDomain.xMax), abs(graphDomain.yMin - graphDomain.yMax));
	pixelInterval = sf::Vector2f(windowSize.x / intervalCount.x, windowSize.y / intervalCount.y);
	originPoint = sf::Vector2f((-graphDomain.xMin * pixelInterval.x), windowSize.y - (-graphDomain.yMin * pixelInterval.y));

	axisOriginLines[0] = sf::RectangleShape(sf::Vector2f(windowSize.x, lineSize));
	axisOriginLines[1] = sf::RectangleShape(sf::Vector2f(lineSize, windowSize.y));

	axisOriginLines[0].setOrigin(sf::Vector2f(originPoint.x, axisOriginLines[0].getSize().y / 2));
	axisOriginLines[1].setOrigin(sf::Vector2f(axisOriginLines[1].getSize().x / 2, originPoint.y));

	axisOriginLines[0].setFillColor(axisLineColor);
	axisOriginLines[1].setFillColor(axisLineColor);

	axisOriginLines[0].setPosition(originPoint);
	axisOriginLines[1].setPosition(originPoint);

	sf::RectangleShape HbaseShape;
	HbaseShape.setSize(sf::Vector2f(windowSize.x, lineSize));
	HbaseShape.setOrigin(axisOriginLines[0].getOrigin());
	HbaseShape.setFillColor(lineColor);

	sf::RectangleShape VbaseShape;
	VbaseShape.setSize(sf::Vector2f(lineSize, windowSize.y));
	VbaseShape.setOrigin(axisOriginLines[1].getOrigin());
	VbaseShape.setFillColor(lineColor);
	
	//Right of the y axis
	for (float i = 0; i <= graphDomain.xMax; i += lineInterval.x)
	{
		VbaseShape.setPosition(sf::Vector2f(originPoint.x + (i * pixelInterval.x), originPoint.y));
		lines.push_back(VbaseShape);
	}
	//Left of y axis
	for (float i = 0; i >= graphDomain.xMin; i -= lineInterval.x)
	{
		VbaseShape.setPosition(sf::Vector2f(originPoint.x + (i * pixelInterval.x), originPoint.y));
		lines.push_back(VbaseShape);
	}
	//Above the x axis
	for (float i = 0; i <= graphDomain.yMax; i += lineInterval.y)
	{
		HbaseShape.setPosition(sf::Vector2f(originPoint.x, originPoint.y - (i * pixelInterval.y)));
		lines.push_back(HbaseShape);
	}
	//Left of x axis
	for (float i = 0; i >= graphDomain.yMin; i -= lineInterval.y)
	{
		HbaseShape.setPosition(sf::Vector2f(originPoint.x, originPoint.y - (i * pixelInterval.y)));
		lines.push_back(HbaseShape);
	}
}

bool Graph::ensureRange(sf::RectangleShape shape)
{
	sf::Vector2f tmpPos = shape.getPosition();
	if (tmpPos.x >= 0 && tmpPos.y >= 0 && tmpPos.x <= windowSize.x && tmpPos.y <= windowSize.y)
		return true;
	else
		return false;
}

bool Graph::ensureRange(sf::CircleShape shape)
{
	sf::Vector2f tmpPos = shape.getPosition();
	if (tmpPos.x >= 0 && tmpPos.y >= 0 && tmpPos.x <= windowSize.x && tmpPos.y <= windowSize.y)
		return true;
	else
		return false;
}

Graph::Graph(Domain GraphDomain, sf::Vector2f WindowSize)
{
	graphDomain = GraphDomain;
	windowSize = WindowSize;
	lineInterval = sf::Vector2f(1, 1);
	setup();
}
Graph::~Graph()
{
	for (int i = 0; i < Points.size(); i++)
		delete Points[i];
	Points.clear();
}


void Graph::draw(sf::RenderWindow& rw)
{
	//Here we draw all of the lines on the graph
	for (int i = 0; i < lines.size(); i++)
		if(ensureRange(lines[i]))
			rw.draw(lines[i]);

	if (ensureRange(axisOriginLines[0]))
		rw.draw(axisOriginLines[0]);
	if (ensureRange(axisOriginLines[1]))
		rw.draw(axisOriginLines[1]);

	for (int i = 0; i < Points.size(); i++)
		if(ensureRange(Points[i]->getShape()))
			rw.draw(Points[i]->getShape());
}

void Graph::addPoint(PrimitivePoint *p)
{
	//Add the point to the graph
	p->adjust(pixelInterval, windowSize, originPoint);
	Points.push_back(p);
}

void Graph::setLineInterval(sf::Vector2f newLineInterval)
{
	if (newLineInterval.x <= 0 || newLineInterval.y <= 0)
		throw std::invalid_argument("One or more interval values were less than or equal to zero!");
	else
	{
		lineInterval = newLineInterval;
		setup();
	}
}

void Graph::setDomain(Domain newDomain)
{
	if (newDomain.xMin >= newDomain.xMax)
		throw std::invalid_argument("X min is greater than or equal to X max!");
	else if (newDomain.yMin >= newDomain.yMax)
		throw std::invalid_argument("Y min is greater than or equal to Y max!");
	else
	{
		graphDomain = newDomain;
		setup();
	}
}
