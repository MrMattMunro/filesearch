package com.searchlocal.thread;

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
public class ThreadManager {

	/** 线程管理类 */
	public static ThreadManager manage = null;

	/** 线程池 */
	private static CThreadPoolExecutor pool;

	/** 
	 * 构造器
	 */
	public ThreadManager() {

		ArrayBlockingQueue<Runnable> abq = new ArrayBlockingQueue<Runnable>(10);
		// corePoolSize,maximumPoolSize,keepAliveTime,
		// TimeUnit,BlockingQueue<Runnable>
		pool = new CThreadPoolExecutor(21, 21, 120000, TimeUnit.SECONDS, abq);
		// pool.setRejectedExecutionHandler(new
		// ThreadPoolExecutor.DiscardOldestPolicy());
	}

	/**
	 * 取得线程池
	 * 
	 * @return Returns the pool.
	 */
	public ThreadPoolExecutor getPool() {
		return pool;
	}

	public void executeThread(Runnable task) {
		pool.execute(task);
	}

	/**
	 * 取得线程管理类
	 * 
	 * @return 线程管理类
	 */
	public static ThreadManager getThreadManager() {
		if (null == manage) {
			manage = new ThreadManager();
		}
		return manage;
	}
}
