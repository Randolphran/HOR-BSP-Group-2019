function[y]=signal_fft(x)
%Ê¾ÀýÐÅºÅ
% T=2*10*pi;
% t=0:0.01:T;
% x=sin(t);
y=fft(x);
% figure(1);subplot(2,1,1);plot(t,x);
% figure(1);subplot(2,1,2);plot(t,y);