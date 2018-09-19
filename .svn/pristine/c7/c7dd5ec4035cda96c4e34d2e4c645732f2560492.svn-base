#include "Sequence.h"

Sequence::Sequence(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib) : mAnimPack(pck), mPrtLib(prtlib), mSndLib(sndlib), mPlaying(false), mLooping(true)
{
	for(int i = 0; i < mAnimPack->GetAnimData()->GetAnimCount(); i++)
	{
		mAnimPack->GetAnimationDirect(i)->mFeed.Subscribe(this);
	}
}

seq_player_idle::seq_player_idle(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib) : Sequence(pck, prtlib, sndlib)
{
}

Frame seq_player_idle::Run()
{
	if (mLooping == false)
	{
		return mAnimPack->ActivateAnimation(IDLE_BEGIN, ONCE)->GetCurrentFrame();
	}
	else
	{
		return mAnimPack->ActivateAnimation(IDLE)->GetCurrentFrame();
	}
}

bool seq_player_idle::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case ANIM_COMPLETE:
		if (eve.GetEventData()->i == IDLE_BEGIN)
		{
			mLooping = true;
		}
	default:
		gCons->ConsPrintf("Sequence asked to process unrecognized event\n");
	}
	return false;
}


seq_player_run::seq_player_run(AnimPack* pck, EventReceiver* prtlib, EventReceiver* sndlib) : Sequence(pck, prtlib, sndlib)
{
}

Frame seq_player_run::Run()
{
	return mAnimPack->ActivateAnimation(RUN)->GetCurrentFrame();
}

bool seq_player_run::EventProcess(Event eve)
{
	switch (*eve.GetEventType())
	{
	case ANIM_COMPLETE:
		if (eve.GetEventData()->i == IDLE_BEGIN)
		{
			mLooping = true;
		}
	default:
		gCons->ConsPrintf("Sequence asked to process unrecognized event\n");
	}
	return false;
}

SequenceGraph::SequenceGraph(AnimPack pck, EventReceiver* prtlib, EventReceiver* sndlib) : mAnimPack(pck)
{
}

bool SequenceGraph::LogSequence(Sequence* seq, int ID)
{
	mSeqs.push_back(seq);
	mIDs.push_back(ID);
	seq->SetSequenceGraph(this);
	return false;
}