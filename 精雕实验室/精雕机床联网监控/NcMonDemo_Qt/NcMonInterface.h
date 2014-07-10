#ifndef _NC_MON_INTERFACE_H_
#define _NC_MON_INTERFACE_H_

#ifdef NC_MON_EXPORT
#define DLL_MONIO __declspec( dllexport )
#else
#define DLL_MONIO __declspec( dllimport )
#endif

#ifndef BOOL
#define BOOL int
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#define JDMACHMON void

//进度条回调函数
#ifndef SetProgPosFunPtr
typedef	void (*SetProgPosFunPtr)(void * pProgCtrl, int ProgPos);
#endif

//API for c users
#ifdef __cplusplus 
extern "C" {
#endif

	/*-------------------------------------------------------------------------
	[功能]:创建机床监控对象(new)
	---------------------------------------------------------------------------*/
	DLL_MONIO JDMACHMON *  __cdecl CreateJDMachMon();

	/*-------------------------------------------------------------------------
	[功能]:销毁机床监控对象(delete)
	---------------------------------------------------------------------------*/
	DLL_MONIO void __cdecl DeleteJDMachMon(JDMACHMON * & JDMachMon);

	/*-------------------------------------------------------------------------
	[功能]:连接到机床
	[输入]:servername:机床IP地址
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl ConnectJDMach(JDMACHMON *JDMachMon, const char* servername);

	/*-------------------------------------------------------------------------
	[功能]:与机床断开连接
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl DisConnectJDMach(JDMACHMON *JDMachMon);
	
	/*-------------------------------------------------------------------------
	[功能]:获取机床坐标
	[输出]: MachCoord:机床坐标;  AbsCoord:绝对坐标; RelCoord:相对坐标
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachPos(JDMACHMON *JDMachMon, double MachCoord[3],double AbsCoord[3],double RelCoord[3]);

	/*-------------------------------------------------------------------------
	[功能]:获取机床报警信息
	[输出]:以下的报警信息之一
	enum NcAlmInfo 
	{ 
	NCALM_NO,         //无报警
	NCALM_EMG,        //急停
	NCALM_ERR,        //报警
	NCALM_UPS,        //外部电源已掉电
	NCALM_PROMPT      //提示
	};
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachAlmInfo(JDMACHMON *JDMachMon, int * AlmInfo);


	/*-------------------------------------------------------------------------
	[功能]:获取程序状态
	[输出]:以下的程序状态之一
	//程序状态
	enum NcProgState
	{
		NCPROG_STOP,      //停止态
		NCPROG_RUN,       //执行态
		NCPROG_PAUSE,     //暂停态
		NCPROG_RESET,     //复位态
	};
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetProgState(JDMACHMON *JDMachMon, int * ProgState);

	/*-------------------------------------------------------------------------
	[功能]:向机床发送加工文件
	       注：机床正在进行加工时不能向其发送加工文件
	[输入]:FileName:本地文件名称(full path name)
		   AddToTsk: 是否自动加载到任务
		   pProgCtrl:进度条控件指针; ProgFunPtr:进度条回调函数.  如果不需要显示进度条,这两个参数传NULL
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl SendFile(JDMACHMON *JDMachMon, BOOL AddToTsk, const char * FileName, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[功能]:向机床发送NC加工文件(上传)
	[输入]:FileName:本地文件名称(full path name)
		   AddToTsk: 是否自动添加到任务 (注: 机台需要处于EDIT和RESET状态)
		   SetMainProgram: 是否添加到主程序(AddToTsk为TRUE时有效)
	       pProgCtrl:进度条控件指针; ProgFunPtr:进度条回调函数.  如果不需要显示进度条,这两个参数传NULL
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl  SendNcFile(JDMACHMON *JDMachMon, const char * FileName, BOOL AddToTsk, BOOL SetMainProgram, 
								void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);

	/*-------------------------------------------------------------------------
	[功能]:是否正在向机床发送文件
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsSendingFile(const JDMACHMON *JDMachMon);

	/*-------------------------------------------------------------------------
	[功能]:是否正在接收文件(下载文件)
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsRcvingFile(const JDMACHMON *JDMachMon);

	/*-------------------------------------------------------------------------
	[功能]:是否和机床连接
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl IsConncect(const JDMACHMON *JDMachMon) ;

	/*-------------------------------------------------------------------------
	[功能]:下载机床文件
	[输入]:SrcFileName:机床端文件名称(full path name)
		   DestFileName: 本地文件名称
	       pProgCtrl:进度条控件指针; ProgFunPtr:进度条回调函数.  如果不需要显示进度条,这两个参数传NULL
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL ReceiveFile(JDMACHMON *JDMachMon, const char * SrcFileName, const char * DestFileName, void * pProgCtrl, SetProgPosFunPtr ProgPosPtr = NULL);


	/*-------------------------------------------------------------------------
	[功能]:获取基本模态信息
	[输出]: CurrWCoord:当前工件坐标系(从54开始递增1:  G54 , G55, G56, G57, G58, G59)
			Feedrate     : 当前进给速度
	        SpindleSpeed : 当前主轴转速
			ToolNo       : 当前刀具号
			MachTime     : 加工时间(程序运行时间) 分
			CurrO        : 当前程序号
			CurrMainO    : 当前主程序号
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetBasicModalInfo(JDMACHMON *JDMachMon, int &CurrWCoord, float & Feedrate, int & SpindleSpeed, int & ToolNo, float & MachTime,
				int & CurrO, int & CurrMainO);

	/*-------------------------------------------------------------------------
	[功能]:获取文件列表
	[输入]: DestDir     : 机台文件夹目录
	StrBufSize  : 文件列表字符串缓冲区长度
	[输出]  FileList    : 文件列表字符串
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachFileList(JDMACHMON *JDMachMon, const char *DestDir, int StrBufSize, char * FileList);

	/*-------------------------------------------------------------------------
	[功能]:删除文件
	[输入]: DestDir     : 机台文件夹目录
	FileName    : 机台文件夹目录下的某个文件名(或子文件夹)
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl DelMachFile(JDMACHMON *JDMachMon, const char *DestDir, const char * FileName);

	/*-------------------------------------------------------------------------
	[功能]:重命名文件
	[输入]: SrcFileName     : 
			机台文件名 full path
			DestFileName    : 新的文件名
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl RenameMachFile(JDMACHMON *JDMachMon, const char *SrcFileName, const char * DestFileName);

	/*-------------------------------------------------------------------------
	[功能]:获取工件加工流水履历表(注：最多纪录1024个工件的加工时间流水)
	[输入]: ArrSize     : 数组元素个数
	[输出]: WorkpieceCount     : 工件个数
	        ProgNo             : 各个程序号
			MachTime           : 各工件加工时间
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetWorkpieceMachTimeRecord(JDMACHMON *JDMachMon, int ArrSize,int & WorkpieceCount, int ProgNo[1024], float MachTime[1024]);


	/*-------------------------------------------------------------------------
	[功能]:设置机床接收文件夹(目录), full path
	[输入]: MachRcvFolder     : 机床接收文件夹(目录) full path
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl SetMachRcvFolder(JDMACHMON *JDMachMon, const char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[功能]:得到机床接收文件夹(目录), full path
	[输入]: MachRcvFolder     : 机床接收文件夹(目录) full path
	[返回]:TRUE:成功 FALSE:失败
	---------------------------------------------------------------------------*/
	DLL_MONIO BOOL __cdecl GetMachRcvFolder(JDMACHMON *JDMachMon, char *MachRcvFolder);

	/*-------------------------------------------------------------------------
	[功能]:获取上个错误
	---------------------------------------------------------------------------*/
	DLL_MONIO UINT __cdecl GetLastErr(const JDMACHMON *JDMachMon);

#ifdef __cplusplus 
}
#endif


#endif