#include <stdio.h> //标准IO头文件
#include <Windows.h> //windows头文件
#include <io.h>
#include <Mmsystem.h> //多媒体头文件
#include <Digitalv.h>
#include <vector> 
#include <string>
#pragma comment(lib, "Winmm.lib") //多媒体库
#define PAUSE 0
#define PLAYING 1
#define INVALID 2
using namespace std;

//函数声明
char *delete_enter(char *str);

//MP3类
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
        printf("输入音量大小(0-1000)：");
        scanf_s("%d", &level, 1);

        MCI_DGV_SETAUDIO_PARMS mci_dgv_setaudio = {0};
        mci_dgv_setaudio.dwValue = level;
        mci_dgv_setaudio.dwItem=MCI_DGV_SETAUDIO_VOLUME;
        mciSendCommand(device_id, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)&mci_dgv_setaudio);        
        system("pause"); 
    }
};

//播放列表类
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
        printf("输入MP3文件路径和文件名：");
        fflush(stdin); //清空缓冲区
        scanf_s("%[^\n]", buf, 255); //接收到回车为止
        if (_access_s(buf, 0) == 0)
        {
            data.push_back(string(buf));
            update_playlist();
        }
        else
            printf("文件不存在\n");
        system("pause");
    }
};

//全局变量
PLAY_LIST g_playlist; //播放列表
MP3 g_mp3;
int g_playing_index = 0; //正在播放的MP3的索引
int g_playing_status = PAUSE; //播放还是暂停，1：播放，0：暂停
int g_playing_volmume = 750; //音量

//去掉字符串结尾的回车符
char *delete_enter(char *str)
{
    for (char *p = str; *p != '\0'; p++)
        if (*p == '\n') *p = '\0';
    return str;
}

//打印所有的信息
void show_info(void)
{
    system("cls"); //┏┗┛┓━┃┣┫
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃MP3音乐播放器                                   ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃1.播放                                          ┃\n");
    printf("┃2.恢复播放                                      ┃\n");
    printf("┃3.暂停                                          ┃\n");
    printf("┃4.停止                                          ┃\n");
    printf("┃5.下一首                                        ┃\n");
    printf("┃6.上一首                                        ┃\n");
    printf("┃7.查看播放列表                                  ┃\n");
    printf("┃8.添加音乐文件                                  ┃\n");
    printf("┃9.调节音量                                      ┃\n"); 
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

    char *str[] = {"暂停", "正在播放", "停止"};
    char info[256];
    sprintf_s(info, 256, "%s %s", str[g_playing_status], 
        g_playlist.data.size() == 0 ? "无歌曲" : g_playlist.data.at(g_playing_index).c_str());
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃当前状态                                        ┃\n");
    printf("┣━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
    printf("┃%-48s┃\n", info);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

char get_choose(void)
{
    printf("\n请输入你的选择：");
    fflush(stdin); //清空缓冲区
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
        case '1': //播放
            if (g_playing_index < (int)g_playlist.data.size() && g_playing_index >= 0)
            {
                g_mp3.load(g_playlist.data.at(g_playing_index).c_str());
                g_mp3.play();
                g_playing_status = PLAYING;
            }
            else
            {
                system("cls");
                printf("播放列表无歌曲\n");
                system("pause");
            }
            break;

        case '2': //恢复播放
            if (g_playing_status == PAUSE)
            {
                g_mp3.resume();
                g_playing_status = PLAYING;
            }
            break;

        case '3': //暂停
            if (g_playing_status == PLAYING)
            {
                g_mp3.pause();
                g_playing_status = PAUSE;
            }
            break;

        case '4': //停止
            g_mp3.stop();
            g_playing_status = INVALID;
            break;

        case '5': //下一首  
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
                printf("播放列表无歌曲\n");
                system("pause");
            }
            break;

        case '6': //上一首 
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
                printf("播放列表无歌曲\n");
                system("pause");
            }
            break;

        case '7': //显示列表
            g_playlist.show_playlist();
            break;

        case '8': //添加音乐文件 
            g_playlist.add_playlist();
            break;

        case '9': //调节音量
            g_mp3.set_volume();
            break;

        default:
            break;
        }
    }
    return 0;
}