#include "gtest/gtest.h"
#include "soko_board.hpp"
#include "soko_position.hpp"
#include <iostream>
using namespace Sokoban;
using namespace std;

class SokoBoardTest : public ::testing::Test {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
    SokoBoard bt1 = SokoBoard("assets/stages/stage1.sok");
};

TEST_F(SokoBoardTest, isValidBoardTest) {
  EXPECT_EQ(bt1.getNumberOfBoxes(),bt1.getNumberofTargets());
  EXPECT_EQ(bt1.getNumberOfBoxes(),bt1.getNumberOfUnresolvedBoxes());

  /* Only one character per board. */
  int characters = 0;
  for (unsigned i = 0; i < bt1.dynamicBoard.size(); ++i)
    for (unsigned j = 0; j < bt1.dynamicBoard[0].size(); ++j)
      if (bt1.dynamicBoard[i][j].getType() == SokoObject::CHARACTER)
        ++characters;
  EXPECT_EQ(characters, 1);
}

TEST(PositionTest, PositionTest) {
  SokoPosition s;
  SokoPosition sp(1, 1);

  EXPECT_EQ(1, sp.x);
  EXPECT_EQ(1, sp.y);

  s = sp + UP;
  EXPECT_EQ(s.x, sp.x); 
  EXPECT_EQ(s.y, sp.y + 1);

  s = sp + DOWN;
  EXPECT_EQ(s.x, sp.x); 
  EXPECT_EQ(s.y, sp.y - 1);

  s = sp + RIGHT;
  EXPECT_EQ(s.x, sp.x + 1); 
  EXPECT_EQ(s.y, sp.y);

  s = sp + LEFT;
  EXPECT_EQ(s.x, sp.x - 1); 
  EXPECT_EQ(s.y, sp.y);
}
