/**
 * \file   BolidRecorder.h
 * \author Jan Milík <milikjan@fit.cvut.cz>
 * \date   2013-11-03
 *
 * \brief  Header file for the BolidRecorder class.
 */

#ifndef BOLIDRECORDER_MKBLQWES
#define BOLIDRECORDER_MKBLQWES


#include "WaterfallBackend.h"


/**
 * \todo Write documentation for class BolidRecorder.
 */
class BolidRecorder : public SnapshotRecorder {
private:
	/**
	 * Copy constructor.
	 */
	BolidRecorder(const BolidRecorder& other);

protected:
	float minNoiseFq_;
	float maxNoiseFq_;
	
	int   lowNoiseBin_;
	int   noiseWidth_;

	float minDetectFq_;
	float maxDetectFq_;

	int   lowDetectBin_;
	int   detectWidth_;
	
	bool  bolidDetected_;
	bool  bolidRecord_;
	int   duration_;
	
	float average(float fromFq, float toFq);
	int   peak(float fromFq, float toFq);

public:
	/**
	 * Constructor.
	 */
	BolidRecorder();
	BolidRecorder(Ref<WaterfallBackend>  backend,
			    int                    snapshotLength,
			    float                  leftFrequency,
			    float                  rightFrequency,
			    float                  minDetectionFq,
			    float                  maxDetectionFq,
			    float                  minNoiseFq,
			    float                  maxNoiseFq) :
		SnapshotRecorder(backend, snapshotLength, leftFrequency, rightFrequency),
		minNoiseFq_(minNoiseFq),
		maxNoiseFq_(maxNoiseFq),
		lowNoiseBin_(0),
		noiseWidth_(0),
		minDetectFq_(minDetectionFq),
		maxDetectFq_(maxDetectionFq),
		bolidDetected_(false),
		bolidRecord_(false),
		duration_(0)
	{
		ORDER_PAIR(minDetectFq_, maxDetectFq_);
		int minFqBin = backend_->frequencyToBin(minDetectFq_);
		int maxFqBin = backend_->frequencyToBin(maxDetectFq_);
		ORDER_PAIR(minFqBin, maxFqBin);
		lowDetectBin_ = minFqBin;
		detectWidth_  = maxFqBin - minFqBin;
		
		minFqBin = backend_->frequencyToBin(minNoiseFq_);
		maxFqBin = backend_->frequencyToBin(maxNoiseFq_);
		
		lowNoiseBin_ = min(minFqBin, maxFqBin);
		noiseWidth_  = max(minFqBin, maxFqBin) - lowNoiseBin_;
	}
	
	/**
	 * Destructor.
	 */
	virtual ~BolidRecorder() {}
	
	virtual string getFileName(WFTime time);
	
	virtual void start();
	virtual void update();
	
	static float noise(float *buffer, int length);
	static float peak(float *buffer, int length);
	static float average(float *buffer, int length);
};

#endif /* end of include guard: BOLIDRECORDER_MKBLQWES */
