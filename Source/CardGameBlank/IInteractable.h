#pragma once
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class IInteractable {

	GENERATED_IINTERFACE_BODY()

public:
	UFUNCTION()
	virtual void OnHoverStart();
	UFUNCTION()
	virtual void OnHoverEnd();
	UFUNCTION()
	virtual void OnSelectStart();
	UFUNCTION()
	virtual void OnSelectEnd();
};
