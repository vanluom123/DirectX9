#ifndef GUNNER_DATA_H
#define GUNNER_DATA_H

class Gunner;
class GunnerState;

class GunnerData
{
private:
	Gunner* gunner;
	GunnerState* gunnerState;

public:
	GunnerData();
	~GunnerData();

	Gunner* GetGunner() const;
	void SetGunner(Gunner* val);

	GunnerState* GetGunnerState() const;
	void SetGunnerState(GunnerState* val);
};

#endif // !GUNNER_DATA_H
