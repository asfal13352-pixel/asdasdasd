#pragma once
#include "Entity.hpp"
#include "../Shared/SharedRenderData.hpp"

void FillESPData(const Entity* ents, int num, int localIdx, SharedRenderData& out, int screenW, int screenH);
