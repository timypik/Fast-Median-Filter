/**
  ******************************************************************************
  * @file    fast_median_filter.c
  * @author  Khusainov Timur
  * @version 0.0.0.3
  * @date    14.04.2014
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
	size_t m_length = filter->count;
	size_t m_position = filter->position;
	//----------------------------------------------------------------------------
	if (filter->count > 0) /* must work */
	//----------------------------------------------------------------------------
	{
		/* pair of index and data in sortion array */
		size_t _old_index; /* add/replace real index */
		float _old_value; /* add/replace reavl value */
		
		/* get real index for replace value */
		if (filter->count == filter->length)
		{
			/* find pair index/data */
			for (size_t i = 0; i < m_length; ++i)
				if (filter->index_array[i] == m_position)
				{
					_old_index = i;
					break;
				}
		}
		else
			_old_index = m_position; /* fill filter - just add new value */
		
		/* get old value */
		_old_value = filter->data_array[m_position];
		
		/* compare values */
		if (_old_value != value)
		{
			filter->data_array[m_position] = value; /* replace old value */
			size_t * _index = &filter->index_array[_old_index]; /* get old sorting index */

			if (_old_value < value)
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
				//----------------------------------------------------------------------
			}
			else if (_old_value > value)
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
				//----------------------------------------------------------------------
			}

			static float _check_array[11] = {0};
			for (size_t i = 0; i < 11; ++i)
			{
				size_t _i = filter->index_array[i];
				_check_array[i] = filter->data_array[_i];
			}
		}
	}
	//----------------------------------------------------------------------------
	else /* init filter */
	//----------------------------------------------------------------------------
	{
		*filter->data_array = value;
		*filter->index_array = 0;

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