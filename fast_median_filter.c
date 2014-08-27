/**
  ******************************************************************************
  * @file    fast_median_filter.c
  * @author  Khusainov Timur
  * @version 0.0.0.1
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
		size_t _old_index;
		float _old_value;
		
		/* get real index for replase value */
		if (filter->count == filter->length)
		{
			for (size_t i = 0; i < m_length; ++i)
				if (filter->index_array[i] == m_position)
				{
					_old_index = i;
					break;
				}
		}
		else
			_old_index = m_position;
		
		/* get and replase old values */
		_old_value = filter->data_array[m_position];
		filter->data_array[m_position] = value;
		
		if (_old_value != value)
		{
			if (_old_value < value)
			{
				/* go up */
				while (++_old_index != m_length)
				{
					/* get real index for next value */
					size_t _check_index = filter->index_array[_old_index];
					
					/* get next value for check */
					float _check_value = filter->data_array[_check_index];
					
					/* compare values */
					if (_check_value < value) 
					{
						/* swap real indexes */
						filter->index_array[_old_index] = filter->index_array[_old_index - 1];
						filter->index_array[_old_index - 1] = _check_index;
					}
					else break;
				}
			}
			else if (_old_value > value)
			{
				/* go down */
				while (_old_index-- != 0)
				{
					/* get real index for previous value */
					size_t _check_index = filter->index_array[_old_index];
					
					/* get previous value for check*/
					float _check_value = filter->data_array[_check_index];
					
					/* compare values */
					if (_check_value > value) 
					{
						/* swap real indexes */
						filter->index_array[_old_index] = filter->index_array[_old_index + 1];
						filter->index_array[_old_index + 1] = _check_index;
					}
					else break;
				}
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