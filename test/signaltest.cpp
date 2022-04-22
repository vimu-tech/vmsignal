#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include "vmwindow.h"
#include "vmfft.h"
#include "vmreal_fft.h"
#include "vmfilters.h"

#define FILTER_FHT_N 4096

void FirFilterTest(double *h, int32_t N, double *date, size_t num)
{
	int m=(int)(log((double)num)/log(2.0));
	unsigned int FFT_LEN;
	if(pow((double)2.0,m)==num)
		FFT_LEN=(int)(pow((double)2.0,m));
	else
		FFT_LEN=(int)(pow((double)2.0,m+1));

	double *x=new double[FFT_LEN];

	memcpy(x, date, num*sizeof(double));
	if(FFT_LEN!=num)
		memset(x+num, 0, (FFT_LEN-num)*sizeof(double));
	//for(size_t i=0;i<num;i++)
	//	x[i]=date[i];

	filters_overlap_add_fht(h, N, x, num, FILTER_FHT_N);

	memcpy(date, x, num*sizeof(double));
	//for(size_t i=0;i<num;i++)
	//	date[i]=(int)(x[i]);

	delete []x;
}

void IirFilterTest(const std::vector<double> b, const std::vector<double> a, double *date, size_t num)
{
	assert(num<=64*1024);

	int m=(int)(log((double)num)/log(2.0));
	unsigned int FFT_LEN;
	if(pow((double)2.0,m)==num)
		FFT_LEN=(int)(pow((double)2.0,m));
	else
		FFT_LEN=(int)(pow((double)2.0,m+1));	

	double *bb=new double[b.size()];
	double *aa=new double[a.size()];

	for(size_t i=0;i<b.size();i++)
		bb[i]=b[i];
	for(size_t i=0;i<a.size();i++)
		aa[i]=a[i];

	double *x=new double[FFT_LEN];

	memcpy(x, date, num*sizeof(double));
	if(FFT_LEN!=num)
		memset(x+num, 0, (FFT_LEN-num)*sizeof(double));
	//for(size_t i=0;i<num;i++)
	//	x[i]=date[i];

	filters_overlap_add_fht(bb, b.size(), aa, a.size(), x, num, FILTER_FHT_N);

	memcpy(date, x, num*sizeof(double));
	//for(size_t i=0;i<num;i++)
	//	date[i]=(int)(x[i]);

	delete []x;
	delete []bb;
	delete []aa;
}

void FFTTest()
{
	double pi = 3.14159265;
	int sample = 1000000;
	int N = 262144;
	int WaveH = 10.0;
	double freq = 60.0;
	double resolution = (double)sample / N;

	double* re = new double[N];
	double* im = new double[N];
	double* m_mag_buffer = new double[N];
	double* m_ph_buffer = new double[N];

	srand((unsigned)time(NULL)); // ��ʼ�������
	for (int l = 0; l < 5; l++)
	{
		//Randomly generate frequency tests
		freq = ((double)rand() /RAND_MAX) * (sample / 2);
		printf("gen freq =%0.3f ", freq);

		//gen wave
		double Cn = sample / freq;
		for (int k = 0; k < N; k++)
		{
			re[k] = WaveH * sin(k * 360.0 / Cn * pi / 180.0);
			im[k] = 0;
		}

		//�Ӵ�
		double window_gain = window_i(BLACKMAN, re, N, 0, 0);

		//fft
		real_fft_signal(re, im, N, N, 3);

		//���Դ��������������
		for (int k = 0; k < N; k++)
		{
			re[k] /= window_gain;
			im[k] /= window_gain;
		}

		//
		Fft_Amplitude(re, im, m_mag_buffer, N, true);
		Fft_Phase(re, im, m_mag_buffer, m_ph_buffer, N, FFT_Phase_Ref_Deg);

		//����벿�֣����ӵ�ǰ�벿��     i=0��ֱ������,�����ʵ�ʵ�2��
		int m_buffer_length = N / 2;
		for (int i = 0; i < m_buffer_length; i++)
			m_mag_buffer[i] = m_mag_buffer[i] * 2;

		//
		//Fft_Amplitude_Conver_Type(m_mag_buffer, m_buffer_length, FFT_Amplitude_Ref_dBV);

		//�ҵ���ߵ㣬����Ƶ��
		int k_max = 0;
		double a_max = m_mag_buffer[0];
		for (int k = 0; k < m_buffer_length; k++)
		{
			if (m_mag_buffer[k] > a_max)
			{
				a_max = m_mag_buffer[k];
				k_max = k;
			}
		}
		double f = (double)k_max * sample / N;
		printf("freq k=%d Amplitude=%0.3f f=%0.3f f-freq=%0.3f resolution=%0.3f\n", k_max, a_max, f, f-freq, resolution);
	}
	
	delete[] re;
	delete[] im;
	delete[] m_mag_buffer;
	delete[] m_ph_buffer;
}

int main()
{
	
	FFTTest();
	return 0;
}


