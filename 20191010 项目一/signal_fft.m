function[f,y]=signal_fft(x,Fs)
% % ʾ���ź�
% Fs=100;N=128;
% n=0:N-1;
% t=n/Fs;
% x=sin(2*pi*15*t);
N=length(x);
n=0:N-1;
y=abs(fft(x,N));
f=n*Fs/N;
% figure(1);subplot(3,1,1);plot(t,x);
% %˫����ʾ��ʽ
% figure(1);subplot(3,1,2);plot(f,y/N);
% xlabel('Ƶ��/Hz');ylabel('���');grid on;
% %������ʾ��ʽ
% figure(1);subplot(3,1,3);plot(f(1:N/2),y(1:N/2)*2/N);
% xlabel('Ƶ��/Hz');ylabel('���');grid on;
