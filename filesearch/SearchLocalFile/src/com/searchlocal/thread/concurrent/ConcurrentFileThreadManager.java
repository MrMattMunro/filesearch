package com.searchlocal.thread.concurrent;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

import com.searchlocal.thread.base.CThreadPoolExecutor;

/**
 * 同步文件线程管理类
 * 
 * <p>Title: 同步索引文件任务</p>
 * <p>Description: </p>
 * <p>site: www.slfile.net</p>
 * @author changsong:qianjinfu@gmail.com
 * @version 1.0
 */
public class ConcurrentFileThreadManager {

	/** 线程管理类 */
	public static ConcurrentFileThreadManager manage = null;

	/** 线程池 */
	private static CThreadPoolExecutor pool;

	/** 
	 * 构造器
	 */
	public ConcurrentFileThreadManager() {
		ArrayBlockingQueue<Runnable> abq = new ArrayBlockingQueue<Runnable>(3);
		pool = new CThreadPoolExecutor(10, 10, 1200, TimeUnit.SECONDS, abq);
	}

	/**
	 * 取得线程池
	 * 
	 * @return Returns the pool.
	 */
	public ThreadPoolExecutor getPool() {
		return pool;
	}

	/**
	 * 执行线程
	 * 
	 * @param task 线程
	 */
	public void executeThread(Runnable task) {
		pool.execute(task);
	}


	/**
	 * 取得线程管理类
	 * 
	 * @return 线程管理类
	 */
	public static ConcurrentFileThreadManager getThreadManager() {
		if (null == manage) {
			manage = new ConcurrentFileThreadManager();
		}
		return manage;
	}
}
