#include "gtest/gtest.h"
#include "soko_board.hpp"
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


