#ifndef BLAST_HORNET_DATA_H
#define BLAST_HORNET_DATA_H

class BlastHornet;
class BlastHornetState;

class BlastHornetData
{
private:
	BlastHornet* blastHornet;
	BlastHornetState* blastHornetState;

public:
	BlastHornetData();
	~BlastHornetData();

	BlastHornet* GetHornet() const;
	void SetHornet(BlastHornet* val);

	BlastHornetState* GetHornetState() const;
	void SetHornetState(BlastHornetState* val);
};


#endif // !BLAST_HORNET_DATA_H
