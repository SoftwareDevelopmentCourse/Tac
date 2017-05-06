// Copyright by GameDream.

#pragma once

#include "Components/ActorComponent.h"
#include "TacHeader.h"
#include "DamageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTacDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TAC_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintReadOnly, Category = State)
	int32 Health;

	UPROPERTY(BlueprintReadOnly, Category = State)
	float Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State)
	int32 MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State)
	float MaxArmor;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State)
	float ArmorRecoveryDelay;
	// Range from 0 to 100
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = State)
	float ArmorRecoveryRate;

public:
	// Dynamic multicast delegate
	FTacDelegate OnDeath;

	UFUNCTION(BlueprintCallable, Category = State)
	void RecoverArmor();
	UFUNCTION(BlueprintCallable, Category = State)
	void StopRecoverArmor();
	UFUNCTION(BlueprintCallable, Category = State)
	void RecoverHealth(int32 val);
	
	void HandleDamage(float DamageVal, AActor* DamageCauser);
	FTimerHandle ArmorRecoveryHandle;

private:
	bool bShouldRecoverArmor;
};
