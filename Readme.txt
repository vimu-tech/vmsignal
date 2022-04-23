说明：
1,该数字信号处理库，使用标准的C语言编写的，没有针对任何的平台进行更好的优化。
2,在使用中发现任何的bug或者建议，可以联系我们。

Note:
1,This digital signal processing library, written in the standard C language, is not better optimized for any platform.
2,If you find any bugs or suggestions in use, you can contact us.
	www.vimu.top  www.instrustar.com

平台支持:
Platform support:
	windows: x86 x64 amr64;
	linux: x64 arm-linux-gnueabi arm-linux-gnueabihf 
More platforms, we will add later.


linux.zip
这个是linux平台下面的so和lib库，你需要拷贝到linux系统然后再解压，在windows解压后拷贝，可能出现链接错误
This is the so and lib library below the Linux platform, you need to copy to the Linux system and then decompress, copy after windows decompression, there may be link errors


1,窗函数window
The following window functions are supported:
Rectangle, bartlett, triangular, cosine, hanning, bartlett_hanning, hamming, blackman, blackman_Harris, tukey, Nuttall, FlatTop, Bohman, Parzen, Lanczos, kaiser, gaussand dolph_chebyshev

2,FFT
Support Base 2 fft , Base 4 fft and Split-radix fft

3,FIR and IIR
Supports filtering of FIR and IIR;
FIR and IIR designs can be designed using QFilter, the QFilter and download from http://www.instrustar.com/update-en.asp
(Multi VirAnalyzer include QFilter ).

