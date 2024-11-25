#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <cstring>
#include <sys/mman.h>
// 进程心跳信息的结构体。
struct stprocinfo
{
    int      pid=0;                 // 进程id。
    char     pname[51]={0};   // 进程名称，可以为空。
    int      timeout=0;         // 超时时间，单位：秒。
    time_t   atime=0;           // 最后一次心跳的时间，用整数表示。
    stprocinfo() = default;   // 有了自定义的构造函数，编译器将不提供默认构造函数，所以启用默认构造函数。
    stprocinfo(const int in_pid,const std::string & in_pname,const int in_timeout, const time_t in_atime) 
                     : pid(in_pid),timeout(in_timeout),atime(in_atime) 
	{ 
		strncpy(pname,in_pname.c_str(),50); 
	}
};

const char* sharedMemoryName = "Test";                     //共享内存的名字
const int sharedMemorySize = 1000 * sizeof(stprocinfo);    //共享内存的大小
int mPos   = 0;                      // 用于存放当前进程在数组中的下标。


int main()
{
    // step1：打开共享内存对象，如果不存在那么创建，设置权限为读写
    int _shmFd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, 0666);   //打开共享内存 如果不存在则创建
    if (_shmFd == -1)
    {
        perror("创建共享内存失败\n");
        return 1;
    }
    // step2: 设置共享内存空间大小（如果是子进程则完全没必要有这一步，父进程创建好就行）
    // if (ftruncate64(_shmFd, sharedMemorySize) == -1)
    // {
    //     perror("设置共享内存大小失败");
    //     close(_shmFd);
    //     return -1;
    // }
    // step3：将当前进程的虚拟地址空间与共享内存形成映射，这样就可以操作共享内存了
    void* _sharedMemory = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, _shmFd, 0);
    if (_sharedMemory == MAP_FAILED)
    {
        perror("映射共享内存失败");
        close(_shmFd);
        return 1;
    }
    std::cout << "sizeof struct is : " << sizeof(stprocinfo) << std::endl;
    // 尝试往共享内存写入进程相关数据
    pid_t _faterId = getpid();
    // step4：操作共享内存空间
    stprocinfo* _getData = static_cast<stprocinfo*>(_sharedMemory);

    std::cout << "当前的进程id是:" << _faterId \
              << "\n从共享内存读取到的数据是: " \
              << "\npid: " << _getData[mPos].pid  \
              << "\nname: " << _getData[mPos].pname \
              << "\nduration time: " << _getData[mPos].timeout \
              << "\nping time: " << _getData[mPos].atime << std::endl;
    // 解除映射关系，并关闭共享内存对象
    sleep(10);
    // step5：解除当前进程虚拟地址空间和共享内存空间的映射
    munmap(_sharedMemory, sharedMemorySize);    //解除当前进程虚拟地址空间和共享内存的映射，不删除对象
    close(_shmFd);      //关闭当前进程对共享内存的对象的文件描述符，不删除对象

    // // 删除共享内存对象
    // shm_unlink(sharedMemoryName);
    return 0;
}