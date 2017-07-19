clc
clear all
close all

global Jr Ix Iy Iz b d l m g 
% of the PD controller

kpp = 50;
kdp = 8;

kpt = 50;
kdt = 8.09;

kpps = 50;
kdps = 8.3996;

kpz = 90;
kdz = 13.795;

kpx = 6;
kdx = 4;

kpy = 6;
kdy = 4;

kpz2 = 6;
kdz2 = 0.4;

Gains = [kpp kdp kpt kdt kpps kdps kpz kdz ...
         kpx kdx kpy kdy kpz2 kdz2];
disp(Gains);
% Quadrotor constants
Ix = 7.5*10^(-3);  % Quadrotor moment of inertia around X axis
Iy = 7.5*10^(-3);  % Quadrotor moment of inertia around Y axis
Iz = 1.3*10^(-2);  % Quadrotor moment of inertia around Z axis
Jr = 6.5*10^(-5);  % Total rotational moment of inertia around the propeller axis
b = 3.13*10^(-5);  % Thrust factor
d = 7.5*10^(-7);  % Drag factor
l = 0.23;  % Distance to the center of the Quadrotor
m = 0.65;  % Mass of the Quadrotor in Kg
g = 9.807;   % Gravitational acceleration

