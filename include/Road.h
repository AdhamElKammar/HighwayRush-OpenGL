#ifndef HIGHWAY_RUSH_ROAD_H
#define HIGHWAY_RUSH_ROAD_H

class Road {
public:
    void draw() const;

private:
    void drawRoadSurface() const;
    void drawLaneMarkings() const;
    void drawRoadsideScenery() const;
};

#endif

