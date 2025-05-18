#include "prt_typedef.h"
#include "prt_tick.h"
#include "prt_task.h"
#include "prt_task_external.h"

extern U32 PRT_Printf(const char *format, ...);
extern void PRT_UartInit(void);
extern void CoreTimerInit(void);
extern U32 OsHwiInit(void);
extern U32 OsActivate(void);
extern U32 OsTskInit(void);
extern U64 g_uniTicks;

void Test1TaskEntry(void)
{
    PRT_Printf("task 1 run ...\n");
    U32 cnt = 20;
    while (cnt > 0) {
        // PRT_TaskDelay(200);
        U32 tick = PRT_TickGetCount();
        if(tick >= 0) {
            g_uniTicks = 0;
            PRT_Printf("引发调度 ...\n");
            OsTskSchedule();
        }
        PRT_Printf("task 1 run ...\n");
        cnt--;
    }
    PRT_Printf("\ntask 1 done ...\n\n");
}

void Test2TaskEntry(void)
{
    PRT_Printf("task 2 run ...\n");
    U32 cnt = 10;
    while (cnt > 0) {
        // PRT_TaskDelay(200);
        U32 tick = PRT_TickGetCount();
        if(tick >= 0) {
            g_uniTicks = 0;
            PRT_Printf("引发调度 ...\n");
            OsTskSchedule();
        }
        PRT_Printf("task 2 run ...\n");
        cnt--;
    }
    PRT_Printf("\ntask 2 done ...\n\n");
}

S32 main(void)
{



    // 初始化GIC
    OsHwiInit();
    // 启用Timer
    CoreTimerInit();
    // 任务系统初始化
    OsTskInit();

    PRT_UartInit();

    PRT_Printf("            _       _ _____      _             _             _   _ _   _ _   _           \n");
    PRT_Printf("  _ __ ___ (_)_ __ (_) ____|   _| | ___ _ __  | |__  _   _  | | | | \\ | | | | | ___ _ __ \n");
    PRT_Printf(" | '_ ` _ \\| | '_ \\| |  _|| | | | |/ _ \\ '__| | '_ \\| | | | | |_| |  \\| | | | |/ _ \\ '__|\n");
    PRT_Printf(" | | | | | | | | | | | |__| |_| | |  __/ |    | |_) | |_| | |  _  | |\\  | |_| |  __/ |   \n");
    PRT_Printf(" |_| |_| |_|_|_| |_|_|_____\\__,_|_|\\___|_|    |_.__/ \\__, | |_| |_|_| \\_|\\___/ \\___|_|   \n");
    PRT_Printf("                                                     |___/                               \n");

    PRT_Printf("                                                                                 ██╗   ██╗██╗     ██╗  ██╗ \n");
    PRT_Printf("                                                                                 ╚██╗ ██╔╝██║     ╚██╗██╔╝\n");
    PRT_Printf("                                                                      █████╗█████╗╚████╔╝ ██║      ╚███╔╝ \n");
    PRT_Printf("                                                                      ╚════╝╚════╝ ╚██╔╝  ██║      ██╔██╗ \n");
    PRT_Printf("                                                                                    ██║   ███████╗██╔╝ ██╗\n");
    PRT_Printf("                                                                                    ╚═╝   ╚══════╝╚═╝  ╚═╝\n");
    PRT_Printf("                                                                                                          \n");
    PRT_Printf("                                                                                  智能2301    202308040128 \n");

    PRT_Printf("ctr-a h: print help of qemu emulator. ctr-a x: quit emulator.\n\n");

    U32 ret;
    struct TskInitParam param = {0};

    // task 1
    // param.stackAddr = 0;
    param.taskEntry = (TskEntryFunc)Test1TaskEntry;
    param.taskPrio = 0;
    // param.name = "Test1Task";
    param.stackSize = 0x1000; //固定4096，参见prt_task_init.c的OsMemAllocAlign

    TskHandle tskHandle1;
    ret = PRT_TaskCreate(&tskHandle1, &param);
    if (ret) {
        return ret;
    }

    ret = PRT_TaskResume(tskHandle1);
    if (ret) {
        return ret;
    }

    // task 2
    // param.stackAddr = 0;
    param.taskEntry = (TskEntryFunc)Test2TaskEntry;
    param.taskPrio = 0;
    // param.name = "Test2Task";
    param.stackSize = 0x1000; //固定4096，参见prt_task_init.c的OsMemAllocAlign

    TskHandle tskHandle2;
    ret = PRT_TaskCreate(&tskHandle2, &param);
    if (ret) {
        return ret;
    }

    ret = PRT_TaskResume(tskHandle2);
    if (ret) {
        return ret;
    }

    // 启动调度
    OsActivate();

    // while(1);
    return 0;

}