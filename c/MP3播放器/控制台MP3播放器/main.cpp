#include <stdio.h> //��׼IOͷ�ļ�
#include <Windows.h> //windowsͷ�ļ�
#include <io.h>
#include <Mmsystem.h> //��ý��ͷ�ļ�
#include <Digitalv.h>
#include <vector> 
#include <string>
#pragma comment(lib, "Winmm.lib") //��ý���
#define PAUSE 0
#define PLAYING 1
#define INVALID 2
using namespace std;

//��������
char *delete_enter(char *str);

//MP3��
class MP3
{
private:
    MCI_OPEN_PARMS mci_open;

public:
    MP3(){}
    ~MP3(){}
    DWORD device_id;

    void load(const char *file_path)
    {
        mciSendCommand(device_id, MCI_CLOSE, 0, 0);
        mci_open.lpstrElementName = file_path;
        mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)&mci_open);
        device_id = mci_open.wDeviceID;
    }

    void play()
    {
        MCI_PLAY_PARMS mci_play = {0};
        mciSendCommand(device_id, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)&mci_play);
    }

    void pause()
    {
        mciSendCommand(device_id, MCI_PAUSE, 0, 0);
    }

    void resume()
    {
        mciSendCommand(device_id, MCI_RESUME, 0, 0);
    }

    void stop()
    {
        mciSendCommand(device_id, MCI_STOP, 0, 0);
        mciSendCommand(device_id, MCI_CLOSE, 0, 0);
    }

    void set_volume()
    {
        int level = 0;
        system("cls");
        printf("����������С(0-1000)��");
        scanf_s("%d", &level, 1);

        MCI_DGV_SETAUDIO_PARMS mci_dgv_setaudio = {0};
        mci_dgv_setaudio.dwValue = level;
        mci_dgv_setaudio.dwItem=MCI_DGV_SETAUDIO_VOLUME;
        mciSendCommand(device_id, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)&mci_dgv_setaudio);        
        system("pause"); 
    }
};

//�����б���
class PLAY_LIST
{
public:
    vector<string> data;

public:
    PLAY_LIST(){}
    ~PLAY_LIST(){}
    void get_playlist()
    {
        char buf[256] = {0};
        FILE *fp = NULL;
        fopen_s(&fp, "playlist.txt", "r");
        if (fp == NULL)
            fopen_s(&fp, "playlist.txt", "w");

        while (fgets(buf, 256, fp) != NULL)
        {
            delete_enter(buf);
            if (_access_s(buf, 0) == 0)
                data.push_back(string(buf));
        }
        fclose(fp);
    }

    void update_playlist()
    {
        FILE *fp = NULL;
        fopen_s(&fp, "playlist.txt", "w");
        if (fp == NULL)
            return;
        int mp3_num = (int)data.size();
        for (int i = 0; i < mp3_num; i++)
            fprintf(fp, "%s\n", data.at(i).c_str());
        fclose(fp);
    }

    void show_playlist()
    {
        system("cls");
        int mp3_num = (int)data.size();
        for (int i = 0; i < mp3_num; i++)
            printf("%d. %s\n", i + 1, data.at(i).c_str());
        system("pause");
    }

    void add_playlist(void)
    {
        char buf[256] = {0};
        system("cls");
        printf("����MP3�ļ�·�����ļ�����");
        fflush(stdin); //��ջ�����
        scanf_s("%[^\n]", buf, 255); //���յ��س�Ϊֹ
        if (_access_s(buf, 0) == 0)
        {
            data.push_back(string(buf));
            update_playlist();
        }
        else
            printf("�ļ�������\n");
        system("pause");
    }
};

//ȫ�ֱ���
PLAY_LIST g_playlist; //�����б�
MP3 g_mp3;
int g_playing_index = 0; //���ڲ��ŵ�MP3������
int g_playing_status = PAUSE; //���Ż�����ͣ��1�����ţ�0����ͣ
int g_playing_volmume = 750; //����

//ȥ���ַ�����β�Ļس���
char *delete_enter(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (*p == '\n') *p = '\0';
    return str;
}

//��ӡ���е���Ϣ
void show_info(void)
{
    system("cls"); //�������������ǩ�
    printf("����������������������������������������������������\n");
    printf("��MP3���ֲ�����                                   ��\n");
    printf("�ǩ�������������������������������������������������\n");
    printf("��1.����                                          ��\n");
    printf("��2.�ָ�����                                      ��\n");
    printf("��3.��ͣ                                          ��\n");
    printf("��4.ֹͣ                                          ��\n");
    printf("��5.��һ��                                        ��\n");
    printf("��6.��һ��                                        ��\n");
    printf("��7.�鿴�����б�                                  ��\n");
    printf("��8.��������ļ�                                  ��\n");
    printf("��9.��������                                      ��\n"); 
    printf("����������������������������������������������������\n");

    char *str[] = {"��ͣ", "���ڲ���", "ֹͣ"};
    char info[256];
    sprintf_s(info, 256, "%s %s", str[g_playing_status], 
        g_playlist.data.size() == 0 ? "�޸���" : g_playlist.data.at(g_playing_index).c_str());
    printf("����������������������������������������������������\n");
    printf("����ǰ״̬                                        ��\n");
    printf("�ǩ�������������������������������������������������\n");
    printf("��%-48s��\n", info);
    printf("����������������������������������������������������\n");
}

char get_choose(void)
{
    printf("\n���������ѡ��");
    fflush(stdin); //��ջ�����
    return getchar();
}

int main()
{
    g_playlist.get_playlist();
    while(1)
    {
        show_info();
        switch(get_choose())
        {
        case '1': //����
            if (g_playing_index < (int)g_playlist.data.size() && g_playing_index >= 0)
            {
                g_mp3.load(g_playlist.data.at(g_playing_index).c_str());
                g_mp3.play();
                g_playing_status = PLAYING;
            }
            else
            {
                system("cls");
                printf("�����б��޸���\n");
                system("pause");
            }
            break;

        case '2': //�ָ�����
            if (g_playing_status == PAUSE)
            {
                g_mp3.resume();
                g_playing_status = PLAYING;
            }
            break;

        case '3': //��ͣ
            if (g_playing_status == PLAYING)
            {
                g_mp3.pause();
                g_playing_status = PAUSE;
            }
            break;

        case '4': //ֹͣ
            g_mp3.stop();
            g_playing_status = INVALID;
            break;

        case '5': //��һ��  
            g_mp3.stop();
            g_playing_index++;
            if (g_playing_index >= (int)g_playlist.data.size())
                g_playing_index = 0;
            if (g_playing_index < (int)g_playlist.data.size() && g_playing_index >= 0)
            {
                g_mp3.load(g_playlist.data.at(g_playing_index).c_str());
                g_mp3.play();
                g_playing_status = PLAYING;
            }
            else
            {
                system("cls");
                printf("�����б��޸���\n");
                system("pause");
            }
            break;

        case '6': //��һ�� 
            g_mp3.stop();
            g_playing_index--;
            if (g_playing_index < 0)
                g_playing_index =  (int)g_playlist.data.size() - 1;
            if (g_playing_index < (int)g_playlist.data.size() && g_playing_index >= 0)
            {
                g_mp3.load(g_playlist.data.at(g_playing_index).c_str());
                g_mp3.play();
                g_playing_status = PLAYING;
            }
            else
            {
                system("cls");
                printf("�����б��޸���\n");
                system("pause");
            }
            break;

        case '7': //��ʾ�б�
            g_playlist.show_playlist();
            break;

        case '8': //��������ļ� 
            g_playlist.add_playlist();
            break;

        case '9': //��������
            g_mp3.set_volume();
            break;

        default:
            break;
        }
    }
    return 0;
}