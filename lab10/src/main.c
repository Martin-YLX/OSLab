#include "prt_typedef.h"
#include "prt_tick.h"
#include "prt_task.h"
#include "prt_sem.h"
#include "prt_shell.h"

extern U32 PRT_Printf(const char *format, ...);
extern void PRT_UartInit(void);
extern U32 OsActivate(void);
extern U32 OsTskInit(void);
extern U32 OsSemInit(void);
extern U32 OsHwiInit(void);
extern void CoreTimerInit(void);


static SemHandle sem_sync;

ShellCB g_shellCB = {
    .consoleID = 1,
    .shellTaskHandle = 0,
    .shellEntryHandle = 0,
    .cmdKeyLink = NULL,
    .cmdHistoryKeyLink = NULL,
    .cmdMaskKeyLink = NULL,
    .shellBufOffset = 0,
    .shellBufReadOffset = 0,
    .shellKeyType = 0,
    .shellBuf = {0}, // 所有元素初始化为 '\0'
    .shellWorkingDirectory = "/", // 假设初始化为根目录
};

extern U32 ShellTaskInit(ShellCB *shellCB);

S32 main(void)
{
    // 初始化GIC
    OsHwiInit();
    // 启用Timer
    CoreTimerInit();

    // 任务模块初始化
    OsTskInit();
    OsSemInit(); // 参见demos/ascend310b/config/prt_config.c 系统初始化注册表

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
    ret = ShellTaskInit(&g_shellCB);
    if (ret != OS_OK) {
        PRT_Printf("ERROR:Failed to create ShellTask\n");
        return 1;
    }

    // 启动调度
    OsActivate();

    // while(1);
    return 0;

}
 





                                                                                                                                        