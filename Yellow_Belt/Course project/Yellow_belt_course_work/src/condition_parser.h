#pragma once

#include <memory>
#include <iostream>
#include "node.h"
#include "token.h"
#include "date.h"

using namespace std;

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
