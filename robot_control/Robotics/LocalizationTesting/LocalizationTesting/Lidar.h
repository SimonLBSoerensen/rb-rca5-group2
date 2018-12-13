#pragma once

#include "Point.h"
#include "Edge.h"

class Lidar
{
public:
	Lidar();
	~Lidar();

	void newMeasurement();
	void addMeasurement(PolarPoint p);
	void addMeasurements(std::vector<PolarPoint> points);

    void setRadius(double val);

    void drawProcess();
	Line leastSquareFit(std::vector<PolarPoint> points);
	std::vector<Line> getLines();
	std::vector<Point> getCorners();

private:
	std::vector<PolarPoint> points;
    double maxRadius = 0;
};
