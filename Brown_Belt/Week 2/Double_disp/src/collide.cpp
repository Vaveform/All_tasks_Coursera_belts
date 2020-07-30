#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

template <typename T>
struct Collider : GameObject {
  bool Collide(const GameObject& that) const override {
    return that.CollideWith(static_cast<const T&>(*this));
  }
};


// Определите классы Unit, Building, Tower и Fence так, чтобы они наследовались от
// GameObject и реализовывали его интерфейс.

class Unit : public Collider<Unit> {
public:
  explicit Unit(geo2d::Point figureition) : figure(figureition){};
  const geo2d::Point& GetPoint() const {
	  return figure;
  }
  //bool Collide(const GameObject& that) const override;
  bool CollideWith(const Unit& that) const override;
  bool CollideWith(const Building& that) const override;
  bool CollideWith(const Tower& that) const override;
  bool CollideWith(const Fence& that) const override;
private:
  geo2d::Point figure;
};

class Building: public Collider<Building> {
public:
  Building(geo2d::Rectangle geometry) : figure(geometry) {};
  const geo2d::Rectangle& GetRectangle() const {
	  return figure;
  }
  //bool Collide(const GameObject& that) const override;
  bool CollideWith(const Unit& that) const override;
  bool CollideWith(const Building& that) const override;
  bool CollideWith(const Tower& that) const override;
  bool CollideWith(const Fence& that) const override;
private:
  geo2d::Rectangle figure;
};

class Tower: public Collider<Tower> {
public:
  Tower(geo2d::Circle geometry) : figure(geometry) {};
  const geo2d::Circle& GetCircle() const {
	  return figure;
  }
  //bool Collide(const GameObject& that) const override;
  bool CollideWith(const Unit& that) const override;
  bool CollideWith(const Building& that) const override;
  bool CollideWith(const Tower& that) const override;
  bool CollideWith(const Fence& that) const override;
private:
  geo2d::Circle figure;
};

class Fence: public Collider<Fence> {
public:
  Fence(geo2d::Segment geometry) : figure(geometry) {};
  const geo2d::Segment& GetSegment() const {
	  return figure;
  }
  //bool Collide(const GameObject& that) const;
  bool CollideWith(const Unit& that) const override;
  bool CollideWith(const Building& that) const override;
  bool CollideWith(const Tower& that) const override;
  bool CollideWith(const Fence& that) const override;
private:
  geo2d::Segment figure;
};


#define Class_Member_Function_Declaration(class_type)                            \
	                                                                             \
                                                                                 \
		bool class_type::CollideWith(const Unit& that) const {                   \
			return geo2d::Collide(figure, that.GetPoint());                      \
		}                                                                        \
                                                                                 \
		bool class_type::CollideWith(const Building& that) const {               \
			return geo2d::Collide(figure, that.GetRectangle());                  \
		}                                                                        \
                                                                                 \
		bool class_type::CollideWith(const Tower& that) const {                  \
			return geo2d::Collide(figure, that.GetCircle());                     \
		}                                                                        \
                                                                                 \
		bool class_type::CollideWith(const Fence& that) const {                  \
			return geo2d::Collide(figure, that.GetSegment());                    \
		}                                                                        \



// Member-function definition of class Unit
Class_Member_Function_Declaration(Unit);


//Member-function definition of class Building
Class_Member_Function_Declaration(Building);


//Member-function definition of class Tower
Class_Member_Function_Declaration(Tower);


//Member-function definition of class Fence
Class_Member_Function_Declaration(Fence);


// Реализуйте функцию Collide из файла GameObject.h

bool Collide(const GameObject& first, const GameObject& second) {
	return first.Collide(second);
}

void TestAddingNewObjectOnMap() {
  // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
  // и мы хотим добавить на неё новый, например, построить новое здание или башню.
  // Мы можем его добавить, только если он не пересекается ни с одним из существующих.
  using namespace geo2d;

  const vector<shared_ptr<GameObject>> game_map = {
    make_shared<Unit>(Point{3, 3}),
    make_shared<Unit>(Point{5, 5}),
    make_shared<Unit>(Point{3, 7}),
    make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
    make_shared<Tower>(Circle{Point{9, 4}, 1}),
    make_shared<Tower>(Circle{Point{10, 7}, 1}),
    make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
  };

  for (size_t i = 0; i < game_map.size(); ++i) {
    Assert(
      Collide(*game_map[i], *game_map[i]),
      "An object doesn't collide with itself: " + to_string(i)
    );

    for (size_t j = 0; j < i; ++j) {
      Assert(
        !Collide(*game_map[i], *game_map[j]),
        "Unexpected collision found " + to_string(i) + ' ' + to_string(j)
      );
    }
  }

  auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
  ASSERT(!Collide(*new_warehouse, *game_map[0]));
  ASSERT( Collide(*new_warehouse, *game_map[1]));
  ASSERT(!Collide(*new_warehouse, *game_map[2]));
  ASSERT( Collide(*new_warehouse, *game_map[3]));
  ASSERT( Collide(*new_warehouse, *game_map[4]));
  ASSERT(!Collide(*new_warehouse, *game_map[5]));
  ASSERT(!Collide(*new_warehouse, *game_map[6]));

  auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
  ASSERT(!Collide(*new_defense_tower, *game_map[0]));
  ASSERT(!Collide(*new_defense_tower, *game_map[1]));
  ASSERT(!Collide(*new_defense_tower, *game_map[2]));
  ASSERT( Collide(*new_defense_tower, *game_map[3]));
  ASSERT( Collide(*new_defense_tower, *game_map[4]));
  ASSERT(!Collide(*new_defense_tower, *game_map[5]));
  ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestAddingNewObjectOnMap);
  return 0;
}
