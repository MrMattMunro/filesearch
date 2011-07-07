package com.searchlocal.thread.concurrent;


/**
 * 程序启动时启动监控是否需要同步的监控线程
 * 
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentFileCore {

	public static void listen() {
		// 开始监控是否同步
		ConcurrentTimerTask concurrentDbTask = new ConcurrentTimerTask();
		ConcurrentFileCoreThreadManager.getThreadManager().executeThread(concurrentDbTask);
	}
}
