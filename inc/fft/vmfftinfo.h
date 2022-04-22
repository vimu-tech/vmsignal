#ifndef VM_FFTINFO_H
#define VM_FFTINFO_H

/********************************************************************************************************************
说明：
1,该数字信号处理库，使用标准的C语言编写的，没有针对任何的平台进行更好的优化。
2,在使用中发现任何的bug或者建议，可以联系我们。

Note:
1,This digital signal processing library, written in the standard C language, is not better optimized for any platform.
2,If you find any bugs or suggestions in use, you can contact us.

	www.vimu.top
	www.instrustar.com
*********************************************************************************************************************/


#include "vmsignal_global.h"
#include "vmfft.h"
#include <stdlib.h>

class SIGNAL_EXPORT fftinfo
{
public:
	fftinfo();

	void CalFftInfo(double frequence, uint32_t sample, double* fft_buffer, size_t fft_n, double R, FFT_Amplitude_Ref_Type type);
public:
	FFT_Amplitude_Ref_Type m_ref_type;

	double m_snr;   //信噪比(SNR)
	double m_sinad;   //信纳比(SINAD) 
	double m_enob;   //有效位数(ENOB)
	double m_thd_db;   //总谐波失真(THD)
	double m_thd_percent;   //总谐波失真(THD)
	double m_sfdr;   //无杂散动态范围 (SFDR)  

	double m_first_harmonic_freq;
	double m_second_harmonic_freq;
	double m_third_harmonic_freq;
	double m_fourth_harmonic_freq;
	double m_fifth_harmonic_freq;
	double m_six_harmonic_freq;
	double m_seventh_harmonic_freq;

	double m_first_harmonic_value;
	double m_second_harmonic_value;
	double m_third_harmonic_value;
	double m_fourth_harmonic_value;
	double m_fifth_harmonic_value;
	double m_six_harmonic_value;
	double m_seventh_harmonic_value;
private:
	int32_t m_first_harmonic_index;
	int32_t m_second_harmonic_index;
	int32_t m_third_harmonic_index;
	int32_t m_fourth_harmonic_index;
	int32_t m_fifth_harmonic_index;
	int32_t m_six_harmonic_index;
	int32_t m_seventh_harmonic_index;

	double CalHarmonic(double frequence, uint32_t sample, int32_t n);
	void CalInfos(double* fft_buffer, size_t fft_n, uint32_t sample);
	size_t FineSecondMax(double* fft_buffer, size_t fft_n);
};

extern "C"  bool GetFftBufFreqAndRms(double* fft_buffer, const size_t fft_n, const uint32_t sample, const double first_harmonic,
								int32_t* freq_index, double* adj_freq, double* adj_rms);

#endif