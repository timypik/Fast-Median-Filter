/**
  ******************************************************************************
  * @file    fast_median_filter.h
  * @author  Khusainov Timur
  * @version 0.0.0.4
  * @date    14.04.2014
  * @brief   Fast implementation of median filter (for FLOAT data)
  ******************************************************************************
  * @attention
  * <h2><center>&copy; COPYRIGHT 2014 timypik@gmail.com </center></h2>
  ******************************************************************************
  */

#ifndef FAST_MEDIAN_FILTER_H
#define FAST_MEDIAN_FILTER_H

typedef struct
{
	float *data_array;
	size_t *index_array;
	size_t position;
	size_t count;
	size_t length;
} tMedianFilter;

float FastMedianFilter(tMedianFilter *filter, float value)

#endif // FAST_MEDIAN_FILTER_H