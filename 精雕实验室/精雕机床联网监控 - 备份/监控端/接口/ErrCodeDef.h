#ifndef _NC_MON_ERRCODE_DEF_H_
#define _NC_MON_ERRCODE_DEF_H_


#define ERR_NETWORK_CONNCT_FAIL			    1		//通讯连接失败
#define ERR_FILESEND_FAIL				    2		//文件发送失败
#define ERR_CNNCT_COUNT_EXCEED				3       //超过一台机床的最大连接数
#define ERR_NETWORK_CONNCT_BRK				4       //通讯连接中断
#define ERR_RPC_TIMEOUT				        5       //函数调用超时
#define ERR_FILERCV_FAIL			        6       //文件接收（下载）失败
#define ERR_VERSION_CONFLICT	            7       //客户端与服务器端版本不匹配
#define ERR_GET_POS_FAIL	                8       //获取机床坐标失败
#define ERR_GET_ALM_FAIL	                9       //获取报警信息失败
#define ERR_GET_STATE_FAIL	                10       //获取程序状态失败
#define ERR_GET_BASIC_MODALINFO_FAIL	    11       //获取基本模态信息失败
#define ERR_GET_FILELIST_FAIL	            12       //获取文件列表失败
#define ERR_GET_DELFILE_FAIL	            13       //删除文件(文件夹)失败
#define ERR_GET_WPMACHTIME_RECORD_FAIL	    14       //获取加工时间履历记录表失败
#define ERR_SET_RCVPATH_FAIL	            15       //设置机床接收文件夹(目录)失败
#define ERR_GET_RCVPATH_FAIL	            16       //获取机床接收文件夹(目录) 失败
#define ERR_RENAMEFILE_FAIL	                17       //重命名文件失败
#endif