function[n,y]=filter_lowpass(Fs,x,fc)
% % 示例信号用于检测滤波器
% Fs=200;N=256;fc=50;
% n=0:N-1;
% t=n/Fs;
% x=sign(sin(2*pi*15*t));   
N=length(x);
n=0:N-1;
Wc=2*fc/Fs;                                          
[b,a]=butter(4,Wc,'low');
y = filter(b,a,x);
% figure(1);subplot(2,1,1);plot(n,x);
% % 显示格式
% figure(1);subplot(2,1,2);plot(n,y);  