
#include <stdbool.h>
#include <stdint.h>
#include <math.h> // for fabs

#include "board.h"

#include "filter.h"

////////////////////////////////////////////////////////////////////////////////////////////
// usage : Exponentially Weighted Moving Average
/*
// filter init
s_EwmaFilter_t ewmaFilter;
ewmaFilter.hasInit = false;
ewmaFilter.prevValue = 0.0f;

// sample_get
output = ewmaFilter_get(&ewmaFilter, sample, range[1 ~ 15]);
 */

float ewmaFilter_get(s_EwmaFilter_t* ewmaFilter, float inputValue, uint8_t sensitivity)
{
    float retval, alpha;
    static float filter_alpha[MAX_FILTER_SIZE] = {
        1.0f, 0.9f, 0.85f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.25f, 
        0.2f, 0.15f, 0.1f, 0.05f, 0.02f
    };

    if (ewmaFilter->hasInit == false) {
        ewmaFilter->prevValue = inputValue;
        ewmaFilter->hasInit = true;
        return inputValue;
    }

    uint8_t idx = sensitivity - 1;
    if (idx < 0) idx = 0;
    if (idx > 14) idx = 14;
    alpha = filter_alpha[idx];

    retval = ((1 - alpha) * ewmaFilter->prevValue) + (alpha * inputValue);

    ewmaFilter->prevValue = retval;

    return retval;
}
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// usage : kalman filter
#ifdef USE_KALMAN_FILTER

static float kalman_q_factor[MAX_FILTER_SIZE] = {
        0.99f, 0.8f, 0.6f, 0.5f, 0.3f, 0.1f, 0.05f, 0.01f, 0.005f,0.001f, 
        0.0005f, 0.0001f, 0.00005f, 0.00001f, 0.000001f};

////////////////////Kalman Filter ///////////////////////////
#if 0
	int Kalman_APP_Init(s_KalmanApp_t *pObj, float Measure_Err, float Est_Err, float Q_Noise)
	{
		pObj->hasInit = false;

		//Set Parameters
		Kalman_setMeasurementError(pObj,Measure_Err);  //How much do we expect to our measurement vary
		Kalman_setEstimateError(pObj,Est_Err);			
		Kalman_setProcessNoise(pObj,Q_Noise);	//usually a small number between 0.001 and 1 - how fast your measurement moves. Recommended 0.01. Should be tunned to your needs.
		

		return true;
	}

	int Kalman_APP_Process(s_KalmanApp_t *pObj,t_LastValue* pOriginVal, t_LastValue* pFilteredVal ,unsigned char sensitivity)
	{
		/* sensitivity = 1 ~ 15 */
		float retval, alpha;
		unsigned char idx,i;


		if (pObj->hasInit == false)
		{
			//INIT
			for (i=0;i<MAX_CHANNEL_NO;i++)
			{
				//if(pOriginVal->last_value[i] != DEF_NO_VALUE )
				if(pOriginVal->last_value[i] > DEF_NO_VALUE_NORMAL_LO) 
				{
					pObj->kalman[i]._last_estimate = pOriginVal->last_value[i];
					pFilteredVal->last_value[i] =  pOriginVal->last_value[i];

				}
				else
				{
					//NO VALUE
					UART_PRINT("[ewmaFilter-Init]ch%d: Set No Value from %f \r\n",i,pFilteredVal->last_value[i] );
					pFilteredVal->last_value[i] = DEF_NO_VALUE;
					pObj->kalman[i]._last_estimate = DEF_NO_VALUE;
				}
			}

			pObj->hasInit = true;
			pFilteredVal->timestamp = pOriginVal->timestamp; //TimeStamp

			return false;
		}

		idx = sensitivity - 1;
		if (idx < 0) idx = 0;
		if (idx > 14) idx = 14;
		alpha = kalman_q_factor[idx];

		pFilteredVal->timestamp = pOriginVal->timestamp; //TimeStamp

		for (i=0;i<MAX_CHANNEL_NO;i++)
		{
			if(pOriginVal->last_value[i] > DEF_NO_VALUE_NORMAL_LO )
			{
				if(pObj->kalman[i]._last_estimate != DEF_NO_VALUE)
				{
					Kalman_updateEstimate(&pObj->kalman[i],pOriginVal->last_value[i]);
					pFilteredVal->last_value[i] = pObj->kalman[i]._current_estimate;
				}
				else
				{
					//Init this channel info
					pObj->kalman[i]._last_estimate = pOriginVal->last_value[i];
					pFilteredVal->last_value[i] =  pOriginVal->last_value[i];				
				}
					
			}
			else
			{
				//NO VALUE, <-1000 
				UART_PRINT("[ewmaFilter ]ch%d: Set No Value from %f \r\n",i,pFilteredVal->last_value[i] );
				pFilteredVal->last_value[i] = DEF_NO_VALUE;
			}
		}
			
		return true;
		
	}

#endif

	float Kalman_updateEstimate(s_KalmanFilter_t *pObj,float mea)
	{

		pObj->_kalman_gain = pObj->_err_estimate/(pObj->_err_estimate + pObj->_err_measure);
		
		pObj->_current_estimate = pObj->_last_estimate + pObj->_kalman_gain * (mea - pObj->_last_estimate);
		
		pObj->_err_estimate =  (1.0 - pObj->_kalman_gain)*pObj->_err_estimate + 
			fabs(pObj->_last_estimate-pObj->_current_estimate)*pObj->_q_process;
		
		pObj->_last_estimate=pObj->_current_estimate;
		
		return pObj->_current_estimate;
	}

	void Kalman_setMeasurementError(s_KalmanFilter_t *pObj,float mea_e)
	{
		pObj->_err_measure=mea_e;
	}
	void Kalman_setEstimateError(s_KalmanFilter_t *pObj,float est_e)
	{
		pObj->_err_estimate=est_e;
	}

	void Kalman_setProcessNoise(s_KalmanFilter_t *pObj,float q)
	{
		pObj->_q_process=q;
	}

	float Kalman_getKalmanGain(s_KalmanFilter_t *pObj)
	{
		return pObj->_kalman_gain;

	}
	float Kalman_getEstimateError(s_KalmanFilter_t *pObj)
	{
		  return pObj->_err_estimate;
	}
#endif //kalman
////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// usage : moving median filter
/*
#define NUM_ELEMENTS    9 // only odd numbers 3/5/7/... allowed

s_MedianFilter_t medianFilter;
s_MedianNode_t medianNode[NUM_ELEMENTS];

// median init
medianFilter.numNodes = NUM_ELEMENTS;
medianFilter.medianBuffer = medianBuffer;

medianFilter_init(&medianFilter);

// sample_get

output = medianFilter_insert(&medianFilter, sample);
*/

#if 0
bool medianFilter_init(s_MedianFilter_t* medianFilter)
{
    if(medianFilter && medianFilter->medianBuffer &&
        (medianFilter->numNodes % 2) && (medianFilter->numNodes > 1))
    {
        //initialize buffer nodes
        for (uint8_t i = 0 ; i < medianFilter->numNodes ; i++)
        {
            medianFilter->medianBuffer[i].value = 0;
            medianFilter->medianBuffer[i].nextAge = &medianFilter->medianBuffer[(i + 1) % medianFilter->numNodes];
            medianFilter->medianBuffer[i].nextValue = &medianFilter->medianBuffer[(i + 1) % medianFilter->numNodes];
            medianFilter->medianBuffer[(i + 1) % medianFilter->numNodes].prevValue = &medianFilter->medianBuffer[i];
        }
        //initialize heads
        medianFilter->ageHead = medianFilter->medianBuffer;
        medianFilter->valueHead = medianFilter->medianBuffer;
        medianFilter->medianHead = &medianFilter->medianBuffer[medianFilter->numNodes / 2];

        return true;
    }

    return false;
}

int16_t medianFilter_insert(s_MedianFilter_t* medianFilter, int16_t sample)
{
    uint8_t i;
    s_MedianNode_t *newNode, *it;

    if (medianFilter->ageHead == medianFilter->valueHead)
    {   //if oldest node is also the smallest node, increment value head
        medianFilter->valueHead = medianFilter->valueHead->nextValue;
    }

    if((medianFilter->ageHead == medianFilter->medianHead) ||
        (medianFilter->ageHead->value > medianFilter->medianHead->value))
    {   //prepare for median correction
        medianFilter->medianHead = medianFilter->medianHead->prevValue;
    }

    //replace age head with new sample
    newNode = medianFilter->ageHead;
    newNode->value = sample;

    //remove age head from list
    medianFilter->ageHead->nextValue->prevValue = medianFilter->ageHead->prevValue;
    medianFilter->ageHead->prevValue->nextValue = medianFilter->ageHead->nextValue;
    //increment age head
    medianFilter->ageHead = medianFilter->ageHead->nextAge;

    //find new node position
    it = medianFilter->valueHead; //set iterator as value head
    for (i = 0 ; i < medianFilter->numNodes - 1 ; i++)
    {
        if (sample < it->value)
        {
            if (i == 0)
            {   //replace value head if new node is the smallest
                medianFilter->valueHead = newNode;
            }
            break;
        }
        it = it->nextValue;
    }

    //insert new node in list
    it->prevValue->nextValue = newNode;
    newNode->prevValue = it->prevValue;
    it->prevValue = newNode;
    newNode->nextValue = it;

    //adjust median node
    if (i >= (medianFilter->numNodes / 2))
    {
        medianFilter->medianHead = medianFilter->medianHead->nextValue;
    }

    return medianFilter->medianHead->value;
}
#endif
/*
 * another function median filter
#define storageSize 9  // size of filter, only odd numbers 3/5/7/... allowed
#define medianPos  4   // position of median in ordered list: (storageSize-1)/2,
                       // don't let the processor calculate this in the loop
#define medianType float // type of data values (int/long/float/...)

medianType median(medianType newVal) {
   static int init = 1; // init flag
   static medianType storageVal[storageSize]; // array of values
   static medianType storageOrd[storageSize]; // array of order numbers
   static int current = 0; // current index of the ring storage
   medianType returnVal = newVal; // the new value could be the median

   if (init) {
      // initialization of arrays
      int i;
      for (i=0; i<storageSize; i++) {
         storageVal[i] = newVal; // fill array with new value
         storageOrd[i] = i;      // just spread all order values
      }
      init = 0; // don't run initialization again
   } else {
      // store new value
      if (++current >= storageSize) current=0; // go one step in ring storage
      medianType oldVal = storageVal[current]; // save old value
      int oldOrd = storageOrd[current]; // save old order number
      storageVal[current] = newVal; // store new value
      storageOrd[current] = 0; // reset order number for new value
   
      // main loop
      int c = current; // index for loop through ring storage
      if (++c >= storageSize) c=0; // go one step (don't process current position)
      do {
         if (newVal <= storageVal[c] && oldOrd > storageOrd[c])
            storageOrd[c]++; // bigger value removed, smaller value added
         else if (newVal > storageVal[c] && oldOrd < storageOrd[c])
            storageOrd[c]--; // smaller value removed, bigger value added
         if (storageOrd[c] == medianPos)
            returnVal = storageVal[c]; // median found
         if (newVal > storageVal[c])
            storageOrd[current]++; // calculate order of new value
         if (++c >= storageSize) c=0; // go one step in ring storage
      } while (c != current); // stop at current position
   }
   // return new median value
   return (returnVal);
}
*/

////////////////////////////////////////////////////////////////////////////////////////////
