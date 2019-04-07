#ifndef BANGER_DATA_H
#define BANGER_DATA_H

class Banger;
class BangerState;

class BangerData
{
private:
	Banger* banger;
	BangerState* bangerState;

public:
	BangerData();
	~BangerData();

	Banger* GetBanger() const;
	void SetBanger(Banger* val);

	BangerState* GetBangerState() const;
	void SetBangerState(BangerState* val);
};
#endif // !BANGER_DATA_H
