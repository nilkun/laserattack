#include "collisionDetection.h"

CollisionDetection::CollisionDetection() {

}

bool CollisionDetection::circleAndPoint(float x1, float y1, float radius, float x2, float y2) {
  int x = (x1 - x2)*(x1 - x2);
  int y = (y1 - y2)*(y1 - y2);
  int distance = x + y;
  int collisionRadius = radius * radius;
  if(collisionRadius >= distance) return true;
  else return false;
}
