//�Ϳյ��ٵ�������;
#include "IHF.h"
#include "Window.h"

//ͼ�λ�����ز���;
Window Win;
#define Win_width 1200     //���ڿ��;
#define Win_heigh 800      //���ڸ߶�;
double asp = 1;            //ͼ����������������;

#define g -9.8             //�������ٶ�;
#define PI 3.14159265      //Բ����;
#define iterate 100000     //����������;
#define Points_Num 100000  //��ʾ��������΢Ԫ����;

//�������;
double M, R, C, dt;        //��������(g),����뾶(m),���ο�������ϵ��,��������(ԽСԽ��ȷ);

//�����˶�ѧ����;
double X, Y;                                          //����λ��(m);
double v, vx, vy, vx_last, vy_last, V, ��;             //�����ٶ�(m/s) [ֱ������,������(��Ϊ������)];
double ax, ay;                                        //������ٶ�(m/s^2);
double air_resistance, air_temper;                    //��������(N),�����¶�(��);
double X_last[Points_Num], Y_last[Points_Num];

//����Ŀ��;
double TargetX, TargetY, Tolerance;  //����λ��,�������뾶(m)(��Ŀ��ΪԲ����RΪ�뾶��һ����,��������������������Ϊ����Ŀ��);
double Mark_V, Mark_��;

//��������ϵ��,�����¶�(���϶�),����ӭ�����(m^2),��Կ����ٶ�ʸ��(m/s);
void Air_resistance(double C, double T, double S) {
	v = sqrt(pow(vx, 2) + pow(vy, 2));                                 //������ٶ�;

	double air_pressure = 101.29 * pow((T + 273.1) / 288.08, 5.256);   //�������ѹǿ;
	double �� = air_pressure / (0.2869 * (T + 273.1));                  //��������ܶ�;
	air_resistance = (C * �� * S * pow(v, 2)) / 2;                      //�����������;
}

//����˲ʱ���Ǽ���;
double d_sin() { return vy / v; }
double d_cos() { return vx / v; }
double d_slope() { return vy / vx; }

//ˮƽ������;
double level() {
	double d_vx, dx;

	//ͨ����������ٶ�;
	ax = (d_cos() * -air_resistance) / M;
	vx_last = vx;

	//��vx����;
	d_vx = ax * dt;
	vx = d_vx + vx;

	//��X����;
	dx = vx * dt;
	X = dx + X;

	return 0;
}
//Ǧ��������;
double vertical() {
	double d_vy, dy;

	//������ٶ�;
	ay = (d_sin() * -air_resistance) / M;
	vy_last = vy;

	//��vy����;
	d_vy = (ay + g) * dt;
	vy = d_vy + vy;

	//��Y����;
	dy = vy * dt;
	Y = dy + Y;

	return 0;
}

//��ʼ��ͼ�ν���;
void Initialize_Graph() {
	Win.Initialize_Window(Win_width, Win_heigh, EW_SHOWCONSOLE);
	setlinecolor(RGB(31, 31, 31)); setlinestyle(PS_SOLID || PS_ENDCAP_ROUND, 1);
}

//���Ƶ���ͼ��;
void Graph_Drawing() {
	//�����켣;
	setfillcolor(RGB(104, 33, 122));
	solidcircle(X * asp, Y * asp, 2);

	//��X��ˮƽ�ٶ�;
	setfillcolor(RGB(10, 89, 247));
	solidcircle(X * asp, abs(vx * asp), 1);

	//��X��Ǧ���ٶ�;
	setfillcolor(RGB(24, 148, 63));
	solidcircle(X * asp, abs(vy * asp), 1);

	//��X�ĺϼ��ٶ�;
	setfillcolor(RGB(244, 120, 34));
	solidcircle(X * asp, abs(sqrt(pow(ax * asp, 2) + pow(ay * asp, 2))), 1);

	//��X�Ŀ�������;
	setfillcolor(RGB(237, 24, 64));
	solidcircle(X * asp, abs(air_resistance * asp), 1);
}

double S, K = 2;
void value_evolution() {
	X = 0; Y = 0;                      //���õ������˲����ٶȳ�ʼλ�ú�Ϊ0;
	�� = PI / K; K += dt;               //������(��Ϊ������)
	vx = V * cos(��); vy = V * sin(��);  //������ת��Ϊֱ������;
}

//���������ʼֵ���ó�ʼ��;
void initialize_value() {
	asp = 1;                        //��ͼ���ű���;
	air_temper = 15;                 //�����¶�(��);

	//��������(g),����뾶(m),���ο�������ϵ��,��������(ԽСԽ��ȷ);
	M = 1, R = 0.06, C = 0.2; dt = 0.03;
	V = 1;                          //������ٶ�(m/s);

	S = PI * pow(R, 2);              //���㵯��ӭ�����(Ĭ��ΪԲ���͸յ�);
	X = 0; Y = 0;                    //�������˲����ٶȳ�ʼλ��;

	TargetX = 1000, TargetY = 300, Tolerance = 6;   //Ŀ��λ��,�ݲ�뾶(m);
}

int main() {
	initialize_value();
	for (int i = 1; i < iterate; i++) {//�ٶȱ仯;
		V += 1; cout << TargetX - X << endl;
		for (int i1 = 0; i1 < iterate; i1++) {//�Ƕȱ仯;
			value_evolution();
			while (1) {//��������;
				Air_resistance(C, air_temper, S);
				level();
				vertical();

				//cout << "(" << X << "," << Y << ")" << endl;

				//�������Ŀ����ж�����;
				if (X > TargetX - Tolerance && X < TargetX + Tolerance) {
					if (Y > TargetY - Tolerance && Y < TargetY + Tolerance) {
						//��¼�������Ŀ�������(V:������ٶ�,��:���巢��Ƕ�);
						Mark_V = V;
						Mark_�� = ��;
						system("cls"); cout << "Mark_V:" << Mark_V << "(m/s) , Mark_��:" << Mark_�� << "(rad)" << endl;
						i = iterate; i1 = iterate;  break;//������������;
					}
				}

				if (Y < 0) { break; }      //�������뺣ƽ����ֹ���ε�������;
			}

			if (K > 20) { K = 2; break; }   //������Ƕ�С��ĳֵ����Ϊ90��,�������Ƕȵ���;
		}
	}

	//��ʼ��ͼ�δ���;
	Initialize_Graph();
	setlinecolor(RGB(30, 30, 30));
	line(0, -20, 0, Win_heigh); line(-20, 0, Win_width, 0);                                              //����������;
	setlinecolor(RGB(120, 120, 120));
	line(0, TargetY * asp, Win_width, TargetY * asp); line(TargetX * asp, 0, TargetX * asp, Win_heigh);  //����Ŀ��X,Y��;
	circle(TargetX * asp, TargetY * asp, Tolerance * asp);                                               //����Ŀ���������뾶;

	dt = 0.001;
	X = 0; Y = 0;                      //�������˲����ٶȳ�ʼλ��;
	V = Mark_V, �� = Mark_��;
	vx = V * cos(��); vy = V * sin(��);  //������ת��Ϊֱ������;

	while (1) {
		Air_resistance(C, air_temper, S);
		level();
		vertical();
		Graph_Drawing();

		if (Y < 0) { break; }      //�������뺣ƽ����ֹ���ε�������;
	}

	/*

	//��ʼ��ͼ�δ���;
	Initialize_Graph();

	int PointsNum = 0;
	for (int m = 1; m < iterate; m++) {
		for (int i = 1; i < iterate; i++) {
			initialize_value();
			value_evolution();

			BeginBatchDraw();
			cleardevice();
			while (1) {
				Air_resistance(C, air_temper, S);
				level();
				vertical();

				Graph_Drawing();

				if (TargetX - 10 < X) { mark = 1; }

				//��¼����;
				//X_last[PointsNum] = X; Y_last[PointsNum] = Y; PointsNum++;

				if (Y < 0) { break; }
			}
			//���ƺ�������;
			line(0, -20, 0, Win_heigh); line(-20, 0, Win_width, 0);
			EndBatchDraw();

			if (mark == 1) { break; }
			if (K >= 10) { break; }
		}
		if (mark != 1) { V += 5; K = 2; cout << V << " , " << �� << endl; } else { cout << "���:" << V << " , " << �� << " , " << X; break; }
	}

	////���ݴ���(Ѱ�ҵ���������ֵ)
	//sort(X_last, X_last + (PointsNum - 1), greater<double>());   //������X�����������;
	//sort(Y_last, Y_last + (PointsNum - 1), greater<double>());   //������Y�����������;

	//circle(X_last[0], Y_last[0], 6);

	*/

	system("pause");
}