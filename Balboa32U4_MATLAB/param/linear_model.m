clear

balboa_param;

% �ϐ�
a11 = (m_w + m_p)*power(r_w, 2) + 2*m_p*r_w*r_p + m_p*power(r_p, 2) + I_p + I_w;
a12 = (m_w + m_p)*power(r_w, 2) + m_p*r_w*r_p + I_w;
a21 = (m_w + m_p)*power(r_w, 2) + m_p*r_w*r_p + I_w;
a22 = (m_w + m_p)*power(r_w, 2) + I_w + power(n, 2)*I_m;

delta = a11*a22 - a12*a21;

% ��ԕ�����
sys_A = [0 1 0 0;
         (a22*m_p*g*r_p)/delta 0 0 (a12*power(n, 2)*k_t*k_b/R)/delta;
         0 0 0 1;
         (-a21*m_p*g*r_p)/delta 0 0 (-a11*power(n, 2)*k_t*k_b/R)/delta];

sys_B = [0;
         (-a12*n*k_t/R)/delta;
         0;
         (a11*n*k_t/R)/delta];

sys_C = eye(4);
sys_D = 0;

% ��ԋ�ԕ\��
sys = ss(sys_A, sys_B, sys_C, sys_D)
% ��ԋ�ԕ\���̌W���̒��o
[sys_A, sys_B, sys_C, sys_D] = ssdata(sys)
% ��ԋ�ԕ\������`�B�֐��\���i��_/��/�Q�C���^�j��
zpk_P = zpk(sys)
% ���U��
Ts = 0.01; % ����[sec]
sysd = c2d(sys, Ts, 'zoh');