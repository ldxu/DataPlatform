/**
 * @breif: 用来测试共享内存的有效性，需要配合SharedMemoryDemo.cpp一起
 * @diff:  
 *      从系统上看：mmap 和 shmget的区别，前者是基于posix标准的，后者是基于system V标准的
 *      从内存上看：mmap是磁盘文件和内存的映射，因此会存盘，但是性能可能会差点
 *                 shmget是基于物理内存的，性能更好，但是断电后所有的信息都回消失
 */
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

/**
 * @method:  mmap  ->  posix实现共享内存方法, 不可以使用ipcs -m 查看共享内存信息，需要在ls -l /dev/shm中查看共享内存信息
 * @steps:      
 *  step1:  打开共享内存映射文件(如果没有则创建，会返回一个类似描述符的对象)
 *  step2:  【可选】设置共享内存空间大小
 *  step3:  将当前进程虚拟地址空间和共享内存地址空间进行映射
 *  step4:  解除当前进程虚拟地址空间和共享内存地址空间的映射
 *  step5:  关闭共享内存对象(仅仅像关闭文件描述那样的关闭)              
 *  step6:  【可选】删除共享内存
 */
const char* sharedMemoryName = "Test";                     //共享内存的名字
const int sharedMemorySize = 1000 * sizeof(stprocinfo);    //共享内存的大小
int mPos   = 0;    
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
    if (ftruncate64(_shmFd, sharedMemorySize) == -1)
    {
        perror("设置共享内存大小失败");
        close(_shmFd);
        return -1;
    }
    // step3：将当前进程的虚拟地址空间与共享内存形成映射，这样就可以操作共享内存了
    void* _sharedMemory = mmap(nullptr, sharedMemorySize, PROT_READ | PROT_WRITE, MAP_SHARED, _shmFd, 0);
    if (_sharedMemory == MAP_FAILED)
    {
        perror("映射共享内存失败");
        close(_shmFd);
        return 1;
    }
    // step4：操作共享内存空间
    // 尝试往共享内存写入进程相关数据
    pid_t _faterId = getpid();
    stprocinfo _firstData(_faterId, "master", 30, time(0));

    memcpy(_sharedMemory, &_firstData, sizeof(stprocinfo));

    std::cout << "尝试往共享内存读取数据:\n" << std::endl;

    stprocinfo* _getData = static_cast<stprocinfo*>(_sharedMemory);

    std::cout << "从共享内存读取到的数据是: \n" \
              << "pid: " << _getData[mPos].pid  \
              << "\nname: " << _getData[mPos].pname \
              << "\nduration time: " << _getData[mPos].timeout \
              << "\nping time: " << _getData[mPos].atime << std::endl;
    sleep(100);
    // step5：解除当前进程虚拟地址空间和共享内存空间的映射
    munmap(_sharedMemory, sharedMemorySize);

    close(_shmFd);

    // step6：删除共享内存对象
    shm_unlink(sharedMemoryName);
    return 0;
}

