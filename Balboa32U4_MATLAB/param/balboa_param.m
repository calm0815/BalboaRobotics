clear
% Balboa32U4

% �U�q�iPendulum�j
m_p = 0.2913 / 2; % ���� [kg]
I_p = 0.000229712 / 2;  % �������[�����g [kg*m2]
r_p = 0.014264; % �ԗ։�]������ԑ̏d�S�܂ł̒��� [m]

% �ԗցiWheel�j
m_w = 0.0197; % ���� [kg]
I_w = 0.000023; % �������[�����g [kg*m2]
r_w = 0.040; % ���a [m]
width = 0.107; % �g���b�h�� [m]

% ���[�^�[�iMotor�j
k_t = 0.003382287; % �g���N�萔 [N*m/A]
k_b = 0.003067344; % �t�N�d�͒萔 [V*sec/rad]
n = 110.103; % �M�A��
t_m = 0.000472285; % ���׃g���N [N*m]
R_m = n*k_t*k_b/t_m; % ������R�l
R_driver = 0.280; % ���[�^�[�h���C�o�̒�R�l
R = R_m + R_driver; % ��R�l
m_rotator = 0.002; % ��]�q���� [kg]
r_rotator = 0.004; % ��]�q���a [m]
I_m = 0.5*m_rotator*r_rotator^2; % �������[�����g [kg*m2]
V_offset = R*t_m/k_t;

% ���p�����[�^
g = 9.81; % �d�͉����x [m/s^2]
