#ifndef _ROUTE_
#define _ROUTE_
#include <kamek.hpp>
#include <game/KMP/Controller.hpp>





class RoutePoint {
    RoutePoint(); //806ecafc
    ~RoutePoint(); //806ecb00
    Vec3 position;
    u16 settings[2];
}; //0x10

class RouteSegment { //from point i to point i+1 except for last if cyclic where it's from n to 0
    RouteSegment(); //806efbf0
    ~RouteSegment(); //806efbf4
    float distance; //0
    float invertedDistance;
    Vec3 unitVec; //0x8 direction from A to B
}; //0x14

class RouteArc {
    RouteArc(); //806ed6c0
    ~RouteArc(); //806ed6c4
    Vec3 originPoint;
    Vec3 secondPoint; //(finalPoint - originPoint)/4 + originPoint
    Vec3 unknown_0x18[3];
}; //0x38

class Route {
    Route(u32 routeId, KMP::POTIHolder *route); //806ec9a4
    Route(u32 routeId, Vec3 *pointsArray, u32 pointCount, u32 isCurved, bool isNotCyclic); //806ec9a4 array of vectors
    virtual ~Route(); //806ecc40 vtable 808c76a8
    virtual float GetTotalDistance() const = 0; //0xC
    virtual RouteSegment *GetSegmentArray() const = 0; //0x10
    virtual RouteArc *GetArcArray() const = 0; //0x14
    virtual u32 GetPointsPerArc() const = 0; //0x18
    virtual float GetPercent() const = 0; //0x1c
    virtual float *GetPercentFromOriginArrays() const = 0; //0x20
    virtual void Update(); //0x24
    virtual void UpdateTotalDistance() = 0;

    void UpdatePoints(Vec3 *pointsArray, u32 pointCount); //806ecf88
    RoutePoint *GetPointById(u16 id); //806ed150
    void AddPoint(Vec3 *point); //806ed110

    u16 routeId; //0x4
    u16 maxPointCount; //0x6
    u16 curPointCount; //0x8
    bool isNotCyclic; //0xA
    u8 padding; //0xB
    RoutePoint *pointsArray; //0xC
    u8 unknown_0x10;
    u8 unknown_0x11[0x20 - 0x11];
    float unknown_0x20;
    u32 isCurved; //0x24
}; //0x28

class RouteStraight : public Route {
    RouteStraight(u32 routeId, KMP::POTIHolder *route); //806ef9b4
    RouteStraight(u32 routeId, Vec3 *pointsArray, u32 pointCount, u32 isCurved, bool isNotCyclic); //806efc34 unsure what r5 is
    ~RouteStraight() override; //806efd6c vtable 808c7768
    float GetTotalDistance() const override; //806f09c0
    RouteSegment *GetSegmentArray() const override; //806f09b8
    RouteArc *GetArcArray() const override; //806f09b0 returns NULL
    u32 GetPointsPerArc() const override; //806f09a8 returns 0
    float GetPercent() const override; //806f099c
    float *GetPercentFromOriginArrays() const override; //806f0994 returns NULL
    void Update() override; //806f0990
    void UpdateTotalDistance(); //806f098c

    u8 unknown_0x28[2];
    u16 segmentCount; //0x2A points - 1 if cyclic, else point count
    RouteSegment *segments; //0x2C
    float totalPointDistance; //0x30 adds distance btw each point
}; //0x34



class RouteCurved : public Route {
    RouteCurved(u32 routeId, KMP::POTIHolder *route); //806ed57c
    RouteCurved(u32 routeId, Vec3 *pointsArray, u32 pointCount, u32 isCurved, bool isNotCyclic); //806ed704 unsure what r5 is
    ~RouteCurved() override; //806ed828 vtable 808c7708
    float GetTotalDistance() const override; //806ef9ac
    RouteSegment *GetSegmentArray() const override; //806ef9a4 returns NULL
    RouteArc *GetArcArray() const override; //806ef99c
    u32 GetPointsPerArc() const override; //806ef994
    float GetPercent() const override; //806ef98c
    float *GetPercentFromOriginArrays() const override; //806ef984
    void Update() override; //806ed8bc
    void UpdateTotalDistance() override; //806ed960 when new point is added

    void Init(u32 r4); //806eda04
    Vec3 Calc(Vec3 &firstPoint, Vec3 &secondPoint, Vec3 &thirdPoint); //806ee4b8

    u8 unknown_0x28[2];
    u16 arcCount; //0x2A points - 1 if nonCyclic, else point count
    RouteArc *arcs; //0x2C
    u32 pointsPerArc; //0x30
    float percentPerArc; //0x34
    float *percentFromOriginArrays; //0x38 (pointsPerCurve+1) * segmentCount
    //each point has pointsPerCurve until the next point; this is an array of an array what percent of the curve each curve poinnt contributes to
    u32 totalCurvePoints; //0x3C
    float totalCurveDistance; //0x40
    u8 unknown_0x44;
    u8 padding[3];
}; //0x48

#endif