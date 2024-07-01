#include<Windows.h>
#include<cstdlib>
#include <iostream>
#include <cstring>
using namespace std;
int capacity, num,num0;  // ������������Ʒ����
int readx=-1;//read��ֵ
int j = 0, i = 1;
int ans0= 0;
int writetape[40] = { -1 }; int writetapeindex = 0; int cmpx = 39;
int write_anstape[40]; int write_anstapeindex = 0;
int step = 0;
int temp = 0;//clamֵ
bool ifcla = false;
int weight[10], value[10];  // �洢ÿ����Ʒ�������ͼ�ֵ
int M[10][100];  // �洢��̬�滮�����Ž����
string state[100] = { "readCapacity"," readNum","readWeight","readValue","writeM","readM","calM","cmp","ansM",
"cmpAnsM","writeAns"," readAns","success "
};
int ans[100];  // ���������洢����ѡ�����Ʒ���
// �Զ���״̬����
enum State {
    readCapacity,  // ��ȡ��������
    readNum,       // ��ȡ��Ʒ����
    readWeight,    // ��ȡ��Ʒ����
    readValue,     // ��ȡ��Ʒ��ֵ
    writeM,        // д�����Ž����
    readM,         // ��ȡ���Ž����
    calM,          // �������Ž����
    cmp,           // �Ƚ����Ž����
    ansM,          // ��ȡ���ŽⲢд�������
    cmpAnsM,       // �ȽϽ����������Ž����
    writeAns,      // д�������
    readAns,
    success        // �ɹ����ģ��
};
// �Զ���״̬ת�ƺ���
State transition(State currentState, int tape[], int& head, int& tapePos, int& memoryPos, int& memorySize) {
    switch (currentState) {
    case readCapacity:  // ��ȡ��������
        capacity = tape[head];
        j = capacity;
        head++;
        return readNum;
    case readNum:       // ��ȡ��Ʒ����
        num = tape[head];
        num0 = num;
        head++;
        tapePos = head+num * 2;
        head = tapePos - 2;// ���������Ĵ洢λ��
        tapePos -= 2;
        return readWeight;
    case readWeight:    // ��ȡ��Ʒ����
        weight[num - 1] = tape[head];
        head++;
        return readValue;
    case readValue:     // ��ȡ��Ʒ��ֵ
        value[num - 1] = tape[head];
        head--;  // ���˵���һ����Ʒ������λ��
        return writeM;
    case writeM:        // д�����Ž����
        if (memoryPos == capacity + 1) {  // ����Ѿ����������Ž����
            tapePos -= 2;
            head = tapePos;  // �ص���һ����Ʒ������λ��
            memoryPos = 0;
            num--;
            
            if (num == 0) {  // ����Ѿ�������������Ʒ����д�������׶�
                head += 2;
                return readM;
            }
            else return readWeight;
        }
       
        if (num == 0) {  // ����Ѿ�������������Ʒ
            return success;
        }
        if (num < num0&&readx==-1)// ����ǰ��Ʒ�ļ�ֵд�����Ž����

        {
            
            
            return readM;
        }
        if (num < num0 && readx != -1)//read֮��
        {
            if (memoryPos < weight[num - 1])
            {
                M[num][memoryPos] = readx;
                readx = -1;
            }
            else
            {
                if (ifcla)
                {
                    
                    M[num][memoryPos] = temp;
                    ifcla = false;
                    readx = -1;
                    
                }
                else
                {
                    
                    return calM;
                }
            }
            
        }
        else  if (memoryPos < weight[num-1])M[num][memoryPos] = 0;
        else  M[num][memoryPos] = value[num-1];
        
        memoryPos++; writetapeindex++;
       
        return writeM;
    case readM:         // ��ȡ���Ž����
        if (memoryPos == capacity + 1) {  // ����Ѿ����������Ž����
            head = tapePos;  // �ص���һ����Ʒ������λ��
            memoryPos = 0;
            num--;
            return readWeight;
        }
        if (num == 0) {  // ����Ѿ�������������Ʒ
            readx = tape[head];
            head += 2;
            return ansM;
        }
        readx = M[num + 1][memoryPos];
        return writeM;
        //if (num < num0)//read;
        //{

        //}
        //else     M[num][memoryPos] = value[num - 1];
        //head = tapePos + (num - 1) * (capacity + 1) + memoryPos - 1;  // ��ת����һ����Ʒ�����Ž����λ��
        return writeM;
    case calM:          // �������Ž����
        

            temp = M[num+1][memoryPos-weight[num-1]] + value[num - 1];  // ����װ�뵱ǰ��Ʒ�ļ�ֵ
            //д��workֽ��
        ifcla=true;
        head += capacity + 1;  // ��ת����һ��λ��
        return cmp;
    case cmp:           // �Ƚ����Ž����
        
        if (temp > M[num +1][memoryPos]) {  // ���װ�뵱ǰ��Ʒ����
            return writeM;  // ֱ��д�����Ž����
        }
        else {  // ����װ�뵱ǰ��Ʒ
            temp = M[num + 1][memoryPos];
            return writeM;  // ֱ�Ӷ�ȡ��һ��λ�õ����Ž����
        }
    case ansM:          // ��ȡ���ŽⲢд�������
        //ans[memoryPos] = num;  // ����ǰ��Ʒ���д�������
        //memoryPos++;
        return cmpAnsM;
    case cmpAnsM:       // �ȽϽ����������Ž����
        if (M[i][j] == M[i+1][j]) {  // �����װ�뵱ǰ��Ʒ����
            
            memoryPos++; i++;
            write_anstapeindex++;
            return readM;  // д�������
        }
        else {  // ����װ�뵱ǰ��Ʒ
            ans0 = 1;
            return writeAns;  // ����Ѱ����һ��λ�õĽ�����
        }
    case writeAns:      // д�������
        ans[memoryPos] = ans0;  // ����һ����Ʒ���д�������
        ans0 = 0;
        memoryPos++;
        j -= readx;
        i++;
        write_anstapeindex++;
        if (j == 0)
            return success;
        else return readM;
    case readAns:       // ��ȡ������
        return success;
    default:
        return success;
    }
}
int main() {
    int tape[] = { 5, 4, 2, 12, 1, 10, 3, 20, 2, 15 };  // ʾ������ֽ��
    int head = 0;  // ��дͷλ��
    int tapePos = 0;  // ֽ��λ��
    int memoryPos = 0;  // �ڴ�λ��
    int memorySize = 10;  // �ڴ��С
    State currentState = readCapacity;  // ��ʼ״̬
    while (currentState != success) {
        cout << "|----------------------------------------|" << endl;
        cout << "|      ��ǰ״̬Ϊ��" << state[currentState] << "          |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << endl << endl << endl << endl;

        cout << "|----------------------------------------|" << endl;
        if (currentState == readCapacity|| currentState == readNum|| currentState == readValue|| currentState == readWeight)
        {
            cout << "��ͷλ��Ϊ����ֽ���ģ�" << tape[head] << "λ�ã�" << head << endl;
        }

        if (currentState == writeM)
        {
            cout << "дͷλ��Ϊ����ֽ���ģ�"  << "λ�ã�" << writetapeindex << endl;
        }

        if (currentState == readM)
        {
            cout << "��ͷλ��Ϊ����ֽ���ģ�" << "λ�ã�" << (writetapeindex)-6 << endl;
        }

        if (currentState == calM)
        {
            cout << "��ͷλ��Ϊ����ֽ���ģ�" << "λ�ã�" <<(3-num)*6+ memoryPos - weight[num - 1] << endl;
        }
        

        if (currentState == cmp)
        {
            cout << "дͷλ��Ϊ����ֽ���ģ�" << "λ�ã�" << cmpx<< endl;
        }

        if (currentState == ansM)
        {
            cout << "��ͷλ��Ϊ����ֽ���ģ�" << "λ�ã�" << "("<<i<<","<<j <<")" << endl;
        }

        if (currentState == cmpAnsM)
        {
            cout << "��ͷλ��Ϊ����ֽ���ģ�" << "λ�ã�" << "(" << i+1 << "," << j << ")" << endl;
        }

        if (currentState == writeAns)
        {
            cout << "��ͷλ��Ϊ���ֽ���ģ�" << "λ�ã�" << write_anstapeindex << endl;
        }
        cout << "|----------------------------------------|" << endl;
        cout << endl << endl << endl;
        cout << "��ά��"<<endl;
        for (int a = 1; a <= 4; a++)
        {
            for (int b = 0; b < 6; b++)

            {
                cout << M[a][b] << " ";
            }
            cout << endl;
        }
        cout << endl << "����ֽ����";
        for (int a = 4; a >= num; a--)
        {
            for (int b = 0; b < 6; b++)

            {
                
                cout << M[a][b] << " ";
            }
           
        }
        if (temp != 0)
        {
            cout << temp;
           
        }
        cout << endl << "���ֽ����";
        for (int a=0;a<num0;a++)
        {
            cout << ans[a] << " ";
        }

        cout << endl << "step��" << step++<<"        "<<"grids"<<writetapeindex+40-cmpx<<endl;
        currentState = transition(currentState, tape, head, tapePos, memoryPos, memorySize);
        
        system("pause");
        system("cls");

        if (currentState == success)
        {
            cout << "|----------------------------------------|" << endl;
            cout << "|��ǰ״̬Ϊ��" << state[currentState] << "--------------------------|" << endl;
            cout << "|-----------------------------------------|" << endl;
            cout << endl << endl << endl << endl;
        }
    }
    cout << "������Ϊ��";
    for (int i = 0; i < num0; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}

