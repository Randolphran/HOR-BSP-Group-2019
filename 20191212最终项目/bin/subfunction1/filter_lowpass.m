function[n,y]=filter_lowpass(Fs,x,fc)
% % ʾ���ź����ڼ���˲���
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
% % ��ʾ��ʽ
% figure(1);subplot(2,1,2);plot(n,y);  