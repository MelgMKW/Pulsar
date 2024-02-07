#ifndef _ROUTECONTROLLER_
#define _ROUTECONTROLLER_
#include <kamek.hpp>
#include <MarioKartWii/KMP/KMPManager.hpp>
#include <MarioKartWii/Route/RouteHolder.hpp>

class RouteController {
    RouteController(u16 routeId, float baseSpeed); //806ed160
    virtual ~RouteController(); //806ed53c vtable 808c7678
    virtual void SetParams() = 0; //0xC
    virtual void Init(u16 firstPoint, float startingPercent) = 0; //0x10
    virtual int Update() = 0; //0x14 0 middle of the route, 1 end of the route, 2 not moving
    virtual void UpdateSpeed(float speed) = 0; //0x18
    virtual void SetPercent(float percent) = 0; //0x1c 806c63a8
    virtual float GetSpeed() const = 0; //0x20
    virtual void vf_0x24() = 0; //0x24
    virtual void vf_0x28(u16& pointId, float& distance) = 0; //0x28
    virtual float GetDistanceToNextPoint() const = 0; //0x2c
    void GetNormal(u16 pointId, Vec3& dest) const; //806ed24c
    float GetTotalDistance() const; //806ed30c
    void GetBLIGHTIndex(u16 pointId, s32* dest) const; //806ed2b4
    bool IsAtRouteEnd() const; //806ef648

    u16 routeId; //0x4
    u16 pointCount; //0x6
    RoutePoint* pointsArray; //0x8
    bool isNotCylic; //0xC
    u8 padding[3];
    float baseSpeed; //0x10
    u8 unknown_0x14[4];
    Vec3 curPosition; //0x18
    Vec3 unitVector; //0x24 for direction
    float curSpeed; //0x30
    float unknown_speed_floats_0x34[2];
    float distancePerFrame; //0x3C speed / norm(toNextPoint)
    float percent; //0x40 starts at 0, gains curSpeed% every frame until it reaches 1, which is the end of the route
    u8 direction; // 0x44 0 opposite, 1 same as the route in the kmp
    u8 padding2;
    u16 curPointId; //0x46
    u16 nextpointId; //0x48
    bool isDisabled; //0x4a disables the route; whatever uses it stops moving
    u8 padding3;
}; //0x4C

class RouteStraightController : public RouteController {
    RouteStraightController(u16 routeId, float unknown); //806efdc4
    ~RouteStraightController() override; //806f094c vtable 808c7738
    void SetParams() override; //0xC 806efe50 sets pointsArray/point count...but already done by ctor
    void Init(u16 firstPoint, float startingPercent) override; //0x10 806efeac
    int Update() override; //0x14 806f0050
    void UpdateSpeed(float speed) override; //0x18 806efff4
    float GetSpeed() const override; //0x20 806f0944
    void vf_0x24() override; //0x24 806f02ec
    void vf_0x28(u16& pointId, float& distance) override; //0x28 806f041c
    float GetDistanceToNextPoint() const override; //0x2c 806f050c
    Vec3 toNextPoint; //0x4C
    RouteSegment* segmentArray; //0x58

}; //0x5c

class RouteCurvedController : public RouteController { //Uses a cubic bezier curve
    RouteCurvedController(); //806ee830
    ~RouteCurvedController() override; //806ef944 vtable 808c76d8 
    void SetParams() override; //0xC 806eead8
    void Init(u16 firstPoint, float startingPercent) override; //0x10 806ee924
    int Update() override; //0x14 806eebec
    void UpdateSpeed(float speed) override; //0x18 806eeb94
    float GetSpeed() const override; //0x20 806ef93c
    void vf_0x24() override; //0x24 806eeebc
    void vf_0x28(u16& pointId, float& distance) override; //0x28 806eefa0
    float GetDistanceToNextPoint() const override; //0x2c 806ef09c
    //if arg == 50%, calculates the total distance percentage from the start of the route to 50% of the curPointId's arc
    float GetTotalPercent(float percentOfCurrentArc); //806ef0d8 inlined, inverts percent if route goes wrong dir
    float GetTotalPercentNormalDir(float percentOfCurrentArc); //806ef0f8 

    void CalculateBezier(u16 curPointId, u16 nextPointId, Vec3& nextPos, Vec3& dir, float totalPercent); //806ef224
    Vec3 CalculateBezierCurve(const RouteArc& arc, float t); //806ef350 (Bezier(t))
    Vec3 CalculateBezierDir(const RouteArc& arc, float t); //806ef454 normalize(Bezier'(t))

    RouteArc* arcArray; //0x4C
    u32 pointsPerArc; //0x50
    float percentPerArc; //0x54
    //this indicates how much % each point of an arc makes up of the distance btw origin and final points,
    //so each array is made of pointsPerArc floats
    float* percentFromOriginArrays; //0x58 
    Vec3 prevPos; //0x5C
    float distToNextPos; //0x68 norm(curPos (freshly calculated) - prevPos)
}; //0x6c
#endif