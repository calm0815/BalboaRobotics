% ���䐫
clear

balboa_param;
linear_model;

% ���䐫�̃`�F�b�N�idet_Vc��0�j
sys_Vc = ctrb(sys_Ad, sys_Bd)
rank_Vc = rank(sys_Vc)
det_Vc = det(sys_Vc)

% �ϑ����̃`�F�b�N
sys_Vo = obsv(sys_Ad, sys_C)
rank_Vo = rank(sys_Vo)
det_Vo = det(sys_Vo)
