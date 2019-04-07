#ifndef HELIT_DATA_H
#define HELIT_DATA_H

class Helit;
class HelitState;

class HelitData
{
private:
	Helit* helit;
	HelitState* helitState;
public:
	HelitData();
	~HelitData();

	HelitState* GetHelitState() const;
	void SetHelitState(HelitState* val);

	Helit* GetHelit() const;
	void SetHelit(Helit* val);
};


#endif
