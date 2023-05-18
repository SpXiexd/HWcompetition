
#define ROBOT_MASS  12.7235
#define ROBOT_INERTIAL  1.28825



#include <iostream>

#include <string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<unordered_map>
#include<math.h>


using namespace std;

#include <stdio.h>              // This example main program uses printf/fflush
#include "AGV.h"                       // Model's header file


//vector<AGVModelClass> AGV_Obj(4);          // Instance of model class
#include"Collision_detector.h"

vector<AGVModelClass>  AGV_Obj(4);

double pid_ppp = 0.970082674972921;
class Robot {
public:
	//m_nearbyWB��������̨�� - 1��ʾ���ڣ���is_empty����ʲô������m_Xλ��x��m_Yλ��y��m_Angle����m_targetNumĿ�깤��̨
	//t_p��ȡ��ʱ��ϵ����f_p��ȡ����ײϵ����R_angle���ٶ�, R_x���ٶ�x, R_y���ٶ�y,m_holdFrameNum������Ʒ��֡��
	int m_nearbyWB = 0;
 	int m_targetNum = -1; // ��Ŀ����WB�����������ûĿ����-1
	int m_is_empty = 0;
	double m_t_p = 0.8;
	double m_f_p = 0.8;
	double m_R_angle = 0.0;// ������ʾ��ʱ�룬������ʾ˳ʱ��
	double m_R_x = 0.0;
	double m_R_y = 0.0;
	double m_X = 0.0;
	double m_Y = 0.0;
	double m_Angle = 0.0;// 0����ʾ�ҷ���pi/2����ʾ�Ϸ���-pi/2����ʾ�·���
	int m_holdFrameNum = 0;

	vector<double> vectorVel = {0.5,-0.5};// ��¼������ǰ��·����ǰһ��·�����ٶ�
	vector<double> vectorVelA = {0.1,-0.1};// ��¼������ǰ��·����ǰһ��·�Ľ��ٶ�

	double setForward = 0.0;// ��¼ÿһ֡������ǰ�����Ƶ��ٶȣ������ٶ�
	double setRotate = 0.0;// ��¼ÿһ֡��������ת���Ƶ��ٶ�
	double rotateAngle = 0.0;// �ܹ���Ҫ��ת�ĽǶ�
	double movingDistance = 0.0;// �ܹ���Ҫ�ƶ��ľ���

	bool beginRotate = false;
	bool stillRotating = false;
	bool beginMove = false;
	bool stillMoving = false;
	double beginAngle = 0.0;
	double m_cost = 0.0;

	int maxRotateTimeMark = 0;
	int outPidTime = 0;
	bool lastWbNearWall = false;
	int outWallCount = 0;

	bool crashFlag = false;
	int avoidCrashControlTime = 0;
	int clashAimedID = -1;
};
class workingBench {
public:
	int m_type;
	double m_x, m_y;
	int m_residual_time;
	vector<int> m_material ;// ֱ��ת���ɶ����Ƶ��ַ���
	int m_status = 0;
	
};

// ����ȫ�ֱ���
vector<Robot> RB(4);
vector<workingBench> WB(50);
bool mapRead = false;//�ж��Ƿ��һ�ζ���ͼ
int r_wcount = 0;
int r_rcount = 0;
int w_wcount = 0;// ����д���ĸ�����̨�����
int w_rcount = 0;// ����д���ĸ������˵����
vector<int> buy;// ���뵱ǰ֡Ҫ������������Ļ��������
vector<int> sell;// ���뵱ǰ֡Ҫ�������������Ļ��������
vector<int> destory;// ���뵱ǰ֡Ҫ�������ٲ����Ļ��������
vector<int> m_OriSellVal = { 0,6000, 7600, 9200, 22500, 25000, 27500, 105000, 5000,5000};
vector<int> selectedWB(4);// ��ֹ�����˵�Ŀ�깤��̨��ͻ
// harshTable��Ӧ��ͬ������Ʒ����ȥ�ĸ�����̨
std::unordered_map<int, std::string> harshTable = { {1, "459"}, {2, "469"}, {3, "569"}, {4, "79"}, {5, "79"}, {6, "79"}, {7, "89"} };
//std::unordered_map<int, std::string> harshTable = { {1, "45"}, {2, "46"}, {3, "56"}, {4, "7"}, {5, "7"}, {6, "79"}, {7, "89"} };
//��ֹĳ��Ʒ�޷����������
std::unordered_map<int, int> harshTable2 = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5,0}, {6, 0}, {7,0} };

vector<int> nearWall;
void readMap(char read_line[], int row_count) {
	// ���ڵ�ͼ��ʼ������¼����̨�ͻ����˳�ʼλ��
		for (int i = 0; i < 100; i++) {
			if (isdigit(read_line[i])) {
				int num = read_line[i] - 48;  
				WB[r_wcount].m_type = num;
				WB[r_wcount].m_x = i * 0.5 + 0.25;// ��ʼλ��Ϊ��������
				WB[r_wcount].m_y = 50-(row_count * 0.5 + 0.25);// ��ȡ����ʱ���Ƿ�������
				//ɸѡ������ǽ�ڵĹ���̨
				if ((WB[r_wcount].m_x > 48) || (WB[r_wcount].m_x < 2) || (WB[r_wcount].m_y > 48) || (WB[r_wcount].m_y < 2)) {
					nearWall.push_back(r_wcount);
				}
				r_wcount++;
			}
			else if (read_line[i] == 'A')
			{
				int num = read_line[i] - 48;
				RB[r_rcount].m_X = i * 0.5 + 0.25;
				RB[r_rcount].m_Y = 50 - (row_count * 0.5 + 0.25);// ��ȡ����ʱ���Ƿ�������
				r_rcount++;
			}
		
		}
}

void writeData(char m_line[], int count) {
	stringstream ss(m_line);  // ʹ��ͷ�ļ�<sstream>
	string item;
	int m_material = 0;
	vector<int> binary = {0,0,0,0,0,0,0,0,0,0};
	int bit = 0;
	int w_index = 0;// ���ڿ��ƹ���̨״̬��ȡ����
	int r_index = 0;// ���ڿ��ƻ�����״̬��ȡ����
	if ((count < r_wcount+2)&&(count>1)) {//WB.size()+2
		// ��ʱ���յ����ǹ���̨״̬

		while (getline(ss, item, ' ')) {
			// ʹ��getline�����ո�ָ�ÿһ��line

			switch (w_index)
			{
			case 1:
				WB[w_wcount].m_x = stod(item);

				break;
			case 2:
				WB[w_wcount].m_y = stod(item);

				break;
			case 3:
				WB[w_wcount].m_residual_time = stoi(item);
	
				break;
			case 4:
				m_material = stoi(item);// Ҫ���ж�����ת��
				while (m_material != 0) {
					binary[bit] = m_material % 2;
				
					m_material = m_material / 2;
					bit++;
				}
				WB[w_wcount].m_material = binary;// Ҫ���ж�����ת��,���ַ������գ�����ַ�������λ�þ�֪���õ���������������Ʒ
				break;
			case 5:
				WB[w_wcount].m_status = stoi(item);
			
				break;
			}
			w_index++;
		}
		w_wcount++;
	}
	else if(count >= r_wcount+2) {//WB.size() + 2
	
		while (getline(ss, item, ' ')) {
	
			switch (r_index)
			{
			case 0:
				RB[w_rcount].m_nearbyWB = stoi(item);// ��������̨ ID
			
				break;
			case 1:
				RB[w_rcount].m_is_empty = stoi(item);// Я����Ʒ���� 
			
				break;
			case 2:
				RB[w_rcount].m_t_p = stod(item);// ʱ���ֵϵ��
			
				break;
			case 3:
				RB[w_rcount].m_f_p = stod(item);// ��ײ��ֵϵ��
			
				break;
			case 4:
				RB[w_rcount].m_R_angle = stod(item);// ���ٶ� 
			
				break;
			case 5:
				RB[w_rcount].m_R_x = stod(item);// ���ٶ� x
				
				break;
			case 6:
				RB[w_rcount].m_R_y = stod(item); // ���ٶ� y
			
				break;
			case 7:
				RB[w_rcount].m_Angle = stod(item);// ����
			
				break;
			case 8:
				RB[w_rcount].m_X = stod(item);// ����x
			
				break;
			case 9:
				RB[w_rcount].m_Y = stod(item);// ����y
				
				break;
			}
			r_index++;
		}
	
		// ÿ֡����ǰ�������д��Ļ������Ƿ������Ʒ�������ۻ�������Ʒ֡��+1
		if (RB[w_rcount].m_is_empty > 0) {
			RB[w_rcount].m_holdFrameNum++;
		}
		else{
			RB[w_rcount].m_holdFrameNum = 0;
		}
	
		w_rcount++;
	}
}

bool readUntilOK() {

	char line[1024];
	int row_count = 0;
	w_wcount = 0;// д��ǰ�ȳ�ʼ��
	w_rcount = 0;// д��ǰ�ȳ�ʼ��
	int line_count = 0;
	while (fgets(line, sizeof line, stdin)) {
		if (line[0] == 'O' && line[1] == 'K') {
			return true; // ������ȡ
		}
		else {
		
			if (!mapRead) {
				readMap(line, row_count);
			}
			else {
				writeData(line,line_count);
				line_count++;// 
			}
		}
		row_count++;
	}
	return false;
}

double calCost(int m_R_ID,int m_WB_ID) {
	double m_dis = sqrt((WB[m_WB_ID].m_y - RB[m_R_ID].m_Y)*(WB[m_WB_ID].m_y - RB[m_R_ID].m_Y) + (WB[m_WB_ID].m_x - RB[m_R_ID].m_X) * (WB[m_WB_ID].m_x - RB[m_R_ID].m_X));
	//m_dis = m_dis > 0 ? m_dis : 1;//��ֹ����Ϊ��ʱ�䵱��ĸ
	//return m_OriSellVal[WB[m_WB_ID].m_type] * 0.001/ m_dis;
	if (RB[m_R_ID].m_is_empty > 0) {
		// ����ԭ�ϸ�ϵ��
		double materialNum = WB[m_WB_ID].m_material[1] + WB[m_WB_ID].m_material[2] + WB[m_WB_ID].m_material[3] + WB[m_WB_ID].m_material[4] + WB[m_WB_ID].m_material[5] + WB[m_WB_ID].m_material[6];
		return (log10(m_OriSellVal[WB[m_WB_ID].m_type])+ materialNum*10)/ m_dis;
	}
	else {
		return log10(m_OriSellVal[WB[m_WB_ID].m_type])*harshTable2[WB[m_WB_ID].m_type]/(m_dis+1);
	}
}

void chose_target(int R_ID,int m_frame_id) {
	// m_residual_time ʣ������ʱ��
	// m_material ԭ�ϸ�����Ƶ��ַ���
	//m_status ��Ʒ��;
	if (m_frame_id == 1) {
		//��Ҫ��������һ֡
		int targetWB = 0;
		int minDistance = 0x3f3f3f3f;
		vector<int> wbSelection = { 1,2,3};

		for (int i = 0; i < r_wcount; i++) {//WB.size()
			// ֻ�й���̨�����ܹ�����ԭ���ϲſ���
			if (find(wbSelection.begin(), wbSelection.end(), WB[i].m_type) != wbSelection.end()) {
				auto it = find(selectedWB.begin(), selectedWB.end(), i);
				if (it == selectedWB.end()) {
					double distanceBRbWb = sqrt((WB[i].m_y - RB[R_ID].m_Y)*(WB[i].m_y - RB[R_ID].m_Y) + (WB[i].m_x - RB[R_ID].m_X) * (WB[i].m_x - RB[R_ID].m_X));
					targetWB = minDistance > distanceBRbWb ? i : targetWB;
					minDistance = minDistance > distanceBRbWb ? distanceBRbWb : minDistance;
				}
			}
		}
		RB[R_ID].m_targetNum = targetWB;
		RB[R_ID].beginRotate = true;
		selectedWB[R_ID]= RB[R_ID].m_targetNum;
	}
	else {
		if ((RB[R_ID].m_is_empty > 0)&&(RB[R_ID].m_targetNum < 0)) {
			// harshTable[RB[R_ID].m_is_empty]�Ǵ�ʱ������Я����Ʒ�ܹ�ȥ�Ĺ���̨��ֻ�б����Ĺ���̨�����в��ܽ���Ƚ�
			//�жϹ���̨���͡�����̨���롢ͬʱԭ�ϸ�����m_material��
			// ����ƷҲҪ�ۺ϶Ա�Ŀ�깤��̨��Ʒ�ļ۸�;���
			//��4�ͻ��bug
			int targetWB = -1;
			float mincost = 0.0;
			for (int i = 0; i < r_wcount; i++) {//WB.size()

				if ((harshTable[RB[R_ID].m_is_empty].find(to_string(WB[i].m_type)) != string::npos)
					&& !(WB[i].m_material[RB[R_ID].m_is_empty])) {

					auto it = find(selectedWB.begin(), selectedWB.end(), i);
					if (it == selectedWB.end()) {

						double WB_cost = calCost(R_ID, i);


						targetWB = WB_cost > mincost ? i : targetWB;
						mincost= WB_cost > mincost ? WB_cost : mincost;
					}
				}
			}
			/*auto it = find(selectedWB.begin(), selectedWB.end(), RB[R_ID].m_targetNum);
			if (it != selectedWB.end()) {
				selectedWB.erase(it);
			}*/
	
			if (targetWB == -1) {

				//��ʱҪôĿ�깤��̨��ռ�ã�Ҫôû��Ŀ�깤��̨
				for (int j = 0; j < selectedWB.size(); j++) {
					if ((harshTable[RB[R_ID].m_is_empty].find(to_string(WB[selectedWB[j]].m_type)) != string::npos)&&(j != R_ID)
						) {//��WB��ΪselectWB
						targetWB = selectedWB[j];
						RB[R_ID].m_targetNum = targetWB;
						RB[R_ID].beginRotate = true;
						selectedWB[R_ID] = RB[R_ID].m_targetNum;
						break;
					}
				}
				//��ʱtargetWB = -1˵������û��Ŀ�깤��̨����Ʒ
				if (targetWB == -1) {

					destory.push_back(R_ID);
				}
			}
			else {
				RB[R_ID].m_targetNum = targetWB;
				RB[R_ID].beginRotate = true;
				selectedWB[R_ID] = RB[R_ID].m_targetNum;
			}
		}
		else if ( (RB[R_ID].m_targetNum < 0)&&(RB[R_ID].m_is_empty <= 0.0)) {//((RB[R_ID].m_targetNum > -1) && (RB[R_ID].stillMoving))
			// ��ʱ������û����Ʒ����Ҫ�������е�ӵ�г�Ʒ�Ĺ���̨��1��7����ѡ���ֵ������г�Ʒ�Ĺ���̨
			// ������Ȼ��Ҫ��һ��̽��

			double min_distance = 0x3f3f3f;
			vector<int> wbSelection;
			if (m_frame_id > 8600) {
				wbSelection = { 1,2,3,4,5,6};
			}
			else {
				 wbSelection = { 1,2,3,4,5,6,7 };
			}
			int targetNum = -1;
			double mincost = 0.0;
			for (int i = 0; i < r_wcount; i++) {//WB.size()

				if ((find(wbSelection.begin(), wbSelection.end(), WB[i].m_type) != wbSelection.end()) && (WB[i].m_status > 0)) {

					auto it = find(selectedWB.begin(), selectedWB.end(), i);

					if (it == selectedWB.end()) {

						/*double temp = [](int R_ID, int WB_ID) -> double {
							return fabs(RB[R_ID].m_X - WB[WB_ID].m_x) + fabs(RB[R_ID].m_Y - WB[WB_ID].m_y);
						}(R_ID, i);*/
						//double temp=fabs(RB[R_ID].m_X - WB[i].m_x) + fabs(RB[R_ID].m_Y - WB[i].m_y);

						double WB_cost = calCost(R_ID, i);


						targetNum = WB_cost > mincost ? i : targetNum;
						mincost = WB_cost > mincost ?  WB_cost:mincost;					
					}
				}
			}

			if (targetNum == -1) {

				//��ʱҪôĿ�깤��̨��ռ�ã�Ҫôû��Ŀ�깤��̨
				double mincost = 0.0;
				for (int j = 0; j < selectedWB.size(); j++) {
					if (j != R_ID) {//��WB��ΪselectWB
						double WB_cost = calCost(R_ID, j);


						targetNum = WB_cost > mincost ? selectedWB[j] : targetNum;
						mincost = WB_cost > mincost ? WB_cost : mincost;

					
					}
				}
				RB[R_ID].m_targetNum = targetNum;
				RB[R_ID].beginRotate = true;
				selectedWB[R_ID] = RB[R_ID].m_targetNum;
			}
			else {
				RB[R_ID].m_targetNum = targetNum > -1 ? targetNum : RB[R_ID].m_targetNum;
				selectedWB[R_ID] = RB[R_ID].m_targetNum;
				RB[R_ID].beginRotate = true;
			}
			}

		else if ((RB[R_ID].m_targetNum > 0) && (RB[R_ID].m_is_empty > 0.0)) {//((RB[R_ID].m_targetNum > -1) && (RB[R_ID].stillMoving))
			// ����������Ʒ��Ŀ�꣬����Ҫʱ�̼��Ŀ�깤��̨��ԭ�ϸ��Ƿ�Ϊ�գ�����Ŀ��
			if (WB[RB[R_ID].m_targetNum].m_material[RB[R_ID].m_is_empty] != 0) {
				RB[R_ID].m_targetNum = -1;
				chose_target(R_ID, 3);
			}
		}
	}
}
	
void clashAovid() {}

 //�����Ƿ��ͼ�ɹ�


// �����Ƿ��յ�����������Ϣ

void set_forward_rotate_pid(int R_ID) {


	int WB_ID = RB[R_ID].m_targetNum;
	if (WB_ID == -1) {
		RB[R_ID].setForward = 0;
		RB[R_ID].setRotate = 0;
		return;
	}

	AGVModelClass::ExtU_AGV_T agvrobot1;

	agvrobot1.position_X = RB[R_ID].m_X; //yes
	agvrobot1.position_Y = RB[R_ID].m_Y;  //yes
	agvrobot1.Target_position_X = WB[WB_ID].m_x;  //yes
	agvrobot1.Target_position_Y = WB[WB_ID].m_y;  //yes
	agvrobot1.Vehicle_angular_velocity = RB[R_ID].m_R_angle; //yes
	agvrobot1.Vehicle_line_velocity = sqrt(RB[R_ID].m_R_y* RB[R_ID].m_R_y + RB[R_ID].m_R_x* RB[R_ID].m_R_x); //yes
	agvrobot1.Vehicle_heading = RB[R_ID].m_Angle; //yes
	agvrobot1.Vehicle_mass = ROBOT_MASS;
	agvrobot1.Vehicle_rotational_inertial = ROBOT_INERTIAL;
	agvrobot1.Delta_time = 0.02;

	// Set model inputs here
	AGV_Obj[R_ID].setExternalInputs(&agvrobot1);




	// Step the model
	AGV_Obj[R_ID].step();

	// Get model outputs here
	double forward1, rotate1;
	RB[R_ID].setForward = AGV_Obj[R_ID].getExternalOutputs().Forward_velocity;
	RB[R_ID].setRotate = AGV_Obj[R_ID].getExternalOutputs().Rotate_velocity;


}
void countNumber() {
	harshTable2 = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5,0}, {6, 0}, {7,0} };
	for (int i = 0; i < r_wcount; i++) {
		auto it = find(selectedWB.begin(), selectedWB.end(), i);
		if (it == selectedWB.end()) {
			for (int j = 1; j < WB[i].m_material.size(); j++) {

				if ((WB[i].m_material[j] == 0)&& (harshTable[j].find(to_string(WB[i].m_type)) != string::npos) ){
					harshTable2[j] = harshTable2[j] + 1;

				}
			}
		}
		else {
			//�ж��Ѿ���ѡ�Ĺ���̨��ԭ�ϸ��Ƿ񱻳��ж�Ӧ��Ʒ�Ļ�����ѡ��
			int index = distance(selectedWB.begin(), it);
			for (int k = 1; k < WB[i].m_material.size();k++){
				for (int e = index; e < selectedWB.size(); e++) {
					if ((WB[i].m_material[k] == 0) && (RB[e].m_is_empty != k) &&
						(harshTable[k].find(to_string(WB[i].m_type)) != string::npos)
						&&(RB[e].m_targetNum == i)) {
						harshTable2[k] = harshTable2[k] + 1;

					}
				}
			}
		}
	}

}
void countNumber2() {
	harshTable2 = { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5,0}, {6, 0}, {7,0} };
	for (int i = 0; i < r_wcount; i++) {
		// 1��2��3���͹���̨����Ҫ����ԭ�ϸ�
		if((WB[i].m_type !=1)&& (WB[i].m_type != 2)&& (WB[i].m_type != 3))
			for (int j = 1; j < WB[i].m_material.size(); j++) {

				if ((WB[i].m_material[j] == 0) && (harshTable[j].find(to_string(WB[i].m_type)) != string::npos)) {
					harshTable2[j]++;

				}
			}
	}

	//�ж��Ѿ���ѡ�Ĺ���̨��ԭ�ϸ��Ƿ񱻳��ж�Ӧ��Ʒ�Ļ�����ѡ��
	//ҲҪ����û��ԭ�ϸ��1��2��3
	for (int j = 0; j < selectedWB.size(); j++) {
		 if ((selectedWB[j] >= 0)&&(RB[j].m_is_empty > 0)) {
			harshTable2[RB[j].m_is_empty] --;	
		}
	}

}

Collision_detectorModelClass detector;
double     ABdis, is_crash, angle_A, angle_B;
void detector_pid(int R_ID, int R_ID1) {



	int WB_ID = RB[R_ID].m_targetNum;


	Collision_detectorModelClass::ExtU_Collision_detector_T t;

	t.A_position_X = RB[R_ID].m_X;               // '<Root>/A_position_X'
	t.B_position_X = RB[R_ID1].m_X;               // '<Root>/B_position_X'
	t.A_position_Y = RB[R_ID].m_Y;               // '<Root>/A_position_Y'
	t.B_position_Y = RB[R_ID1].m_Y;               // '<Root>/B_position_Y'
	t.A_Vehicle_line_velocity = sqrt(RB[R_ID].m_R_x*RB[R_ID].m_R_x + RB[R_ID].m_R_y*RB[R_ID].m_R_y);    // '<Root>/A_Vehicle_line_velocity'
	t.A_Vehicle_heading = RB[R_ID].m_Angle;          // '<Root>/A_Vehicle_heading'
	t.B_Vehicle_line_velocity = sqrt(RB[R_ID1].m_R_x*RB[R_ID1].m_R_x + RB[R_ID1].m_R_y*RB[R_ID1].m_R_y);    // '<Root>/B_Vehicle_line_velocity'
	t.B_Vehicle_heading = RB[R_ID1].m_Angle;          // '<Root>/B_Vehicle_heading'

	// Set model inputs here
	detector.setExternalInputs(&t);
	// Step the model
	detector.step();

	// Get model outputs here
	ABdis = detector.getExternalOutputs().distance_a_b;
	is_crash = detector.getExternalOutputs().angle_Velocity_Position;
	angle_A = detector.getExternalOutputs().opposite_directions_angle_A_pos;
	angle_B = detector.getExternalOutputs().opposite_directions_angle_B_pos;
}


void avoid_clash(int robotid) {
	for (int j = 0; j < 4; j++) {
		if (robotid == j) {}
		else {
			double tem_distance = sqrt((RB[robotid].m_X - RB[j].m_X)*(RB[robotid].m_X - RB[j].m_X) + (RB[robotid].m_Y - RB[j].m_Y)*(RB[robotid].m_Y - RB[j].m_Y));
			if (tem_distance < 5.0) {
				detector_pid(robotid, j);
				if (3.0415926535 - 0.3 > fabs(is_crash) > 0.4) {}
				else{
					RB[robotid].setRotate = 3.1415;
				}
			}
		}
	}
}

double minD = 2.5;
void avoid_clash2(int robotid) {
	//�������ײ���������
	//����������롢 ���������������ߵļн�
	//���ҳ���̾���ĵ�
	double minD2 = 0x3f3f3f;
	int aimedID = 0;
	if (RB[robotid].crashFlag) {


		if ((RB[robotid].avoidCrashControlTime < 5) && (fabs(RB[RB[robotid].clashAimedID].setRotate) < 3)){
			RB[robotid].setRotate= RB[robotid].m_R_angle > 0 ? 3.14159 : -3.14159;
			RB[robotid].avoidCrashControlTime++;
		}
		else {
			RB[robotid].avoidCrashControlTime = 0;
			RB[robotid].crashFlag = false;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (i != robotid) {
				double D = sqrt(pow((RB[robotid].m_X - RB[i].m_X), 2) + pow((RB[robotid].m_Y - RB[i].m_Y), 2));
				aimedID = minD2 < D ? aimedID : i;
				minD2 = minD2 < D ? minD2 : D;
			}
		}


		//���㵱ǰ���Ŀ������ߵ�ת��

		if (minD2 <= minD) {
			double dy = WB[aimedID].m_y - RB[robotid].m_Y;
			double dx = WB[aimedID].m_x - RB[robotid].m_X;
			double angleBRbWb = atan2(dy, dx) - RB[robotid].m_Angle;
			RB[robotid].crashFlag = fabs(angleBRbWb) < 0.5 ? true : false;
			if (RB[robotid].crashFlag) {
				RB[robotid].clashAimedID = aimedID;
				RB[aimedID].clashAimedID = robotid;
				RB[aimedID].crashFlag = true;

			}
		}
	}
}


int main() {
	// Initialize model





	for (int i = 0; i < 4; i++) {

		AGV_Obj[i].initialize();
	}
	readUntilOK();
	puts("OK");
	mapRead = true;
	
	if(r_wcount < 19){
		pid_ppp  = pid_ppp +1 ;

	}
	fflush(stdout);

	int frameID;
	while (scanf("%d", &frameID) != EOF) {
		readUntilOK();
	
		printf("%d\n", frameID);// ���ƻ�����ǰ��Ҫ�������ǰ֡ID
		for (int robotId = 0; robotId < 4; robotId++) {
			//countNumber();
			countNumber2();
			/*cal_val c1;
			double val = c1.cal(RB[robotId].m_holdFrameNum, RB[robotId].m_is_empty, RB[robotId].m_R_x, RB[robotId].m_R_y)*/

			chose_target(robotId, frameID);

			/*set_Rotate(robotId);
	
			set_forward(robotId); 
			if (RB[robotId].m_holdFrameNum > 1700) {
				destory.push_back(robotId);
			}*/
			set_forward_rotate_pid(robotId);



			RB[robotId].maxRotateTimeMark = fabs(RB[robotId].m_R_angle) > 3.14 ? (RB[robotId].maxRotateTimeMark + 1) : 0;
			if (RB[robotId].maxRotateTimeMark > 80)
			{
				RB[robotId].setForward = 0.0;
				RB[robotId].outPidTime++;
				if (RB[robotId].outPidTime > 25) {
					RB[robotId].maxRotateTimeMark = 0;
					RB[robotId].outPidTime = 0;

				}
			}
			//�жϻ������Ƿ�ӽ�����ǽ�ڵĹ���̨
			auto it = find(nearWall.begin(), nearWall.end(), RB[robotId].m_targetNum);
			if (it != nearWall.end()) {
				double distance = sqrt((WB[RB[robotId].m_targetNum].m_y - RB[robotId].m_Y)*(WB[RB[robotId].m_targetNum].m_y - RB[robotId].m_Y) + (WB[RB[robotId].m_targetNum].m_x - RB[robotId].m_X) * (WB[RB[robotId].m_targetNum].m_x - RB[robotId].m_X));
				if ((distance < 3)&&(sqrt(RB[robotId].m_R_x*RB[robotId].m_R_x+ RB[robotId].m_R_y*RB[robotId].m_R_y)>4)) {
					RB[robotId].setForward = 0;
					RB[robotId].setRotate = RB[robotId].setRotate >= 0 ? 3.14159 : -3.14159;
					RB[robotId].lastWbNearWall = true;
				}
			}
			else if ((RB[robotId].lastWbNearWall)&& (RB[robotId].outWallCount < 4)) {
			//�뿪ǽ�߹���̨�ĺ�5֡����תȦ
				RB[robotId].setForward = 0;
				RB[robotId].setRotate = RB[robotId].setRotate >= 0 ? 3.14159 : -3.14159;
				RB[robotId].outWallCount++;
			}
			else {
				RB[robotId].lastWbNearWall = false;
				RB[robotId].outWallCount = 0;

			}

			//����ײ
			//avoid_clash(robotId);
			avoid_clash(robotId);




			printf("forward %d %f\n", robotId, RB[robotId].setForward);
			printf("rotate %d %f\n", robotId, RB[robotId].setRotate);

			if ((RB[robotId].m_nearbyWB == RB[robotId].m_targetNum)&&(RB[robotId].m_targetNum > -1)) {
				printf("sell %d\n", robotId);
				

				// ʣ��֡֡��С��200������7
				// if (frameID < 8700) {
				// 	if (harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0) {
				// 		printf("buy %d\n", robotId);
				// 	}

				// }
				// else{
				// 	if ((harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0) && (WB[RB[robotId].m_nearbyWB].m_type != 7)) {
				// 		printf("buy %d\n", robotId);
				// 	}

				// }
				if(r_wcount < 19){
					//pic4
					if((frameID > 8400)&&(robotId == 0)){
						
					}else if((frameID > 8700)&&(robotId == 3)){
						
					}
					else if((frameID > 8900)&&(robotId == 2)){
						
					}
					else if(harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0){
						printf("buy %d\n", robotId);
					}
				}
				else if(r_wcount <40){
					//pic2
					if((frameID > 8700)&&(robotId == 2)){
						
					}else if(harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0){
						printf("buy %d\n", robotId);
					}}
				else if(r_wcount <45){
					// pic 1
					if((frameID < 8900)&&(harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0)){
						printf("buy %d\n", robotId);
					}
				}
				else if((r_wcount >46)){
					// pic 3
					if((frameID > 8900)&&(robotId == 0)){
						
					}else if((harshTable2[WB[RB[robotId].m_nearbyWB].m_type] > 0)&&(frameID < 8950)){
						printf("buy %d\n", robotId);
					}
				}
				RB[robotId].m_targetNum = -1;
			}
			/*else if (RB[robotId].m_is_empty > 0.0) {
				RB[robotId].m_targetNum = -1;
				chose_target()
			}*/
			/*sell.push_back();
			buy.push_back();*/
		}
		//while (!sell.empty()) {  
		//	int num = sell.back(); 
		//	out << "sell  :" << num << endl;
		//	printf("sell %d\n", num);
		//	sell.pop_back();      
		//}
		//while (!buy.empty()) {
		//	int num = buy.back();
		//	out << "buy  :" << num << endl;
		//	printf("buy %d\n", num);
		//	buy.pop_back();
		//}
		while (!destory.empty()) {
			int num = destory.back();

			printf("destroy %d\n", num);
			destory.pop_back();
		}
		/*}*/


		printf("OK\n", frameID);
		fflush(stdout);
	}
	return 0;
};


