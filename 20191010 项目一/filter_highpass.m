function[y]=filter_highpass(Fs,x,fc)
%示例信号用于检测滤波器
%T=2*10*pi;
%t=0:0.01:T;
%fc=10;
%Fs=200;
%x=sign(sin(t));   
t=length(x);
Wc=2*fc/Fs;                                          
[b,a]=butter(4,Wc,'high');
y = filter(b,a,x);
% figure(1);subplot(2,1,1);plot(t,x);
% figure(1);subplot(2,1,2);plot(t,y);    