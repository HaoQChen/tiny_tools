/************************make directory****************************/
#include <sys/stat.h>//for mkdir
mkdir("./calibrate_images/", S_IRWXO  | S_IRWXG  | S_IRWXU );

//get executable program's real path and set it to current path
#include <unistd.h>//for readlink chdir
char temp[100];
int cnt = readlink("/proc/self/exe", temp, 100);
for(int i = cnt; i > 0; --i){
    if(temp[i-1] == '/'){
        temp[i] = '\0';
        break;
    }
}
chdir(temp);

/*******************get current time, not thread savely************************/
#include <time.h>//for localtime_r tm time_t timespec
timespec time;
tm nowTime;
char temp[20];

clock_gettime(CLOCK_REALTIME, &time);//get second from 1970 to now
localtime_r(&time.tv_sec, &nowtime);//translate to local time

sprintf(temp,"%d%d%d%d%d%d.bmp", nowtime.tm_year+1900, nowtime.tm_mon+1, nowtime.tm_mday, nowtime.tm_hour, nowtime.tm_min, nowtime.tm_sec);


/************************get files' name in the folder**********************************/
#include <dirent.h>//for dirent
#include <unistd.h>//for opendir readdir closedir
#include <string.h>
#include <vector>
#include <string>
using namespace std;


char* base_path = "/home/your_name/test_folder";
vector<string> files_list;

DIR *dir = opendir(base_path);
if(dir == NULL){
    cout << "Open dir error!" << endl;
    return -1;
}

while((ptr = readdir(dir)) != NULL){
    if(ptr->d_type == DT_REG){//file
        if(NULL != strstr(ptr->d_name, ".bmp")){
            files_list.push_back(string(base_path) + string('/') + string(ptr->d_name));
        }
    }
}

closedir(dir);


/***********************sleep***********************/
#include <unistd.h> //sleep
unsigned int sleep(unsigned int seconds);