#pragma once

#include "ECardState.generated.h"

UENUM()
enum class ECardState : uint8
{
	IDLE,
	DRAWN,
	HIGHLIGHTED,
	SELECTED
};
