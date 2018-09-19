#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "Utils.h"
#include "Console.h"
#include "Event.h"
#include "Animation.h"

class Sequence : public EventReceiver
{
public:

	Sequence() {}

	Sequence(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib);

	void SetSequenceGraph(EventReceiver* seqg)
	{
		mSeqG = seqg;
	}

	virtual Frame Run() = 0;

protected:

	AnimPack* mAnimPack;
	EventReceiver* mSeqG;
	EventReceiver* mPrtLib;
	EventReceiver* mSndLib;
	bool mPlaying;
	bool mLooping;
};

class seq_player_idle : public Sequence
{
public:

	seq_player_idle(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib);

	Frame Run();

	bool EventProcess(Event eve);
};


class seq_player_run : public Sequence
{
public:

	seq_player_run(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib);

	Frame Run();

	bool EventProcess(Event eve);

};

class SequenceGraph : public EventReceiver
{
public:

	SequenceGraph() {}

	SequenceGraph(AnimPack pck, EventReceiver* prtlib, EventReceiver* sndlib);

	bool LogSequence(Sequence* seq, int ID);

	AnimPack* GetAnimPack()
	{
		return &mAnimPack;
	}

	//virtual bool ActivateSequence(int seqID);

	//virtual bool EventProcess(Event eve);

protected:

	AnimPack mAnimPack;
	std::vector<Sequence*> mSeqs;
	std::vector<int> mIDs;
	
};

#endif