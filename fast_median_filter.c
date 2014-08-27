/**
  ******************************************************************************
  * @file    fast_median_filter.c
  * @author  Khusainov Timur
  * @version 0.0.0.6
  * @date    16.04.2014
  * @brief   Fast implementation of median filter (for FLOAT data)
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2014 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#include <stdint.h>
#include <stddef.h>
#include <float.h>

#include "fast_median_filter.h"

float FastMedianFilter(tMedianFilter *filter, float value)
{
	float m_result;
	//----------------------------------------------------------------------------
	size_t m_position = filter->position; /* current data array position */
	size_t m_length = filter->count; /* current filter length */
	//----------------------------------------------------------------------------
	if (m_length) /* must work */
	//----------------------------------------------------------------------------
	{
		/* pair of index and data in sorting array */
		size_t _old_index; /* add/replace real index */
		float _old_value; /* add/replace real value */
		
		/* get real index for replace value */
		if (m_length == filter->length)
		{
			_old_index = 0;
			
			/* find pair index/data */
			while (filter->index_array[_old_index] != m_position)
				++_old_index;

			/* get old replacing value */
			_old_value = filter->data_array[m_position];
		}
		else
		{
			filter->index_array[m_position] = m_position;

			_old_index = m_position; /* fill filter - just add new value */
			_old_value = FLT_MAX; /* all new value compare via FLOAT_MAX */
		}
		
		/* get and replace old value */
		filter->data_array[m_position] = value;
		
		/* get old sorting index */
		uint8_t * _index = &filter->index_array[_old_index];

		if (_old_value < value) /* compare values -> get high */
		{
			/* go up */
			while (++_old_index != m_length)
			{
				/* get real index for next value */
				size_t _check_index = *(++_index);

				/* get next value for check and compare values */
				if (filter->data_array[_check_index] < value) 
				{
					/* swap real indexes */
					*_index = *(_index - 1);
					*(_index - 1) = _check_index;
				}
				else break;
			}
			//------------------------------------------------------------------------
		}
		else if (_old_value > value) /* compare values -> get low*/
		{
			/* go down */
			while (_old_index-- != 0)
			{
				/* get real index for previous value */
				size_t _check_index = *(--_index);

				/* get previous value for check and compare values */
				if (filter->data_array[_check_index] > value) 
				{
					/* swap real indexes */
					*_index = *(_index + 1);
					*(_index + 1) = _check_index;
				}
				else break;
			}
			//------------------------------------------------------------------------
		}
		
		/* get median value */
		m_result = filter->data_array[filter->index_array[m_length/2]];
	}
	//----------------------------------------------------------------------------
	else /* init filter */
	//----------------------------------------------------------------------------
	{
		filter->position = 0;
		
		*filter->index_array = 0;
		*filter->data_array = value;

		m_result = value;
	}
	//----------------------------------------------------------------------------
	// filter fill position and count
	//----------------------------------------------------------------------------
	m_position++;
	filter->position = (m_position == filter->length) ? (0) : m_position;
	//----------------------------------------------------------------------------
	if (m_length < filter->length)
		filter->count++;
	//----------------------------------------------------------------------------
	return m_result;
}